#ifndef MATRIX_H
#define MATRIX_H

#include <gl\glew.h>

#include "simple_types.h"

class matrix
{
  private:
    GLdouble mx[ 16 ];

    void multiplicate( GLdouble nm[ 16 ] );

  public:
    void rotate_x( GLdouble alpha );
    void rotate_y( GLdouble alpha );
    void rotate_z( GLdouble alpha );

    void translate( GLdouble xt, GLdouble yt, GLdouble zt );
	void translate( vertex v );

    void scale( GLdouble xs, GLdouble ys, GLdouble zs );

    vertex operator *( vertex v );

    void clear( void );

    matrix( void ) { clear(); }
};

#endif