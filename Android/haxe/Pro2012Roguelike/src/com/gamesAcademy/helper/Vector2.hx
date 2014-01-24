package com.gamesAcademy.helper;

/**
 * ...
 * @author Alexander Luck
 */

class Vector2
{
	public var x :Int = 0;
	public var y :Int = 0;
	
	public function new(X : Int = 0, Y : Int = 0) 
	{
		x = X;
		y = Y;
	}
	
	public function Length(a : Vector2, b : Vector2) :Float
	{
		var c : Vector2 = new Vector2(b.x - a.x, b.y - a.y);
		return Math.sqrt(Math.abs(c.x * c.x + c.y * c.y));
	}
	
	public function SquaredLength(a : Vector2, b : Vector2) :Float
	{
		var c : Vector2 = new Vector2(b.x - a.x, b.y - a.y);
		return Math.abs(c.x * c.x + c.y * c.y);
	}
	
	public function add(v : Vector2) : Vector2
	{
		return new Vector2(x + v.x, y + v.y);
	}
}