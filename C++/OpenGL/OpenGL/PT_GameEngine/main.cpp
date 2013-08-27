#include <windows.h>
#include <gl\glew.h>
#include <gl\glu.h>

#include <time.h>

//FILE HANDLING
#include <iostream>
#include <fstream>
#include <string>
////////////////

#include "screen_interface.h"
#include "simple_types.h"
#include "input_interface.h"

#include "charset.h"
#include "matrix.h"

#include "3DPong.h"

using namespace std;


#define PI 3.1415926535


//Prototypen
uchar handle_input( void );
void drawTest(void);
void drawCircle(void);

vertex* DanielRotAll(float xRot, float yRot, float zRot, float xPos, float yPos, float zPos)
{
   //Für x Rotation
  yPos = cos(xRot *(PI / 180.0f)) * yPos +-sin (xRot * (PI / 180.0f)) * zPos;
  zPos = sin(xRot *(PI / 180.0f)) * yPos + cos (xRot * (PI / 180.0f)) * zPos;
 
  //Für y Rotation
  xPos =  cos(yRot * (PI / 180.0f)) * xPos + sin (yRot * (PI / 180.0f)) * zPos;
  zPos = -sin(yRot * (PI / 180.0f)) * xPos + cos (yRot * (PI / 180.0f)) * zPos;

  //Für z Rotation
  xPos = cos(zRot * (PI / 180.0f)) * xPos + -sin(zRot * (PI / 180.0f)) * yPos;
  yPos = sin(zRot * (PI / 180.0f)) * xPos +  cos(zRot * (PI / 180.0f)) * yPos;

  return new vertex( xPos, yPos, zPos );
}

