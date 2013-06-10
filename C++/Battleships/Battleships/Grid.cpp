#include "Grid.h"

Grid::Grid()
{
	//startposition festlegen
	this->currentPosition = new Koordinaten( 0, 0 );

	//daten initialisieren
	for( int x = 0; x < 10; x++)
		for( int y = 0; y < 10; y++ )
			this->data[x][y] = 0;

	//Array mit Schiffsadressen leeren
	for( int i = 0; i < GRID_MAX_SHIPS_COUNT; i++ )
		ships[i] = NULL;

//	cout << "New Grid created !" << endl;
}  

//anzeigefunktionen
void Grid::showGrid()
{
	cout << "+-------------+" << endl;
	cout << "| 0123456789 x|" << endl;
	for( int y = 0; y < GRID_MAX_Y; y++)
	{
		cout << "|" << y ;
		for( int x = 0; x < GRID_MAX_X; x++ )
		{
			switch( this->data[x][y] )
			{
				case 0: cout << ' '; break; //leer
				case 1: cout << '+'; break; //aktuelles Feld
				case 2: cout << 'S'; break; //Schiffteil
				case 3: cout << ' '; break; //gesperrter bereich um ein Schiffsteil (hier kann kein weiteres Sciff plaziert werden
				case '-': cout << '-'; break; //für das aktuelle Feld
				case '|': cout << '|'; break; //für das aktuelle Feld
				case 'O': cout << 'O'; break; //Hier hast du etwas getroffen
				case 'X': cout << 'X'; break; //Hier hat dein Gegner was getroffen
				case '#': cout << '#'; break; //Hier wurde hingeschossen
			}
		}
		cout << "  |" << endl;
	}
	cout << "|             |"<< endl;
	cout << "|y            |" << endl;
	cout << "+-------------+" << endl;
}

void Grid::showCurrentPosition()
{
	cout << "Current position: x=" << this->currentPosition->x << "|y=" << this->currentPosition->y << endl;
}

void Grid::showExplanation_GAME()
{
	//für erklärung im Spiel beim Zielen
	cout << "\t+----------------> Grid explanation <-------------+" << endl;
	cout << "\t| O -> you HIT a SHIP on this position !          |" << endl;
	cout << "\t| X -> Your ENEMY hit YOUR SHIP at this position! |" << endl;
	cout << "\t| # -> You or your enemy MISS on that position!   |" << endl;
	cout << "\t+-------------------------------------------------+" << endl;
}

//SET
void Grid::selectRight()
{
	if( this->currentPosition->x == GRID_MAX_X - 1 ) this->currentPosition->x = 0;
	else this->currentPosition->x++;
}

void Grid::selectLeft()
{
	if( this->currentPosition->x == 0 ) this->currentPosition->x = GRID_MAX_X - 1;
	else this->currentPosition->x--;
}

void Grid::selectUp()
{
	if( this->currentPosition->y == 0 ) this->currentPosition->y = GRID_MAX_Y - 1;
	else this->currentPosition->y--;
}

void Grid::selectDown()
{
	if( this->currentPosition->y == GRID_MAX_Y - 1 ) this->currentPosition->y = 0;
	else this->currentPosition->y++;
}

void Grid::updateSelection()
{
	for( int x = 0; x < GRID_MAX_X; x++)
	{
		for( int y = 0; y < GRID_MAX_Y; y++ )
		{
			//Was steht schon im SelectionGrid:
			//Filter: Welche Werte bestehen bleiben sollen
			switch( this->data[x][y] )
			{
				case '#': break;
	
				case 'O': break;

				case 3: break;

				default: 
					if( this->currentPosition->x == x && y < this->currentPosition->y ) this->data[x][y] = '|';
					if( this->currentPosition->y == y && x < this->currentPosition->x) this->data[x][y] = '-';
				break;
			}
		}
	}

	//analog oben:
	//Filter: Welche Werte bestehen bleiben sollen
	switch( this->data[this->currentPosition->x][this->currentPosition->y] )
	{
		case '#': break;

		case 'O': break;

		case 3: break;

		default: 
			this->data[ this->currentPosition->x ][ this->currentPosition->y ] = 1;
		break;
	}
}

