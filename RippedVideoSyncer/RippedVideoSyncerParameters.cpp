#include "stdafx.h"
#include "RippedVideoSyncerParameters.h"

#define RVSP_SOURCE L"c:\\video\\handbrake-rips"
#define RVSP_DEST L"c:\\video\\archive"


bool RippedVideoSyncerParameters::is_valid() {

	if (_destination_directory.empty() || _destination_drive.empty() || _destination_filename.empty() ||
		_source_directory.empty() || _source_drive.empty() || _source_filename.empty()) {
		return false;
	}
	else {
		return true;
	}

}

void RippedVideoSyncerParameters::force_default() {

	if (_source_directory.empty() && _source_drive.empty())
		tokenize_string(RVSP_SOURCE, true);
	if (_destination_directory.empty() && _destination_drive.empty())
		tokenize_string(RVSP_DEST, false);
	set_source_filename(NO_FILENAME_USED);
	set_destination_filename(NO_FILENAME_USED);
	
}

void RippedVideoSyncerParameters::tokenize_string(std::wstring token, bool is_source) {

	std::wstring::size_type dir_pos = token.find_first_of('\\');
	std::wstring drive_token = token.substr(0, dir_pos+1);
	std::wstring dir_token = token.substr(dir_pos + 1, token.length()-1);

	if (is_source) {
		set_source_drive(drive_token);
		set_source_dir(dir_token);
	}
	else
	{
		set_destination_drive(drive_token);
		set_destination_dir(dir_token);
	}

}
