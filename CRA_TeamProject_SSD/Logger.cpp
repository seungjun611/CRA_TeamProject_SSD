#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

class Logger {
public:
	static Logger& getInstance() {
		static Logger instance{}; // 지연된 초기화 
		return instance;
	}

	void checkLogFile() {

		if (LogFileSize(LATEST_LOG_NAME) < MAX_LOG_SIZE) return;

		makeBackupLogFileToCompressFile();

		makeLatestFileToBackupFile();
	}

	void makeLatestFileToBackupFile()
	{
		time_t now = time(nullptr);
		struct tm timeinfo;
		char NowTime[80];

		time(&now);
		localtime_s(&timeinfo, &now);
		strftime(NowTime, sizeof(NowTime), "%y%m%d_%Hh_%Mm_%Ss", &timeinfo);

		fs::rename(LATEST_LOG_NAME, LOG_PREFIX + string(NowTime) + LOG_EXTENSION);
	}

	void makeBackupLogFileToCompressFile()
	{
		for (const auto& entry : fs::directory_iterator(".")) {
			if (!(entry.is_regular_file()) || entry.path().filename().string().find(LOG_PREFIX) != 0 && entry.path().extension() != LOG_EXTENSION)  continue;
			
			fs::rename(entry.path(), entry.path().parent_path() / (LOG_PREFIX + entry.path().filename().string().substr(LOG_PREFIX.length(), entry.path().filename().string().length() - LOG_PREFIX.length() - LOG_EXTENSION.length()) + COMPRESS_EXTENSION));
		}
	}

	uintmax_t LogFileSize(string& LogName)
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

private:
	Logger() { }
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;

	const int MAX_LOG_SIZE = 10240;

	string LATEST_LOG_NAME = "latest.log";

	const string LOG_PREFIX = "until_";
	const string LOG_EXTENSION = ".log";
	const string COMPRESS_EXTENSION = ".zip";

};