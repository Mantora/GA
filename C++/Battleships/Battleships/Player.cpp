#include "Player.h"

using namespace std;

Player::Player()
{
	//Variablen ordentlich Initialisieren
	this->init();

//	cout << "Name : " ;
	//Name eingeben
	while( strcmp( this->name, "" ) == 0 )
	{
		cin.getline( this->name, sizeof(this->name), '\n');
	}

	//Spieler fertig erstellt
//	cout << "Player \"" << this->name << "\" created !" << endl << endl;
}

void Player::init()
{
	//name leeren
	strcpy( this->name, "");

	//startposition festlegen für auswahl
	this->x = this->y = 0;
	this->currentSelectedShip = 0;

	//Einstellungen
	this->ready = false;
	this->allShipsPlaced = false;

	//Grids erstellen
	this->ShipGrid = new Grid();
	this->SelectionGrid = new Grid();

	//Shiffe erstellen
	//TODO
	this->ship_two1 = NULL;
	this->ship_two2 = NULL;
	this->ship_three = NULL;
	this->ship_four = NULL;
	this->ship_five = NULL;

}

//funktionen zum Anzeigen
void Player::showSelectionGrid()
{
	//alte eingaben leern
	this->SelectionGrid->clear();
	this->SelectionGrid->updateSelection();
	this->SelectionGrid->drawShips();
	//zeige momentane Position ist in clear drin

	/* Eingaben umsetzen */

	//anzeigen
	this->SelectionGrid->showCurrentPosition();
	cout << "HINT: move your cross hairs with the arrow keys." << endl;
	this->SelectionGrid->showGrid();
}

void Player::showShipGrid()
{
	//system("cls");

	//alte eingaben leern
//	this->ShipGrid->clear();
	this->ShipGrid->drawShips();

	//anzeigen
	cout << "Your ship s :" << endl;
	this->ShipGrid->showGrid();
}

//GET
bool Player::isReady() { return this->ready; }
char* Player::getName() { return this->name; }
Grid* Player::getSelectionGrid() { return this->SelectionGrid; }
Grid* Player::getShipGrid() { return this->ShipGrid; }

//SET
void Player::setReady(bool newState) { this->ready = newState; }

