#ifdef _WIN32
	#include "Socket_UDP_windows.h"

	Socket_UDP_windows::Socket_UDP_windows(unsigned int port)
	{
		PORT = port;
		clientAddrLen = sizeof(SOCKADDR_IN);
	};

	Socket_UDP_windows::~Socket_UDP_windows()
	{};

	void Socket_UDP_windows::ServerStarten(void)
	{
//		system("cls");
		cout << "Unity Game Server - Copyright © CJ 2011-2013 - Windows Version" << endl;
		startWinsock();
		erstelleSocket();
		bindeSocket();
		cout << "Server bereit." << endl << endl;
	};

	void Socket_UDP_windows::ClientStarten(void)
	{
//		system("cls");
		cout << "Test Client - Copyright © CJ 2011-2013 - Windows Version" << endl;
		startWinsock();
		erstelleSocket();
		cout << "Client bereit." << endl << endl;
	};

	void Socket_UDP_windows::startWinsock(void)
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

	void Socket_UDP_windows::erstelleSocket()
	{
		//UDP Socket erstellen --> SOCK_DGRAM = UDP
		s = socket(AF_INET, SOCK_DGRAM, 0);
		if(s == INVALID_SOCKET)
		{
			cout << "Fehler: Der Socket konnte nicht erstellt werden, fehler code: " << WSAGetLastError() << endl;
		}
		else
		{
			cout << "Socket erstellt" << endl;
		}
	}

	void Socket_UDP_windows::bindeSocket()
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(PORT);
		addr.sin_addr.s_addr = ADDR_ANY;

		rc = bind(s, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));

		if(rc == SOCKET_ERROR)
		{
			cout << "Fehler: bind, fehler code: " << WSAGetLastError() << endl;
			exit(-1);
		}
		else
		{
			cout << "Socket an Port " << PORT << " gebunden" << endl;
		}
	};

	DatenPaket* Socket_UDP_windows::empfangen()
	{
		rc = recvfrom(s, reinterpret_cast<char*>(buf), 1500, 0, (SOCKADDR*)&client, &clientAddrLen);
		if(rc == SOCKET_ERROR)
		{
			cout << "Fehler: recvfrom, fehler code: " << WSAGetLastError() << endl;
		}
		else
		{
			//Offenen Stream vom Client schließen
			buf[rc] = '\0';
			cout << "Empfange " << rc << " Bytes von " << inet_ntoa(client.sin_addr) << ":" << client.sin_port ;

			//Hilfe: Ausgabe des gesamten strings in Byte und Char
			//cout << "\tByteansicht: " ;
			cout << " |" ;
			for(int i = 0; i < rc; i++)
				cout << (int)buf[i] << "|";
			cout << endl;
/*			cout << "\tCharansicht: \"" ;
			for(int i = 0; i < rc; i++)
				cout << buf[i] ;
			cout << "\"" << endl;
*/
		}
		//Im Datenpaket befindet sich der Sender und die Daten:
		return new DatenPaket(client, buf);
	};

	void Socket_UDP_windows::senden(DatenPaket* dp_senden)
	{
		char* carr_zusenden = dp_senden->erzeuge_string();

		//Testausgabe der Länge des zu sendenden Stream (Da Koordinaten '\0' enthalten kann)
//		cout << "DEBUG: dp_senden->uiAnzahlByte:" << dp_senden->uiAnzahlByte << endl;

		rc = sendto(s, carr_zusenden, dp_senden->uiAnzahlByte, 0, (SOCKADDR*)&(dp_senden->Adresse), sizeof(SOCKADDR_IN) );

		if(rc == SOCKET_ERROR)
		{
			//Irgend ein Fehler ist beim Senden aufgetreten, aus sicherheitsgründen wird die Verbindunge beendet:
			cout << "Fehler sendto() an " << inet_ntoa(dp_senden->Adresse.sin_addr) << ":" << dp_senden->Adresse.sin_port << " code: " << WSAGetLastError() << endl;
		}
		else
		{
			cout << inet_ntoa(dp_senden->Adresse.sin_addr) << ":" << dp_senden->Adresse.sin_port <<" gesendet: |" ;
			//ByteAnsicht

			for(int i = 0; i < rc; i++)
				cout << (int)carr_zusenden[i] << "|";
			cout << endl;
/*			cout << "\tCharansicht: \"" ;
			for(int i = 0; i < rc; i++)
				cout << carr_zusenden[i] ;
			cout << "\"" << endl;
*/
			//Speicherplatz des gesendeten carr_zusenden freigeben
			free(carr_zusenden);
		}
	};
#endif