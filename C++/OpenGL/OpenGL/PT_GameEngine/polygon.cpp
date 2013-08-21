#include "polygon.h"

//#include "picture.h"

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

	calculateNormal( this->points[1], this->points[2] );
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
	strcpy(	this->textureName, textureName );

	this->texture.load( textureName ); //def Textur

	glGenTextures( 1, &texture_id ); //IdentifikationsID generieren und in texture_id speichern

	glBindTexture( GL_TEXTURE_2D, texture_id ); //Festlegen der aktuellen Textur
//	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->texture.xsize, this->texture.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture.content ); //Aussehen der Textur festlegen
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //MAGNIFICATION -> vergrößerungsartefakte; unschärfefilter
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //MINIFICATION -> verkleinerungsartefakte; schärfefilter

	glEnable( GL_TEXTURE_2D ); //Texturprojektion aktivieren (rechenintensiv)
}

void polygon::setColorIndex( int colorIndex )
{
	this->colorIndex = colorIndex;
}

//Anzeigefunktionen
void polygon::display()
{
	//vor jeder anzeige, die normalen neu berechen:
	vertex v1 = VectCreate( this->points[0], this->points[1] );
	vertex v2 = VectCreate( this->points[0], this->points[2] );
	
	calculateNormal( v1, v2 );

	//TEST: NORMALE ANZEIGEN
	drawNormal();

	//weil schön ist: MESH anzeigen
	drawMesh();

	//normale angeben
	glNormal3d( this->normal.wx, this->normal.wy, this->normal.wz ); 

	//textur festlegen
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, this->texture.xsize, this->texture.ysize, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture.content ); //Aussehen der Textur festlegen

	// Farbe des Polygons festlegen
	glColor3d( 1, 1, 1 ); //Helligkeitswert finden
//	glColor3d( this->helligkeit, this->helligkeit, this->helligkeit ); //Helligkeitswert finden

	//glBegin( GL_TRIANGLE_FAN );
	glBegin( GL_POLYGON );

	for( long i = 0; i < this->pointsCount; i++ )
	{
		//texturCoordinaten in 2d
//		vertex texCoords = this->textureCoords[ i ];
//		glTexCoord2d( texCoords.wx, texCoords.wy );
		
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
}

vertex polygon::VectCreate( vertex p_start, vertex p_end )
{
	vertex v;
    v.wx = p_end.wx - p_start.wx;
    v.wy = p_end.wy - p_start.wy;
    v.wz = p_end.wz - p_start.wz;

    VectNormalize( v );

	return v;
}

//funktion zum berechnen der normalen
void polygon::calculateNormal( vertex p_vector1, vertex p_vector2 )
{
	//anwendung des Kreuzproduktes:
	this->normal.wx = (p_vector1.wy * p_vector2.wz) - (p_vector1.wz * p_vector2.wy);
	this->normal.wy = (p_vector1.wz * p_vector2.wx) - (p_vector1.wx * p_vector2.wz);
	this->normal.wz = (p_vector1.wx * p_vector2.wy) - (p_vector1.wy * p_vector2.wx);

	VectNormalize( this->normal );

	vertex point_light( 10.0f, 0.0f, -1.0f);
	vertex point_zero( 0,0,0 );

	vertex vector_light = VectCreate( point_zero, point_light );

	this->helligkeit = VectScalarProduct( this->normal, vector_light );
}

double polygon::VectLenght( vertex p_vector )
{
    return (float)( sqrt(p_vector.wx*p_vector.wx + p_vector.wy*p_vector.wy + p_vector.wz*p_vector.wz) );
}

void polygon::VectNormalize( vertex& p_vector )
{
    double l_lenght;

    l_lenght = VectLenght( p_vector );
    if(l_lenght == 0) l_lenght = 1;
    p_vector.wx /= l_lenght;
    p_vector.wy /= l_lenght;
    p_vector.wz /= l_lenght;
}

double polygon::VectScalarProduct( vertex p_vector1, vertex p_vector2 )
{
    return( p_vector1.wx*p_vector2.wx + p_vector1.wy*p_vector2.wy + p_vector1.wz*p_vector2.wz );
}

//zum Testen
void polygon::drawNormal()
{
	int scaling = 1;

	vertex v_start;
	for( int i = 0; i < this->pointsCount; i++ )
	{
		v_start.wx += this->points[i].wx;
		v_start.wy += this->points[i].wy;
		v_start.wz += this->points[i].wz;
	}
	v_start.wx /= this->pointsCount;
	v_start.wy /= this->pointsCount;
	v_start.wz /= this->pointsCount;

	glBegin( GL_LINES );
		switch( this->colorIndex )
		{
			case 0: glColor3d(1,0,0); break; //rot
			case 1: glColor3d(0,1,0); break; //grün
			case 2: glColor3d(0,0,1); break; //blau
			case 3: glColor3d(1,1,0); break; //gelb
			case 4: glColor3d(0.83,0.83,0.83); break; //grau
		}

		glVertex3d( v_start.wx, v_start.wy, v_start.wz );
		glVertex3d( v_start.wx + this->normal.wx*scaling, 
					v_start.wy + this->normal.wy*scaling, 
					v_start.wz + this->normal.wz*scaling );
	glEnd();

	glBegin( GL_LINES );
		glColor3d(1,1,1);
		glVertex3d( v_start.wx + this->normal.wx*scaling, 
					v_start.wy + this->normal.wy*scaling, 
					v_start.wz + this->normal.wz*scaling );
		scaling = 2;
		glVertex3d( v_start.wx + this->normal.wx*scaling, 
					v_start.wy + this->normal.wy*scaling, 
					v_start.wz + this->normal.wz*scaling );
	glEnd();
}

//Weils schön ist:
void polygon::drawMesh()
{
	glBegin( GL_LINE_LOOP );
		glColor3d(0,0,0);

		for( long i = 0; i < this->pointsCount; i++ )
		{
			vertex pos = this->points[ i ];
			glVertex3d( pos.wx, pos.wy, pos.wz );
		}

//		vertex pos = this->points[ 0 ];
//		glVertex3d( pos.wx, pos.wy, pos.wz );

	glEnd();
}
