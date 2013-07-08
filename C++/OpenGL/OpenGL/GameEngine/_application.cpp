#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>
#include <math.h>
#include <time.h>

#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"

struct point
{
  double x, y;
};

uchar handle_input( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
  screen_interface.open_window( hinst, 640, 480 );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D( 0, x_res-1, 0, y_res-1 );
  
  while( handle_input() == 0 )
  {
    point mitte;
    mitte.x = 320;
    mitte.y = 240;

	long radius = 100;

    point in_square;
    in_square.x = (rand() % (2*radius)) - radius;
    in_square.y = (rand() % (2*radius)) - radius;

    double d = sqrt( in_square.x * in_square.x + in_square.y * in_square.y );
	if( d > 100 ) continue;

    glBegin( GL_POINTS );

      glColor3d( d/radius, 0, d/radius );
      glVertex2d( mitte.x+in_square.x, mitte.y+in_square.y );

    glEnd();

    glFinish();
  }
  
  return input.msg.wParam;
}

uchar handle_input( void )
{
  if( input.check() == 1 ) return 1;
  if( input.event_key != 0 ) return 1;

  return 0;
}