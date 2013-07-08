#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>

#include <time.h>

//FILE HANDLING
#include <iostream>
#include <fstream>
#include <string>
////////////////

#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"


#include "matrix.h"
#include "Polyeder.h"

using namespace std;

//Prototypen
uchar handle_input( void );
void drawTest(void);
void drawCircle(void);

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 800, 600 );

	glMatrixMode( GL_PROJECTION ); //http://www.opengl.org/sdk/docs/man2/xhtml/glMatrixMode.xml

	glLoadIdentity(); //http://wiki.delphigl.com/index.php/glLoadIdentity


	//3D
	gluPerspective( 30, GLdouble( x_res ) / y_res, 0.1f, 10000.0f );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	Polyeder* cube = new Polyeder( 6 );

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

	// Matrixdefinitionen
	matrix m;
	m.translate( 0, 0, -10.0f );
	cube->update_pos( m );

	/* BOMB */
/*	Polyeder* bomb = new Polyeder( 34 );

	//vertex aus Datei laden:
	char file[] = { "Cannon_Ball_01.obj" };
	ifstream is( file );
	string buffer;

	int vertexCount = 0;

	while( is.good() )
	{
		getline( is, buffer );

		const char* tmp = buffer.c_str();
		if( tmp[0] == 'v' && tmp[1] == 32 )
		{
			//beispiel: "v 0.000000 -0.647214 -0.470228"
			vertexCount++;
		}
	}
	is.close();
//ToDO: Einbauen von OBJ lesen
	vertex* points = new vertex[34];
	//unten
	points[0] = vertex( 0.332502, -0.647214, -0.332502 );
	points[1] = vertex( 0.000000, -0.647214, -0.470228 );
	points[2] = vertex( -0.332502, -0.647214, -0.332502 );
	points[3] = vertex( -0.470228, -0.647214, 0.000000 );
	points[4] = vertex( -0.332502, -0.647214, 0.332502 );
	points[5] = vertex( 0.000000, -0.647214, 0.470228 );
	points[6] = vertex( 0.332502, -0.647214, 0.332502 );
	points[7] = vertex( 0.470228, -0.647214, 0.000000 );
	points[8] = vertex( 0.537999, -0.247214, -0.537999 );
	points[9] = vertex( 0.000000, -0.247214, -0.760845 );
	points[10] = vertex(-0.537999, -0.247214, -0.537999 );
	points[11] = vertex(-0.760845, -0.247214, 0.000000 );
	points[12] = vertex( -0.537999, -0.247214, 0.537999 );
	points[13] = vertex( 0.000000, -0.247214, 0.760845 );
	points[14] = vertex( 0.537999, -0.247214, 0.537999 );
	points[15] = vertex( 0.760845, -0.247214, 0.000000 );
	points[16] = vertex( 0.537999, 0.247214, -0.537999 );
	points[17] = vertex( 0.000000, 0.247214, -0.760845 );
	points[18] = vertex( -0.537999, 0.247214, -0.537999 );
	points[19] = vertex( -0.760845, 0.247214, 0.000000 );
	points[20] = vertex( -0.537999, 0.247214, 0.537999 );
	points[21] = vertex( 0.000000, 0.247214, 0.760845 );
	points[22] = vertex( 0.537999, 0.247214, 0.537999 );
	points[23] = vertex( 0.760845, 0.247214, 0.000000 );
	points[24] = vertex( 0.332502, 0.647214, -0.332502 );
	points[25] = vertex( 0.000000, 0.647214, -0.470228 );
	points[26] = vertex( -0.332502, 0.647214, -0.332502 );
	points[27] = vertex( -0.470228, 0.647214, 0.000000 );
	points[28] = vertex( -0.332502, 0.647214, 0.332502 );
	points[29] = vertex( 0.000000, 0.647214, 0.470228 );
	points[30] = vertex( 0.332502, 0.647214, 0.332502 );
	points[31] = vertex( 0.470228, 0.647214, 0.000000 );
	points[32] = vertex( 0.000000, -0.800000, 0.000000 );
	points[33] = vertex( 0.000000, 0.800000, 0.000000 );
	bomb->setNextPolygon( points, 34 );

	// Matrixdefinitionen
	matrix m;
	m.translate( 0,0,-10);
	bomb->update_pos( m );
*/
//	glPointSize( 10 ); //Da das Objekt kein Polygone ist und die Pixel Float sind -> vergrößern

	while( handle_input() == 0 )
	{
		glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm löschen

		cube->display();
//		bomb->display();

		m.clear();
		//m.rotate_x( 0.01f );
		m.rotate_z( 0.001f );
//		bomb->update_pos( m );

		m.clear();
		m.translate( 0,0,10);
		m.rotate_x( 0.001f );
		m.rotate_y( 0.001f );
		m.rotate_z( 0.001f );
		m.translate( 0,0,-10);
		cube->update_pos( m );
//		bomb->update_pos( m );

		screen_interface.swap_buffers(); // buffer leeren ist hier automatisch drin
//		glFlush(); //buffer leeren
	}
  
	return input.msg.wParam;
}

void drawCircle()
{
	//Bildschirmmittelpunkt
	GLdouble middleX = screen_interface.get_xr()/2;
	GLdouble middleY = screen_interface.get_yr()/2;

	//einen neuen Pixel definieren
	GLdouble newX = rand() % screen_interface.get_xr();
	GLdouble newY = rand() % screen_interface.get_yr();

	//distanz von der Mitte zum Punkt
	GLdouble dis = sqrt( (newX-middleX)*(newX-middleX) + (newY-middleY)*(newY-middleY) );

	if( dis < 10 )
	{
		glColor3d(1,0,0);
		glVertex2d( newX, newY );
	}
}

void drawTest()
{
	GLdouble borderOutside = 100;
	GLdouble borderInside = 400;

	GLdouble newX = rand() % screen_interface.get_xr();
	GLdouble newY = rand() % screen_interface.get_yr();

	GLdouble middleX = screen_interface.get_xr()/2;
	GLdouble middleY = screen_interface.get_yr()/2;

	GLdouble maxDis = sqrt( (1-middleX)*(1-middleX) + (1-middleY)*(1-middleY) );
	GLdouble dis = sqrt( (newX-middleX)*(newX-middleX) + (newY-middleY)*(newY-middleY) );

	if( newX < borderOutside || newX > screen_interface.get_xr()-borderOutside || newY > screen_interface.get_yr()-borderOutside || newY < borderOutside)
	{
		if( dis < 400 )
		{
			glColor3d( dis/maxDis, dis/maxDis, 0 );
		}
		else
		glColor3d( 0, 0, dis/maxDis );
	}
	else if(dis < 200)
	{
		glColor3d( dis/maxDis, dis/maxDis, 0 );
	}
	else if( (newX > middleX-borderInside/2) && (newX < middleX+borderInside/2) && (newY < middleY+borderInside/2) && (newY > middleY-borderInside/2) )
	{
		//inneres Quadrat
		glColor3d( 0, dis/maxDis, 0 );
	}
	else if( dis < 300 )
	{
		glColor3d( dis/maxDis, dis/maxDis, 0 );
	}
	else
	{
		glColor3d( dis/maxDis, 0, 0 );
	}

	glVertex2d( newX, newY );
}

uchar handle_input( void )
{
  if( input.check() == 1 ) return 1;
  if( input.event_key == VK_ESCAPE ) return 1;

  return 0;
}


