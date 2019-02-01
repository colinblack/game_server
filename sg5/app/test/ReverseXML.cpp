#include "LogicInc.h"
#include <stdio.h>
int olsoldier()
{
	string dataPath = "olsoldier.xml";
	CMarkupSTL xmlConf;
	if (!xmlConf.Load(dataPath.c_str())) {
		cout << ("data path wrong") << endl;
		return 1;
	}
	if (!xmlConf.FindElem("content")) {
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();
	if (!xmlConf.FindElem("soldiers")) {
		cout << ("soldiers node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	while (xmlConf.FindElem("soldier")) {
		string id, level, type, name, prof, icon, anim, description,
				targetGroup, horm, hp, ha, ma, hd, md, rp, sp, explode, range,
				gold, produce_time, research_time, cost, silver, silver_type,
				space, locklevel, upcost;
		id = xmlConf.GetAttrib("id");
		level = xmlConf.GetAttrib("level");
		type = xmlConf.GetAttrib("type");
		name = xmlConf.GetAttrib("name");
		prof = xmlConf.GetAttrib("prof");
		icon = xmlConf.GetAttrib("icon");
		anim = xmlConf.GetAttrib("anim");
		description = xmlConf.GetAttrib("description");
		if (xmlConf.FindChildElem("targetGroup")) {
			string temp;
			temp = xmlConf.GetChildData();
			targetGroup = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("horm")) {
			string temp;
			temp = xmlConf.GetChildData();
			horm = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("hp")) {
			string temp;
			temp = xmlConf.GetChildData();
			hp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("ha")) {
			string temp;
			temp = xmlConf.GetChildData();
			ha = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("ma")) {
			string temp;
			temp = xmlConf.GetChildData();
			ma = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("hd")) {
			string temp;
			temp = xmlConf.GetChildData();
			hd = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("md")) {
			string temp;
			temp = xmlConf.GetChildData();
			md = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("rp")) {
			string temp;
			temp = xmlConf.GetChildData();
			rp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("sp")) {
			string temp;
			temp = xmlConf.GetChildData();
			sp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("explode")) {
			string temp;
			temp = xmlConf.GetChildData();
			explode = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("range")) {
			string temp;
			temp = xmlConf.GetChildData();
			range = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("gold")) {
			string temp;
			temp = xmlConf.GetChildData();
			gold = temp.substr(1, temp.length() - 2);
			if (gold.find(",") != string::npos)
				gold.replace(gold.find(","), 1, "|");
		}
		if (xmlConf.FindChildElem("produce_time")) {
			string temp;
			temp = xmlConf.GetChildData();
			produce_time = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("research_time")) {
			string temp;
			temp = xmlConf.GetChildData();
			research_time = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("cost")) {
			string temp;
			temp = xmlConf.GetChildData();
			cost = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("silver")) {
			string temp;
			temp = xmlConf.GetChildData();
			silver = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("silver_type")) {
			string temp;
			temp = xmlConf.GetChildData();
			silver_type = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("space")) {
			string temp;
			temp = xmlConf.GetChildData();
			space = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("locklevel")) {
			string temp;
			temp = xmlConf.GetChildData();
			locklevel = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("upcost")) {
			string temp;
			temp = xmlConf.GetChildData();
			upcost = temp.substr(1, temp.length() - 2);
		}
		cout << id << "," << level << "," << type << "," << name << "," << prof
				<< "," << icon << "," << anim << "," << description << ","
				<< targetGroup << "," << horm << "," << hp << "," << ha << ","
				<< ma << "," << hd << "," << md << "," << rp << "," << sp << ","
				<< explode << "," << range << "," << gold << "," << produce_time
				<< "," << research_time << "," << cost << "," << silver << ","
				<< silver_type << "," << space << "," << locklevel << ","
				<< upcost << "\r\n";
	}
	return 0;
}
int sgmonster()
{
	string dataPath = "sgmonster.xml";
	CMarkupSTL xmlConf;
	if (!xmlConf.Load(dataPath.c_str())) {
		cout << ("data path wrong") << endl;
		return 1;
	}
	if (!xmlConf.FindElem("content")) {
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();
	if (!xmlConf.FindElem("mosters")) {
		cout << ("mosters node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	while (xmlConf.FindElem("moster")) {
		string id, level, type, name, available, ai, rate, prof, icon, anim, body,
				description, hp, mp, ha, ma, hd, md, ip, bp, bv, sp, rp, horm,
				range, refid, attr, skill_id[3], skill_level[3],skill_target[3];
		id = xmlConf.GetAttrib("id");
		level = xmlConf.GetAttrib("level");
		type = xmlConf.GetAttrib("type");
		name = xmlConf.GetAttrib("name");
		available = xmlConf.GetAttrib("available");
		ai = xmlConf.GetAttrib("ai");
		rate = xmlConf.GetAttrib("rate");
		if (rate.find(",") != string::npos)
			rate.replace(rate.find(","), 1, "|");
		if (rate.find(",") != string::npos)
			rate.replace(rate.find(","), 1, "|");
		prof = xmlConf.GetAttrib("prof");
		icon = xmlConf.GetAttrib("icon");
		anim = xmlConf.GetAttrib("anim");
		body = xmlConf.GetAttrib("body");
		description = xmlConf.GetAttrib("description");
		if (xmlConf.FindChildElem("hp")) {
			string temp;
			temp = xmlConf.GetChildData();
			hp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("mp")) {
			string temp;
			temp = xmlConf.GetChildData();
			mp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("ha")) {
			string temp;
			temp = xmlConf.GetChildData();
			ha = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("ma")) {
			string temp;
			temp = xmlConf.GetChildData();
			ma = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("hd")) {
			string temp;
			temp = xmlConf.GetChildData();
			hd = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("md")) {
			string temp;
			temp = xmlConf.GetChildData();
			md = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("ip")) {
			string temp;
			temp = xmlConf.GetChildData();
			ip = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("bp")) {
			string temp;
			temp = xmlConf.GetChildData();
			bp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("bv")) {
			string temp;
			temp = xmlConf.GetChildData();
			bv = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("sp")) {
			string temp;
			temp = xmlConf.GetChildData();
			sp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("rp")) {
			string temp;
			temp = xmlConf.GetChildData();
			rp = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("horm")) {
			string temp;
			temp = xmlConf.GetChildData();
			horm = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("range")) {
			string temp;
			temp = xmlConf.GetChildData();
			range = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("refid")) {
			string temp;
			temp = xmlConf.GetChildData();
			refid = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("attr")) {
			string temp;
			temp = xmlConf.GetChildData();
			attr = temp.substr(1, temp.length() - 2);
		}
		if (xmlConf.FindChildElem("skills")) {
			xmlConf.IntoElem();
			if(xmlConf.FindElem("skills")){
				xmlConf.IntoElem();
				int i = 0;
				while (xmlConf.FindElem("skill")) {
					if(i >= 3)
						break;
					skill_id[i] = xmlConf.GetAttrib("id");
					skill_level[i] = xmlConf.GetAttrib("level");
					skill_target[i] = xmlConf.GetAttrib("target");
					++i;
				}
				xmlConf.OutOfElem();
			}
			xmlConf.OutOfElem();
		}
		cout << id << "," << level << "," << type << "," << name << "," << available
				<< "," << ai << "," << rate << "," << prof << ","
				<< icon << "," << anim << "," << body << "," << description << ","
				<< hp << "," << mp << "," << ha << ","
				<< ma << "," << hd << "," << md << "," << ip << "," << bp << ","
				<< bv << "," << sp << "," << rp << "," << horm
				<< "," << range << "," << refid << "," << attr << ","
				<< skill_id[0] << "," << skill_level[0] << "," << skill_target[0] << ","
				<< skill_id[1] << "," << skill_level[1] << "," << skill_target[1] << ","
				<< skill_id[2] << "," << skill_level[2] << "," << skill_target[2] << "\r\n";
	}
	return 0;
}
int sgenemy()
{
	string dataPath = "sgenemy.xml";
	CMarkupSTL xmlConf;
	if (!xmlConf.Load(dataPath.c_str())) {
		cout << ("data path wrong") << endl;
		return 1;
	}
	if (!xmlConf.FindElem("content")) {
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();
	if (!xmlConf.FindElem("enemies")) {
		cout << ("enemies node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	while (xmlConf.FindElem("enemy")) {
		string level, hero, hlevel, hintv, soldier, slevel, sturn, samount,
				sintv, srota, traitor, tlevel, tturn, tamount, tintv, ptx, pty,
				heroexp, userexp;
		level 		= xmlConf.GetAttrib("level");
		hero 		= xmlConf.GetAttrib("hero");
		hlevel 		= xmlConf.GetAttrib("hlevel");
		hintv 		= xmlConf.GetAttrib("hintv");
		soldier 	= xmlConf.GetAttrib("soldier");
		slevel 		= xmlConf.GetAttrib("slevel");
		sturn 		= xmlConf.GetAttrib("sturn");
		samount 	= xmlConf.GetAttrib("samount");
		sintv 		= xmlConf.GetAttrib("sintv");
		srota 		= xmlConf.GetAttrib("srota");
		traitor 	= xmlConf.GetAttrib("traitor");
		tlevel 		= xmlConf.GetAttrib("tlevel");
		tturn 		= xmlConf.GetAttrib("tturn");
		tamount 	= xmlConf.GetAttrib("tamount");
		tintv 		= xmlConf.GetAttrib("tintv");
		ptx		 	= xmlConf.GetAttrib("ptx");
		pty 		= xmlConf.GetAttrib("pty");
		heroexp 	= xmlConf.GetAttrib("heroexp");
		userexp 	= xmlConf.GetAttrib("userexp");

		while(hero.find(",") != string::npos)
		{
			hero.replace(hero.find(","), 1, "|");
		}
		while(soldier.find(",") != string::npos)
		{
			soldier.replace(soldier.find(","), 1, "|");
		}
		while(traitor.find(",") != string::npos)
		{
			traitor.replace(traitor.find(","), 1, "|");
		}

		cout << level << "," << hero << "," << hlevel << "," << hintv << "," << soldier
				<< "," << slevel << "," << sturn << "," << samount << ","
				<< sintv << "," << srota << "," << traitor << "," << tlevel << ","
				<< tturn << "," << tamount << "," << tintv << "," << ptx << "," << pty << ","
				<< heroexp << "," << userexp << "\r\n";
	}
	return 0;
}
int sgbuildingdata()
{
	string dataPath = "sgbuildingdata.xml";
	CMarkupSTL xmlConf;
	if (!xmlConf.Load(dataPath.c_str())) {
		cout << ("data path wrong") << endl;
		return 1;
	}
	if (!xmlConf.FindElem("content")) {
		cout << ("content node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();
	if (!xmlConf.FindElem("buildings")) {
		cout << ("enemies node wrong") << endl;
		return 1;
	}
	xmlConf.IntoElem();

	while (xmlConf.FindElem("building")) {
		string id, level, food, time, data1, data2, data3, data4, hp, hd, md,
				repairtime, produce, capacity, damage, range, splash, rate,
				hold;
		id 			= xmlConf.GetAttrib("id");
		level 		= xmlConf.GetAttrib("level");
		hp 			= xmlConf.GetAttrib("hp");
		hd 			= xmlConf.GetAttrib("hd");
		md 			= xmlConf.GetAttrib("md");
		repairtime 	= xmlConf.GetAttrib("repairtime");
		produce 	= xmlConf.GetAttrib("produce");
		capacity 	= xmlConf.GetAttrib("capacity");
		damage 		= xmlConf.GetAttrib("damage");
		range 		= xmlConf.GetAttrib("range");
		splash 		= xmlConf.GetAttrib("splash");
		rate	 	= xmlConf.GetAttrib("rate");

		if (xmlConf.FindChildElem("costs")) {
			xmlConf.IntoElem();
			if (xmlConf.FindChildElem("cost")) {
						xmlConf.IntoElem();
						food	 	= xmlConf.GetAttrib("food");
						time	 	= xmlConf.GetAttrib("time");
						if (xmlConf.FindChildElem("re")) {
							xmlConf.IntoElem();
							if (xmlConf.FindChildElem("data"))
								data1	 	= xmlConf.GetChildData();
							xmlConf.OutOfElem();
						}
						xmlConf.OutOfElem();
			}
			xmlConf.OutOfElem();
		}

		food 		= food.substr(1, food.length() - 2);
		data1 		= data1.substr(1, data1.length() - 2);
		while(food.find(",") != string::npos)
		{
			food.replace(food.find(","), 1, "|");
		}
		while(data1.find(",") != string::npos)
		{
			data1.replace(data1.find(","), 1, "|");
		}

		cout << id << "," << level << "," << food << "," << time << "," << data1
				<< "," << data2 << "," << data3 << "," << data4 << ","
				<< hp << "," << hd << "," << md << "," << repairtime << ","
				<< produce << "," << capacity << "," << damage << "," << range << "," << splash << ","
				<< rate << "," << hold << "\r\n";
	}
	return 0;
}
int main(int argc, char *argv[])
{
	map<string, int(*)(void)> reflect;
	reflect["olsoldier"] = olsoldier;
	reflect["sgmonster"] = sgmonster;
	reflect["sgenemy"] = sgenemy;
	reflect["sgbuildingdata"] = sgbuildingdata;

	if(argc < 2 || !reflect.count(argv[1]))
	{
		cout<<"para error! need:";
		for(map<string, int(*)(void)>::iterator it=reflect.begin();it!=reflect.end();++it)
			cout<<" "<<it->first;
		cout<<endl;
		return 1;
	}
	return (*reflect[argv[1]])();
}