//input
void Player::handleInput_setup(int KB_code)
{
	this->updateCurrentSelectedShip();
	switch(KB_code)
	{
		case KB_LEFT: 
			this->SelectionGrid->selectLeft(); 
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		case KB_RIGHT:
			this->SelectionGrid->selectRight();
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		case KB_UP:
			this->SelectionGrid->selectUp();
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		case KB_DOWN:
			this->SelectionGrid->selectDown(); 
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		case KB_ONE:
		{
			Ship* tmp = new Ship( 2, new Koordinaten( this->SelectionGrid->getCurrentPosition()->x, this->SelectionGrid->getCurrentPosition()->y) );

			if( this->SelectionGrid->isFieldsFree4Ship( tmp ) )
			{	
				//alten gesperrten Bereich leeren falls ein Schiff schon gesetzt wurde
				if( this->ship_two1 != NULL )
					this->SelectionGrid->clearLockedArea( this->ship_two1 );

				this->ship_two1 = tmp;
				this->SelectionGrid->setShip( 0, this->ship_two1 );
				this->doFeedback_OK();
			}
			else
			{
				//speicher des temporären schiffes freigeben
				//delete [] tmp;
				//ToDo: Ordentliches Feedback einbauen:
				//"Hier ist kein Platz für dieses Schiff"
				this->doFeedback_ERROR();
				//ToDo: Speicher wieder frei geben 
				//delete [] this->ship_two1;
				//ToFiX: Speicher bleibt allociert
				//this->ship_two1 = NULL;
			}
		}
		break;

		case KB_TWO:
		{
			Ship* tmp = new Ship( 2, new Koordinaten( this->SelectionGrid->getCurrentPosition()->x, this->SelectionGrid->getCurrentPosition()->y) );

			if( this->SelectionGrid->isFieldsFree4Ship( tmp ) )
			{	
				//alten gesperrten Bereich leeren falls ein Schiff schon gesetzt wurde
				if( this->ship_two2 != NULL )
					this->SelectionGrid->clearLockedArea( this->ship_two2 );

				this->ship_two2 = tmp;
				this->SelectionGrid->setShip( 1, this->ship_two2 );
				this->doFeedback_OK();
			}
			else
			{
				//speicher des temporären schiffes freigeben
				//delete [] tmp;
				//ToDo: Ordentliches Feedback einbauen:
				//"Hier ist kein Platz für dieses Schiff"
				this->doFeedback_ERROR();
				//ToDo: Speicher wieder frei geben 
				//delete [] this->ship_two1;
				//ToFiX: Speicher bleibt allociert
				//this->ship_two2 = NULL;
			}
		}
		break;

		case KB_THREE:
		{
			Ship* tmp = new Ship( 3, new Koordinaten( this->SelectionGrid->getCurrentPosition()->x, this->SelectionGrid->getCurrentPosition()->y) );

			if( this->SelectionGrid->isFieldsFree4Ship( tmp ) )
			{	
				//alten gesperrten Bereich leeren falls ein Schiff schon gesetzt wurde
				if( this->ship_three != NULL )
					this->SelectionGrid->clearLockedArea( this->ship_three );

				this->ship_three = tmp;
				this->SelectionGrid->setShip( 2, this->ship_three );
				this->doFeedback_OK();
			}
			else
			{
				//speicher des temporären schiffes freigeben
				//delete [] tmp;
				//ToDo: Ordentliches Feedback einbauen:
				//"Hier ist kein Platz für dieses Schiff"
				this->doFeedback_ERROR();
				//ToDo: Speicher wieder frei geben 
				//delete [] this->ship_two1;
				//ToFiX: Speicher bleibt allociert
				//this->ship_two2 = NULL;
			}
		}
		break;

		case KB_FOUR:
		{
			Ship* tmp = new Ship( 4, new Koordinaten( this->SelectionGrid->getCurrentPosition()->x, this->SelectionGrid->getCurrentPosition()->y) );

			if( this->SelectionGrid->isFieldsFree4Ship( tmp ) )
			{	
				//alten gesperrten Bereich leeren falls ein Schiff schon gesetzt wurde
				if( this->ship_four != NULL )
					this->SelectionGrid->clearLockedArea( this->ship_four );

				this->ship_four = tmp;
				this->SelectionGrid->setShip( 3, this->ship_four );
				this->doFeedback_OK();
			}
			else
			{
				//speicher des temporären schiffes freigeben
				//delete [] tmp;
				//ToDo: Ordentliches Feedback einbauen:
				//"Hier ist kein Platz für dieses Schiff"
				this->doFeedback_ERROR();
				//ToDo: Speicher wieder frei geben 
				//delete [] this->ship_two1;
				//ToFiX: Speicher bleibt allociert
				//this->ship_two1 = NULL;
			}
		}
		break;

		case KB_FIVE:
		{
			Ship* tmp = new Ship( 5, new Koordinaten( this->SelectionGrid->getCurrentPosition()->x, this->SelectionGrid->getCurrentPosition()->y) );
			
			if( this->SelectionGrid->isFieldsFree4Ship( tmp ) )
			{	
				//alten gesperrten Bereich leeren falls ein Schiff schon gesetzt wurde
				if( this->ship_five != NULL )
					this->SelectionGrid->clearLockedArea( this->ship_five );

				this->ship_five = tmp;
				this->SelectionGrid->setShip( 4, this->ship_five );
				this->doFeedback_OK();
			}
			else
			{
				//speicher des temporären schiffes freigeben
				//delete [] tmp;
				//ToDo: Ordentliches Feedback einbauen:
				//"Hier ist kein Platz für dieses Schiff"
				this->doFeedback_ERROR();
				//ToDo: Speicher wieder frei geben 
				//delete [] this->ship_two1;
				//ToFiX: Speicher bleibt allociert
				//this->ship_two1 = NULL;
			}
		}
		break;

		case KB_ROTATE:
			switch( this->currentSelectedShip )
			{
				case 0:
					if( this->SelectionGrid->rotateShip( this->ship_two1 ) ) this->doFeedback_OK();
					else this->doFeedback_ERROR();
				break;

				case 1:
					if( this->SelectionGrid->rotateShip( this->ship_two2 ) ) this->doFeedback_OK();
					else this->doFeedback_ERROR();
				break;

				case 2:
					if( this->SelectionGrid->rotateShip( this->ship_three ) ) this->doFeedback_OK();
					else this->doFeedback_ERROR();
				break;

				case 3:
					if( this->SelectionGrid->rotateShip( this->ship_four ) ) this->doFeedback_OK();
					else this->doFeedback_ERROR();
				break;

				case 4: 
					if( this->SelectionGrid->rotateShip( this->ship_five ) ) this->doFeedback_OK();
					else this->doFeedback_ERROR();
				break;

				default: 
					this->doFeedback_ERROR();
				break;
			}
		break;

		case KB_RETURN: if( this->allShipsPlaced ) this->confirmSelection(); break;

		case KB_ESCAPE: exit(0); break;
	}
}


