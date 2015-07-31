#ifndef __RIPPED_VIDEO_OVERRIDES_H__
#define __RIPPED_VIDEO_OVERRIDES_H__

#include <string>
#include <list>
#include "ProgramParameters.h"
#include "CommandLineParser.h"
#include "Synchronizer.h"

class RippedVideoSynchronizer : public virtual Synchronizer {
public:
	RippedVideoSynchronizer();
	RippedVideoSynchronizer(ProgramParameters* _Params);
	~RippedVideoSynchronizer();

	bool synchronize();

private:
	std::wstring source_drive;
	std::wstring source_directory;
	std::wstring source_filename;
	std::wstring dest_drive;
	std::wstring dest_directory;
	std::wstring dest_filename;

	bool validate_drives();
	bool validate_dirs(const std::wstring first, const std::wstring second);
    std::wstring build_file_name(const std::wstring dir, const std::wstring file);
	int process_directory(const std::wstring src, const std::wstring dst);

};

class RippedVideoCommandLineParser : public virtual CommandLineParser {
public:
	RippedVideoCommandLineParser(int argc, wchar_t** argv);
	~RippedVideoCommandLineParser();

	virtual ProgramParameters* parse();

private:
	int arg_count;
	std::list<std::wstring> args;

};


#endif