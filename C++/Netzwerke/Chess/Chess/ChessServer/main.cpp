// ChessServer.cpp : Defines the entry point for the console application.
//

#include <ZeroMqConnector.h>
#include <iostream>

#include "ChessServerApp.h"


int main(int argc, char* argv[])
{
	ChessServerApp app;

	if( app.setup() )
	{
		app.run();
		app.shutdown();
	}

	return 0;
}

