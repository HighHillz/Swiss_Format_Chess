#include "../include/console_utils.h"

#include <windows.h>

Console::Console() {}

void Console::setColour(int colourCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colourCode);
}