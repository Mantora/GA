#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>
#include <math.h>
#include <time.h>

#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"
#include "charset.h"

#include "Asteroid.h"

uchar handle_input( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 800, 600 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0, x_res-1, 0, y_res-1 );

	/* Polygone erstellen */
	Polygone2D* ball = new Polygone2D();
	ball->makeCircle( 100.0f , 7);
	ball->setColor(1,1,0);

	/* Vater Asteroid erstellen */
	Asteroid* a1 = new Asteroid( ball );
	a1->setPosition( x_res*0.5, y_res*0.5 );
	a1->setRandomMovement( 0.1f, 0.1f, x_res, y_res);
	a1->setVater();

//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	//glPixelZoom( 5, 5 ); //ändern der schriftgröße von write

	//glPointSize( 8 );

    while( 1 )
	{
		if( input.check() == 1 ) break; //1 entspr, esc. bzw alt+F4
		if( input.event_key == VK_ESCAPE ) break; //1 entspr, esc. bzw alt+F4
		
		glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm löschen

		// alles Zeichnen
		a1->drawAllAsteroids();

		char countAll[32] = { "Asteroids (all) : " };
		sprintf( countAll, "Asteroids (all) : %d", Asteroid::countALL);
		chars.write( 0, y_res-15, countAll );

		char goodVSevil[32] = { "good : evil" };
		sprintf( goodVSevil, "good %d : evil %d", Asteroid::counterGood, Asteroid::counterEvil);
		chars.write( 0, y_res-30, goodVSevil );

		char points[32] = { "Asteroids destroyed: " };
		sprintf( points, "Asteroids destroyed: %d", Asteroid::destroyed);
		chars.write( 0, y_res-45, points );

		char debug[32] = { "DEBUG: " };
		sprintf( debug, "DEBUG:  %f | %f", input.mouse_act_pos.wx, input.mouse_act_pos.wy);
		chars.write( 0, 0, debug );

		a1->isAnyAsteroidHit( input.mouse_act_pos.wx, input.mouse_act_pos.wy );

/*		// Steuerung: LINKE SPIELER
		if( input.key_pressed('W') && obj_P1->getPosition().y < y_res-200) obj_P1->addPosition(0.0, 0.2);
		if( input.key_pressed('S') && obj_P1->getPosition().y > 0) obj_P1->addPosition(0.0, -0.2);
		if( input.key_pressed('D') && obj_P1->getPosition().x < x_res*0.5) obj_P1->addPosition( 0.2, 0.0);
		if( input.key_pressed('A') && obj_P1->getPosition().x > 0) obj_P1->addPosition( -0.2, 0.0);

		// Steuerung: RECHTE SPIELER
		if( input.key_pressed(VK_UP) && obj_P2->getPosition().y < y_res-200) obj_P2->addPosition(0.0, 0.2);
		if( input.key_pressed(VK_DOWN) && obj_P2->getPosition().y > 0) obj_P2->addPosition(0.0, -0.2);
		if( input.key_pressed(VK_RIGHT) && obj_P2->getPosition().x < x_res-obj_P2->polygone->getMaxXPoliLenght()) obj_P2->addPosition( 0.2, 0.0);
		if( input.key_pressed(VK_LEFT) && obj_P2->getPosition().x > x_res*0.5) obj_P2->addPosition( -0.2, 0.0);
*/
		screen_interface.swap_buffers();
	}

	return input.msg.wParam;
}
