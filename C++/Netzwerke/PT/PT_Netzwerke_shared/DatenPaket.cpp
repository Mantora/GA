#include "DatenPaket.h"

DatenPaket::DatenPaket()
{

}

DatenPaket::DatenPaket( PT_NETZWERKE_DATENPAKET_TYP type)
{
	this->type = type;

	daten_1 = NULL;
	daten_2 = NULL;
};

DatenPaket::DatenPaket(sockaddr_in von, unsigned char* datenstream)
{
	//Adresse übergeben
	this->Adresse = von;

	type = (PT_NETZWERKE_DATENPAKET_TYP)datenstream[0];
	switch( type )
	{
		case PT_ONLINE:
		{
			//leer
		}
		break;

		case PT_LOGIN:
		{
			//name
			int iCountDaten1 = datenstream[1];
			int iCountDaten2 = datenstream[1+iCountDaten1];
			daten_1 = &datenstream[2];
			datenstream[1+iCountDaten1] = 0;

			//password
			daten_2 = &datenstream[1+1+iCountDaten1];
		}
		break;

		case PT_TERMINAL_CLOSE:
		{
			int* tmp = (int*)(&datenstream[1]);
			this->spaceCount = *tmp;

			int* tmp2 = (int*)(&datenstream[1+4]);
			this->playerID = *tmp2;
			//unsigned char* c = (unsigned char*)(&f);
		}
		break;

		case PT_LOGIN_RESPONS:
		{
			int* tmp = (int*)(&datenstream[1]);
			this->playerID = *tmp;
		}
		break;

		default:
		{
			cout << "Fehler bei \"DatenPaket::DatenPaket(sockaddr_in von, unsigned char* datenstream)\" :" << endl;
			cout << "Implementation von PT_NETZWERKE_DATENPAKET_TYP(" << this->type << ") fehlt, abbruch." << endl;
			system("pause");
			exit(1);
		}
		break;
	}
};

DatenPaket::~DatenPaket()
{

};

void DatenPaket::anzeigen()
{	
	cout << "Datenpaket anzeigen von Adresse :" << inet_ntoa(Adresse.sin_addr) << ":" << Adresse.sin_port << endl;

	switch( this->type )
	{
		case PT_ONLINE:
		{
			cout << " PT_ONLINE" << endl;
		}
		break;

		case PT_LOGIN:
		{
			cout << " PT_LOGIN" << endl;
			cout << "  daten_1:" << this->daten_1 << endl;
			cout << "  daten_2:" << this->daten_2 << endl;
		}
		break;

		case PT_LOGIN_RESPONS:
		{
			cout << " PT_LOGIN_RESPONS" << endl;
			cout << "  ID:" << this->playerID;
		}
		break;

		case PT_TERMINAL_CLOSE:
		{
			cout << " PT_TERMINAL_CLOSE" << endl;
			cout << "  ID:" << this->playerID;
			cout << "  spaceCount:" << this->spaceCount;
		}
		break;

		default:
		{
			cout << "Fehler bei \"DatenPaket::anzeigen()\" :" << endl;
			cout << "Implementation von PT_NETZWERKE_DATENPAKET_TYP(" << this->type << ") fehlt, abbruch." << endl;
			system("pause");
			exit(1);
		}
	}

	cout << endl;
};

//Funktion zum erzeugen des Strings
char* DatenPaket::erzeuge_string()
{
	//Lokale Variable um strcpy und strcat nutzen zu können:
	//Erstes zeichen reinkopieren
	char tmp[1400] = { this->type };

	switch( this->type )
	{
		case PT_INVAILED:
		{
			uiAnzahlByte = 1;
		}
		break;

		case PT_ONLINE:
		{
			uiAnzahlByte = 1;
		}
		break;

		case PT_LOGIN:
		{
			uiAnzahlByte = 1;
			uiAnzahlByte += strlen( (char*)this->daten_1 )+1;
			uiAnzahlByte += strlen( (char*)this->daten_2 )+1;

			int iCountDaten1 = strlen( (char*)this->daten_1 )+1;
			tmp[1] = iCountDaten1;
			strcat( tmp, (char*)this->daten_1 );

			int iCountDaten2 = strlen( (char*)this->daten_2 )+1;
			tmp[1+iCountDaten1] = iCountDaten2;
			strcat( tmp, (char*)this->daten_2 );

			if( DEBUG )
				cout << tmp << endl;
		}
		break;

		case PT_LOGIN_RESPONS:
		{
			uiAnzahlByte = 1+4;

			unsigned char* c = (unsigned char*)(&this->playerID);
			strcat( tmp, (char*)c );
		}
		break;

		case PT_TERMINAL_CLOSE:
		{
			uiAnzahlByte = 1+4+4;
	
			unsigned char* c = (unsigned char*)(&this->spaceCount);
			for( int i = 0; i < sizeof(int); i++ )
				tmp[i+1] = c[i];


			unsigned char* c2 = (unsigned char*)(&this->playerID);
			
			for( int i = 0; i < sizeof(int); i++ )
				tmp[i+5] = c2[i];
			//TestAusgabe
/*			cout << endl;
			for( int i = 0; i < uiAnzahlByte; i++)
			{
				cout << (int)tmp[i] << "|";
			}
			cout << endl;
*/		
		}
		break;

		default:
		{
			cout << "Fehler bei \"DatenPaket::erzeuge_string()\" :" << endl;
			cout << "Implementation von PT_NETZWERKE_DATENPAKET_TYP(" << this->type << ") fehlt, abbruch." << endl;
			system("pause");
			exit(1);
		}
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
