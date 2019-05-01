#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/mman.h>

#include "memcheck.h"
#include "config.h"
#include "uvlog.h"

int str2int (const char *strval, int def)
{
	int ret_code = def;
	if (isdigit (strval[0]) || (strval[0] == '-' && isdigit(strval[1])))
		return atoi (strval);

	if (!strcasecmp (strval, "On"))
		ret_code = 1;
	else if (!strcasecmp (strval, "Off"))
		ret_code = 0;
	else if (!strcasecmp (strval, "Yes"))
		ret_code = 1;
	else if (!strcasecmp (strval, "No"))
		ret_code = 0;
	else if (!strcasecmp (strval, "True"))
		ret_code = 1;
	else if (!strcasecmp (strval, "False"))
		ret_code = 0;
	else if (!strcasecmp (strval, "Enable"))
		ret_code = 1;
	else if (!strcasecmp (strval, "Disable"))
		ret_code = 0;
	else if (!strcasecmp (strval, "Enabled"))
		ret_code = 1;
	else if (!strcasecmp (strval, "Disabled"))
		ret_code = 0;

	return ret_code;
}

void CConfig::Dump (FILE *fp, bool dec)
{
	fprintf(fp, "##### ORIGINAL FILE %s #####\n", filename.c_str());
	for(secmap_t::iterator i = smap.begin(); i != smap.end(); i++)
	{
		const char *sec = i->first.c_str();
		keymap_t &kmap = i->second;
		if(kmap.size()<=0)
			continue;
		fprintf(fp, "\n[%s]\n", sec);
		for(keymap_t::iterator j = kmap.begin(); j != kmap.end(); j++)
		{
			const char *key = j->first.c_str();
			const char *val = j->second.c_str();
			char flag = val[0];
			if(flag=='\0')
			{
				if(dec==true)
					fprintf(fp, "# %s NOT SET\n", key);
			} else {
				val++;
				if(flag==' ' || dec==false)
					fprintf(fp, "%s = %s\n", key, val);
				else
					fprintf(fp, "%c %s = %s\n", flag, key, val);
			}
		}
	}
}

int CConfig::Dump (const char *fn, bool dec)
{
	FILE *fp = fopen(fn, "w");
	if(fp==NULL)
		return -1;
	Dump(fp, dec);
	fclose(fp);
	return 0;
}

static char *skip_blank(char *p)
{
	while(isblank(*p))
		p++;
	return  p;
}

int CConfig::ParseConfig (const char *fn, const char *defsec)
{
	char *buf, *start;
	int len, fd, ret_code = -1;


	if(fn == NULL)
		fn = filename.c_str();
	else if(filename.size() <= 0)
	{
		filename = fn;
	}

	
	if(filename[0]=='\0')
		return -1;


	fd = open (fn, O_RDONLY);
	if (fd < 0) {
		//LOG_ERROR("open %s error, cwd=%s, %m\n", fn, get_current_dir_name ());
		return -1;
	}
	len = lseek (fd, 0L, SEEK_END);
	lseek (fd, 0L, SEEK_SET);
	buf = (char *)MALLOC(len+1);
	read(fd, buf, len);
	buf[len] = '\0';
	ret_code = len + 1;
	close(fd);

	

	if(defsec==NULL)
		defsec = "";
	keymap_t *kmap = &smap[defsec];

	start = buf;
	int ln = 0;
	char *end = start;
	ret_code = 0;
	for (start=buf, ln=0; end && buf + len > start; start = end + 1)
	{
		end = strchr (start, '\n');
		if(end)
		{
			if (*end)
				*end = '\0';
			if(end>start && end[-1]=='\r')
				end[-1] = '\0';
		}

		std::string val("?");
		keymap_t *m = kmap;

		ln++;

		char *v = NULL;
		char *key = skip_blank(start);
		// blank or comment line
		if(key[0]=='\0' || key[0]=='#' || key[0]=='?' || key[0]==';')
			continue;
		// key must printable
		if(!isprint(key[0]))
		{
			LOG_WARNING("%s(%d): invalid line: %s", fn, ln, key);
			ret_code = -1;
			continue;
		}

		// find the equation
		start = key + strcspn(key, "= \t");
		if(*start!='\0')
		{
			char *p = start[0]=='=' ? start : skip_blank(start+1);
			if(*p == '=')
			{
				v = skip_blank(p+1);
			}
			else if(key[0]=='[')
				/*OK*/;
			else {
				//LOG_WARNING("%s(%d): invalid line: %s", fn, ln, key);
				ret_code = -1;
				continue;
			}
			*start = '\0';
		} else if(key[0] != '[')
		{
			//LOG_WARNING("%s(%d): invalid line: %s", fn, ln, key);
			ret_code = -1;
			continue;
		}

		if(key[0]=='[')
		{
			char *r = strchr(key, ']');
			if(!r)
			{
				//LOG_WARNING("%s(%d): invalid section: %s", fn, ln, key);
				ret_code = -1;
				continue;
			} else if(!((r[1]=='\0'&&v==NULL)||(r[1]=='.'&&v!=NULL)))
			{
				//LOG_WARNING("%s(%d): invalid section: %s", fn, ln, key);
				ret_code = -1;
				continue;
			} else {
				*r = '\0';
				m = &smap[key+1];
				if(r[1]=='\0')
				{
					kmap = m;
					continue;
				}
				key = r + 2;
			}
		}

		if(v==NULL)
			continue;

		switch(v[0])
		{
		case '(':
			start = strchr(v, ')');
			if(start==NULL) goto error;
			break;
		case '[':
			start = strchr(v, ']');
			if(start==NULL) goto error;
			break;
		case '{':
			start = strchr(v, '}');
			if(start==NULL) goto error;
			break;

		case '"':
			start = strrchr(v+1, '"');
			if(start==NULL) goto error;
			break;
		case '\'':
			start = strrchr(v+1, '\'');
			if(start==NULL) goto error;
			break;
		default:
			start = end ? end-1 : v+strlen(v)-1;
			if(*start=='\0') start--;
			while(start > v && isblank(*start))
				start--;
			break;
		error:
			//LOG_WARNING("%s(%d): unended quote or bracket", fn, ln);
			ret_code = -1;
			continue;
		}
		start[1] = '\0';

		if(v[0])
			val.append(v);

		(*m)[key] = val;
	}
	FREE(buf);

	return ret_code;
}

