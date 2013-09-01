#include "DatenPaket.h"

DatenPaket::DatenPaket()
{

}

DatenPaket::DatenPaket( SERVER_STATUS status)
{
	this->S_TYP = status;
	//Ist vom Server
	this->b_istServer = true;
//	daten_1 = "";
//	daten_2 = "";
	str_chat = NULL;
	//	cout << "Vorbereitets Datenpaket angelegt" << endl;
};

DatenPaket::DatenPaket(sockaddr_in von, unsigned char* datenstream)
{
	//Ist vom Client
	b_istServer = false;

	//Adresse übergeben
	this->Adresse = von;

	C_TYP = (CLIENT_STATUS)datenstream[0];
	switch( C_TYP )
	{
		case CL_LOGIN:
		{
			//Ab Position 1 (012345...) steht der name
			//Anfangsadresse zuweisen da am ende \n
			daten_1 = &datenstream[1];
			//an position 2+strlen(daten_1) das password
			//dp_empfangen->daten_2 = &buf[2+strlen(dp_empfangen->daten_1)];
		}
		break;

		case CL_ONLINE:
		{
			//An Position [1] steht die ID des Clients:
			ID = datenstream[1];
		}
		break;

		case CL_INITIALISIERUNG:
		{
			//An Position [1] steht die ID des Clients:
			ID = datenstream[1];
		}
		break;

		case CL_LOGOUT:
		{
			//An Position [1] steht die ID des Clients:
			ID = datenstream[1];
		}
		break;

		case CL_CHAT: 
		{
			//Ab Position 1 (012) befindet sich die komplette Nachricht
			str_chat = &datenstream[1];
		}
		break;

		case CL_BEWEGUNG:
		{
			//ID des bewegten spielers
			this->ID = datenstream[1];
			//seine Koordinaten
			position = new Koordinaten( &datenstream[2] );
		}
		break;
	}
};

DatenPaket::~DatenPaket()
{
//	cout << "Datenpaket verworfen" << endl;
};

void DatenPaket::anzeigen()
{	
	if( this->b_istServer )
	{
		cout << "Datenpaket vom Server:" << endl;
//		cout << "\tAn Adresse " << inet_ntoa(Adresse.sin_addr) << ":" << Adresse.sin_port << endl;
		cout << "\tS_TYP: ";
		switch( this->S_TYP )
		{
			case SV_ONLINE: cout << "\tSV_ONLINE" << endl; break;

			case SV_LOGIN:
				cout << "\tSV_LOGIN" << endl;
				cout << "\t\tID: " << (int)this->daten_1[0] << endl;
			break;

			case SV_CHAT: cout << "\tSV_CHAT" << endl; break;

			case SV_BEWEGUNG: 
				cout << "\tSV_BEWEGUNG" << endl;
				cout << "\t\tID:" << ID << endl;
				this->position->anzeigen(); 
			break;

			case SV_INITIALISIERUNG: 
				cout << "\tSV_INITIALISIERUNG" << endl; 
				cout << "\t\tAnzahl Benutzer:" << (int)this->daten_1[0] << endl;
//Bei Initialisierungsdatenpaket Koordinaten aller verbundenen Spieler anzeigen die in daten_1 stehen 
				cout << "\t\tID des Empfaengers:" << ID << endl;
				this->position->anzeigen();
			break;

			case SV_ACTION: cout << "\tSV_ACTION" ;
				switch( this->BEFEHL )
				{
					case CA_NEUER_BENUTZER: 
						cout << " : CA_NEUER_BENUTZER" << endl;
						cout << "\t\tID: " << (int)this->daten_1[1] << endl;
						cout << "\t\tName: " << this->daten_2 << endl;
						this->position->anzeigen();
					break;

					case CA_BENUTZER_GEGANGEN:
						cout << " : CA_BENUTZER_GEGANGEN" << endl;
						cout << "\t\tName:" << this->daten_2 << endl;
						cout << "\t\tID:" << this->ID << endl;
					break;

					case CA_SPIELER_SPAWN: 
						cout << " : CA_SPIELER_SPAWN" << endl; 
						this->position->anzeigen(); 
					break;
				}
			break;
		}
	}
	else
	{
		cout << "Datenpaket vom Client mit Adresse :" << inet_ntoa(Adresse.sin_addr) << ":" << Adresse.sin_port << endl;
		cout << "\tC_TYP: ";
		switch( this->C_TYP )
		{
			case CL_LOGOUT: cout << "\tCL_LOGOUT" << endl; break;
			case CL_ONLINE: cout << "\tCL_ONLINE" << endl; break;
			
			case CL_LOGIN: 
				cout << "\tCL_LOGIN" << endl;
				cout << "\tdaten_1:" << daten_1 << endl; 
			break;

			case CL_CHAT: 
				cout << "\tCL_CHAT" << endl; 
				cout << "\tstr_chat: \"" << str_chat << "\"" << endl;
			break;

			case CL_BEWEGUNG: 
				cout << "\tCL_BEWEGUNG" << endl; 
				cout << "\t\tID:" << ID << endl;
				this->position->anzeigen();
			break;

			case CL_INITIALISIERUNG:
				cout << "\tCL_INITIALISIERUNG" << endl;
				cout << "\t\tID:" << ID << endl;
			break;
		}
	}		
};

