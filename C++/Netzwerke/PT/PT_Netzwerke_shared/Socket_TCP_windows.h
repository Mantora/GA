#ifdef _WIN32
	#include <iostream>
	#include <winsock2.h>

	#include "DatenPaket.h"
	#include "ThreadData.h"

	using namespace std;

	#define DEBUG false

	class Socket_TCP_windows
	{
		private:
			bool isServer;
			bool isClient;

			//Variablen für den Socket:
			int PORT;

			long rc; //recall; anzahl der empfangen Bytes
			SOCKET s;
//			SOCKET connectedSocket
			unsigned char buf[1500];
			SOCKADDR_IN addr;

			SOCKADDR_IN client; //Als Server: Das ist der Sender
			SOCKADDR_IN addr_server; //Als Client: Das ist ZielServer
			int clientAddrLen;

		public:
			Socket_TCP_windows();
			~Socket_TCP_windows();

			//windows UDP als server starten( an port binden )
			void ServerStarten( unsigned int port );
			//windows UDP als client starten (ziel/server als paramter)
			void ClientVerbinden( char* cp_IP_Host, u_short us_Port_Host );

			//Socket Setup funktionen
			void startWinsock();
			void erstelleSocket();
			void bindeSocket();

			SOCKET wait4Client();
//			DatenPaket* empfangen( SOCKET connectedSocket );

			void senden( SOCKET connectedSocket, DatenPaket* dp_senden );
	};

#endif