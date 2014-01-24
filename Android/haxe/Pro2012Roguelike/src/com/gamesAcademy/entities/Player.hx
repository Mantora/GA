package com.gamesAcademy.entities;

import com.gamesAcademy.entities.*;
import com.gamesAcademy.helper.*;

/**
 * ...
 * @author Alexander Luck
 */

class Player extends Actor
{

	public function new(pos : Vector2 = null, rot : Vector2 = null) 
	{
		super(pos, rot);
		
	}
	
	
	public override function Update(dir : Vector2) : Bool
	{
		super.Update(dir);
		
		//Check if Enemy is in the Cell ahead
		
		//else if Cell is occupied
		//return false
		
		//else
		Move(dir);
		return true;
	}
	
	
	
	public override function RecieveDamage(otherActor : Actor)
	{
		super.RecieveDamage(otherActor);
		if (health <= 0)
		{
			//call gamestate
		}
	}
	
}