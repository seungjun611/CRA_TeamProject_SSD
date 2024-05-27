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
		uintmax_t latest_log_size = 0;
		try {
			fs::path latest_log_path = fs::current_path() / "latest.log";

			if (!fs::exists(latest_log_path)) {

				ofstream file(latest_log_path);
				if (!file.is_open()) {
					throw runtime_error("Failed to create 'latest.log' file.");
				}
				file.close();
				cout << "'latest.log' file created." << endl;
			}

			latest_log_size = fs::file_size(latest_log_path);
		}
		catch (exception& e) {
			throw(e.what());
		}		

		if (latest_log_size > MAX_LOG_SIZE) {

			// until_*.log 파일을 찾아 .zip 파일로 변경
			string prefix = "until_";
			string old_extension = ".log";
			string new_extension = ".zip";
			for (const auto& entry : fs::directory_iterator(".")) {
				if (entry.is_regular_file() && entry.path().filename().string().find(prefix) == 0 && entry.path().extension() == old_extension) {
					fs::path new_path = entry.path().parent_path() / (prefix + entry.path().filename().string().substr(prefix.length(), entry.path().filename().string().length() - prefix.length() - old_extension.length()) + new_extension);
					fs::rename(entry.path(), new_path);
					cout << "Renamed: " << entry.path() << " -> " << new_path << endl;
				}
			}

			// 파일 크기가 maxSize를 초과하면 새 파일 이름 생성
			time_t now = time(nullptr);
			struct tm timeinfo;
			char buffer[80];

			time(&now);
			localtime_s(&timeinfo, &now);
			strftime(buffer, sizeof(buffer), "%y%m%d_%Hh_%Mm_%Ss", &timeinfo);

			// 백업 파일 경로 생성
			fs::path backupFilename = "until_" + string(buffer) + ".log"; // until_240527_10h_50m_11s.log

			fs::rename("latest.log", backupFilename);

			cout << "File renamed to: " << backupFilename << endl;
		}

	}

private:
	Logger() { }
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;

	int MAX_LOG_SIZE = 10240;
};