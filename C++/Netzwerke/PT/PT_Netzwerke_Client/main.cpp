//main.cpp von "Client"
#include <iostream>
#include <conio.h> //f�r getch()
#include <signal.h> // f�r terminal exit handling


#include "Socket_UDP_windows.h"

using namespace std;

//START GLOBALE VARIABLEN
Socket_UDP_windows* s;

//diese variable speichert die eingabe:
int i_spaceCount = 0;
int i_playerID = 0;
//END GLOBALE VARIABLEN

int main()
{
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
		
		//Datenpaket f�llen
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

		exit(1);
	}




	{
		dp_empfangen = s->empfangen();

		if( dp_empfangen->type == PT_LOGIN_RESPONS )
		{
			i_playerID = dp_empfangen->playerID;

			cout << endl << "Erfolgreich am Server angemeldet mit ID " << i_playerID << endl;
			cout << "Jetzt kannst du Leertaste d�cken wie ein Irrer." << endl;

			//erfolgreich angemeldet, irgend eine eingabe z�hlen
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