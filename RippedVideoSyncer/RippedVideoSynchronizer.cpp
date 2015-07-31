
#include "stdafx.h"

#ifdef __WINDOWS_BUILD
#include <windows.h>
#include <Shlwapi.h>
#endif

#include <iostream>
#include "RippedVideoOverrides.h"
#include "RippedVideoSyncerParameters.h"



RippedVideoSynchronizer::RippedVideoSynchronizer(ProgramParameters *_Params)
{
	RippedVideoSyncerParameters* params = dynamic_cast<RippedVideoSyncerParameters*>(_Params);

	source_drive = params->get_source_drive();
	source_directory = params->get_source_directory();
	source_filename = params->get_source_filename();
	dest_drive = params->get_destination_drive();
	dest_directory = params->get_destination_directory();
	dest_filename = params->get_destination_filename();
}

RippedVideoSynchronizer::~RippedVideoSynchronizer()
{

}

bool RippedVideoSynchronizer::validate_drives()
{
#ifndef __WINDOWS_BUILD
	std::cout << "FATAL ERROR: file handling code only implemented for windows at this time" << std::endl;
	return false;
#endif

#ifdef __WINDOWS_BUILD

	if (PathFileExists(source_drive.c_str()) && PathFileExists(dest_drive.c_str()))
		return true;
	else
		return false;
#endif
}

bool RippedVideoSynchronizer::validate_dirs(const std::wstring first, const std::wstring second) {
#ifndef __WINDOWS_BUILD
	std::cout << "FATAL ERROR: file handling code only implemented for windows at this time" << std::endl;
	return false;
#endif

#ifdef __WINDOWS_BUILD
	if (PathFileExists(first.c_str()) && PathFileExists(second.c_str()))
		return true;
	else
		return false;
#endif
}

bool RippedVideoSynchronizer::synchronize() 
{

	if ((source_filename != NO_FILENAME_USED) || (dest_filename != NO_FILENAME_USED))
		std::cout << "ERROR: sourcing directories from filenames not currently supported. Please wait for version 2.0" << std::endl;

	if (!(validate_drives())) {
		std::wcout << "FATAL ERROR: invalid drives " << source_drive << " or " << dest_drive << std::endl;
		return false;
	}

	std::wstring wsrc;
	wsrc.clear();
	wsrc.append(source_drive);
	wsrc.append(source_directory);
	std::wstring wdst;
	wdst.clear();
	wdst.append(dest_drive);
	wdst.append(dest_directory);

	if (!(validate_dirs(wsrc, wdst))) {
		std::wcout << "FATAL ERROR: invalid directories " << wsrc << " or " << wdst << std::endl;
		return false;
	}
	
	int files_copied = process_directory(wsrc, wdst);
	if (files_copied)
		return true;
	else
		return false;

}

std::wstring RippedVideoSynchronizer::build_file_name(const std::wstring dir, const std::wstring file)
{
	std::wstring retval = dir;
	retval.append(L"\\");
	retval.append(file);
	return retval;
}


int RippedVideoSynchronizer::process_directory(const std::wstring src, const std::wstring dst)
{

#ifndef __WINDOWS_BUILD
	std::cout << "FATAL ERROR: file handling code only implemented for windows at this time" << std::endl;
	return 0;
#endif

#ifdef __WINDOWS_BUILD
	WIN32_FIND_DATA ffd;
	HANDLE hFind_src = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;
	int retval = 0;
	bool copy_succeeded = true;
	
	std::wstring w_ffd_tmp;

	std::wstring wsrc_dir_name(src);
	wsrc_dir_name.append(L"\\");
	wsrc_dir_name.append(L"*");
	std::wstring wdst_file_name(L"");
	std::wstring wsrc_file_name(L"");

	hFind_src = FindFirstFile(wsrc_dir_name.c_str(), &ffd);
	if (hFind_src == INVALID_HANDLE_VALUE)
	{
		std::wcout << std::endl << "UNEXPECTED ERROR opening directory" << src.c_str() << std::endl;
		return retval;
	}
	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if ((StrCmpW(ffd.cFileName, L".") == 0) || (StrCmpW(ffd.cFileName, L"..")==0)) {
				// do nothing;
			}
			else {
				std::wstring recursive_src_file = ffd.cFileName;
				std::wstring recursive_src_dir = build_file_name(src, recursive_src_file);
				std::wstring recursive_dst_dir = build_file_name(dst, recursive_src_file);
				if (!(PathFileExistsW(recursive_dst_dir.c_str())))
				{
					std::wcout << std::endl << "DIRECTORY DOES NOT EXIST, creating " << recursive_dst_dir.c_str() << std::endl;
					CreateDirectory(recursive_dst_dir.c_str(), NULL);
				}
				process_directory(recursive_src_dir, recursive_dst_dir);
			}
			/* construct the destination file name and copy*/
		}
		else {
			w_ffd_tmp = ffd.cFileName;
			
			wdst_file_name.clear();
			wdst_file_name.append(build_file_name(dst, w_ffd_tmp));

			wsrc_file_name.clear();
			wsrc_file_name.append(build_file_name(src, w_ffd_tmp));
			if (PathFileExists(wdst_file_name.c_str())) {
				std::wcout << std::endl << "WARNING: " << wdst_file_name.c_str() << "already exists, skipping." << std::endl;
			}
			else
			{
				if (CopyFile(wsrc_file_name.c_str(), wdst_file_name.c_str(), true)) {
					std::wcout << std::endl << "copying file: " << wsrc_file_name.c_str() << " to " << wdst_file_name.c_str() << std::endl;
					std::wcout << std::endl << "   deleting original " << wsrc_file_name.c_str() << std::endl;
					DeleteFile(wsrc_file_name.c_str());
					retval++;
				}
				else {
					std::wcout << std::endl << "ERROR --- copying file: " << wsrc_file_name.c_str() << " to " << wdst_file_name.c_str() << std::endl;
				}
			}
		}
	} while (FindNextFile(hFind_src, &ffd) != 0);

	return retval;
#endif
}

