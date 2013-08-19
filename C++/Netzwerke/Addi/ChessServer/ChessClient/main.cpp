// ChessClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <ZeroMqConnector.h>
#include <iostream>

#include "ChessClientApp.h"


int _tmain(int argc, _TCHAR* argv[])
{
  ChessClientApp app;

  app.run();

  return 0;
}