int WINAPI WinMain( HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdl, int cmds )
{
	screen_interface.open_window( hinst, 1100, 700 );

	glMatrixMode( GL_PROJECTION ); //http://www.opengl.org/sdk/docs/man2/xhtml/glMatrixMode.xml

	glLoadIdentity(); //http://wiki.delphigl.com/index.php/glLoadIdentity

	//3D
	gluPerspective( 30, GLdouble( x_res ) / y_res, 0.1f, 10000.0f );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	Spielfeld* spielfeld = new Spielfeld();
	Spieler1* spieler1 = new Spieler1();
	Spieler2* spieler2 = new Spieler2();
	Ball* ball = new Ball();

	// Matrixdefinitionen
	Matrix m;

	float f_player1_startX = -3.75f; //-4.75
	float f_player2_startX = 7.75f; //9.75

	m.translate( f_player1_startX, 0, 0 );
	spieler1->update_pos( m );
	spieler1->v_globalPos->wx += f_player1_startX;

	m.translate( f_player2_startX, 0, 0 );
	spieler2->update_pos( m );
	spieler2->v_globalPos->wx = (f_player1_startX + f_player2_startX);


	//Locale Ausrichtung def:
	float rotMapSpeed = 0.1f;
	local_system user_ls;
	user_ls.pos.wz = 20;

	m.clear();
	m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
	m.rows( user_ls.right, user_ls.up, user_ls.sight );

	spielfeld->update_pos( m );
	ball->update_pos( m );
	spieler1->update_pos( m );
	spieler2->update_pos( m );

//	glPixelZoom( 2, 2 ); //ändern der schriftgröße von write

	vertex v_rot(0,0,0);
	while( handle_input() == 0 )
	{
		glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm löschen


		m.clear();
//		m.translate( 0,0,20);
//		m.rotate_x( 0.01f );
//		m.rotate_y( 0.01f );
//		m.rotate_z( 0.01f );
//		m.translate( 0,0,-20);

					
//		m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
//		m.rows( user_ls.right, user_ls.up, user_ls.sight );

		/* P1 */
		if( spieler1->isBot )
		{
			spieler1->PerfectBotMovement( ball );

			char hintActivateBotP1[64] = { "P1: Press 'v' to DEactivate ultimateBot" };
			chars.write( 0, y_res - 20, hintActivateBotP1 );

			if( input.key_pressed('V') )
			{
				spieler1->isBot = !spieler1->isBot;
			}
		}
		else
		{
			char hintActivateBotP1[64] = { "P1: Press 'v' to Activate ultimateBot" };
			chars.write( 0, y_res - 20, hintActivateBotP1 );

			if( input.key_pressed('V') )
			{
				spieler1->isBot = !spieler1->isBot;
			}

			m.clear();

			m.translate( spieler1->localPosition->wx, spieler1->localPosition->wy, spieler1->localPosition->wz );
			//bewegung P1
			float movementSpeed_P1 = 0.01f; 
			if( input.key_pressed('D') && spieler1->localPosition->wy > -2.5f)
			{
				spieler1->localPosition->wy -= movementSpeed_P1; 
				spieler1->v_globalPos->wy += movementSpeed_P1;
			}
			if( input.key_pressed('E') && spieler1->localPosition->wy < 2.5f)
			{
				spieler1->localPosition->wy += movementSpeed_P1; 
				spieler1->v_globalPos->wy -= movementSpeed_P1;
			}
			if( input.key_pressed('F') && spieler1->localPosition->wz > -2.5f)
			{
				spieler1->localPosition->wz -= movementSpeed_P1; 
				spieler1->v_globalPos->wz -= movementSpeed_P1;
			}
			if( input.key_pressed('S') && spieler1->localPosition->wz < 2.5f)
			{
				spieler1->localPosition->wz += movementSpeed_P1; 
				spieler1->v_globalPos->wz += movementSpeed_P1;
			}
			m.translate( -spieler1->localPosition->wx, -spieler1->localPosition->wy, -spieler1->localPosition->wz );
			
			spieler1->update_pos( m );
		}

		/* P2 */
		if( spieler2->isBot )
		{
			spieler2->PerfectBotMovement( ball );

			char hintActivateBotP2[64] = { "P2: Press 'b' to DEactivate ultimateBot" };
			chars.write( x_res * 0.7f, y_res - 20, hintActivateBotP2 );

			if( input.key_pressed('B') )
			{
				spieler2->isBot = !spieler2->isBot;
			}
		}
		else
		{
			char hintActivateBotP2[64] = { "P2: Press 'b' to Activate ultimateBot" };
			chars.write( x_res * 0.7f, y_res - 20, hintActivateBotP2 );

			if( input.key_pressed('B') )
			{
				spieler2->isBot = !spieler2->isBot;
			}

			m.clear();
			m.translate( spieler2->localPosition->wx, spieler2->localPosition->wy, spieler2->localPosition->wz );
			//bewegung P2
			if( input.key_pressed('K') && spieler2->localPosition->wy > -2.5f)
			{
				spieler2->localPosition->wy -= 0.001f;
			}
			if( input.key_pressed('I') && spieler2->localPosition->wy < 2.5f) 
			{
				spieler2->localPosition->wy += 0.001f;
			}
			if( input.key_pressed('L') && spieler2->localPosition->wz > -2.5f) 
			{
				spieler2->localPosition->wz -= 0.001f;
			}
			if( input.key_pressed('J') && spieler2->localPosition->wz < 2.5f) 
			{
				spieler2->localPosition->wz += 0.001f;
			}

			m.translate( -spieler2->localPosition->wx, -spieler2->localPosition->wy, -spieler2->localPosition->wz );

			spieler2->update_pos( m );
		}
		

		m.clear();
		ball->doRandomMovement( spielfeld, user_ls );

		spieler1->check4BallContakt( ball );
		spieler2->check4BallContakt( ball );

		//prüfen auf punkte:
		if( ball->localPosition->wx < spielfeld->v_boundsUHL->wx-2 )
		{
			spieler2->points++;
			ball = new Ball();

			Matrix m;
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
			//m.rows( user_ls.right, user_ls.up, user_ls.sight );

			ball->update_pos( m );
			ball->v_direction = DanielRotAll( v_rot.wx,  v_rot.wy,  v_rot.wz, ball->v_direction->wx, ball->v_direction->wy, ball->v_direction->wz);
		}

		if( ball->localPosition->wx > spielfeld->v_boundsUVR->wx+2 )
		{
			spieler1->points++;
			ball = new Ball();
			ball->respawn();

			Matrix m;
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
			//m.rows( user_ls.right, user_ls.up, user_ls.sight );

			ball->update_pos( m );
			ball->v_direction = DanielRotAll( v_rot.wx,  v_rot.wy,  v_rot.wz, ball->v_direction->wx, ball->v_direction->wy, ball->v_direction->wz);
		}

		/* Sicht aus der Localen Ausrichtung*/
		//sicht nach der localen ausrichtung ausrichten
		if( input.key_pressed( VK_DOWN ) )
		{
			m.clear();

			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz );
			m.rotate_x( -rotMapSpeed );
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
			v_rot.wx -= rotMapSpeed;
		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );
		//	ball->v_direction = m * ball->v_direction;

			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}
		if( input.key_pressed( VK_UP ) )
		{
			m.clear();

			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz );
			m.rotate_x( +rotMapSpeed );
			v_rot.wx += rotMapSpeed;
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );
		//	ball->v_direction = m * ball->v_direction;

			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}

		if( input.key_pressed( VK_LEFT ) )
		{
			m.clear();
			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz );
			m.rotate_y( +rotMapSpeed );
			v_rot.wy += rotMapSpeed;
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );
			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}
		if( input.key_pressed( VK_RIGHT ) )
		{
			m.clear();
			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz );
			m.rotate_y( -rotMapSpeed );
			v_rot.wx -= rotMapSpeed;
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );

			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}
		if( input.key_pressed( VK_PRIOR ) )
		{
			m.clear();
			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz );
			m.rotate_z( -rotMapSpeed );
			v_rot.wz -= rotMapSpeed;
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );
			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}
		if( input.key_pressed( VK_DELETE ) )
		{
			m.clear();
			m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz );
			m.rotate_z( +rotMapSpeed );
			v_rot.wz += rotMapSpeed;
			m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );
			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}
		
		if( input.key_pressed( VK_END ) )
		{
			m.clear();
			m.translate( 0, 0, +rotMapSpeed );

			user_ls.pos.wz -= rotMapSpeed;

		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );
			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}
		if( input.key_pressed( VK_HOME ) )
		{
			m.clear();
			m.translate( 0, 0, -rotMapSpeed );
			user_ls.pos.wz += rotMapSpeed;

		//	user_ls = m * user_ls;
			
			spielfeld->update_pos( m );
			ball->update_pos( m );
			spieler1->update_pos( m );
			spieler2->update_pos( m );
		}

		ball->v_direction = DanielRotAll( v_rot.wx,  v_rot.wy,  v_rot.wz, ball->v_direction->wx, ball->v_direction->wy, ball->v_direction->wz);
