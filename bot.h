#ifndef BOT_H
#define BOT_H

#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <String>

class bot{
private:
	int arr[64];
	std::string getFENRank(int row);
	HANDLE phandle;
	std::string getFENpiece();
	int getFullMove();
	DWORD64 findA1();
public:
	bot(DWORD pid);
	~bot();
	void updateArray();
	void printArray();
	std::string getFEN();
};

#endif