package com.gamesAcademy.gameState;
import com.gamesAcademy.entities.Enemy;
import com.gamesAcademy.entities.Player;
import com.gamesAcademy.entities.Pickup;
import com.gamesAcademy.helper.Vector2;


/**
 * ...
 * @author Me
 */
class GameState
{

	var Player1:Player;
	var EnemiesAlive:Int;
	var enemies:Array<Enemy>;
	var pickups:Array<Pickup>;

	static private var instance :GameState;
	public static function getGameState() :GameState
	{
		if (instance == null)
		{
			instance = new GameState();
		}
		return instance;
	}
	
	public function new() 
	{
		enemies = new Array<Enemy>();
		//... get map infos
	}
	
	public function RecieveInput(vec:Vector2)
	{
		if (Player1 == null) Player1 = new Player(vec, vec);
		if (Player1.Update(vec))
		{
			for (i in 0... enemies.length)
			{
				enemies[i].Update(vec);
			}
		};
	}
	
	public function SpawnEnemy(loc:Vector2, rot:Vector2)
	{
		var E:Enemy = new Enemy(loc, rot);
		enemies.insert(EnemiesAlive++, E);
	}

	public function SpawnPlayer(loc:Vector2, rot:Vector2)
	{
		Player1 = new Player(loc, rot);
	}	
	
	public function removeEnemy(E:Enemy) :Bool 
	{
		if (--EnemiesAlive == 0)
		{
			win();
		}
		return enemies.remove(E);
	}
	
	public function PlayerDied()
	{
		lose();
	}
	
	function win()
	{

	}
	
	function lose()
	{
		
	}
	
	
	
}