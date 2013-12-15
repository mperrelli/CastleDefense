// Programmer: Matt Perrelli
// Course:	   CMPT 464
// Due Date:   April 30, 2013
//
// Final Project
//
// CASTLE DEFENSE is a spin off of an existing flash game. In this
// version of the game tanks rise from the bottom of the screen 
// with the intention of destroying your castle. Your objective 
// is to defend the castle for as long as you possibly can.
// Click on tanks to launch missiles at them. Destroying tanks
// gains your currancy. You can spend your currancy on defensive
// buildings. Click fast, place strategically and SURVIVE.

// Includes, namespace and prototypes
#include "template.h"
#include <string>
using namespace AGK;
using namespace std;
#include "sprite.h"
#include "moveableSprite.h"
#include "opfor.h"
#include "building.h"
#include "projectile.h"
app App;

// Function prototypes
void loadTiles();
void displayTiles();
void addOpfor();
void advanceOpfor();
void advanceTimer();
void updateCursor();
void checkClicks();
void removeOpfor(int i);
void activateOpfor();
void increaseDifficulty();
void advanceRound();
void advanceScore();
void updateSidebar();
bool checkEnterKey();
void showBuildingBoard();
void hideBuildingBoard();
void moveBuilding();
void checkPlacement();
void buildBuilding(float x, float y, int building);
void hideBuidingCursor();
void rotateBuilding(int i, string);
void fireTowers();
void createProjectile(int x, int y, int dX, int dY, int speed, int type);
void advanceProjectiles();
void activateProjectile(int posX, int posY, int dX, int dY, int speed, int type);
void checkProjectiles();
void removeProjectile(int i);
bool screenClear();
void showSummery();
int checkType(int i);
void displayRedFade();
void pulseRedFade();
void clearBoard();
void playExplosion(int posX, int posY);

// Declaration of opfor linked list
typedef struct opforNode* ptr;

struct opforNode{
	Opfor *sprite;
	ptr next;
};

ptr opforHead = NULL;
ptr opforTailItem = NULL;

// Declaration of building linked list
typedef struct buildingNode* bptr;

struct buildingNode{
	Building *sprite;
	bptr next;
};

bptr buildingHead = NULL;
bptr buildingTailItem = NULL;

// Declaration of projectile linked list
typedef struct projectileNode* pptr;

struct projectileNode{
	Projectile *sprite;
	pptr next;
};

pptr projectileHead = NULL;
pptr projectileTailItem = NULL;

// Constants for the screen resolution
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Constants for the image numbers
const int GRASS     = 1;
const int WCORNER   = 2;
const int WHORIZ    = 3;
const int WVERT     = 4;
const int WSIDE     = 5;
const int WSIDET    = 6;
const int EXPLOSION_IMG = 7;

// Constants for sounds
const int PICKUP_SOUND      = 1;
const int PLACE_SOUND       = 2;
const int EXPLOSION_SOUND   = 3;
const int STATESWITCH_SOUND = 4;
const int AMBIANT_MUSIC     = 5;
const int ALARM_SOUND       = 6;

// Constants for text objects
const int SCORE_TEXT = 1;
const int SCORE_TEXT_X = 560;
const int SCORE_TEXT_Y = 65;
const int CURRENCY_TEXT = 2;
const int CURRENCY_TEXT_X = 560;
const int CURRENCY_TEXT_Y = 105;
const int ENEMIES_TEXT = 3;
const int ENEMIES_TEXT_X = 560;
const int ENEMIES_TEXT_Y = 365;
const int SURVIVED_TEXT = 4;
const int SURVIVED_TEXT_X = 560;
const int SURVIVED_TEXT_Y = 410;
const int NEXTLEVEL_TEXT = 5;
const int HEALTH_TEXT = 6;
const int HEALTH_VAR_TEXT = 7;
const int HEALTH_TEXT_X = SCREEN_HEIGHT / 2;
const int HEALTH_TEXT_Y = 30;

// Constants for sprites
const int GATE_INDEX = 230;
const int CURSORL_INDEX = 231;
const int CURSORR_INDEX = 232;
const int CURSORT_INDEX = 233;
const int CURSORB_INDEX = 234;
const int EXPLOSION_INDEX = 235;
const int SIDEBAR_INDEX = 236;
const int OVERLAYR_INDEX = 237;
const int OVERLAYG_INDEX = 238;
const int ARROWTURRET_INDEX = 239;
const int BOMBCATAPULT_INDEX = 240;
const int GATLINGCANNON_INDEX = 241;
const int TITLESCREEN_INDEX = 242;
const int INSTRUCTIONSCREEN_INDEX = 243;
const int SUMMERYSCREEN_INDEX = 244;
const int REDFADEL_INDEX = 245;
const int REDFADER_INDEX = 246;
const int REDFADET_INDEX = 247;
const int REDFADEB_INDEX = 248;

// Constants for the tile image sizes
const int TILE_WIDTH  = 32;
const int TILE_HEIGHT = 32;

// Constants for the tile map size declarators
const int TILE_ROWS = 15;
const int TILE_COLS = 15;

const int WALL_BOUNDRY = 190;
const int WALL_MARK = 130;
const int GAME_SCREEN_WIDTH = 480;
const int EXPLOSION_SIZE = 75;
const int GATE_START_X = 192;
const int GATE_START_Y = 110;
const int EXPLOSION_FRAMES_AMT = 12;
const int EXPLOSION_FPS = 30;
const int SIDEBAR_X = 480;
const int SIDEBAR_Y = 0;
const int SCORE_INCREMENT = 10;
const int CURRENCY_INCREMENT = 10;
const int BUYBTN_X = 490;
const int BUYBTN_WIDTH = 150;
const int BUYBTN_HEIGHT = 44;
const int BUYBTN_AT_Y = 139;
const int BUYBTN_BC_Y = 189; 
const int BUYBTN_GC_Y = 239; 
const int BUYBTN_AS_Y = 289;
const int ARROWTURRET_COST = 50;
const int BOMBCATAPULT_COST = 150;
const int GATLINGCANNON_COST = 500;
const int AIRSTRIKE_COST = 1000;
const int ARROWTOWER_SPEED = 3;
const int ARROWTOWER_FREQ = 120;
const int BOMBCATAPULT_FREQ = 300;
const int BOMBCATAPULT_SPEED = 1;
const int GATLINGCANNON_FREQ = 60;
const int GATLINGCANNON_SPEED = 3;
const int OPFOR_HIT_FREQ = 150;
const int BUILDING_FIRE_OFFSET = 100;
const int FRIENDLY = 0;
const int OPFOR = 1;
const int ADVANCE_SCORE_FREQ = 40;

