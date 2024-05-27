#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <regex>
#include <filesystem>

using namespace std;

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance{}; // 지연된 초기화 
        return instance;
    }

    void checkLogFile() {
        ifstream file("latest.log", ios::binary | ios::ate); 

        int maxSize = 1;
        if (file.is_open()) {

            streampos fileSize = file.tellg();
            file.close();

            if (fileSize > maxSize) {              

                // until_*.log 파일을 찾아 .zip 파일로 변경
                string prefix = "until_";
                string old_extension = ".log";
                string new_extension = ".zip"; 
                for (const auto& entry : filesystem::directory_iterator(".")) {
                    if (entry.is_regular_file() && entry.path().filename().string().find(prefix) == 0 && entry.path().extension() == old_extension) {
                        filesystem::path new_path = entry.path().parent_path() / (prefix + entry.path().filename().string().substr(prefix.length(), entry.path().filename().string().length() - prefix.length() - old_extension.length()) + new_extension);
                        filesystem::rename(entry.path(), new_path);
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

                ostringstream backupFilename;
                backupFilename << "until_" << buffer << ".log"; //until_240527_10h_50m_11s.log

                if (rename("latest.log", backupFilename.str().c_str()) != 0) {
                    cerr << "Error renaming file." << endl;
                }
                else {
                    cout << "File renamed to: " << backupFilename.str() << endl;
                }
            }
        }
        else {
            cout << "Error opening file." << endl;
        }
    }

private:
    Logger() { }
    Logger& operator=(const Logger& other) = delete;
    Logger(const Logger& other) = delete;
};