int CConfig::getAllSec(vector<string>& secList)
{
	if(smap.empty()) return 0;

	secmap_t::iterator it = smap.begin();
	secmap_t::iterator end = smap.end();
	for(; it!=end; ++it)
	{
		if(it->first.size() == 0) continue;
		secList.push_back(it->first);
	}

	return (int)secList.size();
}

int CConfig::getSecAllKey(const string& sec, vector<string>& keyList)
{
	secmap_t::iterator n = smap.find(sec);
	if(n==smap.end())
	{
		return 0;
	}

	keymap_t &kmap = n->second;
	keymap_t::iterator it = kmap.begin();
	keymap_t::iterator end = kmap.end();
	for(; it!=end; ++it)
	{
		keyList.push_back(it->first);
	}

	return (int)keyList.size();
}

bool CConfig::HasSection (const char *sec)
{
	secmap_t::iterator n = smap.find(sec);
	return n!=smap.end() && n->second.size()>0 ? true : false;
}

bool CConfig::HasKey (const char *sec, const char *key)
{
	secmap_t::iterator n = smap.find(sec);
	if(n==smap.end())
		return false;
	keymap_t &kmap = n->second;
	keymap_t::iterator m = kmap.find(key);
	return m != kmap.end() && m->second.size()>0  ? true : false;
}

const char* CConfig::GetStrVal (const char *sec, const char* key)
{
	keymap_t &kmap = smap[sec];
	std::string &v = kmap[key];
	if(v.size()==0)
		return NULL;
	v[0] = ' ';
	return v.c_str() + 1;
}

int CConfig::GetIntVal (const char *sec, const char* key, int def)
{
	const char* val = GetStrVal(sec, key);
	if (val == NULL)
		return def;

	return str2int (val, def);
}

unsigned long long CConfig::GetSizeVal(
	const char *sec,
	const char* key,
	unsigned long long def,
	char unit)
{
	const char* val = GetStrVal(sec, key);
	if (val == NULL || !isdigit(val[0]))
		return def;

	const char *p;
	double a = strtod(val, (char **)&p);
	if(*p) unit = *p;
	switch(unit)
	{
	case 'b': break;
	case 'B': break;
	case 'k': a *= 1000; break;
	case 'K': a *= 1<<10; break;
	case 'm': a *= 1000000; break;
	case 'M': a *= 1<<20; break;
	case 'g': a *= 1000000000; break;
	case 'G': a *= 1<<30; break;
	case 't': a *= 1000000000000LL; break;
	case 'T': a *= 1ULL<<40; break;
	}

	return (unsigned long long)a;
}

int CConfig::GetIdxVal(
	const char *sec, const char *key,
	const char * const * array, int nDefault)
{
	const char *val = GetStrVal(sec, key);
	if(val == NULL)
		return nDefault;

	if(isdigit(val[0]))
	{
		char *p;
		int n = strtol(val, &p, 0);
		if(*p=='\0')
		{
			for(int i=0; array[i]; i++) {
				if(n==i)
					return i;
			}
		}
	}

	for(int i=0; array[i]; i++) {
		if(!strcasecmp(val, array[i]))
			return i;
	}
	return -1;
}

