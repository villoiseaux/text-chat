#ifndef __textchat__logs_h
	#define __textchat__logs_h



	#define FATAL(msg,id) _fatalError(msg,id,__FILE__,__LINE__)
    #define OUT_ERR(msg,id) _outErr(msg,id,__FILE__,__LINE__)
	
    #define OUT_LOG(msg) _outLog(msg,__FILE__,__LINE__)
    #define OUT_LOGINT(msg,v) _outLogInt(msg,v,__FILE__,__LINE__)
    #define OUT_LOGCHAR(msg,v) _outLogChar(msg,v,__FILE__,__LINE__)

	void _fatalError(char* msg, int id,char* file, int line);
	void _outErr(char* msg, int id,char* file, int line);

	void _outLog(char* msg,char* file, int line);
	void _outLogInt(char* msg,int value,char* file, int line);
	void _outLogChar(char* msg,char* value,char* file, int line);

#endif