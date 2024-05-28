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

private:
	Logger() {}
	~Logger() {}
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;

	void openLogFile();
	void closeLogFile();
	void makeLog(string func, string msg, char* const log);
	void printOut(char* const log);
	void checkLogFile();
	void makeLatestFileToBackupFile();
	void makeBackupLogFileToCompressFile();
	uintmax_t LogFileSize(string& LogName);
	ofstream logfile;
	const int MAX_LOG_SIZE = 10240;
	string LATEST_LOG_NAME = "latest.log";
	const string LOG_PREFIX = "until_";
	const string LOG_EXTENSION = ".log";
	const string COMPRESS_EXTENSION = ".zip";

};