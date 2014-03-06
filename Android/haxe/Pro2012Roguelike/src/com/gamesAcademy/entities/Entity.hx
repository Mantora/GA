package com.gamesAcademy.entities;

import com.gamesAcademy.gameState.*;
import com.gamesAcademy.entities.*;
import com.gamesAcademy.helper.Vector2;

/**
 * ...
 * @author Alexander Luck
 */

class Entity
{
	//world position
	public var position :Vector2 = null;
	
	//Forward vector in local space
	public var rotation :Vector2 = null;
	
	//optional
	public var name :String = "";
	
	
	public function new(pos : Vector2 = null, rot : Vector2 = null)
	{
		if(pos != null)
			position = pos;
		if(rot != null)
			rotation = rot;
		
	}
	
	public function OnFieldGotEntered(otherEntity : Entity)
	{
	}
	
}