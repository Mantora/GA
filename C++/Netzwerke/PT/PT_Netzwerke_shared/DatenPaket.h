#pragma once

/*Compiler-Weiche f�r OS*/
#ifdef _WIN32 //Windows Header
	#include <winsock2.h>
#else //Linux Header
	#include <sys/types.h>
	#include <sys/socket.h>

	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
#endif

class DatenPaket
{
	public:
		DatenPaket( const DatenPaket& other ); //copykonstruktor
		DatenPaket( unsigned char* datenstream, unsigned int bytes ); //f�r ausgehende Daten
		DatenPaket( sockaddr_in von, unsigned char* datenstream, unsigned int bytes ); //f�r ankommende Daten
		~DatenPaket( void );

		//Anzahl der Byte des erzeugtem String
		unsigned int uiAnzahlByte;
		//die gesendeten/empfangenen Daten
		unsigned char* buffer;

		//Verbindungsinformationen:
		sockaddr_in Adresse;
};
