#include "stdafx.h"
#include "RippedVideoOverrides.h"
#include "RippedVideoSyncerParameters.h"

#include <iostream>


RippedVideoCommandLineParser::RippedVideoCommandLineParser(int argc, wchar_t** argv)
{

	arg_count = 0;
	std::wstring cur_arg = L"";
	std::list<std::wstring>::iterator it = args.begin();
	int cur_args = 1; // start with argv[1] because program name is irrelevant

	for (; cur_args < argc; cur_args++)
	{
		cur_arg.clear();
		cur_arg.append(argv[cur_args]);
		args.insert(it, cur_arg);
		arg_count++;
	}

}

RippedVideoCommandLineParser::~RippedVideoCommandLineParser()
{
}


ProgramParameters* RippedVideoCommandLineParser::parse() {

	/* actual parsing not implemented yet, hard-coded strings for testing*/

	bool src_named = false, dst_named = false;

	std::wstring src_drive, src_dir, dst_drive, dst_dir;
	src_drive.clear();
	src_dir.clear();
	dst_drive.clear();
	dst_dir.clear();

	std::wstring cur_arg, cur_ctl_code, cur_data;

	
	std::list<std::wstring>::iterator it = args.begin();
	

	for (; it != args.end(); ++it)
	{
		cur_arg.clear();
		cur_arg.append(it->c_str());
		if ((cur_arg.find(L"-", 0)) == 0)
		{
			cur_ctl_code.clear();
			cur_data.clear();
			cur_ctl_code = cur_arg.substr(1, 1);
			cur_data = cur_arg.substr(2);
			if (((cur_ctl_code.find(L'S')) != std::string::npos) || ((cur_ctl_code.find(L's')) != std::string::npos))
			{

				if (cur_data.at(1) == L':')
				{
					src_drive.clear();
					src_dir.clear();
					src_drive.append(cur_data.substr(0, 3));
					src_dir.append(cur_data.substr(3));
					src_named = true;
				}
				else
				{
					std::wcout << "What? I don't understand this directory name: \"" << cur_data << "\"." << std::endl;
				}
			}
			else if (((cur_ctl_code.find(L'D')) != std::string::npos) || ((cur_ctl_code.find(L'd')) != std::string::npos))
			{

				if (cur_data.at(1) == L':')
				{
					dst_drive.clear();
					dst_dir.clear();
					dst_drive.append(cur_data.substr(0, 3));
					dst_dir.append(cur_data.substr(3));
					dst_named = true;
				} 
				else
				{
					std::wcout << "What? I don't understand this directory name: \"" << cur_data << "\"." << std::endl;
				}
			}
			else
			{
				std::wcout << "What? I don't understand this parameter: \"-" << cur_ctl_code << "\"." << std::endl;
			}
		}
		else
		{
			std::wcout << "Hey, I have no idea what you just said." << std::endl << "\"" << cur_arg << "\" is incomprehensible to me. Please try again?" << std::endl;
		}
	}

	if ((src_named == false) && (dst_named == false))
	{
		std::wcout << std::endl << "WARNING: USING DEFAULT SOURCE AND DESTINATION VALUES" << std::endl;
	}
	else if (src_named = false)
	{
		std::wcout << std::endl << "WARNING: USING DEFAULT DESTINATION VALUE" << std::endl;
	}
	else if (dst_named = false)
	{
		std::wcout << std::endl << "WARNING: USING DEFAULT DESTINATION VALUE" << std::endl;
	}

	RippedVideoSyncerParameters* _retval = new RippedVideoSyncerParameters();
	_retval->set_source_drive(src_drive);
	_retval->set_source_dir(src_dir);
	_retval->set_destination_drive(dst_drive);
	_retval->set_destination_dir(dst_dir); 



	return _retval;

}