// Depth constants
const int CURSOR_DEPTH = 3;

// The tile map
int g_tileMap[TILE_ROWS][TILE_COLS] =
{ {WVERT,   GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  WVERT},
  {WVERT,   GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  WVERT},
  {WVERT,   GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  WVERT},
  {WVERT,   GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS, 
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  WVERT},
  {WCORNER, WHORIZ, WHORIZ,  WHORIZ,  WHORIZ,   WHORIZ,  GRASS,  
  GRASS,  GRASS,  WHORIZ, WHORIZ,  WHORIZ,  WHORIZ,   WHORIZ, WCORNER},
  {WSIDET,  WSIDE,  WSIDE,   WSIDE,   WSIDE,    WSIDE,   GRASS,  
  GRASS,  GRASS,  WSIDE,  WSIDE,   WSIDE,   WSIDE,    WSIDE,  WSIDET},
  {GRASS,   GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS},
  {GRASS,	GRASS,  GRASS,   GRASS,   GRASS,    GRASS,   GRASS,  
  GRASS,  GRASS,  GRASS,  GRASS,   GRASS,   GRASS,    GRASS,  GRASS}
};

int g_buildingMap[TILE_ROWS][TILE_COLS] =
{ {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15,},
  {16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 30,},
  {31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 45,},
  {46, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60,},
  {61, 62, 63, 64, 65, 66, 0, 0, 0, 70, 71, 72, 73, 74, 75,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,}
};

const int BUILDINGS_SIZE = 20;

Sprite gate, sidebar, cursorL, cursorR, cursorT, cursorB, overlayGreen;
Sprite overlayRed, arrowTurret, bombCatapult, gatlingCannon;
Sprite titleScreen, instructionScreen, summeryScreen;
Sprite redFadeR, redFadeL, redFadeT, redFadeB;

// Global vars for sprite index managment
const int OPFOR_START_INDEX = 250;
const int OPFOR_SPAWN_BOUND1 = 40;
const int OPFOR_SPAWN_BOUND2 = 440;
int g_opforListSize = 0;

const int PROJECTILE_START_INDEX = 380;
int g_projectileListSize = 0;

const int BUILDING_START_INDEX = 350;
int g_buildingListSize = 0;

// Global vars
int g_currRound = 0;
int g_opforMinSpeed = 1;
int g_opforMaxSpeed = 1;
int g_opforMinHealth = 1;
int g_opforMaxHealth = 1;
int g_opforSpawnFrequency = 200;
int g_opforCurr = 0;
int g_opforCount = 5;
int g_opforRemaining = 5;
int g_castleHealth = 100;
int g_currency = 1000;
int g_score = 0;
int g_opforDestroyed = 0;
int g_projectileCurr = 0;
int g_redFadeOpacity = 0;
bool g_fadingIn = true;

// Global vars for building state
const int ARROW_TURRET = 1;
const int BOMB_CATAPULT = 2;
const int GATLING_CANNON = 3;
int g_cursorAttach = 0;

// Global timer
int g_timer = 0;

// Gamestate
const int TITLESCREEN = 0;
const int CONTROLS = 1;
const int INPLAY = 2;
const int INTERROUND = 3;
const int BUYSTUFF = 4;
const int BUILDING = 5;
const int INTERROUNDTWO = 6;
const int GAMEOVER = 7;
const int SUMMERY = 8;
int g_gameState = TITLESCREEN;

