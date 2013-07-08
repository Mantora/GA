#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>
#include <math.h>

#include "screen_interface.h"
#include "simple_types.h"
#include "picture.h"

MSG msg;
uchar key_pressed( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
  screen_interface.open_window( hinst, 640, 480 );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 30, GLdouble( x_res ) / y_res, 2.0, 10000.0 );
  glMatrixMode( GL_MODELVIEW );

  glClearColor( 1, 1, 1, 1 );
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );//GL_MODULATE );
// glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); //<-- FÜR HAUSAUFGABE
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 

  picture surface( "surface.bmp" ); //def Textur

  GLuint texture_id; //zur Identifikation der Textur
  glGenTextures( 1, &texture_id ); //IdentifikationsID generieren und in texture_id speichern
  glBindTexture( GL_TEXTURE_2D, texture_id ); //Festlegen der aktuellen Textur

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //MAGNIFICATION -> vergrößerungsartefakte; unschärfefilter
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //MINIFICATION -> verkleinerungsartefakte; schärfefilter

  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface.xsize, surface.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.content ); //Aussehen der Textur festlegen

  glEnable( GL_TEXTURE_2D ); //Texturprojektion aktivieren (rechenintensiv)
  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  GLdouble angle = 0;

  while( key_pressed() == 0 )
  {
    glClear( GL_COLOR_BUFFER_BIT );

    glLoadIdentity();
    glTranslated( 0, 0, -80 );
    glRotated( angle, 0, 1, 0 );
    angle += 0.01;

    glBegin( GL_POLYGON );

	//glColor3d( 0.5, 0.5, 0.5 ); //Helligkeitswert finden
      glColor3d( 1, 0, 0 );  glTexCoord2d( 0, 0 );  glVertex3d( -10, -10, 0 );
      glColor3d( 0, 1, 0 );  glTexCoord2d( 1, 0 );  glVertex3d(  10, -10, 0 );
      glColor3d( 0, 0, 1 );  glTexCoord2d( 1, 1 );  glVertex3d(  10,  10, 0 );
      glColor3d( 0, 0, 0 );  glTexCoord2d( 0, 1 );  glVertex3d( -10,  10, 0 );

    glEnd();

    screen_interface.swap_buffers();
  }
  
  return msg.wParam;
}

uchar key_pressed( void )
{
  if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
  {
    if( msg.message == WM_QUIT || msg.message == WM_KEYDOWN ) return 1;

    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  return 0;
}

