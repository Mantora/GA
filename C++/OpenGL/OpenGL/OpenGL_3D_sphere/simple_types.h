#ifndef SIMPLE_TYPES_H
#define SIMPLE_TYPES_H

#include <math.h>
#include <gl\glew.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

struct color
{
  GLubyte red, green, blue, alpha;
  
  color( void ) : red( 0 ), green( 0 ), blue( 0 ), alpha( 255 ) { }
  color( uchar r, uchar g, uchar b ) : red( r ), green( g ), blue( b ), alpha( 255 ) { }
};

struct vertex
{
  GLdouble wx, wy, wz;

  vertex( void ) : wx( 0 ), wy( 0 ), wz( 0 ) { }
  vertex( GLdouble x, GLdouble y, GLdouble z ) : wx( x ), wy( y ), wz( z ) { }
};

#endif