// Begin app, called once at the start
void app::Begin( void )
{
	// Set the window title.
    agk::SetWindowTitle("Castle Defense");

	// Set up mouse and cursor
	agk::SetRawMouseVisible(FALSE);
	cursorR.createSprite(CURSORR_INDEX, "Resources/cursor.png");
	cursorL.createSprite(CURSORL_INDEX, "Resources/cursor.png");
	cursorT.createSprite(CURSORT_INDEX, "Resources/cursor.png");
	cursorB.createSprite(CURSORB_INDEX, "Resources/cursor.png");

	agk::SetSpriteAngle(CURSORR_INDEX, 90);
	agk::SetSpriteAngle(CURSORL_INDEX, 90);

	agk::SetSpriteDepth(CURSORR_INDEX, CURSOR_DEPTH);
	agk::SetSpriteDepth(CURSORL_INDEX, CURSOR_DEPTH);
	agk::SetSpriteDepth(CURSORT_INDEX, CURSOR_DEPTH);
	agk::SetSpriteDepth(CURSORB_INDEX, CURSOR_DEPTH);

    // Set the virtual resolution.
    agk::SetVirtualResolution(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Load the tile images.
	loadTiles();

	// Create the tile sprites and display them.
	displayTiles();

	// Set up sidebar
	sidebar.createSprite(SIDEBAR_INDEX, "Resources/sidebar.png");
	sidebar.setPosition(SIDEBAR_X, SIDEBAR_Y);

	// Set up sprites
	gate.createSprite(GATE_INDEX, "Resources/gate.png");
	gate.setPosition(GATE_START_X, GATE_START_Y);

	overlayRed.createSprite(OVERLAYR_INDEX, "Resources/overlayRed.png");
	agk::SetSpriteVisible(OVERLAYR_INDEX, FALSE);

	overlayGreen.createSprite(OVERLAYG_INDEX, "Resources/overlayGreen.png");
	agk::SetSpriteVisible(OVERLAYG_INDEX, FALSE);

	arrowTurret.createSprite(ARROWTURRET_INDEX, "Resources/arrowTurret.png");
	agk::SetSpriteVisible(ARROWTURRET_INDEX, FALSE);

	bombCatapult.createSprite(BOMBCATAPULT_INDEX, "Resources/bombCatapult.png");
	agk::SetSpriteVisible(BOMBCATAPULT_INDEX, FALSE);

	gatlingCannon.createSprite(GATLINGCANNON_INDEX, "Resources/gatlingCannon.png");
	agk::SetSpriteVisible(GATLINGCANNON_INDEX, FALSE);

	titleScreen.createSprite(TITLESCREEN_INDEX, "Resources/titlescreen.png");
	agk::SetSpriteDepth(TITLESCREEN_INDEX, 5);
	agk::SetSpriteVisible(TITLESCREEN_INDEX, FALSE);
	titleScreen.setPosition(0,0);

	instructionScreen.createSprite(INSTRUCTIONSCREEN_INDEX, "Resources/instructions.png");
	agk::SetSpriteDepth(INSTRUCTIONSCREEN_INDEX, 5);
	agk::SetSpriteVisible(INSTRUCTIONSCREEN_INDEX, FALSE);
	instructionScreen.setPosition(0,0);

	summeryScreen.createSprite(SUMMERYSCREEN_INDEX, "Resources/gameoverscreen.png");
	agk::SetSpriteDepth(SUMMERYSCREEN_INDEX, 5);
	agk::SetSpriteVisible(SUMMERYSCREEN_INDEX, FALSE);
	summeryScreen.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

	redFadeL.createSprite(REDFADEL_INDEX, "Resources/redFade.png");
	redFadeL.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

	redFadeR.createSprite(REDFADER_INDEX, "Resources/redFade.png");
	redFadeR.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
	agk::SetSpriteFlip(REDFADER_INDEX, 1, 0);

	redFadeT.createSprite(REDFADET_INDEX, "Resources/redFade2.png");
	redFadeT.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

	redFadeB.createSprite(REDFADEB_INDEX, "Resources/redFade2.png");
	redFadeB.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
	agk::SetSpriteFlip(REDFADEB_INDEX, 0, 1);

	// Set up explosion animation
	agk::LoadImage(EXPLOSION_IMG, "Resources/explosion.png");
	agk::CreateSprite(EXPLOSION_INDEX, EXPLOSION_IMG);
	agk::SetSpriteAnimation(EXPLOSION_INDEX, EXPLOSION_SIZE, 
		EXPLOSION_SIZE, EXPLOSION_FRAMES_AMT);
	agk::SetSpriteVisible(EXPLOSION_INDEX, FALSE);

	// Set up text objects
	agk::CreateText(SCORE_TEXT, "0");
	agk::SetTextPosition(SCORE_TEXT, SCORE_TEXT_X, SCORE_TEXT_Y);
	agk::SetTextSize(SCORE_TEXT, 16);
	agk::SetTextAlignment(SCORE_TEXT, 1);

	agk::CreateText(CURRENCY_TEXT, "0");
	agk::SetTextPosition(CURRENCY_TEXT, CURRENCY_TEXT_X, CURRENCY_TEXT_Y);
	agk::SetTextSize(CURRENCY_TEXT, 16);
	agk::SetTextAlignment(CURRENCY_TEXT, 1);

	agk::CreateText(ENEMIES_TEXT, "0");
	agk::SetTextPosition(ENEMIES_TEXT, ENEMIES_TEXT_X, ENEMIES_TEXT_Y);
	agk::SetTextSize(ENEMIES_TEXT, 16);
	agk::SetTextAlignment(ENEMIES_TEXT, 1);

	agk::CreateText(SURVIVED_TEXT, "0");
	agk::SetTextPosition(SURVIVED_TEXT, SURVIVED_TEXT_X, SURVIVED_TEXT_Y);
	agk::SetTextSize(SURVIVED_TEXT, 16);
	agk::SetTextAlignment(SURVIVED_TEXT, 1);

	agk::CreateText(NEXTLEVEL_TEXT, "Press ENTER to start the next round!");
	agk::SetTextPosition(NEXTLEVEL_TEXT, (SCREEN_HEIGHT / 2), (SCREEN_HEIGHT / 2));
	agk::SetTextSize(NEXTLEVEL_TEXT, 16);
	agk::SetTextAlignment(NEXTLEVEL_TEXT, 1);
	agk::SetTextVisible(NEXTLEVEL_TEXT, FALSE);

	agk::CreateText(HEALTH_TEXT, "Castle Health:");
	agk::SetTextPosition(HEALTH_TEXT, HEALTH_TEXT_X + 10, HEALTH_TEXT_Y);
	agk::SetTextSize(HEALTH_TEXT, 16);
	agk::SetTextAlignment(HEALTH_TEXT, 2);

	agk::CreateText(HEALTH_VAR_TEXT, agk::Str(g_castleHealth));
	agk::SetTextPosition(HEALTH_VAR_TEXT, HEALTH_TEXT_X + 15, HEALTH_TEXT_Y);
	agk::SetTextSize(HEALTH_VAR_TEXT, 16);

	agk::SetClearColor(255, 0, 0);

	// Set up sounds
	agk::LoadSound(PICKUP_SOUND, "Resources/click.wav");
	agk::LoadSound(PLACE_SOUND, "Resources/place.wav");
	agk::LoadSound(EXPLOSION_SOUND, "Resources/explosion.wav");
	agk::LoadSound(STATESWITCH_SOUND, "Resources/stateswitch.wav");
	agk::LoadSound(ALARM_SOUND, "Resources/lowhealth.wav");

	// Set up music
	agk::LoadMusic(AMBIANT_MUSIC, "Resources/ambiant.mp3");
}

// Main loop, called every frame
void app::Loop ( void )
{
	// Move the cursor
	updateCursor();

	// Check for click and hover events
	checkClicks();

	// Advance game timer
	advanceTimer();

	if(g_castleHealth <= 20)
	{
		pulseRedFade();

		agk::SetTextColor(HEALTH_TEXT, 255,0,0);
		agk::SetTextColor(HEALTH_VAR_TEXT, 255,0,0);

		if(!agk::GetSoundsPlaying(ALARM_SOUND) 
			&& g_timer % 100 == 0
			&& g_gameState == INPLAY)
		{
			agk::PlaySound(ALARM_SOUND);
		}
	}

	// Gamestate switch
	switch(g_gameState)
	{
	case TITLESCREEN:
		// Show title screen sprite
		agk::SetSpriteVisible(TITLESCREEN_INDEX, TRUE);

		// Check for enter key press, then advance to controls screen
		if(checkEnterKey() == true)
		{
			agk::SetSpriteVisible(TITLESCREEN_INDEX, FALSE);
			titleScreen.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
			g_gameState = CONTROLS;
		}
		break;
		
	case CONTROLS:
		// Show controls sprite
		agk::SetSpriteVisible(INSTRUCTIONSCREEN_INDEX, TRUE);

		// Check for enter key and start the game
		if(checkEnterKey() == true)
		{
			agk::SetSpriteVisible(INSTRUCTIONSCREEN_INDEX, FALSE);
			instructionScreen.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);
			agk::PlaySound(STATESWITCH_SOUND);
			g_gameState = INPLAY;
		}
		break;

	case INPLAY:
		// Play game music
		if(agk::GetMusicPlaying() == 0)
		{
			agk::PlayMusic(AMBIANT_MUSIC);
		}

		// Check for end of round
		if(g_opforRemaining == 0 && screenClear())
		{
			g_gameState = INTERROUND;
		}

		// Spawn new enemies based on timer
		if(g_timer % g_opforSpawnFrequency == 0 
			&& g_opforRemaining > 0)
		{
			g_opforCurr++;
			g_opforRemaining--;

			if(g_opforCurr >= g_opforListSize)
			{
				addOpfor();
			}
			else
			{
				activateOpfor();
			}
		}

		// Check castle health
		if(g_castleHealth <= 0)
		{
			g_gameState = GAMEOVER;
		}

		fireTowers();

		updateSidebar();

		advanceOpfor();

		advanceScore();

		advanceProjectiles();

		checkProjectiles();
		break;

	case INTERROUND:
		g_score += 500;
		updateSidebar();
		advanceRound();
		increaseDifficulty();	
		g_gameState = BUYSTUFF;
		break;

	case BUYSTUFF:
		// The purchase state 
		agk::SetTextVisible(NEXTLEVEL_TEXT, TRUE);

		if(checkEnterKey() == true)
		{
			g_gameState = INTERROUNDTWO;
			agk::PlaySound(STATESWITCH_SOUND);
		}
		break;

	case BUILDING:
		moveBuilding();
		checkPlacement();
		break;

	case INTERROUNDTWO:
		agk::SetTextVisible(NEXTLEVEL_TEXT, FALSE);
		g_gameState = INPLAY;
		break;

	case GAMEOVER:
		agk::StopMusic();
		agk::PlaySound(STATESWITCH_SOUND);
		g_gameState = SUMMERY;
		break;
		
	case SUMMERY:
		agk::SetSpriteVisible(SUMMERYSCREEN_INDEX, TRUE);
		summeryScreen.setPosition(0, 0);
		showSummery();
		break;
	}

	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}