//Setup functions
void Player::showShips4Setup()
{
	cout << "Ships to place:" << endl;
	if( this->ship_two1 == NULL ) cout << "<1> place SS" << endl;
	else
	{
		cout << "<1> REplace SS" << endl;
		//überprüfen, ob die position im "SelectionGrid" == position des Schiffes (Kopfes)
		if( this->SelectionGrid->getCurrentPosition()->x == this->ship_two1->getKoordinatenFromHead()->x && 
			this->SelectionGrid->getCurrentPosition()->y == this->ship_two1->getKoordinatenFromHead()->y )
		{
			cout << " => <r> rotate ship (from head)" << endl;
			this->currentSelectedShip = 0;
		}
	}

	if( this->ship_two2 == NULL ) cout << "<2> place SS" << endl;
	else
	{
		cout << "<2> REplace SS" << endl;
		//überprüfen, ob die position im "SelectionGrid" == position des Schiffes (Kopfes)
		if( this->SelectionGrid->getCurrentPosition()->x == this->ship_two2->getKoordinatenFromHead()->x && 
			this->SelectionGrid->getCurrentPosition()->y == this->ship_two2->getKoordinatenFromHead()->y )
		{
			cout << " => <r> rotate ship (from head)" << endl;
			this->currentSelectedShip = 1;
		}
	}

	if( this->ship_three == NULL ) cout << "<3> place SSS" << endl;
	else 
	{
		cout << "<3> REplace SSS" << endl;
		//überprüfen, ob die position im "SelectionGrid" == position des Schiffes (Kopfes)
		if( this->SelectionGrid->getCurrentPosition()->x == this->ship_three->getKoordinatenFromHead()->x && 
			this->SelectionGrid->getCurrentPosition()->y == this->ship_three->getKoordinatenFromHead()->y )
		{
			cout << " => <r> rotate ship (from head)" << endl;
			this->currentSelectedShip = 2;
		}
	}

	if( this->ship_four == NULL ) cout << "<4> place SSSS" << endl;
	else
	{
		cout << "<4> REplace SSSS" << endl ;
		//überprüfen, ob die position im "SelectionGrid" == position des Schiffes (Kopfes)
		if( this->SelectionGrid->getCurrentPosition()->x == this->ship_four->getKoordinatenFromHead()->x && 
			this->SelectionGrid->getCurrentPosition()->y == this->ship_four->getKoordinatenFromHead()->y )
		{
			cout << " => <r> rotate ship (from head)" << endl;
			this->currentSelectedShip = 3;
		}
	}

	if( this->ship_five == NULL ) cout << "<5> place SSSSS" << endl;
	else
	{
		cout << "<5> REplace SSSSS" << endl;
		//überprüfen, ob die position im "SelectionGrid" == position des Schiffes (Kopfes)
		if( this->SelectionGrid->getCurrentPosition()->x == this->ship_five->getKoordinatenFromHead()->x && 
			this->SelectionGrid->getCurrentPosition()->y == this->ship_five->getKoordinatenFromHead()->y )
		{
			cout << " => <r> rotate ship (from head)" << endl;
			this->currentSelectedShip = 4;
		}
	}

	if( this->ship_two1 != NULL && this->ship_two2 != NULL && this->ship_three != NULL && this->ship_four != NULL && this->ship_five != NULL )
	{
		this->allShipsPlaced = true;
		cout << "All ship s placed." << endl;
		cout << "Press <RETURN> to continue." << endl;
	}
}

void Player::confirmSelection()
{
	//Daten kopieren
	this->ShipGrid->copy( &(*this->SelectionGrid) );

	//Dieser Spieler ist fertig mit dem Platzieren seiner Schiffe
	this->ready = true;
}

