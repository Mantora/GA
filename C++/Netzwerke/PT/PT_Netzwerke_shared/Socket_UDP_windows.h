#ifdef _WIN32
	#pragma once

	#include <iostream>
	#include <winsock2.h>

	#include "DatenPaket.h"

	using namespace std;

	#define DEBUG false

	class Socket_UDP_windows
	{
		private:
			bool isServer;
			bool isClient;

			//Variablen f�r den Socket:
			int PORT;

			long rc; //recall; anzahl der empfangen Bytes
			SOCKET s;
			unsigned char buf[1500];
			SOCKADDR_IN addr;

			SOCKADDR_IN client; //Als Server: Das ist der Sender
			SOCKADDR_IN addr_server; //Als Client: Das ist ZielServer
			int clientAddrLen;

			unsigned long totalBytesSend;

			int volumenTimer; // in MSec
		public:
			Socket_UDP_windows();
			~Socket_UDP_windows();

			//windows UDP als server starten( an port binden )
			void ServerStarten( unsigned int port );
			//windows UDP als client starten (ziel/server als paramter)
			void ClientVerbinden( char* cp_IP_Host ,u_short us_Port_Host );

			//Socket Setup funktionen
			void startWinsock();
			void erstelleSocket();
			void bindeSocket();

			DatenPaket* empfangen();

			void senden(DatenPaket* dp_senden);

			//DEBUG funktion
			void zeigeVerbindungen();
			void updateVolumeTimer( int updateRateinMSec );
			int getTotalBytesSend();
			int currentVolumenTimer;
			void resetTotalBytesSend();
	};
#endif