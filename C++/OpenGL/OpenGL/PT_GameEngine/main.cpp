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
   //F�r x Rotation
  yPos = cos(xRot *(PI / 180.0f)) * yPos +-sin (xRot * (PI / 180.0f)) * zPos;
  zPos = sin(xRot *(PI / 180.0f)) * yPos + cos (xRot * (PI / 180.0f)) * zPos;
 
  //F�r y Rotation
  xPos =  cos(yRot * (PI / 180.0f)) * xPos + sin (yRot * (PI / 180.0f)) * zPos;
  zPos = -sin(yRot * (PI / 180.0f)) * xPos + cos (yRot * (PI / 180.0f)) * zPos;

  //F�r z Rotation
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
	spieler1->isBot = true;

	Spieler2* spieler2 = new Spieler2();
	spieler2->isBot = true;
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

//	glPixelZoom( 2, 2 ); //�ndern der schriftgr��e von write

	//f�r Debug:
	bool isPause = false;

	vertex v_rot(0,0,0);
	vertex v_trans(0,0,0);
	while( handle_input() == 0 )
	{
		glClear( GL_COLOR_BUFFER_BIT ); //Bildschirm l�schen
/*
		if( input.key_pressed( VK_DOWN ) )
		{
			Matrix m;
			m.rotate_x( -rotMapSpeed );
			(*ball->v_direction) = m * (*ball->v_direction);
		}
*/
		if( spieler1->points > 4 || spieler2->points > 4 )
		{
			isPause = true;

			char PLAYER_WIN[128] = { 0 };
			if( spieler1->points > 4 )
			{
				sprintf( PLAYER_WIN, "Player 1 WIN !Press 'n' for new game");
			}

			if( spieler2->points > 4 )
			{
				sprintf( PLAYER_WIN, "Player 2 WIN !\nPress 'n' for new game");
			}

			chars.write( x_res * 0.5f, y_res * 0.5f, PLAYER_WIN );
			if( input.key_pressed( 'N' ) )
			{
				spieler1 = new Spieler1();
				spieler1->isBot = true;

				spieler2 = new Spieler2();
				spieler2->isBot = true;
				// Matrixdefinitionen
				Matrix m;

				m.translate( f_player1_startX, 0, -20 );
				spieler1->update_pos( m );
				spieler1->v_globalPos->wx += f_player1_startX;

				m.translate( f_player2_startX, 0, 0 );
				spieler2->update_pos( m );
				spieler2->v_globalPos->wx = (f_player1_startX + f_player2_startX);

				isPause = false;
			}
		}

		if( input.key_pressed( VK_SPACE ) )
		{
			isPause = !isPause;
		}

		if( !isPause )
		{
			ball->doRandomMovement( spielfeld, &v_rot );
		}

		m.clear();

//////////////////////////// P1 /////////////////////////////////////////////////
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

/////////////////////////////////////// P2 ///////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////


		//pr�fen auf punkte:
		if( ball->localPosition->wx < spielfeld->v_boundsUHL->wx-2 )
		{
			spieler2->points++;
			ball = new Ball();

			Matrix m;
			m.translate( 0, 0, -20 );

			ball->update_pos( m );
		}

		if( ball->localPosition->wx > spielfeld->v_boundsUVR->wx+2 )
		{
			spieler1->points++;
			ball = new Ball();
			ball->respawn();

			Matrix m;
			m.translate( 0, 0, -20 );

			ball->update_pos( m );
		}


		if( input.key_pressed( VK_DOWN ) )
		{
			v_rot.wx -= rotMapSpeed;
		}
		if( input.key_pressed( VK_UP ) )
		{
			v_rot.wx += rotMapSpeed;
		}

		if( input.key_pressed( VK_LEFT ) )
		{
			v_rot.wy += rotMapSpeed;
		}
		if( input.key_pressed( VK_RIGHT ) )
		{
			v_rot.wy -= rotMapSpeed;
		}

		if( input.key_pressed( VK_PRIOR ) )
		{
			v_rot.wz -= rotMapSpeed;
		}
		if( input.key_pressed( VK_DELETE ) )
		{
			v_rot.wz += rotMapSpeed;
		}
		
		if( input.key_pressed( VK_END ) )
		{
			v_trans.wz -= rotMapSpeed;
		}
		if( input.key_pressed( VK_HOME ) )
		{
			v_trans.wz += rotMapSpeed;
		}

//		ball->v_direction = DanielRotAll( v_rot.wx,  v_rot.wy,  v_rot.wz, ball->v_direction->wx, ball->v_direction->wy, ball->v_direction->wz);
//////////////////////////////////////////////////////////////////////////////////////////

		spieler1->check4BallContakt( ball );
		spieler2->check4BallContakt( ball );

		//drehung umsetzen�:
		Matrix m;
		m.translate( user_ls.pos.wx, user_ls.pos.wy, user_ls.pos.wz );
		m.rotate_x( v_rot.wx );
		m.rotate_y( v_rot.wy );
		m.rotate_z( v_rot.wz );
		m.translate( -user_ls.pos.wx, -user_ls.pos.wy, -user_ls.pos.wz );
		m.translate( v_trans.wx, v_trans.wy, v_trans.wz );

		//anzeigen
		spielfeld->display( m );
		spieler1->display( m );
		spieler2->display( m );
		ball->display( m );

		//GUI:
		char countPoints[32] = { "XX : XX" };
		sprintf( countPoints, "%d : %d", spieler1->points, spieler2->points);
		chars.write( x_res * 0.5f - 14, y_res - 20, countPoints );

		char countBallHits[32] = { "XX : XX" };
		sprintf( countBallHits, "%d : %d", spieler1->ballHits, spieler2->ballHits);
		chars.write( x_res * 0.5f - 14, y_res - 40, countBallHits );

/*		//DEBUG:
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

		char DEBUG_ROTATION[128] = { "XX : XX" };
		sprintf( DEBUG_ROTATION, "v_rot: x:%f y:%f z:%f", v_rot.wx, v_rot.wy, v_rot.wz);
		chars.write( 0, 80, DEBUG_ROTATION );

		char DEBUG_DIRECTION[128] = { "XX : XX" };
		sprintf( DEBUG_DIRECTION, "ball->v_direction->: x:%f y:%f z:%f", ball->v_direction->wx, ball->v_direction->wy, ball->v_direction->wz);
		chars.write( 0, 100, DEBUG_DIRECTION );

		char DEBUG_BOUNDS1[128] = { "XX : XX" };
		sprintf( DEBUG_BOUNDS1, "spielfeld->v_boundsOHL->: x:%f y:%f z:%f", spielfeld->v_boundsOHL->wx, spielfeld->v_boundsOHL->wy, spielfeld->v_boundsOHL->wz);
		chars.write( 0, 120, DEBUG_BOUNDS1 );

		char DEBUG_BOUNDS2[128] = { "XX : XX" };
		sprintf( DEBUG_BOUNDS2, "spielfeld->v_boundsUVR->: x:%f y:%f z:%f", spielfeld->v_boundsUVR->wx, spielfeld->v_boundsUVR->wy, spielfeld->v_boundsUVR->wz);
		chars.write( 0, 140, DEBUG_BOUNDS2 );
*/

//		ball->DEBUG_drawDirection();
		
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
