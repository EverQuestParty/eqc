#include <sys/stat.h>
#include <time.h>

#ifdef WIN32
#include <direct.h>
#endif

#include "log.h"

void SetCurrentTimeStamp(char* time_stamp)
{
	time_t raw_time;
	struct tm * time_info;
	time(&raw_time);
	time_info = localtime(&raw_time);
	strftime(time_stamp, 80, "[%m-%d-%Y :: %H:%M:%S]", time_info);
}

void MakeDirectory(const std::string &directory_name)
{
#ifdef WIN32
	struct _stat st;
	if(_stat(directory_name.c_str(), &st) == 0) // exists
		return;
	_mkdir(directory_name.c_str());
#else
	struct stat st;
	if(stat(directory_name.c_str(), &st) == 0) // exists
		return;
	mkdir(directory_name.c_str(), 0755);
#endif
}

Log::Log() {
	f_ = nullptr;
	enabled_[Status] = true;
#ifdef _DEBUG
	enabled_[Debug] = true;
#else
	enabled_[Debug] = false;
#endif
	enabled_[Error] = true;
}

Log::~Log() {
	if(f_) {
		fclose(f_);
	}
}

void Log::EnableLogType(Type t) {
	if(t >= MaxLogType) {
		return;
	}

	enabled_[t] = true;
}

void Log::DisableLogType(Type t) {
	if(t >= MaxLogType) {
		return;
	}

	enabled_[t] = false;
}

void Log::Write(Type t, std::string msg) {
	if(t >= MaxLogType) {
		return;
	}

	if(!enabled_[t]) {
		return;
	}

	MakeDirectory("logs/");

	if(!f_) {
		f_ = fopen("logs/c_dbg.log", "w");
		if(!f_) {
			return;
		}
	}

	char time_stamp[80];
	SetCurrentTimeStamp(time_stamp);

	std::string time_string = time_stamp;
	std::string out_string = time_string + std::string(" ") + msg;

	fprintf(f_, "%s\n", out_string.c_str());
	fflush(f_);
}

void Log::Write(Type t, const char *msg) {
	if(t >= MaxLogType) {
		return;
	}

	if(!enabled_[t]) {
		return;
	}

	MakeDirectory("logs/");

	if(!f_) {
		f_ = fopen("logs/c_dbg.log", "w");
		if(!f_) {
			return;
		}
	}

	char time_stamp[80];
	SetCurrentTimeStamp(time_stamp);

	std::string time_string = time_stamp;
	std::string out_string = time_string + std::string(" ") + msg;

	fprintf(f_, "%s\n", out_string.c_str());
	fflush(f_);
}
