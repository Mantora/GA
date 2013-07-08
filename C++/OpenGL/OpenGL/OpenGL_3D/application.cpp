#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>

#include <time.h>

#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"


#include "matrix.h"
#include "Buffer.h"


//Prototypen
uchar handle_input( void );
void drawTest(void);
void drawCircle(void);

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 800, 600 );

	glMatrixMode( GL_PROJECTION ); //http://www.opengl.org/sdk/docs/man2/xhtml/glMatrixMode.xml

	glLoadIdentity(); //http://wiki.delphigl.com/index.php/glLoadIdentity

	// Matrixdefinitionen
	matrix m;
	m.translate( 0, 0, -20.0f );

	//3D
	gluPerspective( 100, GLdouble( x_res ) / y_res, 2.0, 10000.0 );

	/* Buffer init: */
	pixel Bildschirm;
	Bildschirm.x = screen_interface.get_xr();
	Bildschirm.y = screen_interface.get_yr();

	MyColor red = { 1, 0, 0 };
	MyColor blue = { 0, 0, 1 };
	MyColor green = { 0, 1, 0 };

	Buffer* b0 = new Buffer(Bildschirm);
	b0->createSphere( 5.0f, green );
	b0->updatePos( m );

	Buffer* b1 = new Buffer(Bildschirm);
	b1->createCube(10, red);
	b1->updatePos( new Vector3( 0, 0, -10) );

	Buffer* b2 = new Buffer(Bildschirm);
	b2->createCube(10, blue);
	b2->updatePos( new Vector3( 0, 0, -5) );


	glPointSize( 10 ); //Da das Objekt kein Polygone ist und die Pixel Float sind -> vergrößern

	while( handle_input() == 0 )
	{
		glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm löschen

		glBegin( GL_POINTS );

		b0->draw();
		m.clear();
		//m.rotate_x( 0.01f );
		m.rotate_y( 0.01f );
//versuchen, das Object in seinem Ursprung zu drehen
		b0->updatePos( m );
		b1->draw();
		b2->draw();

		glEnd();

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


