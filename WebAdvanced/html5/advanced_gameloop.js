window.onload = preInit();

var b_drawDebug = false;

var canvas = document.getElementById("myCanvas_1");
window.addEventListener( "keydown", keyboardHandler_down );
window.addEventListener( "keyup", keyboardHandler_up );
var b_lockKeybordInput = false;
var ctx = canvas.getContext("2d");

var FPS = 30;
var ENEMY_SPAWN_RATE = 500;

var maxX = canvas.width;
var maxY = canvas.height;

//game variables
var g_GameState; // save the current game state from pseudo enum i.E. GAMESTATE.INTRO
var playerBullets = [];
var enemys = [];
var enemyCount = 0;
var collisionsChecked = 0;
var sound_volume = 1;

//Assets
//audio
var sound_laser;
var str_laserPath = new Array( "laser_0.wav", "laser_1.wav", "laser_2.wav", "laser_3.wav" );
var str_debug_currentLaserPath;
var str_explosionPath = new Array( "explosion1.mp3", "explosion4.mp3", "explosion6.mp3" );
var str_debug_currentExplosionPath;
//textures
var texture_test;
var str_enemyPath = new Array( "Interceptor.ico", "Arbiter.ico", "Carrier.ico", "Corsair.ico", "Dropship.ico", "Guardian_Morph.ico", "Mutalisk.ico", "Observer.ico", "Overlord.ico", "Scourge.ico", "Scout.ico", "Shuttle.ico", "Valkyrie.ico", "Wraith.ico" );
var str_debug_lastSpawnedEnemyPath;

//GUI variables
var i_enemysKilled = 0;

function preInit()
{
	// start the real init function after 500 msec
	setTimeout( init, 500 );
};

function init()
{
	g_GameState = GAMESTATE.INTRO;
	
	posX = 0;
	posY = Math.floor( 100 );
	speed = 1;

	// Load content/graphics here
/*	sound_laser = new Audio( str_laserPath[0] );
	sound_laser.load();
	sound_laser = new Audio( str_laserPath[1] );
	sound_laser.load();
	sound_laser = new Audio( str_laserPath[2] );
	sound_laser.load();
	sound_laser = new Audio( str_laserPath[3] );
	sound_laser.load();
*/
	texture_test = new Image();
	texture_test.src = str_enemyPath[0];

	player.x = maxX * 0.5;
	player.y = maxY - player.height;
		
	// Start game Loop
	setInterval( gameLoop, 1000/FPS );
	
	// set the enemy spawn rate
	setInterval( spawnEnemys, ENEMY_SPAWN_RATE );
};

function spawnEnemys()
{
	if( !g_GameState == GAMESTATE.RUNNING )
		return;
	
	var spawnPosX = Math.floor( (Math.random()*maxX) );
	if( (spawnPosX+10) > maxX ) spawnPosX -= Enemy.width;
	
	enemy = new Enemy( spawnPosX, 0 );
	enemys.push( enemy );
};

function gameLoop()
{
	// Update ( Figure out whats a happening )
	if( g_GameState == GAMESTATE.RUNNING )
		update();
	
	// Draw ( Show what´s happening )
	draw();
};

function update()
{
	//reset debug variable
	collisionsChecked = 0;

	// update the image
	posX += speed;
	if( posX > maxX-50 || posX < 0 ) speed *= (-1);
	
	//update the player
	player.update();
	
	//update all bullets
	playerBullets.forEach( function(bullet){
		bullet.update();
	});

	// put all activ Bullets in a tmp array
	playerBullets = playerBullets.filter( function(bullet){
		return ( bullet.active );
	});

	//update all enemys
	enemys.forEach( function(enemy){
		enemy.update();
	});

	// put all activ Enemys in a tmp array
	enemys = enemys.filter( function(enemy){
		return ( enemy.active );
	});

	collisionCeck();
};

function collisionCeck()
{
	enemys.forEach( function(enemy){
		playerBullets.forEach( function(bullet){
			collisionsChecked++;
			if( collide( enemy, bullet ) )
			{
				i_enemysKilled++;
				enemy.active = false;
				bullet.active = false;
			}
		});
	});
};

function collide( objA, objB )
{
	if( (objA.x + objA.width) > objB.x && ( objB.x+objB.width) > objA.x )
	{
		if( (objA.y + objA.height) > objB.y && ( objB.y + objB.height ) > objA.y )
		{
			var pathIndex = Math.floor( (Math.random() * str_explosionPath.length ) );
			str_debug_currentExplosionPath = str_explosionPath[pathIndex];
			var tmpExplosion = new Audio( str_explosionPath[pathIndex] );
			tmpExplosion.volume = sound_volume;
			tmpExplosion.load();
			tmpExplosion.play();

			return true;
		}
	}

	return false;
};

function draw()
{
	switch( g_GameState )
	{
		case GAMESTATE.INTRO:
		{
			drawGUI_intro();
		}
		break;
		
		case GAMESTATE.RUNNING:
		{
			drawGUI_running();
		}
		break;
		
		case GAMESTATE.END:
		{
			drawGUI_end();
		}
		break;
	}
	
	if( b_drawDebug ) drawDebugInformations();
};