void Player::updateCurrentSelectedShip()
{
	Ship* tmp = this->SelectionGrid->getShipOnPosition( this->SelectionGrid->getCurrentPosition() );
	if( tmp != NULL )
	{
		if( tmp == this->ship_two1 ) this->currentSelectedShip = 0;
		else if( tmp == this->ship_two2 ) this->currentSelectedShip = 1;
		else if( tmp == this->ship_three ) this->currentSelectedShip = 2;
		else if( tmp == this->ship_four ) this->currentSelectedShip = 3;
		else if( tmp == this->ship_five ) this->currentSelectedShip = 4;
	}
	else
		this->currentSelectedShip = -1;
}

//Game functions
void Player::makeTurn( int gameRound)
{
	while( !this->ready )
	{
		if( _kbhit() ) //http://msdn.microsoft.com/de-de/library/58w7c94c%28v=vs.80%29.aspx
		{
			int KB_code = 0;
			/* 1: EINGABE */
			//Tastatureingabe
			KB_code = _getch(); //ASCII Code
			//anzeigen, welche Taste gedrückt wurde
//					printf("KB_code = %i \n",KB_code); 

			//ungewollte Eingaben abfangen
			if( KB_code == 224 ) 
				continue;

			/* 2: VERARBEITEN */
			//Tastatureingaben verarbeiten
			this->handleInput_game(KB_code);

			/* 3: ANZEIGEN */
			cout << "Gameround: " << gameRound << endl;
			cout << this->getName() << "s turn:" << endl;
			this->showGameGUI();
		}
	}
}

void Player::handleInput_game(int KB_code)
{
	switch( KB_code )
	{
		case KB_LEFT: 
			this->SelectionGrid->selectLeft(); 
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		case KB_RIGHT:
			this->SelectionGrid->selectRight();
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		case KB_UP:
			this->SelectionGrid->selectUp();
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		case KB_DOWN:
			this->SelectionGrid->selectDown(); 
			//Feedback zurücksetzen
			this->doFeedback_NORMAL();
		break;

		//ToDel: für test ob gameloop funktioniert:
		case KB_RETURN:
			//Wen diese Taste gedrückt wird, schießt der aktuelle spieler an die position vom SelectionGrid
			//behandlung außerhalb
			this->ready = true;
		break;

		default: cout << "handleInput_game: " << this->getName() << endl; break; 
	}

	//nach der eingabe den Bildschirm löschen:
	system("cls");
}

void Player::showGameGUI()
{
	this->getShipGrid()->showExplanation_GAME();
	this->showShipGrid();

	cout << "Aiming Grid:" << endl;
	cout << "HINT #1: Move your cross hairs with the arrow keys." << endl;
	cout << "HINT #2: Fire to your position with <RETURN>." << endl;
	this->showSelectionGrid();
}

bool Player::allShipsSunk()
{
	if( this->ship_two1->isShipDead() &&
		this->ship_two2->isShipDead() &&
		this->ship_three->isShipDead() &&
		this->ship_four->isShipDead() &&
		this->ship_five->isShipDead() )
		return true;
	else
		return false;
}

//Feedback funktions
void Player::doFeedback_NORMAL()
{
	system("color 0f");
}

void Player::doFeedback_OK()
{
	system("color 0a");
}

void Player::doFeedback_ERROR()
{
	system("color 0c");
}


//-----------------------------ToDelet 4 Development-----------------------------//
Player::Player( char* developmentName)
{
	//Variablen ordentlich initialisieren (Grids erstellen usw)
	this->init();

	strcpy( this->name, developmentName);
	cout << "Player " << this->name << " created !" << endl;

	//Shiffe erstellen
/*	this->ship_two1 = new Ship( 2, new Koordinaten( 6, 0) );
	this->ship_two2 = new Ship( 2, new Koordinaten( 3, 3) );
	this->ship_three = new Ship( 3, new Koordinaten( 0, 5) );
	this->ship_four = new Ship( 4, new Koordinaten( 5, 7) );
	this->ship_five = new Ship( 5, new Koordinaten( 1, 9) );

	this->SelectionGrid->setShip( 0, this->ship_two1 );
	this->SelectionGrid->setShip( 1, this->ship_two2 );
	this->SelectionGrid->setShip( 2, this->ship_three );
	this->SelectionGrid->setShip( 3, this->ship_four );
	this->SelectionGrid->setShip( 4, this->ship_five );

	this->ShipGrid->copy( &(*this->SelectionGrid) );
*/
}
//-------------------------------------------------------------------------------//