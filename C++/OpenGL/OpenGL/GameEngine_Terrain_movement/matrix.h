#ifndef MATRIX_H
#define MATRIX_H

#include "simple_types.h"

class matrix
{
  private:
    GLdouble mx[ 16 ];

    void multiplicate( GLdouble nm[ 16 ] );

  public:
    void rotate( double alpha, vector dir );
    void rotate_x( GLdouble alpha ) {  rotate( alpha, vector( 1, 0, 0 ) );  }
    void rotate_y( GLdouble alpha ) {  rotate( alpha, vector( 0, 1, 0 ) );  }
    void rotate_z( GLdouble alpha ) {  rotate( alpha, vector( 0, 0, 1 ) );  }

    void translate( GLdouble xt, GLdouble yt, GLdouble zt );
    void scale( GLdouble xs, GLdouble ys, GLdouble zs );

    void shear_x( GLdouble a, GLdouble b, GLdouble c );
    void shear_y( GLdouble a, GLdouble b, GLdouble c );
    void shear_z( GLdouble a, GLdouble b, GLdouble c );

    vertex operator * ( vertex v );
    vector operator * ( vector v );
    local_system operator * ( local_system ls );

    void rows( vector a, vector b, vector c );
    void columns( vector a, vector b, vector c );

    void clear( void );
    void load_hardware( void ) {  glLoadMatrixd( mx );  }
    void multiply_hardware( void ) {  glMultMatrixd( mx );  }

    matrix( void ) { clear(); }

  friend matrix operator * ( matrix a, matrix b );
};

matrix operator * ( matrix second, matrix first )
{
  first.multiplicate( second.mx );
  return first;
}

void matrix::multiplicate( GLdouble nm[ 16 ] )
{
  char x, a, b;
  GLdouble tm[ 16 ];

  for( x=0 ; x<16 ; x++ )
  {
    a = x % 4;  b = (x / 4) * 4;

    tm[ x ] = nm[ a    ] * mx[ b   ] +
              nm[ a+4  ] * mx[ b+1 ] +
              nm[ a+8  ] * mx[ b+2 ] +
              nm[ a+12 ] * mx[ b+3 ];
  }

  for( x=0 ; x<16 ; x++ ) mx[ x ] = tm[ x ];
}

void matrix::rotate( double alpha, vector dir )
{
  GLdouble rm[ 16 ];

  if( dir.length() < 0.0001 ) return;

  dir = (1.0 / dir.length()) * dir;
  GLdouble x = dir.x, y = dir.y, z = dir.z;

  const GLdouble pi = 3.1415926535;
  GLdouble s = sin( (pi * alpha) / 180.0 );
  GLdouble c = cos( (pi * alpha) / 180.0 );

  rm[ 0 ] = x*x*(1-c)+c;    rm[ 4 ] = x*y*(1-c)-z*s;  rm[ 8  ] = x*z*(1-c)+y*s;  rm[ 12 ] = 0;
  rm[ 1 ] = x*y*(1-c)+z*s;  rm[ 5 ] = y*y*(1-c)+c;    rm[ 9  ] = y*z*(1-c)-x*s;  rm[ 13 ] = 0;
  rm[ 2 ] = x*z*(1-c)-y*s;  rm[ 6 ] = y*z*(1-c)+x*s;  rm[ 10 ] = z*z*(1-c)+c;    rm[ 14 ] = 0;
  rm[ 3 ] = 0;              rm[ 7 ] = 0;              rm[ 11 ] = 0;              rm[ 15 ] = 1;

  multiplicate( rm );
}

void matrix::translate( GLdouble xt, GLdouble yt, GLdouble zt )
{
  GLdouble tm[ 16 ];

  tm[ 0 ] = 1;   tm[ 4 ] = 0;   tm[ 8  ] = 0;   tm[ 12 ] = xt;
  tm[ 1 ] = 0;   tm[ 5 ] = 1;   tm[ 9  ] = 0;   tm[ 13 ] = yt;
  tm[ 2 ] = 0;   tm[ 6 ] = 0;   tm[ 10 ] = 1;   tm[ 14 ] = zt;
  tm[ 3 ] = 0;   tm[ 7 ] = 0;   tm[ 11 ] = 0;   tm[ 15 ] = 1;

  multiplicate( tm );
}

void matrix::scale( GLdouble xs, GLdouble ys, GLdouble zs )
{
  GLdouble sm[ 16 ];

  sm[ 0 ] = xs;  sm[ 4 ] = 0;   sm[ 8  ] = 0;   sm[ 12 ] = 0;
  sm[ 1 ] = 0;   sm[ 5 ] = ys;  sm[ 9  ] = 0;   sm[ 13 ] = 0;
  sm[ 2 ] = 0;   sm[ 6 ] = 0;   sm[ 10 ] = zs;  sm[ 14 ] = 0;
  sm[ 3 ] = 0;   sm[ 7 ] = 0;   sm[ 11 ] = 0;   sm[ 15 ] = 1;

  multiplicate( sm );
}

