//main.cpp von "Server"
#include <iostream>
#include <pthread.h>
#include <vector>

#include "Socket_UDP_windows.h"
#include "Socket_TCP_windows.h"

#include "MySQLmgr.h"

using namespace std;

void removeSOCKET( SOCKET s );
void sendToAllSOCKETS( const char* msg, int size );
void sendToOtherSOCKETS( SOCKET senderSOCKET, const char* msg, int size );
void createSendThread();

std::vector<SOCKET> connectedSockets;

extern "C" 
void* 
recieveNetworkDataThread( void* ptrToSocket )
{
	SOCKET s = (SOCKET)ptrToSocket;
	printf( "recieveNetworkDataThread() %u for SOCKET %d gestartet.\n", pthread_self() );

	unsigned char buf[1400] = {0};
	bool closeThread = false;

	while( !closeThread )
	{
		int rc = recv( s, reinterpret_cast<char*>(buf), sizeof(buf), 0 );
		printf( "recieveNetworkDataThread() %d: ", pthread_self() );
		if(rc == SOCKET_ERROR)
		{
			printf( "Fehler bei recv, fehler code: %d.\n", WSAGetLastError() );
			closeThread = true;
		}
		else if( rc == 0 )
		{
			printf( "%d: %d bytes empfangen. Thread auslaufen lassen...\n", s, rc );
			closeThread = true;
		}
		else
		{
			printf( "%d: %d bytes empfangen. verarbeiten...\n", s, rc );
		}
	}

	printf( "recieveNetworkDataThread() %u beendet.\n", pthread_self() );
	closesocket(s);
	printf("SOCKET s close");

	//remove SOCKET from connectedSockets std::vector:
	removeSOCKET( s );

	return 0;
}

extern "C" 
void* 
sendNetworkDataThread(void*)
{
	printf( "sendNetworkDataThread() gestartet.\n", pthread_self() );

	bool closeThread = false;
	char input;

	while( !closeThread )
	{
		cin >> input;

		switch( input )
		{
			case 'e': closeThread = true; break;
			default: 
				sendToAllSOCKETS( "test", 5 );
				cout << "sendNetworkDataThread(): gesendet" << endl;
		}
	}

	printf( "sendNetworkDataThread() %u beendet.\n", pthread_self() );

	return 0;
}

void removeSOCKET( SOCKET s )
{
	std::vector<SOCKET>::iterator iter;
	for( iter = connectedSockets.begin(); iter != connectedSockets.end(); iter )
	{
		if( (*iter) == s )
		{
			iter = connectedSockets.erase( iter );
		}
		else
		{
			++iter;
		}
	}
}

void sendToAllSOCKETS( const char* msg, int size )
{
	std::vector<SOCKET>::iterator iter;
	for( iter = connectedSockets.begin(); iter != connectedSockets.end(); iter )
	{
		send( (*iter), msg, size, 0 );
		++iter;
	}
	cout << "sendToAllSOCKETS(): " << connectedSockets.size() << endl;
}


void sendToOtherSOCKETS( SOCKET senderSOCKET, const char* msg, int size )
{
	std::vector<SOCKET>::iterator iter;
	for( iter = connectedSockets.begin(); iter != connectedSockets.end(); iter )
	{
		if( (*iter) != senderSOCKET )
			send( (*iter), msg, size, 0 );

		++iter;
	}
	cout << "sendToAllSOCKETS(): " << connectedSockets.size() << endl;
}

void createSendThread()
{
	pthread_t thread;
	if( pthread_create( &thread, NULL, sendNetworkDataThread, NULL) != 0)
	{
		cout << "Fehler beim erzeugen des Empfangs Thread" << endl;
		exit(1);
	}
}