// The loadTiles function loads the images that will be
// used for tiles.
void loadTiles()
{
   agk::LoadImage(GRASS,      "Resources/grass.png");
   agk::LoadImage(WCORNER,    "Resources/wallcorner.png");
   agk::LoadImage(WHORIZ,     "Resources/wallhoriz.png");
   agk::LoadImage(WVERT,      "Resources/wallvert.png");
   agk::LoadImage(WCORNER,    "Resources/wallcorner.png");
   agk::LoadImage(WSIDE,      "Resources/wallside.png");
   agk::LoadImage(WSIDET,     "Resources/wallside2.png");
}

// The displayTiles function displays the tiles, as
// specified by the tile map.
void displayTiles()
{
   // Variables for the tile coordinates
   float x = 0, y = 0;

   // Variable to temporarily hold a sprite index
   int spriteIndex = 1;
   
   // Display all the tiles specified in the map.
   for (int r = 0; r < TILE_ROWS; r++)
   {
      // Set x to 0.
      x = 0;

      // Display all the tiles in this row.
      for (int c = 0; c < TILE_COLS; c++)
      {
         // Create a sprite for this tile.
         agk::CreateSprite(spriteIndex, g_tileMap[r][c]);

         // Set the tile's position.
         agk::SetSpritePosition(spriteIndex, x, y);

		 // Increment sprite Index
		 spriteIndex++;

         // Update the X coordinate for the next tile.
         x += TILE_WIDTH;
      }
   
      // Increase y for the next row.
      y += TILE_HEIGHT;
    }
}

// When called adds an enemy to the game
void addOpfor()
{
	// Position, speed, and health are randomly selected
	int distance = agk::Random(g_opforMinSpeed, g_opforMaxSpeed);
	int health = agk::Random(g_opforMinHealth, g_opforMaxHealth);
	int posY = SCREEN_HEIGHT;
	int posX = agk::Random(OPFOR_SPAWN_BOUND1, OPFOR_SPAWN_BOUND2); 

	// A new sprite is dynamically created
	Opfor *p = new Opfor;
	p -> createSprite(OPFOR_START_INDEX + g_opforListSize, "Resources/opfortank.png");
	p -> setPosition(posX, posY);
	p -> setDistance(distance);
	p -> setHealth(health);
	p -> setActive(true);

	g_opforListSize++;
	
	// A new node is created in the linked list
	ptr newptr;
	newptr = new opforNode;
	newptr -> sprite = p;
	newptr -> next = NULL;

	if(opforHead == NULL)
	{
		opforHead = newptr;
	}
	else
	{
		opforTailItem -> next = newptr;
	}

	opforTailItem = newptr;
}

// Moves all the enemies on the screen up
void advanceOpfor()
{
	ptr cur = opforHead;

	while(cur != NULL)
	{
		// If an enemy is not in range of the wall move 
		// him up
		if(cur -> sprite -> getY() > WALL_BOUNDRY &&
			cur -> sprite -> getActive() == true)
		{
			cur -> sprite -> moveUp();
		}

		// If he is in range, fire on the wall
		if(cur ->sprite->getY() <= WALL_BOUNDRY &&
			g_timer % OPFOR_HIT_FREQ == 0 + 
			cur->sprite->getFireOffset() &&
			cur -> sprite -> getActive() == true)
		{
			g_projectileCurr++;

			if(g_projectileCurr >= g_projectileListSize)
			{
				createProjectile(cur -> sprite -> getX(), 
					cur-> sprite -> getY() - 20,
					0, -1, ARROWTOWER_SPEED, OPFOR);
			}
			else
			{
				activateProjectile(cur -> sprite -> getX(), 
					cur-> sprite -> getY() - 20,
					0, -1, ARROWTOWER_SPEED, OPFOR);
			}
		}

		cur = cur -> next;
	}
}

// Advances the game timer
void advanceTimer()
{
	g_timer++;
}

// Updates the position of our cursor
void updateCursor()
{
	const int CURSOR_V_WIDTH = 2;
	const int CURSOR_V_HEIGHT = 11;
	const int CURSOR_H_WIDTH = 11;
	const int CURSOR_H_HEIGHT = 2;
	const int CURSOR_GAP = 5;

	int posX = agk::GetRawMouseX();
	int posY = agk::GetRawMouseY();

	cursorT.setPosition(posX - (CURSOR_V_WIDTH / 2), 
		posY - CURSOR_GAP * 2);
	cursorB.setPosition(posX - (CURSOR_V_WIDTH / 2),
		posY + CURSOR_GAP * 2);
	cursorR.setPosition(posX + (CURSOR_H_WIDTH + CURSOR_GAP), 
		posY - (CURSOR_H_HEIGHT / 2));
	cursorL.setPosition(posX - (CURSOR_H_WIDTH + CURSOR_GAP), 
		posY - (CURSOR_H_HEIGHT / 2));
}

