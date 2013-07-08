#include "matrix.h"

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

void matrix::rotate_x( GLdouble alpha )
{
  GLdouble rm[ 16 ];

  const GLdouble pi = 3.1415926535;
  GLdouble s = sin( (pi * alpha) / 180.0 );
  GLdouble c = cos( (pi * alpha) / 180.0 );

  rm[ 0 ] = 1;  rm[ 4 ] = 0;  rm[ 8  ] = 0;  rm[ 12 ] = 0;
  rm[ 1 ] = 0;  rm[ 5 ] = c;  rm[ 9  ] =-s;  rm[ 13 ] = 0;
  rm[ 2 ] = 0;  rm[ 6 ] = s;  rm[ 10 ] = c;  rm[ 14 ] = 0;
  rm[ 3 ] = 0;  rm[ 7 ] = 0;  rm[ 11 ] = 0;  rm[ 15 ] = 1;

  multiplicate( rm );
}

void matrix::rotate_y( GLdouble alpha )
{
  GLdouble rm[ 16 ];

  const GLdouble pi = 3.1415926535;
  GLdouble s = sin( (pi * alpha) / 180.0 );
  GLdouble c = cos( (pi * alpha) / 180.0 );

  rm[ 0 ] = c;  rm[ 4 ] = 0;  rm[ 8  ] = s;  rm[ 12 ] = 0;
  rm[ 1 ] = 0;  rm[ 5 ] = 1;  rm[ 9  ] = 0;  rm[ 13 ] = 0;
  rm[ 2 ] =-s;  rm[ 6 ] = 0;  rm[ 10 ] = c;  rm[ 14 ] = 0;
  rm[ 3 ] = 0;  rm[ 7 ] = 0;  rm[ 11 ] = 0;  rm[ 15 ] = 1;

  multiplicate( rm );
}

void matrix::rotate_z( GLdouble alpha )
{
  GLdouble rm[ 16 ];

  const GLdouble pi = 3.1415926535;
  GLdouble s = sin( (pi * alpha) / 180.0 );
  GLdouble c = cos( (pi * alpha) / 180.0 );

  rm[ 0 ] = c;  rm[ 4 ] =-s;  rm[ 8  ] = 0;  rm[ 12 ] = 0;
  rm[ 1 ] = s;  rm[ 5 ] = c;  rm[ 9  ] = 0;  rm[ 13 ] = 0;
  rm[ 2 ] = 0;  rm[ 6 ] = 0;  rm[ 10 ] = 1;  rm[ 14 ] = 0;
  rm[ 3 ] = 0;  rm[ 7 ] = 0;  rm[ 11 ] = 0;  rm[ 15 ] = 1;

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

void matrix::translate( vertex v )
{
  GLdouble tm[ 16 ];

  tm[ 0 ] = 1;   tm[ 4 ] = 0;   tm[ 8  ] = 0;   tm[ 12 ] = v.wx;
  tm[ 1 ] = 0;   tm[ 5 ] = 1;   tm[ 9  ] = 0;   tm[ 13 ] = v.wy;
  tm[ 2 ] = 0;   tm[ 6 ] = 0;   tm[ 10 ] = 1;   tm[ 14 ] = v.wz;
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

vertex matrix::operator *( vertex p )
{
  GLdouble wx = p.wx * mx[ 0 ] + p.wy * mx[ 4 ] + p.wz * mx[ 8  ] + mx[ 12 ];
  GLdouble wy = p.wx * mx[ 1 ] + p.wy * mx[ 5 ] + p.wz * mx[ 9  ] + mx[ 13 ];
  GLdouble wz = p.wx * mx[ 2 ] + p.wy * mx[ 6 ] + p.wz * mx[ 10 ] + mx[ 14 ];

  p.wx = wx;  p.wy = wy;  p.wz = wz;  return p;
}
/*
pixel matrix::operator *( pixel a )
{
	vertex p;
	p.wx = a.x;
	p.wy = a.y;
	p.wz = a.z;

	GLdouble wx = p.wx * mx[ 0 ] + p.wy * mx[ 4 ] + p.wz * mx[ 8  ] + mx[ 12 ];
	GLdouble wy = p.wx * mx[ 1 ] + p.wy * mx[ 5 ] + p.wz * mx[ 9  ] + mx[ 13 ];
	GLdouble wz = p.wx * mx[ 2 ] + p.wy * mx[ 6 ] + p.wz * mx[ 10 ] + mx[ 14 ];

	a.x = wx;
	a.y = wy;
	a.z = wz;  
	
	return a;
}
*/
void matrix::clear( void )
{
  mx[ 0 ] = 1;  mx[ 4 ] = 0;  mx[ 8  ] = 0;  mx[ 12 ] = 0;
  mx[ 1 ] = 0;  mx[ 5 ] = 1;  mx[ 9  ] = 0;  mx[ 13 ] = 0;
  mx[ 2 ] = 0;  mx[ 6 ] = 0;  mx[ 10 ] = 1;  mx[ 14 ] = 0;
  mx[ 3 ] = 0;  mx[ 7 ] = 0;  mx[ 11 ] = 0;  mx[ 15 ] = 1;
}
