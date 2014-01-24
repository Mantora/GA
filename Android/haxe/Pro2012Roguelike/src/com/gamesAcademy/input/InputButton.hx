package com.gamesAcademy.input;

import flash.display.Sprite;

/**
 * ...
 * @author CJ
 */
class InputButton extends Sprite
{
	public function new( centerX:Float, centerY:Float, width:Float, height:Float ) 
	{
		super();
		
		graphics.lineStyle( 3.0, 0x000000, 0.33 );
		graphics.beginFill( 0xFF0000, 0.33 );
		graphics.drawRect( centerX-width*0.5, centerY-height*0.5, width, height );
		graphics.endFill();
	}
	
}