#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void ClearScreen();

#else // !_WIN32
#include <unistd.h>
#include <term.h>

void ClearScreen();
#endif