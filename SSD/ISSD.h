#pragma once
#include <string>

#define READ(x) execute(SSDCommand{OPCODE::R, x, "", 0})
#define WRITE(x, y) execute(SSDCommand{OPCODE::W, x, y, 0})
#define ERASE(x, y) execute(SSDCommand{OPCODE::E, x, "", y})
#define FLUSH() execute(SSDCommand{OPCODE::F, 0, "", 0})

enum OPCODE {
    W = 0,  // Write
    R,  // Read
    E,  // Erase
    F,  // Flush
};

struct SSDCommand {
    OPCODE opcode;
    int param1;
    std::string param2;
    int param3;
};

class ISSD
{
public:
	virtual ~ISSD() {}
    virtual bool execute(SSDCommand command) = 0;
    const int getMinLBA() { return minLBA; }
    const int getMaxLBA() { return maxLBA; }
    virtual std::string getReadData() { return readData; }
    virtual const char* getReadFileName() = 0;

protected:
    int minLBA;
    int maxLBA;
    std::string readData;

	virtual void write(int lba, std::string data) = 0;
	virtual std::string read(int lba) = 0;
    virtual bool erase(int lba, int size) = 0;
    virtual bool flush() = 0;
};