void Grid::setShip( int ID, Ship* newShip )
{
	//bevor das Schiff gesetzt wird muss überprüft werden, 
	//ob ein Feld um die Einzelteile frei ist

	this->ships[ID] = newShip;

	//Um das schiff herum einen gesperrten bereich einrichten
	this->makeLockedArea( newShip );
}

void Grid::makeLockedArea( Ship* shipToLock )
{
	int partIndex = 0;
	while( shipToLock->hasNextPart( partIndex ) )
	{
		Koordinaten* partPos = shipToLock->getKoordinatenFromPart( partIndex );
		
		int fromX = partPos->x - 1;
		int fromY = partPos->y - 1;

		int toX = partPos->x + 1;
		int toY = partPos->y + 1;

		//Variablen kontrollieren
		if( fromX < 0 ) fromX = 0;
		if( fromY < 0 ) fromY = 0;
		if( toX >= GRID_MAX_X ) toX = GRID_MAX_X - 1;
		if( toY >= GRID_MAX_Y ) toY = GRID_MAX_Y - 1;

		for( int x = fromX; x <= toX; x++)
		{
			for( int y = fromY; y <= toY; y++)
			{
				this->data[ x ][ y ] = 3;
			}
		}
	
		partIndex++;
	}
}

void Grid::clearLockedArea( Ship* shipToUnlock )
{
	int partIndex = 0;
	while( shipToUnlock->hasNextPart( partIndex ) )
	{
		Koordinaten* partPos = shipToUnlock->getKoordinatenFromPart( partIndex );
		
		int fromX = partPos->x - 1;
		int fromY = partPos->y - 1;

		int toX = partPos->x + 1;
		int toY = partPos->y + 1;

		//Variablen kontrollieren
		if( fromX < 0 ) fromX = 0;
		if( fromY < 0 ) fromY = 0;
		if( toX >= GRID_MAX_X ) toX = GRID_MAX_X - 1;
		if( toY >= GRID_MAX_Y ) toY = GRID_MAX_Y - 1;

		for( int x = fromX; x <= toX; x++)
		{
			for( int y = fromY; y <= toY; y++)
			{
				if( this->data[ x ][ y ] != 2 )
				{
					this->data[ x ][ y ] = 0;
				}
			}
		}
	
		partIndex++;
	}

	//nachdem dieser bereich gereinigt ist, all bereiche der anderen Schiffe nachzeichnen
	//es kann sein, das diese funktion einen gesperrten Bereich eines anderen Schiffes geleert hat
	for( int i = 0; i < GRID_MAX_SHIPS_COUNT; i++)
	{
		//vom "shipToUnlock" den bereich nicht nachzeichnen
		if( shipToUnlock != ships[i] && ships[i] != NULL)
			this->makeLockedArea( ships[i] );
	}
}

//GET
Koordinaten* Grid::getCurrentPosition()
{
	return this->currentPosition;
}

int Grid::getValueAt( Koordinaten* pos )
{
	return this->data[pos->x][pos->y];
}

Ship* Grid::getShipWithID(int ID)
{
	return this->ships[ID];
}

//arbeitsfunktionen
void Grid::clear()
{
	for( int y = 0; y < GRID_MAX_Y; y++)
	{
		for( int x = 0; x < GRID_MAX_X; x++ )
		{
			//für Gamescene: 
			switch( this->data[x][y] )
			{
				case 'O': break;
				case '#': break;
				case 3:	break;
				default: this->data[x][y] = 0; break;
//hier wird irgendwie im selectionGrid nicht die alten schüsse gespeichert
			}
		}
	}
}

