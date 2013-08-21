#include <gl\glew.h>

#include "matrix.h"
#include "picture.h"

class Landscape
{
	private:
		int size;
		vertex* points;
		//variable zum speichern der verschiebung mit "matrix.translate"
		vertex* translation;

	public:
		Landscape( int size, picture* p );
		~Landscape();

		//anzeigefunktionen
		void draw( matrix m );
		void drawWireframe( matrix m );

		//matrixfunktionen
		void updatePos( matrix m );

		//funktionen zum speichern der verschiebung
		void setTranslation( double x, double y, double z );
		vertex* getTranslation();
};

Landscape::Landscape( int size, picture* p )
{
	this->size = size;

	this->translation = new vertex(0,0,0);

	this->points = 0;
	this->points = new vertex[ size * size ]; // array mit size*size elementen

    picture height_colors( "height_colors.bmp" );

	double fix = (size - 1) * 0.5f;

	//dyn Array füllen
	for( int x = 0; x < size; x++ )
	{
		for( int y = 0; y < size; y++ )
		{
			this->points[ size * y + x ].wx = x - fix;
			this->points[ size * y + x ].wy = y - fix;
			this->points[ size * y + x ].wz = p->content[size * y + x].red * 0.25f ;
			this->points[ size * y + x ].c = height_colors.content[ p->content[size * y + x ].red ];

            this->points[ size * y + x ].tx = double( x*4 ) / (size - 1);
            this->points[ size * y + x ].ty = double( y*4 ) / (size - 1);

            this->points[ size * y + x ].c.red = GLubyte( (p->content[size * y + x ].red / 255.0) * this->points[ size * y + x ].c.red );
            this->points[ size * y + x ].c.green = GLubyte( (p->content[size * y + x ].red / 255.0) * this->points[ size * y + x ].c.green );
            this->points[ size * y + x ].c.blue = GLubyte( (p->content[size * y + x ].red / 255.0) * this->points[ size * y + x ].c.blue );
		}
	}
}

Landscape::~Landscape()
{
	delete [] points;
}

void Landscape::draw( matrix m )
{
	glBegin( GL_POINTS );

	for( int x = 0; x < this->size; x++ )
	{
		for( int y = 0; y < this->size; y++ )
		{
			vertex current = m * this->points[ size * y + x ];

			glVertex3d( current.wx, current.wy, current.wz );
		}
	}

	glEnd();
}

void Landscape::drawWireframe( matrix m )
{
  long offset = 0;

  for( long y=0 ; y<size-1 ; y++ )
  {
    glBegin( GL_TRIANGLE_STRIP );

      for( long x=0 ; x<this->size ; x++ )
	  {
//        glColor3ubv( (GLubyte *) &this->points[ offset ].c );
		glTexCoord2dv( (GLdouble *) &this->points[ offset ].tx );
		vertex current = m * this->points[ offset ];
        glVertex3dv( (GLdouble *) &current );
        
//        glColor3ubv( (GLubyte *) &this->points[ offset+this->size ].c );
		glTexCoord2dv( (GLdouble *) &this->points[ offset+this->size ].tx );
	    current = m * this->points[ offset+this->size ];
        glVertex3dv( (GLdouble *) &current );

	    offset++;
	  }

    glEnd();
  }

/*
	//glBegin( GL_TRIANGLE_STRIP );
	
	for( int x = 0; x < this->size-1; x++ )
	{
		for( int y = 0; y < this->size-1; y++ )
		{
			glBegin( GL_TRIANGLES );
			
			if( x < this->size-1 && y < this->size-1)
			{
				vertex current = this->points[ (size * y) + x ];
				glVertex3d( current.wx, current.wy, current.wz );

				current = this->points[ (size * y) + x+1 ];
				glVertex3d( current.wx, current.wy, current.wz );

				current = this->points[ (size * (y+1)) + x ];
				glVertex3d( current.wx, current.wy, current.wz );
			}
			glEnd();
		}
	}

	for( int x = this->size-1; x > 0; x-- )
	{
		for( int y = this->size-1; y > 0; y-- )
		{
			glBegin( GL_TRIANGLES );
			
			if( x > 0 && y > 0)
			{
				vertex current = this->points[ (size * y) - x ];
				glVertex3d( current.wx, current.wy, current.wz );

				current = this->points[ (size * y) - x-1 ];
				glVertex3d( current.wx, current.wy, current.wz );

				current = this->points[ (size * (y-1)) - x ];
				glVertex3d( current.wx, current.wy, current.wz );
			}
			glEnd();
		}
	}
*/
}

//matrixfunktionen
void Landscape::updatePos( matrix m )
{
	int lengt = this->size * this->size;

	for( int i = 0; i < lengt; i++)
	{
		this->points[i] = m * this->points[i];
	}
}

//funktionen zum speichern der verschiebung
void Landscape::setTranslation( double x, double y, double z )
{
	this->translation->wx += x;
	this->translation->wy += y;
	this->translation->wz += z;
}

vertex* Landscape::getTranslation()
{
	return this->translation;
}