void matrix::shear_x( double a, double b, double c )
{
  GLdouble sm[ 16 ];

  sm[ 0 ] = a;   sm[ 4 ] = b;   sm[ 8  ] = c;   sm[ 12 ] = 0;
  sm[ 1 ] = 0;   sm[ 5 ] = 1;   sm[ 9  ] = 0;   sm[ 13 ] = 0;
  sm[ 2 ] = 0;   sm[ 6 ] = 0;   sm[ 10 ] = 1;   sm[ 14 ] = 0;
  sm[ 3 ] = 0;   sm[ 7 ] = 0;   sm[ 11 ] = 0;   sm[ 15 ] = 1;

  multiplicate( sm );
}

void matrix::shear_y( double a, double b, double c )
{
  GLdouble sm[ 16 ];

  sm[ 0 ] = 1;   sm[ 4 ] = 0;   sm[ 8  ] = 0;   sm[ 12 ] = 0;
  sm[ 1 ] = a;   sm[ 5 ] = b;   sm[ 9  ] = c;   sm[ 13 ] = 0;
  sm[ 2 ] = 0;   sm[ 6 ] = 0;   sm[ 10 ] = 1;   sm[ 14 ] = 0;
  sm[ 3 ] = 0;   sm[ 7 ] = 0;   sm[ 11 ] = 0;   sm[ 15 ] = 1;

  multiplicate( sm );
}

void matrix::shear_z( double a, double b, double c )
{
  GLdouble sm[ 16 ];

  sm[ 0 ] = 1;   sm[ 4 ] = 0;   sm[ 8  ] = 0;   sm[ 12 ] = 0;
  sm[ 1 ] = 0;   sm[ 5 ] = 1;   sm[ 9  ] = 0;   sm[ 13 ] = 0;
  sm[ 2 ] = a;   sm[ 6 ] = b;   sm[ 10 ] = c;   sm[ 14 ] = 0;
  sm[ 3 ] = 0;   sm[ 7 ] = 0;   sm[ 11 ] = 0;   sm[ 15 ] = 1;

  multiplicate( sm );
}

vertex matrix::operator * ( vertex p )
{
  GLdouble wx = p.wx * mx[ 0 ] + p.wy * mx[ 4 ] + p.wz * mx[ 8  ] + mx[ 12 ];
  GLdouble wy = p.wx * mx[ 1 ] + p.wy * mx[ 5 ] + p.wz * mx[ 9  ] + mx[ 13 ];
  GLdouble wz = p.wx * mx[ 2 ] + p.wy * mx[ 6 ] + p.wz * mx[ 10 ] + mx[ 14 ];

  p.wx = wx;  p.wy = wy;  p.wz = wz;  return p;
}

vector matrix::operator * ( vector v )
{
  GLdouble x = v.x * mx[ 0 ] + v.y * mx[ 4 ] + v.z * mx[ 8 ];
  GLdouble y = v.x * mx[ 1 ] + v.y * mx[ 5 ] + v.z * mx[ 9 ];
  GLdouble z = v.x * mx[ 2 ] + v.y * mx[ 6 ] + v.z * mx[ 10 ];

  return vector( x, y, z );
}

local_system matrix::operator * ( local_system ls )
{
  ls.pos = this->operator * ( ls.pos );
  ls.right = this->operator * ( ls.right );
  ls.up = this->operator * ( ls.up );
  ls.sight = this->operator * ( ls.sight );

  return ls;
}

void matrix::clear( void )
{
  mx[ 0 ] = 1;  mx[ 4 ] = 0;  mx[ 8  ] = 0;  mx[ 12 ] = 0;
  mx[ 1 ] = 0;  mx[ 5 ] = 1;  mx[ 9  ] = 0;  mx[ 13 ] = 0;
  mx[ 2 ] = 0;  mx[ 6 ] = 0;  mx[ 10 ] = 1;  mx[ 14 ] = 0;
  mx[ 3 ] = 0;  mx[ 7 ] = 0;  mx[ 11 ] = 0;  mx[ 15 ] = 1;
}

void matrix::rows( vector a, vector b, vector c )
{
  GLdouble rm[ 16 ];

  rm[ 0 ] = a.x;  rm[ 4 ] = a.y;  rm[ 8  ] = a.z;  rm[ 12 ] = 0;
  rm[ 1 ] = b.x;  rm[ 5 ] = b.y;  rm[ 9  ] = b.z;  rm[ 13 ] = 0;
  rm[ 2 ] = c.x;  rm[ 6 ] = c.y;  rm[ 10 ] = c.z;  rm[ 14 ] = 0;
  rm[ 3 ] = 0;    rm[ 7 ] = 0;    rm[ 11 ] = 0;    rm[ 15 ] = 1;

  multiplicate( rm );
}

void matrix::columns( vector a, vector b, vector c )
{
  GLdouble cm[ 16 ];

  cm[ 0 ] = a.x;  cm[ 4 ] = b.x;  cm[ 8  ] = c.x;  cm[ 12 ] = 0;
  cm[ 1 ] = a.y;  cm[ 5 ] = b.y;  cm[ 9  ] = c.y;  cm[ 13 ] = 0;
  cm[ 2 ] = a.z;  cm[ 6 ] = b.z;  cm[ 10 ] = c.z;  cm[ 14 ] = 0;
  cm[ 3 ] = 0;    cm[ 7 ] = 0;    cm[ 11 ] = 0;    cm[ 15 ] = 1;

  multiplicate( cm );
}

#endif