// Function to check any and all screen clicks and hovers
void checkClicks()
{
	// Get mouse position
	float posX = agk::GetRawMouseX();
	float posY = agk::GetRawMouseY();

	// Check click events
	// Check if we clicked an enemy
	if(agk::GetRawMouseLeftPressed() && posX <= GAME_SCREEN_WIDTH 
		&& posY >= WALL_BOUNDRY)
	{
		agk::SetSpriteVisible(EXPLOSION_INDEX, FALSE);
		agk::SetSpritePosition(EXPLOSION_INDEX, 
			SCREEN_WIDTH, SCREEN_HEIGHT);

		// Check out click against the position of each enemy
		for(int i = OPFOR_START_INDEX; 
			i < OPFOR_START_INDEX + g_opforListSize; i++)
		{
			if(agk::GetSpriteHit(posX, posY) == i)
			{
				removeOpfor(i);
			}
		}

		// Play missile animation and sound
		playExplosion(posX, posY);
		
	}

	// Check if we are left clicking a turret
	if(agk::GetRawMouseLeftPressed() && posX <= GAME_SCREEN_WIDTH 
		&& posY < WALL_BOUNDRY)
	{
		for(int i = BUILDING_START_INDEX; 
			i < BUILDING_START_INDEX + g_buildingListSize; i++)
		{
			if(agk::GetSpriteHit(posX, posY) == i)
			{
				rotateBuilding(i, "CW");
				agk::PlaySound(PICKUP_SOUND);
			}
		}
	}

	// Check if we are right clicking a turret
	if(agk::GetRawMouseRightPressed() && posX <= GAME_SCREEN_WIDTH 
		&& posY < WALL_BOUNDRY)
	{
		for(int i = BUILDING_START_INDEX;
			i < BUILDING_START_INDEX + g_buildingListSize; i++)
		{
			if(agk::GetSpriteHit(posX, posY) == i)
			{
				rotateBuilding(i, "CCW");
				agk::PlaySound(PICKUP_SOUND);
			}
		}
	}

	// Check if we are right clicking if we have a building attached
	// to the cursor
	if(agk::GetRawMouseRightPressed() && g_gameState == BUILDING)
	{
		hideBuidingCursor();
		g_cursorAttach = 0;
		g_gameState = BUYSTUFF;
		hideBuildingBoard();
		updateSidebar();
	}

	// Checks if we place a building on the screen
	if(agk::GetRawMouseLeftPressed() && posX > GAME_SCREEN_WIDTH)
	{
		if(posX > BUYBTN_X && posY > BUYBTN_AT_Y 
			&& posX < (BUYBTN_X + BUYBTN_WIDTH)
			&& posY < (BUYBTN_AT_Y + BUYBTN_HEIGHT))
		{
			if(g_currency >= ARROWTURRET_COST
				&& g_gameState == BUYSTUFF)
			{
				g_gameState = BUILDING;
				showBuildingBoard();
				g_cursorAttach = ARROW_TURRET;
				agk::PlaySound(PLACE_SOUND);
			}
		}
		else if(posX > BUYBTN_X && posY > BUYBTN_BC_Y 
			&& posX < (BUYBTN_X + BUYBTN_WIDTH)
			&& posY < (BUYBTN_BC_Y + BUYBTN_HEIGHT))
		{
			if(g_currency >= BOMBCATAPULT_COST
				&& g_gameState == BUYSTUFF)
			{
				g_gameState = BUILDING;
				showBuildingBoard();
				g_cursorAttach = BOMB_CATAPULT;
				agk::PlaySound(PLACE_SOUND);
			}
		}
		else if(posX > BUYBTN_X && posY > BUYBTN_GC_Y 
			&& posX < (BUYBTN_X + BUYBTN_WIDTH)
			&& posY < (BUYBTN_GC_Y + BUYBTN_HEIGHT))
		{
			if(g_currency >= GATLINGCANNON_COST
				&& g_gameState == BUYSTUFF)
			{
				g_gameState = BUILDING;
				showBuildingBoard();
				g_cursorAttach = GATLING_CANNON;
				agk::PlaySound(PLACE_SOUND);
			}
		}
		else if(posX > BUYBTN_X && posY > BUYBTN_AS_Y 
			&& posX < (BUYBTN_X + BUYBTN_WIDTH)
			&& posY < (BUYBTN_AS_Y + BUYBTN_HEIGHT))
		{
			if(g_currency >= AIRSTRIKE_COST && g_gameState == INPLAY)
			{
				g_currency -= AIRSTRIKE_COST;
				clearBoard();
			}
		}
	}

	// Check hover events
	if(posX > BUYBTN_X && posY > BUYBTN_AT_Y 
		&& posX < (BUYBTN_X + BUYBTN_WIDTH)
		&& posY < (BUYBTN_AT_Y + BUYBTN_HEIGHT))
	{
		if(g_currency >= ARROWTURRET_COST)
		{
			overlayGreen.setPosition(BUYBTN_X, BUYBTN_AT_Y);
			agk::SetSpriteVisible(OVERLAYG_INDEX, TRUE);
		}
		else
		{
			overlayRed.setPosition(BUYBTN_X, BUYBTN_AT_Y);
			agk::SetSpriteVisible(OVERLAYR_INDEX, TRUE);
		}
	}
	else if(posX > BUYBTN_X && posY > BUYBTN_BC_Y 
		&& posX < (BUYBTN_X + BUYBTN_WIDTH)
		&& posY < (BUYBTN_BC_Y + BUYBTN_HEIGHT))
	{
		if(g_currency >= BOMBCATAPULT_COST)
		{
			overlayGreen.setPosition(BUYBTN_X, BUYBTN_BC_Y);
			agk::SetSpriteVisible(OVERLAYG_INDEX, TRUE);
		}
		else
		{
			overlayRed.setPosition(BUYBTN_X, BUYBTN_BC_Y);
			agk::SetSpriteVisible(OVERLAYR_INDEX, TRUE);
		}
	}
	else if(posX > BUYBTN_X && posY > BUYBTN_GC_Y 
		&& posX < (BUYBTN_X + BUYBTN_WIDTH)
		&& posY < (BUYBTN_GC_Y + BUYBTN_HEIGHT))
	{
		if(g_currency >= GATLINGCANNON_COST)
		{
			overlayGreen.setPosition(BUYBTN_X, BUYBTN_GC_Y);
			agk::SetSpriteVisible(OVERLAYG_INDEX, TRUE);
		}
		else
		{
			overlayRed.setPosition(BUYBTN_X, BUYBTN_GC_Y);
			agk::SetSpriteVisible(OVERLAYR_INDEX, TRUE);
		}
	}
	else if(posX > BUYBTN_X && posY > BUYBTN_AS_Y 
		&& posX < (BUYBTN_X + BUYBTN_WIDTH)
		&& posY < (BUYBTN_AS_Y + BUYBTN_HEIGHT))
	{
		if(g_currency >= AIRSTRIKE_COST)
		{
			overlayGreen.setPosition(BUYBTN_X, BUYBTN_AS_Y);
			agk::SetSpriteVisible(OVERLAYG_INDEX, TRUE);
		}
		else
		{
			overlayRed.setPosition(BUYBTN_X, BUYBTN_AS_Y);
			agk::SetSpriteVisible(OVERLAYR_INDEX, TRUE);
		}
	}
	else
	{
		agk::SetSpriteVisible(OVERLAYG_INDEX, FALSE);
		agk::SetSpriteVisible(OVERLAYR_INDEX, FALSE);
	}
}

