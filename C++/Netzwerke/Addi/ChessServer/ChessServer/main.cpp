// ChessServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <ZeroMqConnector.h>
#include <iostream>

#include "ChessServerApp.h"


int _tmain(int argc, _TCHAR* argv[])
{
  ChessServerApp app;

  app.run();

  return 0;
}

