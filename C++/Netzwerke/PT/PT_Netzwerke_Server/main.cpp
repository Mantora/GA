//main.cpp von "Server"
#include <iostream>

#include "Socket_UDP_windows.h"

using namespace std;

int main()
{
	cout << "Server startet ... " << endl;

	Socket_UDP_windows* s = new Socket_UDP_windows(25001);
	s->ServerStarten();
	while(1)
	{
		DatenPaket* dp_empfangen = s->empfangen();
		dp_empfangen->anzeigen();
	}
	system("pause");
	return 0;
}