// Removes an ememy of the given index
void removeOpfor(int sIndex)
{
	ptr cur = opforHead;
	bool found = false;

	while(cur != NULL && found == false)
	{
		if(cur -> sprite -> getSpriteIndex() == sIndex)
		{
			if(cur -> sprite -> getHealth() == 1)
			{
				int posX = agk::Random(OPFOR_SPAWN_BOUND1, 
					OPFOR_SPAWN_BOUND2); 
				cur -> sprite -> deactivate(posX, SCREEN_HEIGHT);
				g_opforCurr--;
				g_opforDestroyed++;
				g_score += SCORE_INCREMENT;
				g_currency += CURRENCY_INCREMENT;
			}
			else
			{
				cur -> sprite -> decrementHealth();
			}

			found = true;
		}

		cur = cur -> next;
	}
}

// Increases game difficulty
void increaseDifficulty()
{
	// Intervals in rounds
	const int SPEED_MAX_INCREASE = 3;
	const int SPEED_MIN_INCREASE = 5;
	const int HEALTH_MAX_INCREASE = 2;
	const int HEALTH_MIN_INCREASE = 3;

	const int SPAWN_FREQ_INCREASE = 1;
	const int SPAWN_FREQ_DECREMENT = 25;
	const int SPAWN_FREQ_BOUNDRY = 50;

	const int AMOUNT_INCREASE = 1;
	const int AMOUNT_INCREASE_INCREMENT = 2;

	if(g_currRound % SPEED_MAX_INCREASE == 0)
	{
		g_opforMaxSpeed++;
	}

	if(g_currRound % SPEED_MIN_INCREASE == 0)
	{
		g_opforMinSpeed++;
	}
	
	if(g_currRound % HEALTH_MAX_INCREASE == 0)
	{
		g_opforMaxHealth++;
	}

	if(g_currRound % HEALTH_MIN_INCREASE == 0)
	{
		g_opforMinHealth++;
	}
	
	if(g_currRound % SPAWN_FREQ_INCREASE == 0 &&
		g_opforSpawnFrequency > SPAWN_FREQ_BOUNDRY)
	{
		g_opforSpawnFrequency -= SPAWN_FREQ_DECREMENT;
	}

	if(g_currRound % AMOUNT_INCREASE == 0)
	{
		g_opforCount += AMOUNT_INCREASE_INCREMENT;
	}

	g_opforRemaining = g_opforCount;
}

// Rather than create an enemie we may want to reuse an old one.
// This function activates an old opfor
void activateOpfor()
{
	ptr cur = opforHead;
	bool activated = false;

	while(cur != NULL && activated == false)
	{
		if(cur -> sprite -> getActive() == false)
		{
			int distance = agk::Random(g_opforMinSpeed, 
				g_opforMaxSpeed);
			int health = agk::Random(g_opforMinHealth, 
				g_opforMaxHealth);
			cur -> sprite -> setActive(true);
			cur -> sprite -> setDistance(distance);
			cur -> sprite -> setHealth(health);
			activated = true;
		}

		cur = cur -> next;
	}
}

// Advance the round
void advanceRound()
{
	g_currRound++;
	agk::SetTextString(SURVIVED_TEXT, agk::Str(g_currRound));
}

// Updates sidebar information
void updateSidebar()
{
	agk::SetTextString(HEALTH_VAR_TEXT, agk::Str(g_castleHealth));
	agk::SetTextString(SCORE_TEXT, agk::Str(g_score));
	agk::SetTextString(CURRENCY_TEXT, agk::Str(g_currency));
	agk::SetTextString(ENEMIES_TEXT, agk::Str(g_opforDestroyed));
}

// Advances the game score
void advanceScore()
{
	if(g_timer % ADVANCE_SCORE_FREQ == 0)
	{
		g_score++;
	}
}

// Checks ifthe enter key was pressed.
bool checkEnterKey()
{
	if(agk::GetRawKeyPressed(AGK_KEY_ENTER))
	{
		return true;
	}
	
	return false;
}

// Shows which tiles on the texture map are available for building
// placement.
void showBuildingBoard()
{
	int spriteIndex = 1;

	for (int r = 0; r < TILE_ROWS; r++)
	{
		for (int c = 0; c < TILE_COLS; c++)
		{
			if(g_buildingMap[r][c] == 0)
			{
				agk::SetSpriteColorAlpha(spriteIndex, 100);
			}

			spriteIndex++;
		}
	}
}

// Hides the building board
void hideBuildingBoard()
{
	int spriteIndex = 1;

	for (int r = 0; r < TILE_ROWS; r++)
	{
		for (int c = 0; c < TILE_COLS; c++)
		{
			agk::SetSpriteColorAlpha(spriteIndex, 255);

			spriteIndex++;
		}
	}
}

// If we have a building attached to our cursor it is moved with 
// the cursor using this function
void moveBuilding()
{
	int posX = agk::GetRawMouseX();
	int posY = agk::GetRawMouseY();

	const int HALFWIDTH = 16;

	if(g_cursorAttach == ARROW_TURRET)
	{
		agk::SetSpriteVisible(ARROWTURRET_INDEX, TRUE);
		arrowTurret.setPosition(posX - HALFWIDTH, posY - HALFWIDTH);
	}
	else if(g_cursorAttach == BOMB_CATAPULT)
	{
		agk::SetSpriteVisible(BOMBCATAPULT_INDEX, TRUE);
		bombCatapult.setPosition(posX - HALFWIDTH, posY - HALFWIDTH);
	}
	else if(g_cursorAttach == GATLING_CANNON)
	{
		agk::SetSpriteVisible(GATLINGCANNON_INDEX, TRUE);
		gatlingCannon.setPosition(posX - HALFWIDTH, posY - HALFWIDTH);
	}
}

// If we click on a valid tile we place a building there.
void checkPlacement()
{
	int posX = agk::GetRawMouseX();
	int posY = agk::GetRawMouseY();

	bool placed = false;

	float x, y = 0;

	if(agk::GetRawMouseLeftPressed())
	{
		int spriteIndex = 1;

		for (int r = 0; r < TILE_ROWS && placed == false; r++)
		{
			x = 0;

			for (int c = 0; c < TILE_COLS && placed == false; c++)
			{
				if(g_buildingMap[r][c] > 0 
					&& posX > x 
					&& posX < x + TILE_WIDTH 
					&& posY > y 
					&& posY < y + TILE_HEIGHT)
				{
					placed = true;
					buildBuilding(x, y, g_cursorAttach);
					g_buildingMap[r][c] = 0;
				}

				spriteIndex++;

				x += TILE_WIDTH;
			}

			y += TILE_HEIGHT;
		}
	}
}

