#ifndef __PROGRAM_PARAMETERS_H__
#define __PROGRAM_PARAMETERS_H__

class ProgramParameters {
public:
	virtual bool is_valid() = 0;
	virtual void force_default() = 0;
	virtual ~ProgramParameters() { };
};





#endif