function drawGUI_intro()
{
	ctx.fillStyle = "#000000";
	ctx.font = "26px bold Courier New";
	
	var str_intro = "Shoot as many enemys as you can.";
	ctx.fillText( str_intro, 20, maxY*0.3, maxY );
	
	ctx.fillStyle = "#FF0000";
	var str_intro_end = "Game end, if one enemy can pass trouth.";
	ctx.fillText( str_intro_end, 0, maxY*0.4, maxY );
	
	ctx.fillStyle = "#000000";
	var str_controls_move = "movement: WSAD";
	ctx.fillText( str_controls_move, 70, maxY*0.55, maxY );
	
	var str_controls_shoot = "space: shoot";
	ctx.fillText( str_controls_shoot, 70, maxY*0.6, maxY );
	
	var str_howToStart = "Press <RETURN> to start !";
	ctx.fillText( str_howToStart, 40, maxY*0.75, maxY );
	
	ctx.fillStyle = "#FF0000";
	ctx.font = "9px bold Courier New";
	
	var str_howToDebug = "debuglog: L";
	ctx.fillText( str_howToDebug, 300, maxY*0.99, maxY );
};

function drawGUI_running()
{
	ctx.clearRect( 0, 0, canvas.width, canvas.height );
	
	// draw the player
	player.draw();
	
	//draw all bullets
	playerBullets.forEach( function(Bullet){
		Bullet.draw();
	});

	//draw all enemys
	enemys.forEach( function(enemy){
		enemy.draw();
	});
	
	// draw GUI at last to overpaint ALL
	drawPlayerGUI();
};

function drawGUI_end()
{
	ctx.fillStyle = "#000000";
	ctx.font = "46px bold Courier New";
	
	var str_end = "Your Score is " + i_enemysKilled;
	ctx.fillText( str_end, 50, maxY*0.4, maxY );
	
	var str_end = "please try again";
	ctx.fillText( str_end, 50, maxY*0.6, maxY );
	
	var str_end = "restart => \"f5\" ";
	ctx.fillText( str_end, 150, maxY*0.95, maxY );
};

function drawPlayerGUI()
{
	ctx.fillStyle = "#FF0000";
	ctx.font = "26px bold Courier New";
	
	var str_score = "Score: " + i_enemysKilled;
	ctx.fillText( str_score, maxX*0.5 - 50, 24, maxY );
};

// define a "player class"
var player = {
	color:"#FF0000",
	x:50, 
	y:100,
	width:8,
	height:8,
	speed:10,
	name:"Player",
	draw: function()
	{
		ctx.fillStyle = this.color;
		ctx.fillRect( this.x, this.y, this.width, this.height);
		
		ctx.font = "10px Arial";
		ctx.fillText( "Player", this.x-10, this.y-5, 100 );
	},
	update: function()
	{
		//this.y += this.speed;
		//if( this.y > maxY-this.height || this.y < 0 ) this.speed *= (-1);
	},
	//movement functions
	moveUp: function()
	{
		if( this.y < 0+20 ) return;
		this.y -= this.speed; 
	},
	moveDown: function()
	{
		if( this.y > maxY-this.height ) return;
		this.y += this.speed; 
	},
	moveRight: function()
	{
		if( this.x > maxX-this.width-8 ) return;
		this.x += this.speed; 
	},
	moveLeft: function()
	{
		if( this.x < 0+5 ) return;
		this.x -= this.speed;
	},
	fire: function()
	{
		var pathIndex = Math.floor( (Math.random() * str_laserPath.length ) );
		str_debug_currentLaserPath = str_laserPath[pathIndex];
		var tmpLaser = new Audio( str_laserPath[pathIndex] );
		tmpLaser.volume = sound_volume;
		tmpLaser.load();
		tmpLaser.play();
		
		bullet = new Bullet( player.x + player.width*0.5, player.y + player.height*0.5);
		playerBullets.push( bullet );
	}
};

//define healthbar class
var healthbar = {
	x:0,
	y:0,
	
	width:32,
	height:10,
	
	min:0,
	max:100,
	
	color:"#999999",
	
	draw: function()
	{
		ctx.fillRect( this.x, this.y, this.width, this.height);
	}
};


//define the Bullet class
function Bullet( posX, posY )
{
	var I = new Object();
	I.active = true;
	I.speed = 1;
	I.x = posX;
	I.y = posY;
	I.width = 3;
	I.height = 3;
	I.color = "#000000";
	
	I.xVelocity = 0;
	I.yVelocity = -I.speed;
	
	I.draw = function()
	{
		ctx.fillStyle = this.color;
		ctx.fillRect( this.x, this.y, this.width, this.height );
	};
	
	I.update = function()
	{
		I.y += I.yVelocity;
		I.x += I.xVelocity;
		
		if( this.y < 0 ) this.active = false;
	};
	
	return I;
};

