#ifdef _WIN32
	#include <iostream>
	#include <winsock2.h>

	#include "DatenPaket.h"

	using namespace std;

	class Socket_UDP_windows
	{
		private:
			//Variablen für den Socket:
			int PORT;

			long rc; //recall; anzahl der empfangen Bytes
			SOCKET s;
			unsigned char buf[1500];
			SOCKADDR_IN addr;

			SOCKADDR_IN client; //Das ist der Sender
			int clientAddrLen;

		public:
			Socket_UDP_windows(unsigned int port);
			~Socket_UDP_windows();

			void ServerStarten(void);
			void ClientStarten(void);
			void startWinsock(void);
			void erstelleSocket(void);
			void bindeSocket(void);

			DatenPaket* empfangen();

			void senden(DatenPaket* dp_senden);

			void zeigeVerbindungen();
	};
#endif