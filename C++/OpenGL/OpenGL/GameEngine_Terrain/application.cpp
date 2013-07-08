#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>
#include <math.h>
#include <time.h>

#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"

#include "Landscape.h"

#include "matrix.h"

uchar handle_input( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 800, 600 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
//	gluOrtho2D( 0, x_res-1, 0, y_res-1 );
	gluPerspective( 30, double(x_res)/y_res, 0.01f, 10000 );

//	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	//Terrain definieren
	Landscape* terrain = new Landscape(100);

	//zum speichern der translate
	terrain->setTranslation( 0, 0, 100 );

	// Matrixdefinitionen
	matrix m;
	m.translate( 0, 0, -terrain->getTranslation()->wz );
	terrain->updatePos( m );

    while( 1 )
	{
		if( input.check() == 1 ) break; //1 entspr, esc. bzw alt+F4
		if( input.event_key == VK_ESCAPE ) break; //1 entspr, esc. bzw alt+F4
		
		glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm löschen

		terrain->draw();

		/* Steuerung */
		//drehung
		if( input.key_pressed('W') )
		{
			m.clear();
			
			m.translate( 0, -terrain->getTranslation()->wy, +terrain->getTranslation()->wz );
			m.rotate_x( -0.01f );
			m.translate( 0, +terrain->getTranslation()->wy, -terrain->getTranslation()->wz );
			terrain->updatePos( m );
		}
		if( input.key_pressed('S') )
		{
			m.clear();
			m.translate( 0, -terrain->getTranslation()->wy, +terrain->getTranslation()->wz );
			m.rotate_x( 0.01f );
			m.translate( 0, +terrain->getTranslation()->wy, -terrain->getTranslation()->wz );
			terrain->updatePos( m );
		}
		if( input.key_pressed('D') ) 
		{
			m.clear();
			m.translate( -terrain->getTranslation()->wx, 0, +terrain->getTranslation()->wz );
			m.rotate_y( 0.01f );
			m.translate( +terrain->getTranslation()->wx, 0, -terrain->getTranslation()->wz );
			terrain->updatePos( m );
		}
		if( input.key_pressed('A') )
		{
			m.clear();
			m.translate( -terrain->getTranslation()->wx, 0, +terrain->getTranslation()->wz );
			m.rotate_y( -0.01f );
			m.translate( +terrain->getTranslation()->wx, 0, -terrain->getTranslation()->wz );
			terrain->updatePos( m );
		}

		//bewegung
		if( input.key_pressed(VK_LEFT) )
		{
			m.clear();
			m.translate( -0.001, 0, 0 );
			terrain->setTranslation( -0.001, 0, 0);
			terrain->updatePos( m );
		}
		if( input.key_pressed(VK_RIGHT) )
		{
			m.clear();
			m.translate( 0.001, 0, 0 );
			terrain->setTranslation( +0.001, 0, 0);
			terrain->updatePos( m );
		}

		if( input.key_pressed(VK_DOWN) )
		{
			m.clear();
			m.translate( 0, -0.001, 0 );
			terrain->setTranslation( 0, -0.001, 0);
			terrain->updatePos( m );
		}
		if( input.key_pressed(VK_UP) )
		{
			m.clear();
			m.translate( 0, 0.001, 0 );
			terrain->setTranslation( 0, +0.001, 0);
			terrain->updatePos( m );
		}


		screen_interface.swap_buffers();
	}

	return input.msg.wParam;
}
