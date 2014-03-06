package com.gamesAcademy.entities;

import com.gamesAcademy.entities.*;
import com.gamesAcademy.helper.*;
import com.gamesAcademy.gameState.*;

/**
 * ...
 * @author Alexander Luck
 */

class Pickup extends Entity
{

	public function new(pos : Vector2 = null, rot : Vector2 = null) 
	{
		super(pos, rot);
		
	}
	
	public override function OnFieldGotEntered(otherEntity : Entity)
	{
	}
	
}