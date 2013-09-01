/* Klasse zum verwalten der Positionskoordinaten
 * Beinhaltet:
 * - Verschlüsseln, Entschlüsseln, anzeigen
 */

#include <iostream>

using namespace std;

class Koordinaten
{
	public:
		// Variablen
		float x,y,z;	// Koordinaten
		float o;		// Orientierung (Blickrichtung)

		// Konsturktor
		Koordinaten(float x, float y, float z);
		Koordinaten(unsigned char* stream);
		Koordinaten(Koordinaten* pos);

		//Funktionen
		void anzeigen();
		void codieren(unsigned char* stream, int anfang);
		float decodieren(unsigned char* stream);
};
