// RippedVideoSyncer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CommandLineParser.h"
#include "Synchronizer.h"
#include <string>
#include "RippedVideoOverrides.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	CommandLineParser* _CommandLineParser = new RippedVideoCommandLineParser(argc, (_TCHAR**)argv);
	ProgramParameters* _ProgramParameters = _CommandLineParser->parse();

	if (!(_ProgramParameters->is_valid()))
	{
		_ProgramParameters->force_default();
	}
	
	Synchronizer* _Synchronizer = new RippedVideoSynchronizer(_ProgramParameters);
	_Synchronizer->synchronize();

	delete _Synchronizer;
	
	delete _ProgramParameters;
	delete _CommandLineParser;

	
	return 0;
}

