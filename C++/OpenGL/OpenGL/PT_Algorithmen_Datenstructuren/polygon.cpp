#include "polygon.h"

#include "picture.h"

//Konstruktors
polygon::polygon()
{
	this->pointsCount = 0;
	this->points = 0;

	this->textureCoordsCount = 0;
	this->textureCoords = 0;

	this->colorIndex = 0;
}

//SET
void polygon::setPoints( const vertex* points, const int pointsCount )
{
	this->pointsCount = pointsCount;
	this->points = new vertex[ pointsCount ];

	for( int i = 0; i < pointsCount; i++ )
	{
		this->points[i].wx = points[i].wx;
		this->points[i].wy = points[i].wy;
		this->points[i].wz = points[i].wz;
	}
}

void polygon::setTextureCoords(const vertex* points, const int pointsCount )
{
	this->textureCoordsCount = pointsCount;
	this->textureCoords = new vertex[ pointsCount ];

	for( int i = 0; i < pointsCount; i++ )
	{
		this->textureCoords[i].wx = points[i].wx;
		this->textureCoords[i].wy = points[i].wy;
		this->textureCoords[i].wz = points[i].wz;
	}
}

void polygon::setTexture(char* textureName )
{
	picture surface0( textureName ); //def Textur
	GLuint texture_id0; //zur Identifikation der Textur
	glGenTextures( 1, &texture_id0 ); //IdentifikationsID generieren und in texture_id speichern

	glBindTexture( GL_TEXTURE_2D, texture_id0 ); //Festlegen der aktuellen Textur
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //MAGNIFICATION -> vergrößerungsartefakte; unschärfefilter
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //MINIFICATION -> verkleinerungsartefakte; schärfefilter
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface0.xsize, surface0.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface0.content ); //Aussehen der Textur festlegen
	glEnable( GL_TEXTURE_2D ); //Texturprojektion aktivieren (rechenintensiv)
}

void polygon::setColorIndex( int colorIndex )
{
	this->colorIndex = colorIndex;
}

//Anzeigefunktionen
void polygon::display()
{
	// Farbe des Polygons festlegen
	glColor3d( 1, 1, 1 ); //Helligkeitswert finden
/*	switch( this->colorIndex )
	{
		case 0: glColor3d(1,0,0); break; //rot
		case 1: glColor3d(0,1,0); break; //grün
		case 2: glColor3d(0,0,1); break; //blau
		case 3: glColor3d(1,1,0); break; //gelb
		case 4: glColor3d(0.83,0.83,0.83); break; //grau
	}
*/

	//glBegin( GL_TRIANGLE_FAN );
	glBegin( GL_POLYGON );

	for( long i = 0; i < this->pointsCount; i++ )
	{
		//texturCoordinaten in 2d
		vertex texCoords = this->textureCoords[ i ];
		glTexCoord2d( texCoords.wx, texCoords.wy );
		
		//position in 3D
		vertex pos = this->points[ i ];
		glVertex3d( pos.wx, pos.wy, pos.wz );
	}
	glEnd();
}

//matrix funktionen
void polygon::addMatrix( Matrix m )
{
	for( int i = 0; i < this->pointsCount; i++ )
	{
		this->points[i] = m * this->points[i];
	}

		
	//ToDelet: sind alle Vertex in "vertex* points" ?
/*	vertex test[20];
	for( int i = 0; i < pointsCount; i++ )
		test[i] = this->points[i];
*/
}
