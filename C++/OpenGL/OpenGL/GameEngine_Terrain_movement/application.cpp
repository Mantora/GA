/*
vertex pos; //Objektkoordinaten
vertex world_coords = model * pos;
glvertex3d( world_coords.wx, world_coords.wy, world_coords.wz );
*/

#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>
#include <math.h>
#include <time.h>

#include "screen_interface.h"

#include "input_interface.h"

#include "Landscape.h"

#include "matrix.h"

#include "picture.h"

unsigned char display_mode = 0;

uchar handle_input( void );
void display( local_system );
void load_texture( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 1600, 1000 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
//	gluOrtho2D( 0, x_res-1, 0, y_res-1 );
	gluPerspective( 30, double(x_res)/y_res, 0.01f, 10000 );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glEnable( GL_DEPTH_TEST );

	load_texture();

	picture* pic = new picture( "terrain_highmap.bmp" );

	//Terrain definieren
	Landscape* terrain = new Landscape( pic->xsize, pic);

	//zum speichern der translate
	terrain->setTranslation( 0, 0, 800 );

	// Matrixdefinitionen
	matrix m;
	m.translate( 0, 0, -terrain->getTranslation()->wz );
	terrain->updatePos( m );

	//Locale Ausrichtung def:
	local_system user_ls;
	user_ls.pos.wz = -700;

///////////////////// CUBE
/*	Polyeder* cube = new Polyeder( 6 );

	vertex* points = new vertex[4];
	//unten
	points[0] = vertex( -1, -1, -1 );
	points[1] = vertex( 1, -1, -1 );
	points[2] = vertex( 1, -1, 1 );
	points[3] = vertex( -1, -1, 1 );
	cube->setNextPolygon( points, 4 );
	//oben
	points[0] = vertex( -1, 1, -1 );
	points[1] = vertex( 1, 1, -1 );
	points[2] = vertex( 1, 1, 1 );
	points[3] = vertex( -1, 1, 1 );
	cube->setNextPolygon( points, 4 );
	//links
	points[0] = vertex( -1, 1, -1 );
	points[1] = vertex( -1, -1, -1 );
	points[2] = vertex( -1, -1, 1 );
	points[3] = vertex( -1, 1, 1 );
	cube->setNextPolygon( points, 4 );
	//rechts
	points[0] = vertex( 1, 1, -1 );
	points[1] = vertex( 1, -1, -1 );
	points[2] = vertex( 1, -1, 1 );
	points[3] = vertex( 1, 1, 1 );
	cube->setNextPolygon( points, 4 );
	//vorn
	points[0] = vertex( -1, 1, 1 );
	points[1] = vertex( -1, -1, 1 );
	points[2] = vertex( 1, -1, 1 );
	points[3] = vertex( 1, 1, 1 );
	cube->setNextPolygon( points, 4 );
	//hinten
	points[0] = vertex( -1, 1, -1 );
	points[1] = vertex( 1, 1, -1 );
	points[2] = vertex( 1, -1, -1 );
	points[3] = vertex( -1, -1, -1 );
	cube->setNextPolygon( points, 4 );

	m.clear();
	m.translate( 0, 0, -10.0f );
	cube->update_pos( m );
*/
    while( 1 )
	{
/*		cube->display();

		m.clear();
		m.translate( 0,0,10);
		m.rotate_x( 0.001f );
		m.rotate_y( 0.001f );
		m.rotate_z( 0.001f );
		m.translate( 0,0,-10);
		cube->update_pos( m );
*/
		if( input.check() == 1 ) break; //1 entspr, esc. bzw alt+F4
		if( input.event_key == VK_ESCAPE ) break; //1 entspr, esc. bzw alt+F4
		if( input.event_key == VK_SPACE ) display_mode = (display_mode + 1) % 2;

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //Bildschirm löschen

		if( display_mode == 0 )
		{
          matrix m;

//          terrain->draw( m );
		terrain->drawWireframe( m );
		//locales_system anzeigen
		  display( user_ls ); 
		}

  		if( display_mode == 1 )
		{
          matrix m;

          m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
          m.rows( user_ls.right, user_ls.up, user_ls.sight );

          terrain->drawWireframe( m );
		}

/*///////////////////////////////////////////////////////////////////////////////
Aus Richtung "user_ls" schauen:
M * right
M * up
M * sight
//////////////////////////////////////////////////////////////////////////////*/
		/* Steuerung */
		//drehung
		double rotMapSpeed = 1;
		if( input.key_pressed('S') )
		{
			m.clear();
			m.translate( 0, -terrain->getTranslation()->wy, +terrain->getTranslation()->wz );
			m.rotate_x( -rotMapSpeed );
			m.translate( 0, +terrain->getTranslation()->wy, -terrain->getTranslation()->wz );
			user_ls = m * user_ls;
			terrain->updatePos( m );
		}
		if( input.key_pressed('W') )
		{
			m.clear();
			m.translate( 0, -terrain->getTranslation()->wy, +terrain->getTranslation()->wz );
			m.rotate_x( rotMapSpeed );
			m.translate( 0, +terrain->getTranslation()->wy, -terrain->getTranslation()->wz );
			user_ls = m * user_ls;
			terrain->updatePos( m );
		}
		if( input.key_pressed('A') ) 
		{
			m.clear();
			m.translate( -terrain->getTranslation()->wx, 0, +terrain->getTranslation()->wz );
			m.rotate_y( rotMapSpeed );
			m.translate( +terrain->getTranslation()->wx, 0, -terrain->getTranslation()->wz );
			user_ls = m * user_ls;
			terrain->updatePos( m );
		}
		if( input.key_pressed('D') )
		{
			m.clear();
			m.translate( -terrain->getTranslation()->wx, 0, +terrain->getTranslation()->wz );
			m.rotate_y( -rotMapSpeed );
			m.translate( +terrain->getTranslation()->wx, 0, -terrain->getTranslation()->wz );
			user_ls = m * user_ls;
			terrain->updatePos( m );
		}

		//bewegung
		if( input.key_pressed(VK_LEFT) )
		{
			m.clear();
			m.translate( -2, 0, 0 );
			terrain->setTranslation( -2, 0, 0);
			terrain->updatePos( m );
			user_ls = m * user_ls;
		}
		if( input.key_pressed(VK_RIGHT) )
		{
			m.clear();
			m.translate( +2, 0, 0 );
			terrain->setTranslation( +2, 0, 0);
			terrain->updatePos( m );
			user_ls = m * user_ls;
		}

		if( input.key_pressed(VK_DOWN) )
		{
			m.clear();
			m.translate( 0, -2, 0 );
			terrain->setTranslation( 0, -2, 0);
			terrain->updatePos( m );
			user_ls = m * user_ls;
		}
		if( input.key_pressed(VK_UP) )
		{
			m.clear();
			m.translate( 0, +2, 0 );
			terrain->setTranslation( 0, +2, 0);
			terrain->updatePos( m );
			user_ls = m * user_ls;
		}
		if( input.key_pressed('Q') )
		{
			m.clear();
			m.translate( 0, 0, -4 );
			terrain->setTranslation( 0, 0, -4);
			terrain->updatePos( m );
			user_ls = m * user_ls;
		}
		if( input.key_pressed('E') )
		{
			m.clear();
			m.translate( 0, 0, 4 );
			terrain->setTranslation( 0, 0, 4);
			terrain->updatePos( m );
			user_ls = m * user_ls;
		}

		//bewegung locales_system
	    double speed = 1.5;
		if( input.key_pressed( VK_NUMPAD7 ) ) user_ls.pos = user_ls.pos + (-speed) * user_ls.sight;
		if( input.key_pressed( VK_NUMPAD1 ) ) user_ls.pos = user_ls.pos +  speed  * user_ls.sight;
		if( input.key_pressed( VK_NUMPAD4 ) ) user_ls.pos = user_ls.pos +  (-speed)  * user_ls.right;
		if( input.key_pressed( VK_NUMPAD6 ) ) user_ls.pos = user_ls.pos +  speed  * user_ls.right;
		if( input.key_pressed( VK_NUMPAD2 ) ) user_ls.pos = user_ls.pos +  (-speed)  * user_ls.up;
		if( input.key_pressed( VK_NUMPAD8 ) ) user_ls.pos = user_ls.pos +  speed  * user_ls.up;

		//drehung locales_system
		double rotSpeed = 1.5f;
		if( input.key_pressed( 'X' ) )
		{
			m.clear();
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
			m.rotate( rotSpeed, user_ls.right );
			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz ); 
			user_ls = m * user_ls;
		}
		if( input.key_pressed( 'Y' ) )
		{
			m.clear();
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
			m.rotate( rotSpeed, user_ls.sight );
			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz ); 
			user_ls = m * user_ls;
		}
		if( input.key_pressed( 'Z' ) )
		{
			m.clear();
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
			m.rotate( rotSpeed, user_ls.up );
			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz ); 
			user_ls = m * user_ls;
		}

		screen_interface.swap_buffers();
	}

	return input.msg.wParam;
}

