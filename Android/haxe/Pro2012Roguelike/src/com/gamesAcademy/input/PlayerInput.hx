package com.gamesAcademy.input;
import com.gamesAcademy.gameState.GameState;
import flash.display.Sprite;
import flash.display.Stage;
import flash.events.Event;
import flash.events.MouseEvent;
import com.gamesAcademy.helper.Vector2;

/**
 * Class 4 handle PlayerInput + handles
 * Needed static GameState instance
 * @author CJ
 */
class PlayerInput extends Sprite 
{
	public function new( stage:Stage ) 
	{
		super();
		
		var f_btnOffset:Float = 100.0;
		var btn_up = new InputButton(stage.stageWidth*0.5, stage.stageHeight*0.5-f_btnOffset-50, 100.0, 200.0 );
		stage.addChild( btn_up );
		btn_up.addEventListener( MouseEvent.CLICK, btnH_up );
		
		var btn_down = new InputButton(stage.stageWidth*0.5, stage.stageHeight*0.5+f_btnOffset+50, 100.0, 200.0 );
		stage.addChild( btn_down );
		btn_down.addEventListener( MouseEvent.CLICK, btnH_down );
		
		var btn_left = new InputButton(stage.stageWidth*0.5-f_btnOffset-50, stage.stageHeight*0.5, 200.0, 100.0 );
		stage.addChild( btn_left );
		btn_left.addEventListener( MouseEvent.CLICK, btnH_left );
				
		var btn_right = new InputButton(stage.stageWidth*0.5+f_btnOffset+50, stage.stageHeight*0.5, 200.0, 100.0 );
		stage.addChild( btn_right );
		btn_right.addEventListener( MouseEvent.CLICK, btnH_right );
	}
	
	//EventListener 4 input
	private function btnH_up( e:Event ):Void
	{
		//trace("klick on " + e.target.mouseX + "/" + e.target.mouseY);
		trace("Input: btnH_up");
		var newPlayerPos:Vector2 = new Vector2(0, -1);
		GameState.getGameState().RecieveInput( newPlayerPos );
	}
	private function btnH_down( e:Event ):Void 
	{
		//trace("klick on " + e.target.mouseX + "/" + e.target.mouseY);
		trace("Input: btnH_down");
		var newPlayerPos:Vector2 = new Vector2(0, 1);
		GameState.getGameState().RecieveInput( newPlayerPos );
	}
	private function btnH_left( e:Event ):Void 
	{
		//trace("klick on " + e.target.mouseX + "/" + e.target.mouseY);
		trace("Input: btnH_left");
		var newPlayerPos:Vector2 = new Vector2( -1, 0);
		GameState.getGameState().RecieveInput( newPlayerPos );
	}	
	private function btnH_right( e:Event ):Void 
	{
		//trace("klick on " + e.target.mouseX + "/" + e.target.mouseY);
		trace("Input: btnH_right");
		var newPlayerPos:Vector2 = new Vector2(1, 0);
		GameState.getGameState().RecieveInput( newPlayerPos );
	}	
}