//define th Enemy class
function Enemy( posX, posY )
{
	enemyCount++;

	var I = new Object();
	I.active = true;
	I.speed = 0.5;
	I.x = posX;
	I.y = posY;

	I.color = "#00FF00";
	
	I.xVelocity = 0;
	I.yVelocity = +I.speed;
	
	I.name = "enemy "+enemyCount;
	
	var pathIndex = Math.floor( (Math.random() * str_enemyPath.length ) );
	str_debug_lastSpawnedEnemyPath = str_enemyPath[pathIndex];
	I.img = new Image();
	I.img.src = str_enemyPath[pathIndex];
	
	I.width = I.img.width;
	I.height = I.img.height;
	
	I.draw = function()
	{
		ctx.fillStyle = this.color;
		//ctx.fillRect( this.x, this.y, this.width, this.height );
		ctx.drawImage( this.img, this.x, this.y );
		
		ctx.fillStyle = "#000000";
		ctx.font = "10px Arial";
		ctx.fillText( this.name, this.x-10, this.y-5, 100 );
	};
	
	I.update = function()
	{
		I.y += I.yVelocity;
		I.x += I.xVelocity;
		
		if( this.y > maxY )
		{
			this.active = false;
			//end game if the first enemy reaches the ground
			b_updateLoop = false;
			
			g_GameState = GAMESTATE.END;
		}
	};
	
	return I;
};

/* ENUMs*/
// pseudo enum 4 use 4 Input
var PlayerInput = {
	KEY_A:65,
	KEY_D:68,
	KEY_W:87,
	KEY_S:83,
	
	KEY_L:76,
	
	KEY_SPACE:32,
	
	KEY_RETURN:13
};

var GAMESTATE = 
{
	INTRO:0,
	RUNNING:1,
	END:2
};

/* EVENTHANDLER */
// handler 4 input DOWN press
function keyboardHandler_down( event )
{
	//allert 4 find out a specefic keyCode from Input
	//alert( event.keyCode );
	switch( event.keyCode )
	{
		case PlayerInput.KEY_S:
		{
			if( g_GameState == GAMESTATE.RUNNING )
				player.moveDown();
		}
		break;
		
		case PlayerInput.KEY_W:
		{
			if( g_GameState == GAMESTATE.RUNNING )
				player.moveUp();
		}
		break;
		
		case PlayerInput.KEY_A: 
		{
			if( g_GameState == GAMESTATE.RUNNING )
			if( g_GameState == GAMESTATE.RUNNING )player.moveLeft(); 
		}
		break;
		
		case PlayerInput.KEY_D: 
		{
			if( g_GameState == GAMESTATE.RUNNING )
				player.moveRight();	
		}
		break;
		
		case PlayerInput.KEY_L:
		{
			b_drawDebug = !b_drawDebug;
		}
		break;
		
		case PlayerInput.KEY_RETURN:
		{
			// multible use of one Key depending on the curren GameState
			switch( g_GameState )
			{
				case GAMESTATE.INTRO:
				{
					g_GameState = GAMESTATE.RUNNING;
				}
				break;
			}
		}
		break;
		
		case PlayerInput.KEY_SPACE:
		{
			player.fire();
		}
		break;
	}
	
	b_lockKeybordInput = true;
};

// handler 4 input UP press
function keyboardHandler_up( event )
{
	b_lockKeybordInput = false;
};

// DEBUG FUNKTION
function drawDebugInformations()
{
	ctx.fillStyle = "#FF0000";
	ctx.font = "12px Courier New";
	
	var str_debugText0 = "Debug output:";
	ctx.fillText( str_debugText0, 0, 10, maxY );
	
	var str_debugText1 = "Player: x=" + player.x + " y=" + player.y;
	ctx.fillText( str_debugText1, 0, 20, maxY );
	
	var str_debugText2 = "playerBullets.length=" + playerBullets.length;
	ctx.fillText( str_debugText2, 0, 30, maxY );
	
	var str_debugText3 = "enemys.length=" + enemys.length;
	ctx.fillText( str_debugText3, 0, 40, maxY );
	
	var str_debugText4 = "collisionsChecked=" + collisionsChecked;
	ctx.fillText( str_debugText4, 0, 50, maxY );
	
	var str_debugText5 = "g_GameState=" + g_GameState;
	ctx.fillText( str_debugText5, 0, 60, maxY );
	
	var str_debugText5 = "str_debug_currentLaserPath=" + str_debug_currentLaserPath;
	ctx.fillText( str_debugText5, 0, 70, maxY );	
	
	var str_debugText5 = "str_debug_currentExplosionPath=" + str_debug_currentExplosionPath;
	ctx.fillText( str_debugText5, 0, 80, maxY );		
	
	var str_debugText5 = "str_debug_lastSpawnedEnemyPath=" + str_debug_lastSpawnedEnemyPath;
	ctx.fillText( str_debugText5, 0, 90, maxY );	
};