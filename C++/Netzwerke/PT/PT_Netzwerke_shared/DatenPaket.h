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

#include "Koordinaten.h"

using namespace std;

//VON client AN server (abstimmen mit C# client)
enum CLIENT_STATUS
{
	CL_LOGOUT = 0,				//Client meldet sich vom Server Ab
	CL_ONLINE = 1,				//Client überprüft, ob der Server erreichbar ist
	CL_LOGIN = 2,				//Client meldet sich beim Server An
	CL_CHAT = 3,				//Client schickt eine Chatnachricht
	CL_BEWEGUNG = 4,			//Client schickt seine Bewegungsdaten
	CL_INITIALISIERUNG = 5		//Client fordert ein Initialisierungsdatenpaket an, dieses wird beim LOGIN ausgelöst
};

//VON server AN client
enum SERVER_STATUS
{
	SV_ONLINE = 1,			//Server ist online
	SV_LOGIN = 2,			//Login erfolgreich
	SV_CHAT = 3,			//Chatnachricht an alle Clients
	SV_BEWEGUNG = 4,		//Bewegungsdaten an alle Clients, außer dem aktuellen
	SV_INITIALISIERUNG = 5,	//Initialisierungsdatenpaket an den aktuellen Client
	SV_ACTION = 6,			//Befehl an den Client schicken: Unterteilung

	//vorläufig
	SV_VOLL = 123		//Kein Platz mehr frei
};

//Befehl an Client senden (abstimmen mit C# dll - enum SERVER_ACTION )
enum CLIENT_ACTION
{
	CA_NEUER_BENUTZER = 1,		// für Chat, anzahl aktualisieren
	CA_BENUTZER_GEGANGEN = 2,	// für Chat, anzahl aktualisieren
	CA_SPIELER_SPAWN = 3		// Spawnposition des aktuellen spielers
};

class DatenPaket
{
	public:
		/* Variablen */
		bool b_istServer; //Wichtig beim Switch zum erzeugen des char[]
		CLIENT_STATUS C_TYP;
		SERVER_STATUS S_TYP;
		CLIENT_ACTION BEFEHL;
		int ID;
		unsigned char* daten_1;
		unsigned char* daten_2;
		const unsigned char* str_chat;

		Koordinaten* position;

		//Anzahl der Byte des erzeugtem String
		unsigned int uiAnzahlByte;

		//Verbindungsinformationen:
		sockaddr_in Adresse;

		/* Funktionen */
		DatenPaket();
		DatenPaket(SERVER_STATUS status);
		DatenPaket(sockaddr_in von,unsigned char* was);
		~DatenPaket();
		void anzeigen();
		char* erzeuge_string();
};
