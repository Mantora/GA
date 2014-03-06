#ifdef _WIN32
	#include "Socket_TCP_windows.h"

	Socket_TCP_windows::Socket_TCP_windows()
	{
		clientAddrLen = sizeof(SOCKADDR_IN);
	};

	Socket_TCP_windows::~Socket_TCP_windows()
	{};

	void Socket_TCP_windows::ServerStarten( unsigned int port )
	{
		isServer = true;
		isClient = false;

		PORT = port;
		clientAddrLen = sizeof(SOCKADDR_IN);

//		system("cls");
		cout << "Unity Game Server - Copyright © CJ 2011-2013 - Windows Version" << endl;
		startWinsock();
		erstelleSocket();
		bindeSocket();
/*------------------------------------------------------------------------------------------------------------------------*/

		int iOptVal = 0;
		int iOptLen = sizeof (int);
		int iResult = getsockopt(this->s, SOL_SOCKET, SO_SNDTIMEO, (char *) &iOptVal, &iOptLen);
		if(iResult == SOCKET_ERROR)
		{
			cout << "getsockopt for SO_SNDTIMEO failed with error: " <<  WSAGetLastError() << endl;
		}
		else
			cout << "SO_SNDTIMEO Value: " << iOptVal << endl;

		iOptVal = 5000; //inMSec

		iResult = setsockopt(this->s, SOL_SOCKET, SO_SNDTIMEO, (char *) &iOptVal, iOptLen);
		if (iResult == SOCKET_ERROR)
		{
			cout << "setsockopt for SO_SNDTIMEO failed with error: " << WSAGetLastError() << endl;
		}
		else
		{
			cout << "Set SO_SNDTIMEO: " << iOptVal << endl;
		}
/*------------------------------------------------------------------------------------------------------------------------*/
		cout << "Server bereit." << endl << endl;

		rc = listen( this->s, 10 );
		if(rc == SOCKET_ERROR)
		{
			cout << "Fehler: listen(), fehler code: " << WSAGetLastError() << endl;
			exit(-1);
		}
		else
		{
			cout << "Socket ist im listen Modus...." << endl;
		}
	};

	void Socket_TCP_windows::ClientVerbinden( char* cp_IP_Host ,u_short us_Port_Host )
	{
		isServer = false;
		isClient = true;

		clientAddrLen = sizeof(SOCKADDR_IN);

//		system("cls");
		cout << "Test Client - Copyright © CJ 2011-2013 - Windows Version" << endl;
		startWinsock();
		erstelleSocket();

		this->addr_server.sin_family = AF_INET;
		this->addr_server.sin_port = htons(us_Port_Host);
		this->addr_server.sin_addr.s_addr = inet_addr(cp_IP_Host);

		cout << "Client bereit." << endl << endl;
	};

	void Socket_TCP_windows::startWinsock(void)
	{
		//WSAStartup() ist notwendig um Sockets zu benutzen
		WSADATA wsa;
		rc = WSAStartup(MAKEWORD(2,0), &wsa);
		if(rc != 0)
		{
			//fehler
			cout << "Fehler: startWinsock, fehler code: " << rc << endl;
			exit(-1);
		}
		else
		{
			cout << "Winsock gestartet!" << endl;
		}
	};

	void Socket_TCP_windows::erstelleSocket()
	{
		//UDP Socket erstellen --> SOCK_DGRAM = UDP
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(s == INVALID_SOCKET)
		{
			cout << "Fehler: Der Socket konnte nicht erstellt werden, fehler code: " << WSAGetLastError() << endl;
		}
		else
		{
			cout << "Socket erstellt" << endl;
		}
	}

	void Socket_TCP_windows::bindeSocket()
	{
		memset(&addr, 0, sizeof(SOCKADDR_IN) );

		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);
		addr.sin_addr.s_addr = ADDR_ANY;

		rc = bind(s, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
		if(rc == SOCKET_ERROR)
		{
			cout << "Fehler: bind(), fehler code: " << WSAGetLastError() << endl;
			exit(-1);
		}
		else
		{
			cout << "Socket an Port " << PORT << " gebunden" << endl;
		}
	};

	SOCKET Socket_TCP_windows::wait4Client()
	{
		SOCKET connectedSocket = accept( this->s,(SOCKADDR*)&client, &clientAddrLen );
		if(connectedSocket==INVALID_SOCKET)
		{
			cout << "Fehler: accept, fehler code: " << WSAGetLastError() << endl;
			exit(-1);
		}
		else
		{
			cout << "Neue Verbindung wurde akzeptiert von " << (int)connectedSocket << endl;
			return connectedSocket;
		}

	}
/*
	DatenPaket* Socket_TCP_windows::empfangen( SOCKET connectedSocket )
	{
		//rc = recvfrom(s, reinterpret_cast<char*>(buf), 1500, 0, (SOCKADDR*)&client, &clientAddrLen);
		rc = recv( connectedSocket, reinterpret_cast<char*>(buf), 1400, 0 );

		if(rc == SOCKET_ERROR)
		{
			cout << "Fehler: recvfrom, fehler code: " << WSAGetLastError() << endl;
			system("pause");
			exit(1);
		}
		else
		{
			//Offenen Stream vom Client schließen
			//buf[rc] = '\0';
			cout << "Empfange " << rc << " Bytes" << endl;// von " << inet_ntoa(client.sin_addr) << ":" << client.sin_port ;

		}
		//Im Datenpaket befindet sich der Sender und die Daten:
		return new DatenPaket(client, buf, rc);
	};
*/
	void Socket_TCP_windows::senden( SOCKET connectedSocket, DatenPaket* dp_senden )
	{
		char* carr_zusenden = (char*)dp_senden->buffer;

		//Testausgabe der Länge des zu sendenden Stream (Da Koordinaten '\0' enthalten kann)
//		cout << "DEBUG: dp_senden->uiAnzahlByte:" << dp_senden->uiAnzahlByte << endl;

//		rc = sendto(s, carr_zusenden, dp_senden->uiAnzahlByte, 0, (SOCKADDR*)&(dp_senden->Adresse), sizeof(SOCKADDR_IN) );
		rc = send( connectedSocket, carr_zusenden, dp_senden->uiAnzahlByte, 0);

		if(rc == SOCKET_ERROR)
		{
			//Irgend ein Fehler ist beim Senden aufgetreten, aus sicherheitsgründen wird die Verbindunge beendet:
			cout << "Fehler sendto() " << endl;//an " << inet_ntoa(dp_senden.sin_addr) << ":" << client.sin_port << " code: " << WSAGetLastError() << endl;
			system("pause");
			exit(1);
		}
		else
		{
			//Speicherplatz des gesendeten carr_zusenden freigeben
			free(carr_zusenden);
		}
//		Sleep(5);
	};
#endif