void Grid::drawShips()
{
	//gibt es überhaupt etwas zum Zeichnen?
	for( int i = 0; i < GRID_MAX_SHIPS_COUNT; i++ )
	{
		if( this->ships[i] != NULL )
		{
			//Koordinaten aller Teile in das Grid zeichnen
						
			//wurde hier hin geschossen ?
			if( this->data[ ships[i]->getKoordinatenFromHead()->x ][ships[i]->getKoordinatenFromHead()->y] == 'X' )
			{
				//dieses Teil wurde getroffen
				//Der Kopf wurde getroffen XD
			}
			else
			{
				//dieses Teil wurde noch nicht getroffen
				this->data[ ships[i]->getKoordinatenFromHead()->x ][ships[i]->getKoordinatenFromHead()->y] = 2;
			}

			int nextPart = 1;
			while( ships[i]->hasNextPart( nextPart ) )
			{
				//Eintragen
				//wurde hier hin geschossen ?
				if( this->data[ ships[i]->getKoordinatenFromPart(nextPart)->x ][ ships[i]->getKoordinatenFromPart(nextPart)->y ] == 'X' )
				{
					//dieses Teil wurde getroffen
				}
				else
				{
					//dieses Teil wurde noch nicht getroffen
					this->data[ ships[i]->getKoordinatenFromPart(nextPart)->x ][ ships[i]->getKoordinatenFromPart(nextPart)->y ] = 2;
				}
				//nächstes Teil
				nextPart++;
			}
		}
	}
}

void Grid::copy( Grid* gridToCopy )
{
	//PROBLEM: DIE SCHIFFE SIND JETZT NICHT MEHR MITEINANDER VERBUNDEN
	//LÖSUNG: NUR DIE SCHIFFSREERENZEN KOPIEREN UND DANN IMMER WIEDER ZEICHNEN LASSEN

	for( int i = 0; i < GRID_MAX_SHIPS_COUNT; i++ )
	{
		this->ships[i] = gridToCopy->getShipWithID(i);
	}

//TODO: kontrollieren ob von allen Schiffen die Adressen übernommen werden
//		  wenn nicht: neue Schiffe erzeugen -> CopyConstruktor z.B 
//		  Ship::Ship(Ship* shipToCopy);

	/* das zu kopierende Grid leeren: */
	//alten speicher wieder freigeben
	delete [] gridToCopy;
	//neuen pointer zu einem leeren Grid erzeugen
	Grid* newGrid = new Grid();
	//Dereferenzierung: "adresse von"gridToCopy = "adresse von"newGrid
	*gridToCopy = *newGrid;
}

bool Grid::isFieldsFree4Ship( Ship* shipToCheck )
{
	//1. Prüfen ob der Platz für das Schiff reicht
	int shipSize = shipToCheck->partsCount();
	//ist das schiff zu lang
	//ToFix: Länge in abhängigkeit der drehung beachten
	if( shipToCheck->getKoordinatenFromHead()->x + shipSize > GRID_MAX_X )
		return false;

	//2. Für alle Teile dieses Schiffes durchgehen, ob platz ist
	int index = 0;
	while( shipToCheck->hasNextPart( index ) )
	{
		Koordinaten* posToCheck = shipToCheck->getKoordinatenFromPart( index );

		if( !this->checkOneField( posToCheck ) )
			return false;

		index++;
	}
	
	//wenn er bis zum ende durchläuft, gibt es kein Problem
	return true;
}

bool Grid::checkOneField( Koordinaten* posToCheck )
{
	if( this->data[ posToCheck->x ][ posToCheck->y ] == 2 )
	{
		//an dieser Position gibt es schon ein anderes Schiffsteil
		return false;		
	}
	else if( this->data[ posToCheck->x ][ posToCheck->y ] == 3 )
	{
		//zu nah an einem anderen Schiff
		return false;	
	}
	else
	{
		//kein Problem
		return true;
	}
}

