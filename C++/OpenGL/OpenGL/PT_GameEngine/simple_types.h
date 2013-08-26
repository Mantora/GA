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

struct vector
{
  GLdouble x, y, z;

  double length( void ) {  return sqrt( x*x + y*y + z*z );  }

  vector( void ) : x( 0 ), y( 0 ), z( 0 ) { }
  vector( double vx, double vy, double vz ) : x( vx ), y( vy ), z( vz ) { }
};

struct local_system
{
  vertex pos;
  vector right, up, sight;

  local_system( void )
  {
    pos = vertex( 0, 0, 0 );  right = vector( 1, 0, 0 );  up = vector( 0, 1, 0 );  sight = vector( 0, 0, 1 );
  }
};

#endif