// Constructs a building at a given location
void buildBuilding(float x, float y, int building)
{
	// Creates a building class
	Building *p = new Building;
	p -> setType(building);

	if(building == ARROW_TURRET)
	{
		p -> createSprite(BUILDING_START_INDEX + g_buildingListSize, 
			"Resources/arrowTurret.png");
		g_currency -= ARROWTURRET_COST;
	}
	else if(building == BOMB_CATAPULT)
	{
		p -> createSprite(BUILDING_START_INDEX + g_buildingListSize, 
			"Resources/bombCatapult.png");
		g_currency -= BOMBCATAPULT_COST;
	}
	else if(building == GATLING_CANNON)
	{
		p -> createSprite(BUILDING_START_INDEX + g_buildingListSize, 
			"Resources/gatlingCannon.png");
		g_currency -= GATLINGCANNON_COST;
	}

	p -> setPosition(x, y);

	g_buildingListSize++;
	
	// Creates a building node in our list
	bptr newptr;
	newptr = new buildingNode;
	newptr -> sprite = p;
	newptr -> next = NULL;

	if(buildingHead == NULL)
	{
		buildingHead = newptr;
	}
	else
	{
		buildingTailItem -> next = newptr;
	}

	buildingTailItem = newptr;

	// Play the placement sound and update the game
	agk::PlaySound(PLACE_SOUND);
	hideBuidingCursor();
	g_cursorAttach = 0;
	g_gameState = BUYSTUFF;
	hideBuildingBoard();
	updateSidebar();
}

// Hides the building cursor
void hideBuidingCursor()
{
	agk::SetSpriteVisible(ARROWTURRET_INDEX, FALSE);
	agk::SetSpriteVisible(BOMBCATAPULT_INDEX, FALSE);
	agk::SetSpriteVisible(GATLINGCANNON_INDEX, FALSE);
}

// Rotates a building
void rotateBuilding(int sIndex, string dir)
{
	bptr cur = buildingHead;
	bool found = false;

	while(cur != NULL && found == false)
	{
		if(cur -> sprite -> getSpriteIndex() == sIndex)
		{
			if(dir == "CW")
			{
				cur -> sprite -> rotateCW();
			}
			else
			{
				cur -> sprite -> rotateCCW();
			}

			found = true;
		}

		cur = cur -> next;
	}
}

// Fires towers
void fireTowers()
{
	bptr cur = buildingHead;

	while(cur != NULL)
	{
		if(cur -> sprite -> getType() == ARROW_TURRET && 
			g_timer % ARROWTOWER_FREQ == 0 +
			cur -> sprite -> getFireOffset())
		{
			g_projectileCurr++;

			if(g_projectileCurr >= g_projectileListSize)
			{
				createProjectile(cur -> sprite -> getX(), 
					cur-> sprite -> getY(),
					cur -> sprite -> getDeltaX(), 
					cur -> sprite -> getDeltaY(), 
					ARROWTOWER_SPEED, FRIENDLY);
			}
			else
			{
				activateProjectile(cur -> sprite -> getX(), 
					cur-> sprite -> getY(),
					cur -> sprite -> getDeltaX(),
					cur -> sprite -> getDeltaY(), 
					ARROWTOWER_SPEED, FRIENDLY);
			}
		}
		else if(cur -> sprite -> getType() == BOMB_CATAPULT && 
			g_timer % BOMBCATAPULT_FREQ == 0)
		{
			g_projectileCurr++;

			if(g_projectileCurr >= g_projectileListSize)
			{
				createProjectile(cur -> sprite -> getX(), 
					cur-> sprite -> getY(),
					cur -> sprite -> getDeltaX(), 
					cur -> sprite -> getDeltaY(), 
					BOMBCATAPULT_SPEED, FRIENDLY);
			}
			else
			{
				activateProjectile(cur -> sprite -> getX(), 
					cur-> sprite -> getY(),
					cur -> sprite -> getDeltaX(), 
					cur -> sprite -> getDeltaY(), 
					BOMBCATAPULT_SPEED, FRIENDLY);
			}
		}
		else if(cur -> sprite -> getType() == GATLING_CANNON && 
			g_timer % GATLINGCANNON_FREQ == 0)
		{
			g_projectileCurr++;

			if(g_projectileCurr >= g_projectileListSize)
			{
				createProjectile(cur -> sprite -> getX(), 
					cur-> sprite -> getY(),
					cur -> sprite -> getDeltaX(), 
					cur -> sprite -> getDeltaY(), 
					GATLINGCANNON_SPEED, FRIENDLY);
			}
			else
			{
				activateProjectile(cur -> sprite -> getX(),
					cur-> sprite -> getY(),
					cur -> sprite -> getDeltaX(), 
					cur -> sprite -> getDeltaY(), 
					GATLINGCANNON_SPEED, FRIENDLY);
			}
		}
		

		cur = cur -> next;
	}
}

// Creates a projectile
void createProjectile(int x, int y, int dX, int dY, int speed, 
					  int type)
{
	// Creates an instance of our projectile class
	Projectile *p = new Projectile(PROJECTILE_START_INDEX +
		g_projectileListSize, 
		"Resources/projectile.png", speed, 1, dX, dY);
	p -> createSprite();
	p -> setPosition(x + (TILE_WIDTH / 2), y + (TILE_HEIGHT / 2));
	p -> setType(type);

	g_projectileListSize++;
	
	// defines a new projectile node in our linked list
	pptr newptr;
	newptr = new projectileNode;
	newptr -> sprite = p;
	newptr -> next = NULL;

	if(projectileHead == NULL)
	{
		projectileHead = newptr;
	}
	else
	{
		projectileTailItem -> next = newptr;
	}

	projectileTailItem = newptr;
}

// Moves all projectiles on the trajectories
void advanceProjectiles()
{
	pptr cur = projectileHead;

	while(cur != NULL)
	{
		if(cur -> sprite -> getActive() == true)
		{
			cur -> sprite -> advanceProjectile();

			int posX = cur -> sprite -> getX();
			int posY = cur -> sprite -> getY();

			if(posY > SCREEN_HEIGHT || posY < 0
				|| posX > SCREEN_HEIGHT || posX < 0)
			{
				removeProjectile(cur -> sprite -> getSpriteIndex());
			}
		}

		cur = cur -> next;
	}	
}

