#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>

#include <time.h>

//FILE HANDLING
#include <iostream>
#include <fstream>
#include <string>
////////////////

//#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"


#include "Matrix.h"
#include "Polyeder.h"

#include "LoadMeshFromFile.h"


using namespace std;

//Prototypen
uchar handle_input( void );

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 800, 600 );

	glMatrixMode( GL_PROJECTION ); //http://www.opengl.org/sdk/docs/man2/xhtml/glMatrixMode.xml
	glLoadIdentity(); //http://wiki.delphigl.com/index.php/glLoadIdentity
	//3D
	gluPerspective( 30, GLdouble( x_res ) / y_res, 0.1f, 10000.0f );
	glMatrixMode( GL_MODELVIEW );

	glClearColor( 1, 1, 1, 1 );
	glLineWidth( 2.0f );


//	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	glPolygonMode( GL_FRONT_AND_BACK, GL_POLYGON );
	glEnable( GL_DEPTH_TEST );

	//für Textur:
///////////////////////////////// Polyeder mit daten aus datei füllen /////////////////////////////////
	LoadMeshFromFile* mesh = new LoadMeshFromFile( "compound.tg4" );
	Polyeder* tg4Poly = new Polyeder( mesh->i_countPolygone );

	for( int i = 0; i < mesh->i_countPolygone; i++ )
	{
		//texturePositions
		vertex* textureCoords = new vertex[ mesh->polygones[i].count_vertices ];
		for( int anzahlVerts = 0; anzahlVerts < mesh->polygones[i].count_vertices; anzahlVerts++ )
		{
			int indexCurrentText = mesh->polygones[i].index_textureKoords[ anzahlVerts ];
			textureCoords[ anzahlVerts ] = vertex( 
												mesh->points2D[ indexCurrentText ].x,
												mesh->points2D[ indexCurrentText ].y,
												0
											);
		}
		tg4Poly->setTextureCoords( textureCoords, mesh->polygones[i].count_vertices );

		//textur bestimmen
		char* textureName = mesh->cstr_textureNames[ mesh->polygones[i].index_texture ];
		tg4Poly->setTexture( textureName );

		//vertexPositions
		vertex* points = new vertex[ mesh->polygones[i].count_vertices ];
		for( int anzahlVerts = 0; anzahlVerts < mesh->polygones[i].count_vertices; anzahlVerts++ )
		{
			int indexCurrentVert = mesh->polygones[i].index_pos[ anzahlVerts ];
			points[ anzahlVerts ] = vertex( 
												mesh->points3D[ indexCurrentVert ].x,
												mesh->points3D[ indexCurrentVert ].y,
												mesh->points3D[ indexCurrentVert ].z
											);
		}
		
		tg4Poly->setPolygonColor( mesh->polygones[i].index_texture );

		tg4Poly->setNextPolygon( points, mesh->polygones[i].count_vertices );
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Matrixdefinitionen
	Matrix m;
	m.translate( 0, 0, -4.0f );
	tg4Poly->update_pos( m );

//	glPointSize( 10 ); //Da das Objekt kein Polygone ist und die Pixel Float sind -> vergrößern

	/*Für Schattierung:*/
	//licht definieren
	GLfloat light_diffuse[]=  { 1.0f, 1.0f, 1.0f, 0.0f };
	//Lichtposition definieren
	GLfloat light_position[]= { 10.0f, 0.0f, -1.0f, 1.0f };
	//licht setzen
	glLightfv( GL_LIGHT1, GL_DIFFUSE,  light_diffuse );
	//Lichtpostion setzen
	glLightfv( GL_LIGHT1, GL_POSITION, light_position );
	//Licht aktivieren
//	glEnable( GL_LIGHT1 );
	//OpenGL Beleuchtung aktivieren
//	glEnable( GL_LIGHTING );
	
	float transX = 0;
	float transY = 0;
	float transZ = 0;
	while( handle_input() == 0 )
	{
		//glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm löschen
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		//Drehung
		m.clear();

		m.translate( transX, transY, transZ+4);

		//bewegung
		if( input.key_pressed('J') ) transX -= 0.01;
		if( input.key_pressed('L') ) transX += 0.01;

		if( input.key_pressed('U') ) transY -= 0.01;
		if( input.key_pressed('O') ) transY += 0.01;

		if( input.key_pressed('I') ) transZ -= 0.01;
		if( input.key_pressed('K') ) transZ += 0.01;

		//drehung
		bool autRotate = true;
		if( autRotate )
		{
			float speed = 0.1f;
			m.rotate_x( speed );
			m.rotate_y( speed );
			m.rotate_z( speed );
		}
		else
		{
			float speed = 0.1f;

			float rotX = 0;
			if( input.key_pressed('E') ) rotX -= speed;
			if( input.key_pressed('D') ) rotX += speed;
			m.rotate_x( rotX );
			
			float rotY = 0;
			if( input.key_pressed('S') ) rotY -= speed;
			if( input.key_pressed('F') ) rotY += speed;
			m.rotate_y( rotY );

			float rotZ = 0;
			if( input.key_pressed('R') ) rotZ -= speed;
			if( input.key_pressed('W') ) rotZ += speed;
			m.rotate_z( rotZ );
		}



		m.translate( -transX, -transY, -(transZ+4));

		tg4Poly->update_pos( m );
	

		tg4Poly->display();

		screen_interface.swap_buffers(); // buffer leeren ist hier automatisch drin
//		glFlush(); //buffer leeren
	}
  
	return input.msg.wParam;
}


uchar handle_input( void )
{
  if( input.check() == 1 ) return 1;
  if( input.event_key == VK_ESCAPE ) return 1;

  return 0;
}


