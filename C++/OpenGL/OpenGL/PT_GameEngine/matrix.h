#ifndef MATRIX_H
#define MATRIX_H

#include "simple_types.h"


class Matrix
{
  private:
    GLdouble mx[ 16 ];

    void multiplicate( GLdouble nm[ 16 ] );

  public:
	void rotate( double alpha, vector dir );
    void rotate_x( GLdouble alpha );
    void rotate_y( GLdouble alpha );
    void rotate_z( GLdouble alpha );
    void translate( GLdouble xt, GLdouble yt, GLdouble zt );
    void scale( GLdouble xs, GLdouble ys, GLdouble zs );

	vertex operator *( vertex v );
	vertex* operator *( vertex* v );
    vector operator * ( vector v );
    local_system operator * ( local_system ls );

	void rows( vector a, vector b, vector c );

    void clear( void );

    Matrix( void ) { clear(); }
};

#endif