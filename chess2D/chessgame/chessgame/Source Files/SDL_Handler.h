/**
 * @file SDL_Handler.h
 * @class SDL_Handler
 * @author Michael
 * @brief handles and displays a board to the user. aggregates from game
 */
#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "chess/game.h"

/**
* @brief enum used for accessing objects in a 1d piece's array which contain their images
*
*/
enum pictureobjs
{
	TOP_LABEL,//=0
	SIDE_LABEL,//=1
	BANNER_LABEL,//=3
	/*
	space between
	*/
	bPAWN_ONE, bPAWN_TWO, bPAWN_THREE, bPAWN_FOUR, bPAWN_FIVE, bPAWN_SIX, bPAWN_SEVEN, bPAWN_EIGHT,
	bROOK_ONE, bKNIGHT_ONE, bBISHOP_ONE, bQUEEN, bKING, bBISHOP_TWO, bKNIGHT_TWO, bROOK_TWO,
	/*
	space between
	*/
	wPAWN_ONE, wPAWN_TWO, wPAWN_THREE, wPAWN_FOUR, wPAWN_FIVE, wPAWN_SIX, wPAWN_SEVEN, wPAWN_EIGHT,
	wROOK_ONE, wKNIGHT_ONE, wBISHOP_ONE, wKING, wQUEEN, wBISHOP_TWO, wKNIGHT_TWO, wROOK_TWO,
	/*
	space between
	*/
	TOTAL //=37
};

enum textObj
{
	PLAYER_TURN, //=0
	PLAYER_MESSAGE, //=1
	TTOTAL //=2
};

class SDL_Handler 
{
private:
	/**
	* @brief screen window width
	*
	*/
	const int SCREEN_WIDTH = 860;

	/**
	* @brief screen window height
	*
	*/
	const int SCREEN_HEIGHT = 660;

	/**
	* @brief The window we'll be rendering to
	* 
	*/
	SDL_Window* gWindow = NULL;

	/**
	* @brief the renderer
	*
	*/
	SDL_Renderer* renderer = NULL;

	/**
	* @brief displayed texture which contains images for all 32 chess pieces
	*
	*/
	SDL_Texture* gTexture[pictureobjs::TOTAL];

	/**
	* @brief displayed rectangle boxes which contain the images for all 32 chess pieces in boxes
	*
	*/
	SDL_Rect rect[pictureobjs::TOTAL];

	/**
	* @brief Globally used font
	*
	*/
	TTF_Font* gFont = NULL;

	/**
	* @brief The actual hardware texture
	*
	*/
	SDL_Texture* mTexture[textObj::TTOTAL];

	/**
	* @brief holds the sound effect for blocking a chess move
	*
	*/
	Mix_Chunk* gMove_Block = NULL;

	/**
	* @brief holds the sound for making a chess move
	*
	*/
	Mix_Chunk* gPiece_Move = NULL;

	/**
	* @brief holds the sound for a game win
	*
	*/
	Mix_Chunk* gGame_Win = NULL;

	/**
	* @brief The dimensions describing the sizes of the text boxes
	*
	*/
	int playerTurnW, playerTurnH, messageW, messageH;

	/**
	* @brief the game object used to play the game in the background
	*
	*/
	game* GAMEobj = new game();

	/**
	* @brief keeps data about the current selected piece's x and y co-ords, and it's pos in the textures array
	*
	*/
	int currentlySelectedPieceInObjArr = -1, pieceCurrentX = -1, pieceCurrentY = -1;

	/**
	* @brief used to verify if a game has ended or not
	*
	*/
	bool gameOver = false;

public:
	
	/**
	* @brief inits all SDL related stuff
	* @param none
	*
	* @return bool
	*/
	bool init();

	/**
	* @brief draws SDL content onto screen and updates the display
	*@param none
	*
	* @return void
	*/
	void displayStuff();

	/**
	* @brief Frees media and shuts down SDL
	*@param none
	*
	* @return void
	*/
	void close();

	/**
	* @brief handles an event whether it is an onclick event or keyboard press
	*@param none
	*
	* @return void
	*/
	void handleEvent(SDL_Event* e);

	/**
	* @brief loads all pictures onto SDL textures
	* @param none
	*
	* @return bool
	*/
	bool initPictures();

private:

	/**
	* @brief loads all black pieces pictures onto SDL textures
	* @param none
	*
	* @return bool
	*/
	bool initBlackPieces();

	/**
	* @brief loads all white pieces pictures onto SDL textures
	* @param none
	*
	* @return bool
	*/
	bool initWhitePieces();

	/**
	* @brief loads sets up the SDL fonts
	* @param none
	*
	* @return bool
	*/
	bool initFontAndText();

	/**
	* @brief places the text passed in onto a banner to display to the window
	* @param playerTurn string containing which players turn it is
	* @param message the message for the player
	*
	* @return bool
	*/
	void loadThisText(std::string playerTurn, std::string message);

	/**
	* @brief loads images for all pieces except for pawns onto and SDL_Surface object and returns the object
	* @param none
	*
	* @return SDL_Surface*
	*/
	SDL_Surface* getImage(int numToCompare);

	/**
	* @brief takes in a value, whehter x or y representing the position of the mouse on the screen then returns
	* a number which corresponds with the co-ord system used by the chess board
	* 
	*@param num the position of the mouse on the screen
	*
	* @return int
	*/
	int getLowerBoundCo_ord(int num);

	/**
	* @brief handles an event whether it is an onclick event or keyboard press
	*@param vector vector containing possible positions to move to
	* @param rect rect object defining the size of the grid boxes
	* @param iVal x co-ord
	* @param jVal y co-ord
	*
	* @return void
	*/
	void drawHighLightedTile(std::vector<XYpos> vector, SDL_Rect rect, int iVal, int jVal);

	/**
	* @brief upgrades a pawn to a queen, visually, so changes a pawn's texture image to a queen
	* @param none
	*
	* @return void
	*/
	void upgradePossiblePawnToQueen();

	/**
	* @brief undoes the most recent pawn to queen upgrade
	* @param olddata information about the most recently completed move
	*
	* @return void
	*/
	void undoQueenUpgrade(previousMove olddata);

	/**
	* @brief resets the entire game
	* @param none
	*
	* @return void
	*/
	void restartGame();
};