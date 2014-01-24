package com.gamesAcademy.entities;

import com.gamesAcademy.entities.*;
import com.gamesAcademy.helper.*;

/**
 * ...
 * @author Alexander Luck
 */

class Actor extends Entity
{
	var health :Int = 1;
	
	var strength :Int = 10;
	
	var speed : Int = 1;
	
	var ActionPoints : Int = 1;
	
	public function new(pos : Vector2 = null, rot : Vector2 = null) 
	{
		super(pos, rot);
		
	}
	
	public function Update(dir : Vector2) :Bool
	{
		ActionPoints = speed;
		return true;
	}
	
	public function Move(dir : Vector2)
	{
		if (ActionPoints <= 0)
			return;
		
		//Check if walking allowed
		
		ActionPoints--;
		position =  position.add(dir);
	}
	
	public function BasicMeele()
	{
		//test if cell is really occupied by enemy
		
	}
	
	public function RecieveDamage(otherActor : Actor)
	{
		health -= otherActor.strength;
	}
	
}