void load_texture( void )
{
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

  picture surface( "surface.bmp" );

  GLuint texture_id;
  glGenTextures( 1, &texture_id );
  glBindTexture( GL_TEXTURE_2D, texture_id );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface.xsize, surface.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.content );

  glEnable( GL_TEXTURE_2D ); //Texturprojektion aktivieren
}

void display( local_system ls )
{
	glPushAttrib( GL_CURRENT_BIT );
	
	int scaling = 20;

	ls.right = scaling * ls.right;
	ls.up = scaling * ls.up;
	ls.sight = scaling * ls.sight;

	glBegin( GL_LINES );
		glColor3d( 1,0,0 );
		glVertex3d( ls.pos.wx, ls.pos.wy, ls.pos.wz );
		glVertex3d( ls.pos.wx + ls.right.x, ls.pos.wy + ls.right.y, ls.pos.wz + ls.right.z );

		glColor3d( 0,1,0 );
		glVertex3d( ls.pos.wx, ls.pos.wy, ls.pos.wz );
		glVertex3d( ls.pos.wx + ls.up.x, ls.pos.wy + ls.up.y, ls.pos.wz + ls.up.z );

		glColor3d( 0,0,1 );
		glVertex3d( ls.pos.wx, ls.pos.wy, ls.pos.wz );
		glVertex3d( ls.pos.wx + ls.sight.x, ls.pos.wy + ls.sight.y, ls.pos.wz + ls.sight.z );
	glEnd();

	glPopAttrib();
}