int main()
{
	cout << "Server startet ... " << endl;
	
	int currentThread = 0;

	Socket_TCP_windows* s = new Socket_TCP_windows();
//	Socket_UDP_windows* s = new Socket_UDP_windows();
	s->ServerStarten( 25001 );

	createSendThread();

	while( 1 )
	{
		SOCKET connectedSocket = s->wait4Client();
		//nach dieser Stelle ist ein neuer Client verbunden

		connectedSockets.push_back( connectedSocket );

		//einen Empfangsthread für den verbundenen SOCKET starten
		cout << "Neuer Client verbunden, starte neuen recieveNetworkDataThread()" << endl;
		pthread_t thread;
		if( pthread_create( &thread, NULL, recieveNetworkDataThread, (void*)connectedSocket) != 0)
		{
			cout << "Fehler beim erzeugen des Empfangs Thread" << endl;
			exit(1);
		}
		
		cout << "Alle verbundenen Informieren" << endl;
		char* msg = "Neue Verbindung";
		sendToAllSOCKETS( msg, strlen(msg) );

		while(1)
		{
			cout << "Server Hauptschleife arbeitet..." << endl;
			Sleep(1000);
		}
	}

/*
	DatenPaket* dp_empfangen = s->empfangen( clientSocket );
	cout << "Empfangen: " << dp_empfangen->uiAnzahlByte << " byte." << endl;

	//Serverschleife def.
	while( 1 )
	{
		DatenPaket* dp_toSend = new DatenPaket( PT_LOGIN_RESPONS );
		dp_toSend->Adresse = dp_empfangen->Adresse;
		s->senden( dp_toSend );
		cout << "gesendet" << endl;

		cout << "Ready to send 1000 PT_LOGIN_RESPONS" << endl;
		system("pause");
		for( int i = 0; i < 1000; i++)
		{
			char* msg = "Das Ist irgend ein InhaltDas Ist irgend ein InhaltDas Ist irgend ein InhaltDas Ist irgend ein Inhalt";
			unsigned char* dataStream = (unsigned char*)msg;
			//int streamSize = strlen(msg+1);
			int streamSize = 5;
			DatenPaket* dp = new DatenPaket( dataStream, streamSize );
			dp->Adresse = dp_empfangen->Adresse;
			s->senden( dp );
		}
		cout << "Bytes send: " << s->getTotalBytesSend() << " (" << s->getTotalBytesSend()/1024 << " KB)" << endl;
		s->resetTotalBytesSend();
	}
		//DatenPaket* dp_empfangen = s->empfangen();
		unsigned char* stream = (unsigned char*)dp_empfangen;
*/



/*		if( DEBUG )
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

				MySQLmgr* sql = new MySQLmgr( "127.0.0.1", "root", "2011#myroot!", "ga_datenbank" );
				char sqlQuery[256] = {0};
				sprintf( sqlQuery, "SELECT * FROM users WHERE NAME = '%s' AND PASSWORD = SHA('%s');", dp_empfangen->daten_1, dp_empfangen->daten_2 );
//				sprintf( sqlQuerry, "SELECT * FROM benutzer WHERE name = '%s' AND passwort = '%s';", dp_empfangen->daten_1, dp_empfangen->daten_2 );
				if( DEBUG )
					cout << sqlQuery << endl;
				sql->Query(sqlQuery);
				int rows = sql->getRowsCountFromQuerry();

				if( rows == 1 )
				{
					char sqlQuery[256] = {0};
					sprintf( sqlQuery, "SELECT ID FROM users WHERE NAME = '%s';" , dp_empfangen->daten_1 );
					if( DEBUG )
						cout << sqlQuery << endl;
					int userID = sql->getSingleDataFromQuerry( sqlQuery, 0 );
			
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
				MySQLmgr* sql = new MySQLmgr( "127.0.0.1", "root", "2011#myroot!", "ga_datenbank" );
				char sqlQuery[256] = {0};
				sprintf( sqlQuery, "INSERT INTO log_CJ(user_id,date,space_count) VALUES(%d,NOW(),%d);", dp_empfangen->playerID, dp_empfangen->spaceCount );
				
				if( DEBUG )
					cout << sqlQuery << endl;

//				int rows = sql->Querry(sqlQuerry);
			}
			break;
		}
*/

	system("pause");
	return 0;
}