// Activates projectiles to reuse old projectiles rahter than 
// creating new ones
void activateProjectile(int posX, int posY, int dX, int dY, int speed, 
						int type)
{
	pptr cur = projectileHead;
	bool activated = false;

	while(cur != NULL && activated == false)
	{
		if(cur -> sprite -> getActive() == false)
		{
			cur -> sprite -> setActive();
			cur -> sprite -> setPosition(posX + (TILE_WIDTH / 2),
				posY + (TILE_WIDTH / 2));
			cur -> sprite -> setTrajectory(dX, dY);
			cur -> sprite -> setDistance(speed);
			cur -> sprite -> setType(type);
			activated = true;
		}

		cur = cur -> next;
	}
}

// Check projectile collisions
void checkProjectiles()
{
	for(int i = PROJECTILE_START_INDEX; 
		i < PROJECTILE_START_INDEX + g_projectileListSize; i++)
	{
		int posY = agk::GetSpriteY(i);
		int posX = agk::GetSpriteX(i);

		for(int j = OPFOR_START_INDEX;
			j < OPFOR_START_INDEX + g_opforListSize; j++)
		{
			if(agk::GetSpriteCollision(i, j))
			{
				playExplosion(posX, posY);

				removeOpfor(j);
				removeProjectile(i);
			}
		}

		if(posY < WALL_MARK && checkType(i) == OPFOR)
		{
			removeProjectile(i);

			playExplosion(posX, posY);

			g_castleHealth -= 10;
		}
	}
}

void checkProjectiles2()
{
	pptr curProjectile = projectileHead;
	ptr curOpfor = opforHead;

	while(curProjectile != NULL)
	{
		int posY = curProjectile->sprite->getX();
		int posX = curProjectile->sprite->getY();

		while(curOpfor != NULL)
		{
			if(agk::GetSpriteCollision(
				curProjectile->sprite->getSpriteIndex(), 
				curOpfor->sprite->getSpriteIndex()))
			{
				playExplosion(posX, posY);

				removeOpfor(curOpfor->sprite->getSpriteIndex());
				removeProjectile(
					curProjectile->sprite->getSpriteIndex());
			}

			if(posY < WALL_MARK && 
				curProjectile->sprite->getType() == OPFOR)
			{
				removeProjectile(
					curProjectile->sprite->getSpriteIndex());

				playExplosion(posX, posY);

				g_castleHealth -= 10;
			}

			curOpfor = curOpfor->next;
		}

		curOpfor = opforHead;
		curProjectile = curProjectile->next;
	}

}
// Removes a projectile of the given index
void removeProjectile(int sIndex)
{
	g_projectileCurr--;

	pptr cur = projectileHead;
	bool found = false;

	while(cur != NULL && found == false)
	{
		if(cur -> sprite -> getSpriteIndex() == sIndex)
		{
			cur -> sprite -> deactivate(SCREEN_WIDTH, SCREEN_HEIGHT);
			found = true;
		}

		cur = cur -> next;
	}
}

// Checks if the screen is clear of tanks or not
bool screenClear()
{
	ptr cur = opforHead;

	while(cur != NULL)
	{
		if(cur -> sprite -> getY() < SCREEN_HEIGHT)
		{
			return false;
		}

		cur = cur -> next;
	}

	return true;
}

// Shows game summery
void showSummery()
{
	agk::SetTextVisible(HEALTH_TEXT, FALSE);
	agk::SetTextVisible(HEALTH_VAR_TEXT, FALSE);
	agk::SetTextString(SURVIVED_TEXT, agk::Str(g_currRound));
	agk::SetTextString(SCORE_TEXT, agk::Str(g_score));
	agk::SetTextString(ENEMIES_TEXT, agk::Str(g_opforDestroyed));

	agk::SetTextDepth(SURVIVED_TEXT, 5);
	agk::SetTextDepth(SCORE_TEXT, 5);
	agk::SetTextDepth(ENEMIES_TEXT, 5);

	agk::SetTextPosition(SCORE_TEXT, 72, 330);
	agk::SetTextPosition(ENEMIES_TEXT, 260, 330);
	agk::SetTextPosition(SURVIVED_TEXT, 520, 330);
}

// Checks the projectile type and returns if its an enemy or friendly
int checkType(int sIndex)
{
	pptr cur = projectileHead;
	int rType;
	bool found = false;

	while(cur != NULL && found == false)
	{
		if(cur -> sprite -> getSpriteIndex() == sIndex)
		{
			rType = cur->sprite->getType();
			found = true;
		}

		cur = cur -> next;
	}

	return rType;
}

// shows the red emergency pulse
void displayRedFade()
{
	redFadeL.setPosition(0, 0);
	redFadeR.setPosition(SCREEN_WIDTH - redFadeR.getWidth(), 0);
	redFadeT.setPosition(0, 0);
	redFadeB.setPosition(0, SCREEN_HEIGHT - redFadeB.getHeight());
}

// Animates the pulse
void pulseRedFade()
{
	const int PULSE_TIME = 8;

	displayRedFade();

	switch(g_fadingIn)
	{
	case true:
		if(g_redFadeOpacity < 255)
		{
			g_redFadeOpacity += PULSE_TIME;
		}
		else
		{
			g_fadingIn = false;
		}
		break;

	case false:
		if(g_redFadeOpacity > 0)
		{
			g_redFadeOpacity -= PULSE_TIME;
		}
		else
		{
			g_fadingIn = true;
		}
		break;
	}

	agk::SetSpriteColorAlpha(REDFADEL_INDEX, g_redFadeOpacity);
	agk::SetSpriteColorAlpha(REDFADER_INDEX, g_redFadeOpacity);
	agk::SetSpriteColorAlpha(REDFADET_INDEX, g_redFadeOpacity);
	agk::SetSpriteColorAlpha(REDFADEB_INDEX, g_redFadeOpacity);
}

// Clears the board of enemies. Used for airstrike
void clearBoard()
{
	ptr cur = opforHead;

	while(cur != NULL)
	{
		if(cur->sprite->getActive() == true)
		{
			int posX = cur->sprite->getCenterX();
			int posY = cur->sprite->getCenterY();

			playExplosion(posX, posY);

			removeOpfor(cur->sprite->getSpriteIndex());
		}

		cur = cur->next;
	}
}

// Plays the explosion animation and sound at a given location
void playExplosion(int posX, int posY)
{
	agk::PlaySound(EXPLOSION_SOUND);

	agk::SetSpritePosition(EXPLOSION_INDEX, posX - 
	(EXPLOSION_SIZE / 2), posY - (EXPLOSION_SIZE / 2));

	agk::SetSpriteVisible(EXPLOSION_INDEX, TRUE);

	agk::PlaySprite(EXPLOSION_INDEX, EXPLOSION_FPS, FALSE);
}