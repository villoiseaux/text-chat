#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "logs.h"

#define ANSI "\033["
#define ANSI_RESET ANSI"0m"

#define ANSI_FATAL ANSI"6;41m"
#define ANSI_ERR ANSI"41m"

#define ANSI_WARNING ANSI"30;43m"

#define ANSI_LOG ANSI"44m"
#define ANSI_VAL ANSI"42m"

void _fatalError(char* msg,int id,char* file, int line,const char* function){
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	
	printf(ANSI_FATAL"FATAL"ANSI_RESET" "ANSI_ERR"[%02d/%02d/%02d %02d:%02d:%02d] %10s (%06d) %s(): %s (%s %d)"ANSI_RESET"\n",
			timeinfo->tm_mday,timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
			file,line,function,
			msg,strerror(id),id);
	exit(EXIT_FAILURE);
}

void _outErr(char* msg,int id,char* file, int line,const char* function){
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	
	printf(ANSI_ERR" ERR "ANSI_RESET" [%02d/%02d/%02d %02d:%02d:%02d] %10s (%06d) %s(): %s (%d)\n",
			timeinfo->tm_mday,timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
			file,line,function,
			msg,id);
}

void _outWarning(char* msg,char* file, int line,const char* function){
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	
	printf(ANSI_WARNING" WRN "ANSI_RESET" [%02d/%02d/%02d %02d:%02d:%02d] %10s (%06d) %s(): %s\n",
			timeinfo->tm_mday,timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
			file,line,function,
			msg);
}


void _outLog(char* msg,char* file, int line,const char* funct){
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	
	printf(ANSI_LOG" LOG "ANSI_RESET" [%02d/%02d/%02d %02d:%02d:%02d] %10s (%06d) %s(): %s\n",
			timeinfo->tm_mday,timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
			file , line, funct,
			msg);
}

void _outLogInt(char* msg,int value,char* file, int line,const char* function){
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	
	printf(ANSI_VAL" VAL "ANSI_RESET" [%02d/%02d/%02d %02d:%02d:%02d] %10s (%06d) %s(): %s:%d\n",
			timeinfo->tm_mday,timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
			file , line, function,
			msg,value);
}

void _outLogChar(char* msg,char* value,char* file, int line,const char* function){
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime(&rawtime);
	
	printf(ANSI_VAL" VAL "ANSI_RESET" [%02d/%02d/%02d %02d:%02d:%02d] %10s (%06d) %s(): %s:%s\n",
			timeinfo->tm_mday,timeinfo->tm_mon + 1, timeinfo->tm_year + 1900,
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
			file , line,function,
			msg,value);
}