//drehung
bool Grid::rotateShip( Ship* shipToRotate )
{
	if( this->canRotate_right( shipToRotate ) )
	{
//		prüfen, ob ein anderes Schiff im bereich ist
		
		this->clearLockedArea( shipToRotate );
		shipToRotate->rotate_right();
		this->makeLockedArea( shipToRotate );
		return true;
	}
	else
		return false;
}

//Diese funktion prüft, ob der PLATZ für dieses Schiff reicht 
bool Grid::canRotate_right( Ship* shipToRotate )
{
	int neededSize = shipToRotate->partsCount() - 1 ; // -1 wegen Kopf
	Koordinaten* ursprung = shipToRotate->getKoordinatenFromHead();
	//Koordinaten vom nächsten Teil holen um anhand dieses die neue Rotation zu bestimmen
	Koordinaten* posToRotate = shipToRotate->getKoordinatenFromPart(1);

	//was für eine Drehung soll ausgeführt werden
	if( posToRotate->x > ursprung->x )
	{
		//HSSS

		//H
		//S
		//S
		//S

		//reicht der Platz ?
		if( ursprung->y + neededSize > GRID_MAX_Y - 1)
			return false;

		//ist ein anderes Schiff im Weg
		
		//vor der kontrolle die eigenen gesperrten Bereich löschen
		this->clearLockedArea( shipToRotate );

		int currentPart = 1;
		//für alle Parts
		while( shipToRotate->hasNextPart( currentPart ) )
		{
			//Koordinaten vergleichen
			Koordinaten* thisPart = shipToRotate->getKoordinatenFromPart( currentPart );

			int currentX = ursprung->x;
			int currentY = ursprung->y + currentPart;

			//ob ein Schiffsteil oder gesperrter Bereich
			if( this->data[ currentX ][ currentY ] == 2 || this->data[ currentX ][ currentY ] == 3 )
			{
				//nach der Kontrolle Bereiche um das zu drehende Schiff sperren
				this->makeLockedArea( shipToRotate );
				return false;
			}

			currentPart++;
		}
	}
	else if( posToRotate->y > ursprung->y )
	{
		//H
		//S
		//S
		//S

		//SSSH
		if( ursprung->x - neededSize < 0 )
			return false;

		//ist ein anderes Schiff im Weg
				
		//vor der kontrolle die eigenen gesperrten Bereich löschen
		this->clearLockedArea( shipToRotate );

		int currentPart = 1;
		//für alle Parts
		while( shipToRotate->hasNextPart( currentPart ) )
		{
			//Koordinaten vergleichen
			Koordinaten* thisPart = shipToRotate->getKoordinatenFromPart( currentPart );

			int currentX = ursprung->x - currentPart;
			int currentY = ursprung->y;

			//ob ein Schiffsteil oder gesperrter Bereich
			if( this->data[ currentX ][ currentY ] == 2 || this->data[ currentX ][ currentY ] == 3 )
			{
				//nach der Kontrolle Bereiche um das zu drehende Schiff sperren
				this->makeLockedArea( shipToRotate );
				return false;
			}

			currentPart++;
		}
	}
	else if( posToRotate->x < ursprung->x )
	{
		//SSSH

		//S
		//S
		//S
		//H
		if( ursprung->y - neededSize < 0 )
			return false;

		//ist ein anderes Schiff im Weg
				
		//vor der kontrolle die eigenen gesperrten Bereich löschen
		this->clearLockedArea( shipToRotate );

		int currentPart = 1;
		//für alle Parts
		while( shipToRotate->hasNextPart( currentPart ) )
		{
			//Koordinaten vergleichen
			Koordinaten* thisPart = shipToRotate->getKoordinatenFromPart( currentPart );

			int currentX = ursprung->x;
			int currentY = ursprung->y - currentPart;

			//ob ein Schiffsteil oder gesperrter Bereich
			if( this->data[ currentX ][ currentY ] == 2 || this->data[ currentX ][ currentY ] == 3 )
			{
				//nach der Kontrolle Bereiche um das zu drehende Schiff sperren
				this->makeLockedArea( shipToRotate );
				return false;
			}

			currentPart++;
		}
	}
	else
	{
		//S
		//S
		//S
		//H

		//HSSS
		if( ursprung->x + neededSize - 1 > GRID_MAX_X )
			return false;

		//ist ein anderes Schiff im Weg
				
		//vor der kontrolle die eigenen gesperrten Bereich löschen
		this->clearLockedArea( shipToRotate );

		int currentPart = 1;
		//für alle Parts
		while( shipToRotate->hasNextPart( currentPart ) )
		{
			//Koordinaten vergleichen
			Koordinaten* thisPart = shipToRotate->getKoordinatenFromPart( currentPart );

			int currentX = ursprung->x + currentPart;
			int currentY = ursprung->y;

			//ob ein Schiffsteil oder gesperrter Bereich
			if( this->data[ currentX ][ currentY ] == 2 || this->data[ currentX ][ currentY ] == 3 )
			{
				//nach der Kontrolle Bereiche um das zu drehende Schiff sperren
				this->makeLockedArea( shipToRotate );
				return false;
			}

			currentPart++;
		}
	}
	//nach der Kontrolle Bereiche um das zu drehende Schiff sperren
	this->makeLockedArea( shipToRotate );
	return true;
}