//Funktion zum erzeugen des Strings
char* DatenPaket::erzeuge_string()
{
	//Lokale Variable um strcpy und strcat nutzen zu können:
	//Erstes zeichen reinkopieren
	unsigned char tmp[1400] = { this->S_TYP };

	switch( this->S_TYP )
	{
		case SV_LOGIN:
		{
			/* Client will sich Anmelden: */
			// Benutzer bekommt seine neue ID zugeschickt (wichtig für identifizierung)
			tmp[1] = daten_1[0];

			tmp[2] = '\0';
			uiAnzahlByte = strlen((char*)tmp)+1;
		}
		break;

		case SV_ONLINE:
		{
			/* Server ist online */
			// Nichts unternehmen, da tmp[0] = '1';
			tmp[1] = '\0';
			uiAnzahlByte = strlen((char*)tmp);
		}
		break;

		case SV_CHAT:
		{
			strncat((char*)tmp, (char*)str_chat, strlen((char*)str_chat)+1);
			uiAnzahlByte = strlen((char*)tmp);
		}
		break;

		case SV_BEWEGUNG:
		{
			//ID des bewegenden Spielers
			tmp[1] = ID;
			this->position->codieren( tmp, 2 );

			uiAnzahlByte = 13;
		}
		break;

		case SV_INITIALISIERUNG:
		{
			/* Nach dem Login wird dieses Paket angefordert: */
			/* Aufbau:
			[0]			5
			[1]			{aktuelle ID}
			[2]			{i_verbundeneClients}
			[3..12]		{koordinaten}

			[13]		{ID_Benutzer1}
			[14..23]	{koordinaten Benutzer1}

			[24]		{ID_Benutzer2}
			[25..34]	{koordinaten Benutzer2}

			usw.
			*/
			//ID des spielers
			tmp[1] = this->ID;
			//Anzahl verbindungen
			tmp[2] = this->daten_1[0]; 
			//Spawnposition hinzufügen
			this->position->codieren( tmp, 3 );

			//ID und Koordinaten der bereits verbunden Spieler kopieren:
			int anzahl = (tmp[2]*10);
			for(int i = 0; i < anzahl; i++)
			{
				tmp[13+i] = this->daten_1[1+i];
			}

			//Anzahl der Gesamtbyte berechnen
			uiAnzahlByte = 13;
			uiAnzahlByte += ((tmp[2]-1)*11);
		}
		break;

		case SV_ACTION:
		{
			//Befehl steht an position 2
			tmp[1] = BEFEHL;
			//weitere Unterteilung:
			switch( BEFEHL )
			{
				case CA_NEUER_BENUTZER:
				{
					tmp[2] = this->daten_1[0]; //An position 0 steht die anzahl der Verbindungen als byte
					tmp[3] = this->daten_1[1]; //An position 1 steht die ID des Clients
					//Spawnkooardinaten
					this->position->codieren( tmp, 4 ); //von [4] bis [13] Koordinaten
/*Problem: strcat_s hängt nicht an das ende von tmp[] an, da zwischen drin durch die
Koordinaten '0' steht und für ihn dort des Array zuende ist
*/
//Tempräre Lösung für obigen Problem:
					for(unsigned int i = 0; i < strlen((char*)this->daten_2); i++)
					{
						tmp[14+i] = this->daten_2[i];
					}
					//strcat_s(tmp, 32, this->daten_2);
					/*	Ergebniss: 
					 *  [0] = 6
					 *	[1] = CA_NEUER_BENUTZER = 1
					 *	[2] = anzahl verbindungen zum Server
					 *  [3...??] = Position
					 *  [??..x] = name des neuen spielers
					 */	
				}
				break;
				
				case CA_BENUTZER_GEGANGEN:
				{
					tmp[2] = this->daten_1[0]; //An position 0 steht die anzahl der Verbindungen als byte
					tmp[3] = this->ID; //An position 1 steht die ID des Clients
//					strcat_s(tmp, 32, this->daten_2);
/*Problem: strcat_s hängt nicht an das ende von tmp[] an, da zwischen drin durch die
Koordinaten '0' steht und für ihn dort des Array zuende ist
*/
//Tempräre Lösung für obigen Problem:
					for(unsigned int i = 0; i < strlen((char*)this->daten_2); i++)
					{
						tmp[4+i] = this->daten_2[i];
					}
					/*	Ergebniss: 
					 *  [0] = 6
					 *	[1] = CA_BENUTZER_GEGANGEN = 2
					 *	[2] = anzahl verbindungen zum Server
					 *  [3]...[x] = name des gegangenen spielers
					 */	
				}
				break;
			}
		}
		break;
	}

	//Bestimmung der länge notwendig, da Koordinaten '\0' beinhalten kann
	switch( tmp[0] )
	{

		case SV_ACTION:
			switch( tmp[1] )
			{
				case CA_NEUER_BENUTZER: uiAnzahlByte = (14 + strlen((char*)daten_2)); break;
				case CA_BENUTZER_GEGANGEN: uiAnzahlByte = (4 + strlen((char*)daten_2)); break;
			}
		break;
//		default: uiAnzahlByte = strlen(tmp); break;
	}

	//Speicherplatz allokieren für return
	char* cptr = (char*)malloc(1400);
//	strncpy(cptr, tmp, uiAnzahlByte+1);

	for(unsigned int i = 0; i < uiAnzahlByte; i++)
	{
		cptr[i] = tmp[i];
	}

	return cptr;
};
