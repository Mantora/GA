#include "Battleships.h"

using namespace std;

Battleships::Battleships()
{
	cout << "Welcome to Battleships !" << endl;
}

//1: SetUp function
void Battleships::createPlayers()
{
	/* Release: */
	//p1
	cout << "Player 1 please enter Name: " ;
	char tmp[32] = {0};
	while( strncmp( tmp, "", sizeof(tmp) ) == 0 )
	{
		cin.getline( tmp, sizeof(tmp), '\n');
	}
	this->p1 = new Player( tmp );

	//p2
	cout << "Player 2 please enter Name: " ;
	char tmp2[32] = {0};
	while( strncmp( tmp2, "", sizeof(tmp2) ) == 0 )
	{
		cin.getline( tmp2, sizeof(tmp2), '\n');
	}
	this->p2 = new Player( tmp2 );

	//ToDelet 4 Development
//	this->p1 = new Player("eins");
//	this->p1 = new Player("zwei");
}

void Battleships::setupShips( Player* currentPlayer )
{
	system("cls");
	int KB_code = 0;

	//was wird angezeigt beim ersten mal ?
	cout << "Player \"" << currentPlayer->getName() << "\" please place your ships." << endl;
	currentPlayer->showShips4Setup();
	currentPlayer->showSelectionGrid();
	
	while( !currentPlayer->isReady() )
	{
		if( _kbhit() ) //http://msdn.microsoft.com/de-de/library/58w7c94c%28v=vs.80%29.aspx
		{
			//alten Bildschirm leeren
			system("cls");

			/* 1: EINGABE */
			//Tastatureingabe
			KB_code = _getch(); //ASCII Code
			//anzeigen, welche Taste gedrückt wurde
//			printf("KB_code = %i \n",KB_code); 

			//ungewollte Eingaben abfangen
			if( KB_code == 224 ) 
				continue;

			/* 2: VERARBEITEN */
			//Tastatureingaben verarbeiten
			currentPlayer->handleInput_setup(KB_code);

			/* 3: ANZEIGEN */
			cout << "Player \"" << currentPlayer->getName() << "\" please place your ships." << endl;
			//Grid anzeigen
			currentPlayer->showShips4Setup();
			currentPlayer->showSelectionGrid();
		}
	}
	system("cls");
	currentPlayer->showShipGrid();
}

