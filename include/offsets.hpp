#pragma once

#include <map>
#include <string>
#include <Windows.h>

extern std::map<std::string, DWORD> basicOffsets;
extern std::map<std::string, std::map<std::string, DWORD>> entityOffsets;