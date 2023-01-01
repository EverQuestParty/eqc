#ifndef EQC_COMMON_LOG_H
#define EQC_COMMON_LOG_H

#include <string>
#include <stdio.h>

class Log
{
public:
	enum Type
	{
		Status,
		Debug,
		Error,
		MaxLogType
	};

	~Log();
	
	void EnableLogType(Type t);
	void DisableLogType(Type t);
	void Write(Type t, std::string msg);
	void Write(Type t, const char *msg);

	static Log& Get() {
		static Log inst;
		return inst;
	}
private:
	Log();
	Log(const Log&);
	Log& operator=(const Log&);
	
	bool enabled_[MaxLogType];
	FILE *f_;
};

#endif