//2: Game Scene funktions
//TOFIX: doppelten code entfernen
Player* Battleships::runGameLoop()
{
	system("cls");

	//return: der spieler, der verlohren hat
	Player* playerHasWon = NULL;
	int gameRound = 1;

	cout << "Gameround: " << gameRound << endl;

	//1. Runde Spieler1
	cout << this->p1->getName() << "s turn:" << endl;
	
	cout << "Press <RETURN> to continue." << endl;
	getchar();

	this->p1->showGameGUI();

	bool allShipsOfOnePlayerSunk = false;
	while( !allShipsOfOnePlayerSunk )
	{
		if( gameRound % 2 )
		{
			//Player1 ist am Zug:
			this->p1->setReady( false );

			this->p1->makeTurn( gameRound );

			//Bildschirm leeren, damit der andere Spieler nicht weiß, wie die Schiffe sind
			system("cls");
			//Auf das Ship Grid von Spieler2 schießen:

			//hat man schon auf dieses Feld geschossen?
			Koordinaten* posTarget = this->p1->getSelectionGrid()->getCurrentPosition();
			//SIEHE: Grid::showGrid()
			switch( this->p1->getSelectionGrid()->getValueAt( posTarget ) )
			{
				case 'O': 
					//Hier wurde etwas getroffen -> eingabe wiederholen
					this->p1->doFeedback_ERROR();

					system("cls");

					//GUI für nächsten Spieler anzeigen
					cout << "Gameround: " << gameRound << endl;
					cout << this->p1->getName() << "s turn:" << endl;
					this->p1->showGameGUI();

					this->p1->makeTurn( gameRound );
				break; 

				case '#': 
					//Hier wurde nichts getroffen -> eingabe wiederholen
					this->p1->doFeedback_ERROR();

					system("cls");

					//GUI für nächsten Spieler anzeigen
					cout << "Gameround: " << gameRound << endl;
					cout << this->p1->getName() << "s turn:" << endl;
					this->p1->showGameGUI();

					this->p1->makeTurn( gameRound );
				break;

				default:
				{
					if( this->p1->getSelectionGrid()->fireToGrid( p2->getShipGrid() ) )
					{
						cout << this->p1->getName() <<", you HIT on position (" << this->p1->getSelectionGrid()->getCurrentPosition()->x << "|" << this->p1->getSelectionGrid()->getCurrentPosition()->y << ")" << endl;
						cout << "Next player. Press any key to confirm 4 next round." << endl;
						getchar();
					}
					else
					{
						cout << this->p1->getName() <<", you MISS on position (" << this->p1->getSelectionGrid()->getCurrentPosition()->x << "|" << this->p1->getSelectionGrid()->getCurrentPosition()->y << ")" << endl;
						cout << "Next player. Press any key to confirm 4 next round." << endl;
						getchar();
					}

					//runde vorbei
					gameRound++;

					//prüfen ob alle Schiffe von diesem Spieler gesunken sind
					if( this->p2->allShipsSunk() )
					{
						//ja, ende
						allShipsOfOnePlayerSunk = true;
						playerHasWon = this->p1;
					}
					else
					{
						//nein, weiter gehts:
						//Bildschirm leeren für nächsten Zug
						system("cls");

						//GUI für nächsten Spieler anzeigen
						cout << "Gameround: " << gameRound << endl;
						cout << this->p2->getName() << "s turn:" << endl;
						this->p2->showGameGUI();
					}
				}
				break;
			}
		}
		else
		{
			//Player1 ist am Zug:
			this->p2->setReady( false );

			this->p2->makeTurn( gameRound );

			//Bildschirm leeren, damit der andere Spieler nicht weiß, wie die Schiffe sind
			system("cls");
			//Auf das Ship Grid von Spieler1 schießen:

			//hat man schon auf dieses Feld geschossen?
			Koordinaten* posTarget = this->p2->getSelectionGrid()->getCurrentPosition();
			//SIEHE: Grid::showGrid()
			switch( this->p2->getSelectionGrid()->getValueAt( posTarget ) )
			{
				case 'O': 
					//Hier wurde etwas getroffen -> eingabe wiederholen
					this->p2->doFeedback_ERROR();

					system("cls");

					//GUI für nächsten Spieler anzeigen
					cout << "Gameround: " << gameRound << endl;
					cout << this->p2->getName() << "s turn:" << endl;
					this->p2->showGameGUI();

					this->p2->makeTurn( gameRound );
				break; 

				case '#': 
					//Hier wurde nichts getroffen -> eingabe wiederholen
					this->p2->doFeedback_ERROR();

					system("cls");

					//GUI für nächsten Spieler anzeigen
					cout << "Gameround: " << gameRound << endl;
					cout << this->p2->getName() << "s turn:" << endl;
					this->p2->showGameGUI();

					this->p2->makeTurn( gameRound );
				break;

				default:
				{
					if( this->p2->getSelectionGrid()->fireToGrid( p1->getShipGrid() ) )
					{
						cout << this->p2->getName() <<", you HIT on position (" << this->p2->getSelectionGrid()->getCurrentPosition()->x << "|" << this->p2->getSelectionGrid()->getCurrentPosition()->y << ")" << endl;
						cout << "Next player. Press any key to confirm 4 next round." << endl;
						getchar();
					}
					else
					{
						cout << this->p2->getName() <<", you MISS on position (" << this->p2->getSelectionGrid()->getCurrentPosition()->x << "|" << this->p2->getSelectionGrid()->getCurrentPosition()->y << ")" << endl;
						cout << "Next player. Press any key to confirm 4 next round." << endl;
						getchar();
					}

					//runde vorbei
					gameRound++;

					//prüfen ob alle Schiffe von diesem Spieler gesunken sind
					if( this->p1->allShipsSunk() )
					{
						//ja, ende
						allShipsOfOnePlayerSunk = true;
						playerHasWon = this->p2;
					}
					else
					{
						//nein, weiter gehts:
						//Bildschirm leeren für nächsten Zug
						system("cls");

						//GUI für nächsten Spieler anzeigen
						cout << "Gameround: " << gameRound << endl;
						cout << this->p1->getName() << "s turn:" << endl;
						this->p1->showGameGUI();
					}
				}
				break;
			}
		}
	}
	return playerHasWon;
}

//3: GameOver Scene
void Battleships::playerWin( Player* winner )
{
	system("cls");
	cout << "Congratulations \"" << winner->getName() << "\". You won the battle." << endl;
}

//ToDel 4 DEV:
void Battleships::DEV_createPlayersFULL()
{
	this->p1 = new Player("Player1");
	this->p2 = new Player("Player2");
}
