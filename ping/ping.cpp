#include "stdafx.h"
#include "windows.h "  
#include "shellapi.h " 
#include "stdio.h" 
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <stdlib.h>
#include <regex>
using namespace std;

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )


string readFileIntoString(char * filename)
{
	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	while (buf&&ifile.get(ch))
		buf.put(ch);
	return buf.str();
}
int findChildCnt(char* str1, char* str2)
{
	int len = strlen(str2);
	int cnt = 0;
	while (str1 = strstr(str1, str2)) 
	{
		cnt++;
		str1 += len;
	}
	return cnt;
}
int main(int argc, char *agrv[])
{
	
	agrv[2];
	char * target = agrv[1];
	char * packets = agrv[2];
	char * size = agrv[3];
	char * mode = agrv[4];
	string  cmdsql = (string)"/C ping " +target + (string)" -n " +packets + (string)" -l " +size + (string)" > 1.txt";
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = cmdsql.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	//ShellExecuteEx(NULL, "open", "cmd.exe", cmdsql.c_str(), NULL, SW_HIDE);
	
	

	char * pingfile = "1.txt";
	string ping;
	ping = readFileIntoString(pingfile);
	//cout << ping << endl;
	char *p = const_cast<char*>(ping.data());
	int count;
	count =findChildCnt(p, "ms")-3;
	regex pattern_info("= ([0-9]+)ms(.+)= ([0-9]+)ms(.+)= ([0-9]+)ms", regex_constants::extended);

	string str = ping;

	smatch base_match;
	if (regex_search(str, base_match, pattern_info))
	{
		if (base_match.size() == 6) {
			ssub_match base_sub_match = base_match[1];
			string minVal = base_sub_match.str();
			
			base_sub_match = base_match[3];
			string maxVal = base_sub_match.str();

			base_sub_match = base_match[5];
			string avgVal = base_sub_match.str();

			if (!strcmp(mode,"min"))
			{
				cout << minVal << endl;
				return false;
			}
			else if (!strcmp(mode, "max"))
			{
				cout << maxVal << endl;
				return false;
			}
			else if (!strcmp(mode, "avg"))
			{
				cout << avgVal << endl;
				return false;
			}
			
		}
	}

	
	
	
  //  return 0;
}



