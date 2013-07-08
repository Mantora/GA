#ifndef CHARSET_H
#define CHARSET_H

#include <stdio.h>

#include "simple_types.h"
#include "screen_interface.h"
#include "picture.h"

class charset
{
  private:
	picture signs[ 128 ];

  public:
    vertex text_pos;

    void write( char *string );
	void write( long sx, long sy, char *string ) {  text_pos = vertex( sx, sy );  write( string );  }

    charset( char *def_filename, char *picture_filename );
} chars( "chars.txt", "chars.bmp" );

void charset::write( char *string )
{
  GLdouble sx = text_pos.wx, sy = text_pos.wy;

  long length = strlen( string );
  for( long x=0 ; x<length ; x++ )
  {
    if( string[ x ] == '\n' )
    {
      sx = text_pos.wx;  sy -= 17;
      continue;
	}

    uchar c = string[ x ];  if( signs[ c ].xsize < 0 ) c = 127;

    if( string[ x ] == 'ä' ) c = 26;  if( string[ x ] == 'Ä' ) c = 29;
    if( string[ x ] == 'ö' ) c = 27;  if( string[ x ] == 'Ö' ) c = 30;
    if( string[ x ] == 'ü' ) c = 28;  if( string[ x ] == 'Ü' ) c = 31;

    glWindowPos2d( sx, sy );
    glDrawPixels( signs[ c ].xsize, signs[ c ].ysize, GL_RGBA, GL_UNSIGNED_BYTE, signs[ c ].content );

	if( string[ x ] == ':' ) sx += signs[ c ].xsize - 1;
	else sx += signs[ c ].xsize + 20;
   
//	sx += signs[ c ].xsize + 2;

  }
}

charset::charset( char *def_filename, char *picture_filename )
{
  FILE *input = fopen( def_filename, "rb" );
  if( input == NULL ) exit_nofile( "charset::charset()", def_filename );

  picture charset_picture( picture_filename );

  for( long z=0 ; z<128 ; z++ )
  {
    long tx, ty;

    fscanf( input, "%ld", &tx );

	if( tx == -1 ) signs[ z ].xsize = -1;

	else
	{
      fscanf( input, "%ld %ld %ld", &ty, &signs[ z ].xsize, &signs[ z ].ysize );

      if( (signs[ z ].content = new color[ signs[ z ].xsize * signs[ z ].ysize ]) ==  NULL )
        exit_nomemory( "charset::charset()", "signs[ z ].content[]" );

      for( long y=0 ; y<signs[ z ].ysize ; y++ )
         for( long x=0 ; x<signs[ z ].xsize ; x++ )
		 {
           signs[ z ].content[ y * signs[ z ].xsize + x ] = 
             charset_picture.content[ (ty+y) * charset_picture.xsize + (tx+x) ];
		 }
	}
  }

  fclose( input );
}

#endif