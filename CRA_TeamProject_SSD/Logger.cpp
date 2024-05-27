#include "Logger.h"

#include <iostream>
#include <ctime>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;
	
void Logger::printLog(string func, string msg)
{
	checkLogFile();

	if (logfile.is_open() == false)
	{
		logfile.open(LATEST_LOG_NAME, ios::app);
	}
	char log[1000];
	string funcname = func + "()";
	time_t now = time(nullptr);
	tm tmTime;
	localtime_s(&tmTime, &now);

	sprintf_s(log, "[%04d.%02d.%02d %02d:%02d:%02d] %-30s : %s\n",
		tmTime.tm_year + 1900, tmTime.tm_mon + 1, tmTime.tm_mday, tmTime.tm_hour, tmTime.tm_min, tmTime.tm_sec,
		funcname.c_str(), msg.c_str());
	cout << log;
	logfile << log;
}

void Logger::checkLogFile() {

	if (LogFileSize(LATEST_LOG_NAME) < MAX_LOG_SIZE) return;

	makeBackupLogFileToCompressFile();

	makeLatestFileToBackupFile();
}

void Logger::makeLatestFileToBackupFile()
{
	time_t now = time(nullptr);
	struct tm timeinfo;
	char NowTime[80];

	time(&now);
	localtime_s(&timeinfo, &now);
	strftime(NowTime, sizeof(NowTime), "%y%m%d_%Hh_%Mm_%Ss", &timeinfo);

	fs::rename(LATEST_LOG_NAME, LOG_PREFIX + string(NowTime) + LOG_EXTENSION);
}

void Logger::makeBackupLogFileToCompressFile()
{
	for (const auto& entry : fs::directory_iterator(".")) {
		if (!(entry.is_regular_file()) || entry.path().filename().string().find(LOG_PREFIX) != 0 && entry.path().extension() != LOG_EXTENSION)  continue;
		
		fs::rename(entry.path(), entry.path().parent_path() / (LOG_PREFIX + entry.path().filename().string().substr(LOG_PREFIX.length(), entry.path().filename().string().length() - LOG_PREFIX.length() - LOG_EXTENSION.length()) + COMPRESS_EXTENSION));
	}
}

uintmax_t Logger::LogFileSize(string& LogName)
{
	try {
		fs::path latest_log_path = fs::current_path() / LogName;

		if (!fs::exists(latest_log_path)) {

			ofstream file(latest_log_path);
			if (!file.is_open()) {
				throw runtime_error("Failed to create 'latest.log' file.");
			}
			file.close();
		}

		return fs::file_size(latest_log_path);
	}
	catch (exception& e) {
		throw("LogFileSize Check Error!!!");
	}
}

