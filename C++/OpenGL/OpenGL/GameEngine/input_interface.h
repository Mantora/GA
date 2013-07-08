#ifndef INPUT_INTERFACE_H
#define INPUT_INTERFACE_H

#include <windows.h>
#include "simple_types.h"

class input_interface
{
  public:
    vertex mouse_left_downpos, mouse_left_uppos;
    vertex mouse_act_pos;

    char mouse_left_state;

    long event_key;

    MSG msg;

    long check( void );
    uchar key_pressed( int key ) {  return GetKeyState( key ) < 0;  }
    uchar capital_active( void );

    input_interface( void ) : mouse_left_state( 0 ), event_key( 0 ) { }
} input;

uchar input_interface::capital_active( void )
{
  short state = GetKeyState( VK_CAPITAL );
  
  if( state == 0 || state == -128 ) return 0;

  return 1;
}

long input_interface::check( void )
{
  event_key = 0;

  if( mouse_left_state == 1 ) mouse_left_state = 0;

  if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
  {
    switch( msg.message )
    {
      case WM_KEYDOWN     : event_key = msg.wParam;
                            break;
      case WM_MOUSEMOVE   : mouse_act_pos.wx = short( msg.lParam & 0xffff );
                            mouse_act_pos.wy = y_res - 1 - short( msg.lParam >> 16 );
                            break;
      case WM_LBUTTONDOWN : mouse_left_state = -1;  mouse_left_downpos = mouse_act_pos;
                            break;
      case WM_LBUTTONUP   : mouse_left_state = 1;   mouse_left_uppos = mouse_act_pos;
                            break;
      case WM_QUIT        : return 1;
    }

    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  return 0;
}

#endif