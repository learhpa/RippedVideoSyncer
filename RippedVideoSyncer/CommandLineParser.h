#ifndef __COMMANDLINEPARSER_H__

#define __COMMANDLINEPARSER_H__

#include "ProgramParameters.h"

class CommandLineParser {
public:
	virtual ProgramParameters* parse() = 0;
	virtual ~CommandLineParser() { };

};







#endif