package com.gamesAcademy.entities;

import com.gamesAcademy.entities.*;
import com.gamesAcademy.helper.*;
import com.gamesAcademy.gameState.*;

/**
 * ...
 * @author Alexander Luck
 */

class Coin extends Pickup
{
	public var CoinValue :Int = 10;
	
	public function new(pos : Vector2 = null, rot : Vector2 = null) 
	{
		super(pos, rot);
		
	}
	
	public override function OnFieldGotEntered(otherEntity : Entity)
	{
		//Check if entity is player
		if (Std.is(otherEntity, Player))
		{
			//Call gamestate recieve points  (CoinValue);
			//Destroy object
		}
	}
	
}