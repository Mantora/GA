//main.cpp von "Client"
#include <iostream>
#include <conio.h> //für getch()
#include <signal.h> // für terminal exit handling


#include "Socket_UDP_windows.h"

using namespace std;

//START GLOBALE VARIABLEN
Socket_UDP_windows* s;

//diese variable speichert die eingabe:
int i_spaceCount = 0;
//END GLOBALE VARIABLEN

void handler(int signum)
{
	cout << "GUI: STRG-C -> shutdown" << endl;
	switch(signum)
	{
		case 2:
		case 6:
		case 15:
		case 21:
		case 22:
		default: 
		{
			DatenPaket* dp_terminal_close = new DatenPaket( PT_TERMINAL_CLOSE );
			dp_terminal_close->spaceCount = i_spaceCount;
			s->senden( dp_terminal_close );
		}
		break;
	}
	exit(1); // sonst würde er unbeeindruckt in das laufende Programm zurückspringen
}

int main()
{
	/*Abfangen der Signale bei STRG+C*/
	#ifdef _WIN32 //Windows Header
		signal(SIGBREAK, handler);
		signal(SIGABRT_COMPAT, handler);
	#endif
	signal(SIGINT, handler);
	signal(SIGABRT, handler);
	signal(SIGTERM, handler);


	cout << "Client startet ... " << endl;

	s = new Socket_UDP_windows();
	s->ClientVerbinden("127.0.0.1", 25001);


	{
		//Datenpaket vorbereiten
		DatenPaket* dp_toSend = new DatenPaket( PT_ONLINE );

		//Datenpaket senden
		s->senden( dp_toSend );
	}


	DatenPaket* dp_empfangen;
	do
	{
		dp_empfangen = s->empfangen();
	}
	while( dp_empfangen->type != PT_ONLINE );



	{
		cout << "Anmeldung beim Server" << endl << endl;

		DatenPaket* dp_toSend = new DatenPaket( PT_LOGIN );
		
		//Datenpaket füllen
		unsigned char daten_1[32] = {0};
		cout << "Name: " ;
		cin >> daten_1;
		dp_toSend->daten_1 = daten_1;

		unsigned char daten_2[32] = {0};
		cout << "Password: " ;
		cin >> daten_2;
		dp_toSend->daten_2 = daten_2;

		//Datenpaket senden
		s->senden( dp_toSend );
	}




	{
		dp_empfangen = s->empfangen();

		if( dp_empfangen->type == PT_LOGIN_RESPONS )
		{
			cout << endl << "Erfolgreich am Server angemeldet" << endl;
			cout << "Jetzt kannst du Leertaste dücken wie ein Irrer." << endl;

			//erfolgreich angemeldet, irgend eine eingabe zählen
			{
				i_spaceCount = 0;
				char c = 0;
				while(1)
				{
					char c = getch();
					//putchar (c);

					if( c == ' ' )
						i_spaceCount++;

					cout << "Space: " << i_spaceCount << endl;
				}
			}


		}
		else
		{
			cout << "Der Server hat die Verbindung abgelehnt" << endl;
			system("pause");
			exit(0);
		}
	}



	system("pause");
	return 0;
}