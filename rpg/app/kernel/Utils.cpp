#include "Utils.h"
#include "basic.h"

#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

//#define MAX_PATH_LEN 255
//#define VERSION "1.0"
/**
 modified at 2010-09-14
 add delete file cmd
 modified at 2010-09-20
 support empty file transfer
 */
#define VERSION "1.0"

volatile int stop = 0;

volatile int Utils::timerFlag = 0;
int background = 1;
char confFile[100] = { 0 };

int Utils::fdinfo(int fd, char* ipStr, uint32_t& ipVal, uint16_t& port) {
	struct sockaddr_in address;
	socklen_t addrLen = sizeof(address);
	struct sockaddr* socketAddress = reinterpret_cast<sockaddr*>(&address);

	int error = getpeername(fd, socketAddress, &addrLen);
	if (error) {
		return error;
	}
	ipVal = address.sin_addr.s_addr;
	strncpy(ipStr, inet_ntoa(address.sin_addr), 20);
	port = ntohs(address.sin_port);
	return 0;
}

static void showVersion(int argc, char** argv) {
	printf("%s v%s build on %s %s\n", argv[0], VERSION, __DATE__, __TIME__);
}

static void showUsage(int argc, char** argv) {
	showVersion(argc, argv);
	printf("Usage:\n    %s [-d] [-f config/common.conf] \n", argv[0]);
}

static int checkConfig(const char* confFile) {
	return 0;
}

static void sigterm_handler(int signo) {

}

int Utils::daemonInit(int argc, char** argv) {
	srand(time(NULL));
	int c;
	while ((c = getopt(argc, argv, "dc:o:hv")) != -1) {
		switch (c) {
		case 'd':
			background = 0;
			break;
		case 'c':
			strncpy(confFile, optarg, sizeof(confFile) - 1);
			break;
		case 'h':
			showUsage(argc, argv);
			_exit(0);
		case 'v':
			showVersion(argc, argv);
			_exit(0);
		case '?':
			showUsage(argc, argv);
			_exit(-1);
		}
	}

	if (strlen(confFile) == 0) {
		fprintf(stderr, "must give the config file!\n");
		_exit(-2);
	}

	if (checkConfig(confFile) != 0) {
		_exit(-3);
	}

	return Utils::daemonStart();
}

int Utils::daemonStart() {
	struct sigaction sa;
	sigset_t sset;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigterm_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	signal(SIGPIPE, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

	sigemptyset(&sset);
	sigaddset(&sset, SIGSEGV);
	sigaddset(&sset, SIGBUS);
	sigaddset(&sset, SIGABRT);
	sigaddset(&sset, SIGILL);
	sigaddset(&sset, SIGCHLD);
	sigaddset(&sset, SIGFPE);
	sigprocmask(SIG_UNBLOCK, &sset, &sset);

	//return 0;
	return background ? daemon(1, 1) : 0;
}

std::string Utils::b2s(const char *ptr, size_t nbytes, int32_t line_len) {
	std::string hex_string;
	for (unsigned int i = 0; i < nbytes; i++) {
		if (i > 0 && i % line_len == 0) {
			hex_string += '[';
			for (unsigned int j = i - line_len; j < i; j++) {
				char chr = *((char*) ptr + j);
				if (isprint(chr))
					hex_string += chr;
				else
					hex_string += '.';
			}
			hex_string += "]\n";
		}
		char chr[3] = { 0 };
		sprintf(chr, "%02x ", (unsigned char) (*((char*) ptr + i)));
		hex_string += string(chr);
	}

	int left = nbytes % line_len;
	for (int i = line_len - left; i > 0; i--) {
		hex_string += "   ";
	}

	if (left < line_len) {
		hex_string += "[";
		for (unsigned int j = nbytes - left; j < nbytes; j++) {
			char chr = *((char*) ptr + j);
			if (isprint(chr))
				hex_string += chr;
			else
				hex_string += '.';
		}
		hex_string += ']';
	}
	hex_string += '\n';
	return hex_string;
}

unsigned int Utils::getMaxMapPageCount() {
	FILE* fp = fopen("/proc/sys/vm/max_map_count", "r");
	if (!fp) {
		printf("open file /proc/sys/vm/max_map_count failed:%m");
		return 65536;
	}
	unsigned int val = 0;
	fscanf(fp, "%u", &val);
	fclose(fp);
	return val;
}

unsigned int Utils::getCurSharePageCount() {
	char buf[512] = { 0 };
	sprintf(buf, "/proc/%u/statm", getpid());
	FILE* fp = fopen(buf, "r");
	if (!fp) {
		printf("open file %s failed:%m", buf);
		return 0;
	}
	unsigned int v1, v2, mc = 0;
	fscanf(fp, "%u %u %u", &v1, &v2, &mc);
	fclose(fp);
	return mc;
}

bool Utils::Parse2DFloat(const std::string& value, const std::string& split1, const std::string& split2, std::list<std::vector<float> >& data) {
	//{{36,43.8,-31.17,65,0,1}}
	//{{?,?,?,?,?,?},{?,?,?,?,?,?}}
	const char *ptr = value.c_str();
	if (value.size() < 2) {
		return false;
	}
	int sub = 2;
	if (*(ptr) != '{' || *(ptr + 1) != '{') {
		return false;
	}
	if (*(ptr + value.size() - 1) != '}') {
		return false;
	}
	if (*(ptr + value.size() - 2) != '}' && *(ptr + value.size() - 2) != ',') {
		return false;
	}
	if (*(ptr + value.size() - 2) == ',') {
		if (value.size() < 3) {
			return false;
		}
		if (*(ptr + value.size() - 3) == '}') {
			return false;
		}
		sub = 3;
	}
	string content = value.substr(2, value.size() - sub);
	vector<string> nodes;
	CBasic::StringSplitTrim(content, split1, nodes);
	vector<string>::iterator itr = nodes.begin();
	for (; itr != nodes.end(); ++itr) {
		if (nodes.empty()) {
			continue;
		}
		vector<float> data_item;
		vector<string> items;
		CBasic::StringSplitTrim(*itr, split2, items);
		for (vector<string>::iterator it = items.begin(); it != items.end(); ++it) {
			data_item.push_back(atof(it->c_str()));
		}
		data.push_back(data_item);
	}
	return true;
}

