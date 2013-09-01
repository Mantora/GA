/*
Klasse zum anlegen eines Datenpaketes zum Senden.
Standart C untersützt keinen Datentyp "byte". Lösung: char(0-255)
*/
#include <iostream>

/*Compiler-Weiche für OS*/
#ifdef _WIN32 //Windows Header
	#include <winsock2.h>
#else //Linux Header
	#include <sys/types.h>
	#include <sys/socket.h>

	#include <netinet/in.h>
	#include <netdb.h>
	#include <arpa/inet.h>
#endif

using namespace std;

#define DEBUG true

//enum zur einteilung der Datenpaket für PT
enum PT_NETZWERKE_DATENPAKET_TYP
{
	PT_INVAILED = -1,

	PT_ONLINE		= 0 ,	//prüfen, ob server online ist
	PT_LOGIN			,	//client meldet sich an
	PT_LOGIN_RESPONS	,	//client anmeldung erfolgreich
	PT_TERMINAL_CLOSE	,	//client hat das terminal geschlossen

	PT_COUNT
};

class DatenPaket
{
	public:
		/* Variablen */
		PT_NETZWERKE_DATENPAKET_TYP type;

		int spaceCount;
		unsigned char* daten_1;
		unsigned char* daten_2;

		//Anzahl der Byte des erzeugtem String
		unsigned int uiAnzahlByte;

		//Verbindungsinformationen:
		sockaddr_in Adresse;

		/* Funktionen */
		DatenPaket();
		DatenPaket(PT_NETZWERKE_DATENPAKET_TYP DATENPAKET_TYP);
		DatenPaket(sockaddr_in von, unsigned char* datenstream); //server: für ankommende daten

		~DatenPaket();

		char* erzeuge_string();

		//DEBUG funktion
		void anzeigen();
};
