#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>
#include <math.h>
#include <time.h>

#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"
#include "charset.h"

#include "Object.h"

uchar handle_input( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 1200, 600 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, x_res-1, 0, y_res-1 );

	/* Polygone erstellen */
	Polygone* ball = new Polygone();
	ball->addPoint( 0,	0 );
	ball->addPoint( 10,	0 );
	ball->addPoint( 10,	10 );
	ball->addPoint( 0,	10 );
	ball->setColor(0,1,0);

	Object* obj_ball = new Object(ball);
	obj_ball->setID(0);
	obj_ball->setPosition(x_res*0.5, y_res*0.5 );
	obj_ball->setRandomMovement( 0.1, 0.1, x_res, y_res);

	Polygone* P1 = new Polygone();
	P1->addPoint( 0, 0);
	P1->addPoint( 10, 0);
	P1->addPoint( 10, 200);
	P1->addPoint( 0, 200);
	P1->setColor(1,0,0);

	Object* obj_P1 = new Object(P1);
	obj_P1->setID(1);
	obj_P1->setPosition( 50, y_res*0.5 );

	Polygone* P2 = new Polygone();
	P2->setColor(0,0,1);
	P2->addPoint( 0, 0);
	P2->addPoint( 10, 0);
	P2->addPoint( 10, 200);
	P2->addPoint( 0, 200);

	Object* obj_P2 = new Object(P2);
	obj_P2->setID(2);
	obj_P2->setPosition( x_res-50-50, y_res*0.5 );

	int scoreP1 = 0;
	int scoreP2 = 0;

	glPixelZoom( 5, 5 ); //ändern der schriftgröße von write

    while( 1 )
	{
		if( input.check() == 1 ) break; //1 entspr, esc. bzw alt+F4
		if( input.event_key == VK_ESCAPE ) break; //1 entspr, esc. bzw alt+F4
		
		glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm löschen

		// Steuerung: LINKE SPIELER
		if( input.key_pressed('W') && obj_P1->getPosition().y < y_res-200) obj_P1->addPosition(0.0, 0.2);
		if( input.key_pressed('S') && obj_P1->getPosition().y > 0) obj_P1->addPosition(0.0, -0.2);
		if( input.key_pressed('D') && obj_P1->getPosition().x < x_res*0.5) obj_P1->addPosition( 0.2, 0.0);
		if( input.key_pressed('A') && obj_P1->getPosition().x > 0) obj_P1->addPosition( -0.2, 0.0);

		// Steuerung: RECHTE SPIELER
		if( input.key_pressed(VK_UP) && obj_P2->getPosition().y < y_res-200) obj_P2->addPosition(0.0, 0.2);
		if( input.key_pressed(VK_DOWN) && obj_P2->getPosition().y > 0) obj_P2->addPosition(0.0, -0.2);
		if( input.key_pressed(VK_RIGHT) && obj_P2->getPosition().x < x_res-obj_P2->polygone->getMaxXPoliLenght()) obj_P2->addPosition( 0.2, 0.0);
		if( input.key_pressed(VK_LEFT) && obj_P2->getPosition().x > x_res*0.5) obj_P2->addPosition( -0.2, 0.0);


		// Kollision des Balles
		if( obj_ball->hit(obj_P1) && (obj_ball->getID() != obj_P1->getID()) )
		{
			obj_ball->polygone->setColor( 1,0,0 );
			obj_ball->negateX();
			obj_ball->setID( obj_P1->getID() );
		}
		if( obj_ball->hit(obj_P2) && (obj_ball->getID() != obj_P2->getID()) )
		{
			obj_ball->polygone->setColor( 0,0,1 );
			obj_ball->negateX();
			obj_ball->setID( obj_P2->getID() );
		}

		// Ist der Ball außerhalb
		if( obj_ball->getPosition().x+obj_ball->polygone->getMaxXPoliLenght() > x_res )
		{
			scoreP1++;
			obj_ball->setPosition( x_res*0.5, y_res*0.5);
		}
		if( obj_ball->getPosition().x < 0 ) 
		{
			scoreP2++;
			obj_ball->setPosition( x_res*0.5, y_res*0.5);
		}

		// Scorebord
		char score[32] = { "XXX : YYY" };
		sprintf( score, "%d : %d", scoreP1, scoreP2);
		chars.write( x_res*0.5-50, y_res-100, score );

		// Name
		chars.write( 0, 0, "Ultra P O N G" );

		// alles Zeichnen
		obj_ball->draw();
		obj_P1->draw();
		obj_P2->draw();

		screen_interface.swap_buffers();
	}

	return input.msg.wParam;
}
