#pragma once
#include <string>

static enum OPCODE {
    W = 0,  // Write
    R,  // Read
    E,  // Erase
    F,  // Flush
};

typedef struct SSDCommand {
    OPCODE opcode;
    int param1;
    std::string param2;
    int param3;
};

class ISSD
{
public:
	virtual ~ISSD() {}
	virtual void write(int lba, std::string data) = 0;
	virtual std::string read(int lba) = 0;
    virtual bool execute(SSDCommand command) = 0;
};