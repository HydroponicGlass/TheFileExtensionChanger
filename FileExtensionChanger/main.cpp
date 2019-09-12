// C++

/* Reference

 WIN32_FIND_DATA struct
 https://docs.microsoft.com/ko-kr/windows/win32/api/minwinbase/ns-minwinbase-win32_find_dataa
 FindFirstFile function
 https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilea
 FindNextFile function
 https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findnextfilea
 Listing example
 https://docs.microsoft.com/ko-kr/windows/win32/fileio/listing-the-files-in-a-directory

 */

#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#include <tchar.h> 

#define EXT ".mp4" // Modify the extension you want

void reName(char *input)
{
	char newName[MAX_PATH];

	strcpy_s(newName, MAX_PATH, input);
	strcat_s(newName, MAX_PATH, EXT);

	/* Attempt to rename file: */
	int result = rename(input, newName);
	if (result != 0)
		printf("Could not rename '%s'\n", input);
	else
		printf("File '%s' renamed to '%s'\n", input, newName);
}

void findList(char *input) {

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	printf_s("Target file is %s\n", input);

	// If you want to modify your search location, modify 3rd parameter. Asterisk reters to all files
	// strcat_s(input, MAX_PATH, "\\*"); 

	strcat_s(input, MAX_PATH, "*");

	hFind = FindFirstFileA(input, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf_s("FindFirstFile failed (%d)\n", GetLastError());
		return;
	}

	do
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) // Search only for files
		{
			bool dot = false;
			char tmp[MAX_PATH];
			strcpy_s(tmp, MAX_PATH, FindFileData.cFileName);

			for (int i = strlen(tmp); i >= 0; i--)
			{
				if (tmp[i] == '.')
				{
					dot = true;
					break;
				}
			}

			if (dot == false) reName(tmp);
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);

	FindClose(hFind);
}

int main() {
	char input[MAX_PATH] = "";
	//printf_s("Input a sub directory : ");
	//scanf_s("%s", &input, sizeof(input));
	findList(input);
}