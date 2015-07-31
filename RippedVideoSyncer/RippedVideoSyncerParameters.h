#ifndef __RIPPEDVIDEOSYNCER_PARAMETERS_H__
#define __RIPPEDVIDEOSYNCER_PARAMETERS_H_

#define NO_FILENAME_USED L"NO_FILENAME_USED"


#include <string>

#include "ProgramParameters.h"

class RippedVideoSyncerParameters : public virtual ProgramParameters {
public:
	RippedVideoSyncerParameters() : _source_directory(L""), _source_drive(L""), _source_filename(L""), _destination_directory(L""), _destination_drive(L""), _destination_filename(L"") { }
	~RippedVideoSyncerParameters() {};


	virtual bool is_valid();
	virtual void force_default();

	void set_source_drive(std::wstring drive_source) { _source_drive = drive_source; }
	void set_source_dir(std::wstring dir_source) { _source_directory = dir_source; }
	void set_source_filename(std::wstring filename_source) { _source_filename = filename_source;  }

	void set_destination_drive(std::wstring drive_destination) { _destination_drive = drive_destination; }
	void set_destination_dir(std::wstring dir_destination) { _destination_directory = dir_destination; }
	void set_destination_filename(std::wstring filename_destination) { _destination_filename = filename_destination; }

	std::wstring get_source_drive() const { return _source_drive; }
	std::wstring get_source_directory() const { return _source_directory; }
	std::wstring get_source_filename() const { return _source_filename; }

	std::wstring get_destination_drive() const { return _destination_drive; }
	std::wstring get_destination_directory() const { return _destination_directory; }
	std::wstring get_destination_filename() const { return _destination_filename; }

private:
	std::wstring _source_drive;
	std::wstring _source_directory;
	std::wstring _source_filename;
	std::wstring _destination_drive;
	std::wstring _destination_directory;
	std::wstring _destination_filename;

	void tokenize_string(std::wstring _token, bool is_source);
};



#endif