//////////////////////////////////////////////////////////////////////////////////////////

		//anzeigen
		spielfeld->display();
		spieler1->display();
		spieler2->display();
		ball->display();


		//GUI:
		char countPoints[32] = { "XX : XX" };
		sprintf( countPoints, "%d : %d", spieler1->points, spieler2->points);
		chars.write( x_res * 0.5f - 14, y_res - 20, countPoints );

		char countBallHits[32] = { "XX : XX" };
		sprintf( countBallHits, "%d : %d", spieler1->ballHits, spieler2->ballHits);
		chars.write( x_res * 0.5f - 14, y_res - 40, countBallHits );

		//DEBUG:
		char DEBUG_SPIELFELD[128] = { "XX : XX" };
		sprintf( DEBUG_SPIELFELD, "spielfeld->v_globalPos: x:%f y:%f z:%f", spielfeld->v_globalPos->wx, spielfeld->v_globalPos->wy, spielfeld->v_globalPos->wz);
		chars.write( 0, 0, DEBUG_SPIELFELD );

		char DEBUG_BALL[128] = { "XX : XX" };
		sprintf( DEBUG_BALL, "ball->v_globalPos: x:%f y:%f z:%f", ball->v_globalPos->wx, ball->v_globalPos->wy, ball->v_globalPos->wz);
		chars.write( 0, 20, DEBUG_BALL );

		char DEBUG_P1[128] = { "XX : XX" };
		sprintf( DEBUG_P1, "spieler1->v_globalPos: x:%f y:%f z:%f", spieler1->v_globalPos->wx, spieler1->v_globalPos->wy, spieler1->v_globalPos->wz);
		chars.write( 0, 40, DEBUG_P1 );

		char DEBUG_P2[128] = { "XX : XX" };
		sprintf( DEBUG_P2, "spieler2->v_globalPos: x:%f y:%f z:%f", spieler2->v_globalPos->wx, spieler2->v_globalPos->wy, spieler2->v_globalPos->wz);
		chars.write( 0, 60, DEBUG_P2 );

		screen_interface.swap_buffers(); // buffer leeren ist hier automatisch drin
