#pragma once
#include <fstream>
#include <string>

using namespace std;

#define PRINTLOG(msg) Logger::getInstance().printLog(__FUNCTION__, msg);

class Logger {
public:
	static Logger& getInstance() {
		static Logger instance{}; // 지연된 초기화 
		return instance;
	}
	void printLog(string func, string msg);
	void checkLogFile();
	void makeLatestFileToBackupFile();
	void makeBackupLogFileToCompressFile();
	uintmax_t LogFileSize(string& LogName);
private:
	Logger()
	{
		logfile.open(LATEST_LOG_NAME);
	}
	~Logger()
	{
		logfile.close();
	}
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;
	ofstream logfile;

	const int MAX_LOG_SIZE = 10240;
	string LATEST_LOG_NAME = "latest.log";
	const string LOG_PREFIX = "until_";
	const string LOG_EXTENSION = ".log";
	const string COMPRESS_EXTENSION = ".zip";

};