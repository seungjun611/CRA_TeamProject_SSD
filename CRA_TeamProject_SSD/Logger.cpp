
class Logger {
public:
	static Logger& getInstance() {
		static Logger instance{}; // 지연된 초기화 
		return instance;
	}

private:
	Logger() { } 
	Logger& operator=(const Logger& other) = delete;
	Logger(const Logger& other) = delete;
};