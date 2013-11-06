//main.cpp von "Server"
#include <iostream>

#include "Socket_UDP_windows.h"

#include "MySQLmgr.h"

using namespace std;

#define DEBUG true

int main()
{
	cout << "Server startet ... " << endl;

	Socket_UDP_windows* s = new Socket_UDP_windows();
	s->ServerStarten( 25001 );

	//Serverschleife def.
	while(1)
	{
		DatenPaket* dp_empfangen = s->empfangen();
		if( DEBUG )
			dp_empfangen->anzeigen();
		
		switch( dp_empfangen->type )
		{
			case PT_ONLINE:
			{
				cout << "Client fragt, ob ich online bin." << endl;
				DatenPaket* dp_toSend = new DatenPaket( PT_ONLINE );
				dp_toSend->Adresse = dp_empfangen->Adresse;
				s->senden( dp_toSend );
			}
			break;

			case PT_LOGIN:
			{
				cout << "Client hat sich ";
				//handle login here

				MySQLmgr* sql = new MySQLmgr();
				char sqlQuerry[256] = {0};
				sprintf( sqlQuerry, "SELECT * FROM users WHERE NAME = '%s' AND PASSWORD = SHA('%s');", dp_empfangen->daten_1, dp_empfangen->daten_2 );
//				sprintf( sqlQuerry, "SELECT * FROM benutzer WHERE name = '%s' AND passwort = '%s';", dp_empfangen->daten_1, dp_empfangen->daten_2 );
				if( DEBUG )
					cout << sqlQuerry << endl;
				int rows = sql->Querry(sqlQuerry);

				if( rows == 1 )
				{
					char sqlQuerry[256] = {0};
					sprintf( sqlQuerry, "SELECT ID FROM users WHERE NAME = '%s';" , dp_empfangen->daten_1 );
					if( DEBUG )
						cout << sqlQuerry << endl;
					int userID = sql->getSingleDataFromQuerry( sqlQuerry );
			
					cout << "erfolgreich bei mir angemeldet ";
					DatenPaket* dp_toSend = new DatenPaket( PT_LOGIN_RESPONS );
					dp_toSend->Adresse = dp_empfangen->Adresse;
					//ID in daten_1 speichern
					dp_toSend->playerID = userID;
					s->senden( dp_toSend );

					cout << "mit id " << userID << endl;
				}
				else
				{
					cout << "falsch bei mir angemeldet" << endl;
					DatenPaket* dp_toSend = new DatenPaket( PT_INVAILED );
					dp_toSend->Adresse = dp_empfangen->Adresse;
					s->senden( dp_toSend );
				}
			}
			break;

			case PT_TERMINAL_CLOSE:
			{
				cout << "Client mit der ID " << dp_empfangen->playerID  << " hat sein Terminal geschlossen und " << dp_empfangen->spaceCount << " mal space gedrückt." << endl;
				
				//eintragen in MySQL Datenbank
				MySQLmgr* sql = new MySQLmgr();
				char sqlQuerry[256] = {0};
				sprintf( sqlQuerry, "INSERT INTO log_CJ(user_id,date,space_count) VALUES(%d,NOW(),%d);", dp_empfangen->playerID, dp_empfangen->spaceCount );
				
				if( DEBUG )
					cout << sqlQuerry << endl;

//				int rows = sql->Querry(sqlQuerry);
			}
			break;
		}
	}

	system("pause");
	return 0;
}