#pragma once
#include <string>
#include <vector>
static class ReckonEditor
{
public:
	static void InitWorkingDirectories();
	static void SaveLayoutWithName(const char* name);
	static void LoadLayoutWithName(const std::string& name);
	static void SaveLayoutPathFile();
	static void LoadLayoutPathFile();
	static void ClearLayoutData();
};

