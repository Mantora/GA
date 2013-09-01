//main.cpp von "Client"
#include <iostream>

#include "Socket_UDP_windows.h"

using namespace std;

int main()
{
	cout << "Client startet ... " << endl;

	Socket_UDP_windows* s = new Socket_UDP_windows(25001);
	s->ClientStarten();

	DatenPaket* dp_toSend = new DatenPaket(SV_CHAT);

	dp_toSend->Adresse.sin_family = AF_INET;
	dp_toSend->Adresse.sin_port = htons(25001);
	dp_toSend->Adresse.sin_addr.s_addr = inet_addr("127.0.0.1");

	unsigned char tmp[32] = "Test :)";
	dp_toSend->str_chat = tmp;

	s->senden( dp_toSend );

	system("pause");
	return 0;
}