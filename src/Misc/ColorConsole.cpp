#include "ColorConsole.h"

#ifndef _WIN32 // Linux
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define PURPLE  "\033[0;35m"
#define RESET   "\033[0m"
#endif

void PrintColoredText(const std::string& text, const ConsoleColor color)
{
#ifdef _WIN32
	int col = 15;
	switch (color)
	{
	case Red:
		col = 12; break;
	case Green:
		col = 10; break;
	case Yellow:
		col = 6; break;
	case Blue:
		col = 3; break;
	case Purple:
		col = 5; break;
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, col);
	std::cout << text << std::endl;		
	SetConsoleTextAttribute(hConsole, 15); // Reset

#else // Ubuntu
	std::string colorCode;
	switch (color)
	{
	case Red:
		colorCode = RED; break;
	case Green:
		colorCode = GREEN; break;
	case Yellow:
		colorCode = YELLOW; break;
	case Blue:
		colorCode = BLUE; break;
	case Purple:
		colorCode = PURPLE; break;
	}

	std::cout << colorCode << text << RESET << std::endl;
#endif
}

void PrintSuccess(const std::string& text)
{
	PrintColoredText(text, ConsoleColor::Green);
}

void PrintDebug(const std::string& text)
{
#if _DEBUG
	PrintColoredText("[DEBUG] - " + text, ConsoleColor::Default);
#endif
}

void PrintWarning(const std::string& text)
{
	PrintColoredText("[WARNING] - " + text, ConsoleColor::Yellow);
}

void PrintError(const std::string& text)
{
	PrintColoredText("[ERROR] - " + text, ConsoleColor::Red);
}