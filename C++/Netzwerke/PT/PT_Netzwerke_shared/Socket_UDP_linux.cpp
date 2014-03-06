#ifdef __unix__
	#include "Socket_UDP_linux.h"

	Socket_UDP_linux::Socket_UDP_linux()
	{
		clientAddrLen = sizeof(sockaddr_in);
		this->volumenTimer = 1000;
		this->currentVolumenTimer = this->volumenTimer;
	};

	Socket_UDP_linux::~Socket_UDP_linux()
	{};

	void Socket_UDP_linux::ServerStarten( unsigned int port )
	{
		this->resetTotalBytesSend();

		isServer = true;
		isClient = false;

		PORT = port;

//		system("clear");
//		cout << "Unity Game Server - Copyright © CJ 2011-2013 - Linux Version" << endl;
		erstelleSocket();
		bindeSocket();
	};

	void Socket_UDP_linux::ClientVerbinden( const char* cp_IP_Host, u_short us_Port_Host )
	{
		isServer = false;
		isClient = true;

//		system("cls");
//		cout << "Test Client - Copyright © CJ 2011-2013 - Linux Version" << endl;
		erstelleSocket();

		addr.sin_family = AF_INET; // IPv4-Adresse
		addr.sin_port = htons(us_Port_Host); //Portnummer
		addr.sin_addr.s_addr = inet_addr(cp_IP_Host); 

//		cout << "Client bereit." << endl << endl;
	};

	void Socket_UDP_linux::ClientTrennen()
	{
		isServer = false;
		isClient = false;

		close( this->s );
	};

	void Socket_UDP_linux::erstelleSocket()
	{
		//zuweisung von leerem Speicher
		memset( &addr, 0, sizeof(addr));

		//UDP Socket erstellen --> SOCK_DGRAM = UDP
		s = socket( AF_INET, SOCK_DGRAM, 0);
		if(s < 0)
		{
			cout << "Fehler beim Anlegen eines Sockets: "<< strerror(errno) << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
//			cout << "Socket erstellt" << endl;

		}
	};

	void Socket_UDP_linux::bindeSocket()
	{
		addr.sin_family = AF_INET; // IPv4-Adresse
		addr.sin_port = htons(PORT);  //Portnummer
		addr.sin_addr.s_addr = htonl(INADDR_ANY);  // Jede IP-Adresse ist gültig

		rc = bind( s, (sockaddr*)&addr, sizeof(sockaddr_in));
		if( rc < 0 )
		{
			cout << "Fehler bei bind(): " << strerror(errno) << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
//			cout << "Socket an Port " << PORT << " gebunden" << endl;
		}
	};

	DatenPaket* Socket_UDP_linux::empfangen()
	{
		rc = recvfrom(s, reinterpret_cast<char*>(buf), 1500, 0, (sockaddr*)&client, (socklen_t *)&clientAddrLen);
		if(rc == -1)
		{
			cout << "Fehler bei recvfrom: " << strerror(errno) << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			//Offenen Stream vom Client schließen
			buf[rc] = '\0';
			if( DEBUG )
			{
				cout << "Empfange " << rc << " Bytes von " << inet_ntoa(client.sin_addr) << ":" << client.sin_port << " " ;

				cout << "Index:       |" ;
				for( int i = 0; i < rc; i++)
				{
					cout.width(3);
					cout << i << "|";
				}
				cout << endl;

				cout << "Byteansicht: |" ;
				for( int i = 0; i < rc; i++)
				{
					cout.width(3);
					cout << (int)buf[i] << "|";
				}
				cout << endl;

				cout << "Charansicht: |" ;
				for( int i = 0; i < rc; i++)
				{
					cout.width(3);
					cout << buf[i] << "|";
				}
				cout << endl;
			}
		}
		//Im Datenpaket befindet sich der Sender und die Daten:
		return new DatenPaket(client, buf, rc);
	};

	void Socket_UDP_linux::senden(DatenPaket* dp_senden)
	{
		char* carr_zusenden = (char*)dp_senden->buffer;

		if( this->isClient )
		{
			dp_senden->Adresse = this->addr_server;
		}

		//Testausgabe der Länge des zu sendenden Stream (Da Koordinaten '\0' enthalten kann)
//		cout << "DEBUG: dp_senden->uiAnzahlByte:" << dp_senden->uiAnzahlByte << endl;

		rc = sendto(s, carr_zusenden, dp_senden->uiAnzahlByte, 0, (sockaddr*)&(dp_senden->Adresse), sizeof(sockaddr_in) ); 

		if(rc == -1)
		{
			//Irgend ein Fehler ist beim Senden aufgetreten, aus sicherheitsgründen wird die Verbindunge beendet:
			cout << "Fehler beim senden an " << inet_ntoa(dp_senden->Adresse.sin_addr) << ":" << dp_senden->Adresse.sin_port << " code: " << strerror(errno) << endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			this->totalBytesSend += rc;
			if( DEBUG )
			{
				cout << "Gesendet " << rc << " bytes an " << inet_ntoa(dp_senden->Adresse.sin_addr) << ":" << dp_senden->Adresse.sin_port << endl;
				
				cout << "Index:       |" ;
				for( int i = 0; i < rc; i++)
				{
					cout.width(3);
					cout << i << "|";
				}
				cout << endl;

				cout << "Byteansicht: |" ;
				for(int i = 0; i < rc; i++)
				{
					cout.width(3);
					cout << (int)carr_zusenden[i] << "|";
				}
				cout << endl;

				cout << "Charansicht: |" ;
				for(int i = 0; i < rc; i++)
				{
					cout.width(3);
					cout << carr_zusenden[i] << "|";
				}
				cout << endl << endl;
			}

			//Speicherplatz des gesendeten carr_zusenden freigeben
			free(carr_zusenden);
		}
	};

	int Socket_UDP_linux::getTotalBytesSend()
	{
		return this->totalBytesSend;
	};

	void Socket_UDP_linux::resetTotalBytesSend()
	{
		this->totalBytesSend = 0;
	};

	void Socket_UDP_linux::updateVolumeTimer( int updateRateinMSec )
	{
		this->currentVolumenTimer -= updateRateinMSec;

		if( this->currentVolumenTimer <= 0 )
		{
			cout << "Bytes send: " << this->getTotalBytesSend() << endl;
			this->resetTotalBytesSend();
			this->currentVolumenTimer = this->volumenTimer;
		}
	};
#endif
