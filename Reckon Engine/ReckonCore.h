#pragma once
#ifdef RCK_BUILD_DLL
#define RCK_API __declspec(dllexport)
#else
#define RCK_API __declspec(dllimport)
#endif
#pragma warning(push)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)