//		glFlush(); //buffer leeren
	}
  
	return input.msg.wParam;
}

void drawCircle()
{
	//Bildschirmmittelpunkt
	GLdouble middleX = screen_interface.get_xr()/2;
	GLdouble middleY = screen_interface.get_yr()/2;

	//einen neuen Pixel definieren
	GLdouble newX = rand() % screen_interface.get_xr();
	GLdouble newY = rand() % screen_interface.get_yr();

	//distanz von der Mitte zum Punkt
	GLdouble dis = sqrt( (newX-middleX)*(newX-middleX) + (newY-middleY)*(newY-middleY) );

	if( dis < 10 )
	{
		glColor3d(1,0,0);
		glVertex2d( newX, newY );
	}
}

void drawTest()
{
	GLdouble borderOutside = 100;
	GLdouble borderInside = 400;

	GLdouble newX = rand() % screen_interface.get_xr();
	GLdouble newY = rand() % screen_interface.get_yr();

	GLdouble middleX = screen_interface.get_xr()/2;
	GLdouble middleY = screen_interface.get_yr()/2;

	GLdouble maxDis = sqrt( (1-middleX)*(1-middleX) + (1-middleY)*(1-middleY) );
	GLdouble dis = sqrt( (newX-middleX)*(newX-middleX) + (newY-middleY)*(newY-middleY) );

	if( newX < borderOutside || newX > screen_interface.get_xr()-borderOutside || newY > screen_interface.get_yr()-borderOutside || newY < borderOutside)
	{
		if( dis < 400 )
		{
			glColor3d( dis/maxDis, dis/maxDis, 0 );
		}
		else
		glColor3d( 0, 0, dis/maxDis );
	}
	else if(dis < 200)
	{
		glColor3d( dis/maxDis, dis/maxDis, 0 );
	}
	else if( (newX > middleX-borderInside/2) && (newX < middleX+borderInside/2) && (newY < middleY+borderInside/2) && (newY > middleY-borderInside/2) )
	{
		//inneres Quadrat
		glColor3d( 0, dis/maxDis, 0 );
	}
	else if( dis < 300 )
	{
		glColor3d( dis/maxDis, dis/maxDis, 0 );
	}
	else
	{
		glColor3d( dis/maxDis, 0, 0 );
	}

	glVertex2d( newX, newY );
}

uchar handle_input( void )
{
  if( input.check() == 1 ) return 1;
  if( input.event_key == VK_ESCAPE ) return 1;

  return 0;
}