//Game funktionen
bool Grid::fireToGrid( Grid* targetGrid )
{
	//Schiffe im Grid zeichnen
	targetGrid->drawShips();

	if( targetGrid->getValueAt( this->currentPosition ) == 2 )
	{
		//Treffer!
		//Hier wurde was getroffen im SelectionGrid markieren
		this->data[ currentPosition->x ][ currentPosition->y ] = 'O';
		//Treffer beim targetGrid
		targetGrid->gotHitOnPosition( this->currentPosition );
		return true;
	}
	else
	{
		//Hier wurde nichts getroffen im SelectionGrid markieren
		this->data[ currentPosition->x ][ currentPosition->y ] = '#';
		//Miss beim targetGrid
		targetGrid->gotMissOnPosition( this->currentPosition );
		return false;
	}
}

void Grid::gotHitOnPosition(Koordinaten* hit)
{
	this->data[ hit->x ][ hit->y ] = 'X';
	//FEEDBACK XD
	cout << "\a";
	
	/* Anmerkung: Umständlicher Weg, dises funktionen könnten später hilfreich sein */
	//Herausfinden welches Schiff getroffen wurde und parts markieren
	Ship* hittingShip = this->getShipOnPosition( hit );
	//In diesen Schiff den part mit den Koordinaten "hit" als getroffen markieren
	hittingShip->hitPartWithPos( hit );

	if( hittingShip->isShipDead() )
		cout << "\a\aShip sunk\a\a!" << endl;
}

//bei verwendung: Prüfen auf > NULL
//Geht auch alle parts durch
Ship* Grid::getShipOnPosition( Koordinaten* pos )
{
	for( int i = 0; i < GRID_MAX_SHIPS_COUNT; i++)
	{
		Ship* currentShip = this->getShipWithID(i);

		//prüfen auf NULL pointer
		if( currentShip != NULL )
		{
			int partIndex = 0;
			while( currentShip->hasNextPart( partIndex ) )
			{
				Koordinaten* posCurrentShipPart = currentShip->getKoordinatenFromPart( partIndex );
				
				if( posCurrentShipPart->Equals( pos ) )
					return currentShip;

				partIndex++;
			}
		}
	}

	return NULL;
}

void Grid::gotMissOnPosition( Koordinaten* miss )
{
	this->data[ miss->x ][ miss->y ] = '#';
}
