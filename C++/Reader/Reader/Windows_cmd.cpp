#include "Windows_cmd.h"

void Windows_cmd::execute(char* windows_cmd)
{
	system( windows_cmd );
}

