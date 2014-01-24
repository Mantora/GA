package com.gamesAcademy.entities;

import com.gamesAcademy.entities.*;
import com.gamesAcademy.helper.*;

/**
 * ...
 * @author Alexander Luck
 */

class Enemy extends Actor
{
	public var playerPos :Vector2;
	
	
	public function new(pos : Vector2 = null, rot : Vector2 = null) 
	{
		super(pos, rot);
		
	}
	
	public override function Update(dir : Vector2) : Bool
	{
		super.Update(dir);
		//ai logic
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