	#pragma once
	#ifdef RCK_BUILD_DLL
	#define RCK_API __declspec(dllexport)
	#else
	#define RCK_API __declspec(dllimport)
	#endif