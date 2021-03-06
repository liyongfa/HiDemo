#include <stdio.h>
#include <stdlib.h>
#include "MainWin.h"
#include <windows.h>

#ifdef _DEBUG
#pragma comment(lib, "libutilsd.lib")
#pragma comment(lib, "libcamerad.lib")
#else
#pragma comment(lib, "libutils.lib")
#pragma comment(lib, "libcamera.lib")
#endif

using namespace e;

int main(int argc, char* argv[])
{
	::CoInitialize(NULL);

	MainWin* window = 0;

	try
	{
		window = new MainWin;
		window->Create();
		window->ShowWindow();
		window->MainLoop();
		delete window;
		window = 0;
	}
	catch (...)
	{
		printf("create main window exception\n");
	}

	::CoUninitialize();

	return 0;
}