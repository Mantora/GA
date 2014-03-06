#ifdef __unix__
	#pragma once

	#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
	#include <iostream>
	#include <cstring> //memset

	#include <cerrno>
	//c++ für "cout << strerror(errno) << endl;"
	//analog c
	//#include <errno.h>

	#include <sys/types.h>
	#include <sys/socket.h>

	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <unistd.h>

	#include "DatenPaket.h"

	using namespace std;

	#define DEBUG false

	class Socket_UDP_linux
	{
		private:
			bool isServer;
			bool isClient;

			//Variablen für den Socket:
			int PORT;

			int rc; //recall; anzahl der empfangen Bytes
			int s; //Socketnummer (Deskriptor)
			unsigned char buf[1500];
			sockaddr_in addr;

			sockaddr_in client; //Als Server: Das ist der Sender
			sockaddr_in addr_server; //Als Client: Das ist ZielServer
			int clientAddrLen;

			unsigned long totalBytesSend;

			int volumenTimer; // in MSec
			int currentVolumenTimer;
			int getTotalBytesSend();
			void resetTotalBytesSend();
		public:
			/* Konstruktor */
			Socket_UDP_linux();
			~Socket_UDP_linux();

			//linux UDP als server starten( an port binden )
			void ServerStarten( unsigned int port );
			//linux UDP als client starten (ziel/server als paramter)
			void ClientVerbinden( const char* cp_IP_Host ,u_short us_Port_Host );
			//linux UDP Client verbindung zum server trennen
			void ClientTrennen();

			//Socket Setup funktionen
			void startWinsock();
			void erstelleSocket();
			void bindeSocket();

			DatenPaket* empfangen();

			void senden(DatenPaket* dp_senden);

			void zeigeVerbindungen();
			void updateVolumeTimer( int updateRateinMSec );
	};
#endif
