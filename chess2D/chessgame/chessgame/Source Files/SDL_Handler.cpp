#include "SDL_Handler.h"

bool SDL_Handler::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		this->gWindow = SDL_CreateWindow("CHESS2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->SCREEN_WIDTH, this->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (this->gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			this->renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (this->renderer == NULL)
			{
				fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
				SDL_DestroyWindow(this->gWindow);
				SDL_Quit();
				return EXIT_FAILURE;
			}
			else {

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}

			SDL_RenderClear(this->renderer);
		}
	}

	return success;
}

void SDL_Handler::displayStuff()
{
	//Top corner viewport
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);

	std::vector<XYpos> vect;
	if (this->GAMEobj != NULL)
		vect = this->GAMEobj->getVector();

	SDL_Rect single_rect;
	single_rect.w = 80;
	single_rect.h = 80;
	for (int i = 0; i < 8; ++i)
	{
		single_rect.x = i * 80 + 20;
		for (int j = 0; j < 8; ++j) 
		{
			single_rect.y = j * 80 + 20;
			this->drawHighLightedTile(vect, single_rect, i, j);
			SDL_RenderFillRect(this->renderer, &single_rect);
		}
	}

	for (int i = 0; i < pictureobjs::TOTAL; ++i) 
	{
		if (this->gTexture[i] != NULL && (&this->rect[i] != NULL)) 
		{
			//Copying the texture on to the window using renderer and rectangle
			SDL_RenderCopy(this->renderer, this->gTexture[i], NULL, &this->rect[i]);
		}
	}

	//Set rendering space and render to screen
	SDL_Rect renderQuad[textObj::TTOTAL];
	renderQuad[textObj::PLAYER_TURN] = {680, 160, this->playerTurnW, this->playerTurnH};
	renderQuad[textObj::PLAYER_MESSAGE] = { 680, 320, this->messageW, this->messageH };
	//Render to screen
	for (int i = 0; i < textObj::TTOTAL; ++i)
	{
		SDL_RenderCopyEx(this->renderer, this->mTexture[i], NULL, &renderQuad[i], 0.0, NULL, SDL_FLIP_NONE);
	}

	//Update screen
	SDL_RenderPresent(this->renderer);
}

bool SDL_Handler::initPictures()
{
	SDL_Surface* temp = NULL;
	temp = IMG_Load("res/high/top_label.png");
	if (temp == NULL) 
	{
		std::cout << "cannot load the top label" << std::endl;
		return false;
	}
	//Filling texture with the image using a surface
	this->gTexture[pictureobjs::TOP_LABEL] = SDL_CreateTextureFromSurface(this->renderer, temp);
	//Deleting the temporary surface
	SDL_FreeSurface(temp);
	temp = NULL;


	temp = IMG_Load("res/high/side_label.png");
	if (temp == NULL)
	{
		std::cout << "cannot load the side label" << std::endl;
		return false;
	}
	//Filling texture with the image using a surface
	this->gTexture[pictureobjs::SIDE_LABEL] = SDL_CreateTextureFromSurface(this->renderer, temp);
	//Deleting the temporary surface
	SDL_FreeSurface(temp);
	temp = NULL;

	temp = IMG_Load("res/high/bannerimg.png");
	if (temp == NULL) 
	{
		std::cout << "cannot load the banner img" << std::endl;
		return false;
	}
	//Filling texture with the image using a surface
	this->gTexture[pictureobjs::BANNER_LABEL] = SDL_CreateTextureFromSurface(this->renderer, temp);
	//Deleting the temporary surface
	SDL_FreeSurface(temp);
	temp = NULL;


	//load sound files
	//Load sound effects
	this->gMove_Block = Mix_LoadWAV("res/sounds/move_block.wav");
	if (this->gMove_Block == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	this->gPiece_Move = Mix_LoadWAV("res/sounds/chess_move.wav");
	if (this->gPiece_Move == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	this->gGame_Win = Mix_LoadWAV("res/sounds/game_win.wav");
	if (this->gGame_Win == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}


	this->rect[pictureobjs::TOP_LABEL].x = 0;
	this->rect[pictureobjs::TOP_LABEL].y = 0;
	this->rect[pictureobjs::TOP_LABEL].w = 660;
	this->rect[pictureobjs::TOP_LABEL].h = 20;

	this->rect[pictureobjs::SIDE_LABEL].x = 0;
	this->rect[pictureobjs::SIDE_LABEL].y = 20;
	this->rect[pictureobjs::SIDE_LABEL].w = 20;
	this->rect[pictureobjs::SIDE_LABEL].h = 660;

	this->rect[pictureobjs::BANNER_LABEL].x = 660;
	this->rect[pictureobjs::BANNER_LABEL].y = 0;
	this->rect[pictureobjs::BANNER_LABEL].w = 200;
	this->rect[pictureobjs::BANNER_LABEL].h = 660;

	if (!this->initBlackPieces()) 
	{
		std::cout << "failed to load black pieces" << std::endl;
		return false;
	}
	if (!this->initWhitePieces()) 
	{
		std::cout << "failed to load white pieces" << std::endl;
		return false;
	}
	if (!this->initFontAndText())
	{
		std::cout << "failed to load text on screen" << std::endl;
		return false;
	}
	return true;
}

void SDL_Handler::close()
{
	//Free loaded side images
	for (int i = 0; i < pictureobjs::TOTAL; ++i)
	{
		if (this->gTexture[i] != NULL) 
		{
			SDL_DestroyTexture(this->gTexture[i]);
			this->gTexture[i] = NULL;
		}
	}

	for (int i = 0; i < textObj::TTOTAL; ++i)
	{
		if (this->mTexture[i] != NULL)
		{
			SDL_DestroyTexture(this->mTexture[i]);
			this->mTexture[i] = NULL;
		}
	}

	if (this->GAMEobj != NULL) 
	{
		delete GAMEobj;
		GAMEobj = NULL;
	}

	//free the sound effects
	Mix_FreeChunk(this->gMove_Block);
	this->gMove_Block = NULL;

	Mix_FreeChunk(this->gPiece_Move);
	this->gPiece_Move = NULL;

	Mix_FreeChunk(this->gGame_Win);
	this->gGame_Win = NULL;

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->gWindow);
	this->gWindow = NULL;
	this->renderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDL_Handler::handleEvent(SDL_Event* e)
{
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		if (this->gameOver) 
		{
			Mix_PlayChannel(-1, this->gMove_Block, 0);
			if (this->GAMEobj == NULL)return;
			this->loadThisText(this->GAMEobj->playerTurnString(), "the game is over, press r to restart or close the application");
			return;
		}
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		int crrntX = this->getLowerBoundCo_ord(x);
		int crrntY = this->getLowerBoundCo_ord(y);

		if (this->GAMEobj == NULL)return;

		if (this->GAMEobj->checkIfCoordsInVec(crrntX, crrntY))
		{
			int eliminatedPosIndex = -1;
			for (int i = 0; i < pictureobjs::TOTAL; ++i)
			{
				if (this->rect[i].x == crrntX && this->rect[i].y == crrntY) 
				{
					eliminatedPosIndex = i;
					break;
				}
			}
			int num = this->currentlySelectedPieceInObjArr;
			bool safeKing = this->GAMEobj->movePieceToCoords(this->pieceCurrentX, this->pieceCurrentY, crrntX, crrntY, num, eliminatedPosIndex);
			//attempted a move that would comprimise the king
			if (!safeKing) 
			{
				Mix_PlayChannel(-1, this->gMove_Block, 0);
				return;
			}

			//check if co-ords is occupied by piece then eliminate it if it is
			if (eliminatedPosIndex != -1)
			{
				this->rect[eliminatedPosIndex].x = -1;
				this->rect[eliminatedPosIndex].y = -1;
				this->rect[eliminatedPosIndex].w = 0;
				this->rect[eliminatedPosIndex].h = 0;
			}

			this->rect[this->currentlySelectedPieceInObjArr].x = crrntX;
			this->rect[this->currentlySelectedPieceInObjArr].y = crrntY;
			Mix_PlayChannel(-1, this->gPiece_Move, 0);

			//check if the pieces y co-ords are at the border and upgrade the piece if it is a pawn
			if (crrntY == 20 || crrntY == 580)
			{
				this->upgradePossiblePawnToQueen();
			}

			this->currentlySelectedPieceInObjArr = -1;
			this->pieceCurrentX = -1;
			this->pieceCurrentY = -1;

			this->gameOver = this->GAMEobj->kingInCheck();
			//if game over play game won sound effect
			if (this->gameOver) 
			{
				Mix_PlayChannel(-1, this->gGame_Win, 0);
			}
			else 
			{
				this->gameOver = this->GAMEobj->isStaleMate();
			}

			
		}
		else 
		{
			if (this->GAMEobj == NULL)return;

			if (this->GAMEobj->selectThisPiece(crrntX, crrntY)) 
			{
				this->pieceCurrentX = crrntX;
				this->pieceCurrentY = crrntY;

				for (int i = 0; i < pictureobjs::TOTAL; ++i) 
				{
					if (this->rect[i].x == crrntX && this->rect[i].y == crrntY) 
					{
						this->currentlySelectedPieceInObjArr = i;
						break;
					}
				}
			}
			else 
			{
				Mix_PlayChannel(-1, this->gMove_Block, 0);
			}
		}

		this->loadThisText(this->GAMEobj->playerTurnString(), this->GAMEobj->getMessage());
	}
	else if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.sym == SDLK_u) 
		{
			//std::cout << "undo move was pressed" << std::endl;
			if (this->gameOver)
			{
				Mix_PlayChannel(-1, this->gMove_Block, 0);

				if (this->GAMEobj == NULL)return;
				this->loadThisText(this->GAMEobj->playerTurnString(), "the game is over, press r to restart or close the application");
				return;
			}

			if (this->GAMEobj == NULL)return;

			if (!this->GAMEobj->emptyStack()) 
			{
				previousMove olddata = this->GAMEobj->undoPrevMove();

				//change pos of piece
				this->rect[olddata.posInArr].x = olddata.oldX;
				this->rect[olddata.posInArr].y = olddata.oldY;
				Mix_PlayChannel(-1, this->gPiece_Move, 0);
				
				this->undoQueenUpgrade(olddata);

				//check if piece was eliminated and undo change
				if (olddata.takenPiecePosInArr != -1)
				{
					this->rect[olddata.takenPiecePosInArr].x = olddata.newX;
					this->rect[olddata.takenPiecePosInArr].y = olddata.newY;
					this->rect[olddata.takenPiecePosInArr].w = 80;
					this->rect[olddata.takenPiecePosInArr].h = 80;
				}
			}
			else 
			{
				Mix_PlayChannel(-1, this->gMove_Block, 0);
			}

			this->loadThisText(this->GAMEobj->playerTurnString(), this->GAMEobj->getMessage());
			this->GAMEobj->clearoutVector();
		}
		else if (e->key.keysym.sym == SDLK_r)
		{
			if (this->restartGame())this->gameOver = false;
			else std::cout << "failed to restart game" << std::endl;
		}
	}
}

int SDL_Handler::getLowerBoundCo_ord(int num)
{
	if (num >= 20 && num <= 99)return 20;
	else if (num >= 100 && num <= 179)return 100;
	else if (num >= 180 && num <= 259)return 180;
	else if (num >= 260 && num <= 339)return 260;
	else if (num >= 340 && num <= 419)return 340;
	else if (num >= 420 && num <= 499)return 420;
	else if (num >= 500 && num <= 579)return 500;
	else if (num >= 580 && num <= 659)return 580;
	else return -1;
}

bool SDL_Handler::initBlackPieces()
{
	SDL_Surface* temp;
	//pawn, pawn, pawn, pawn pawn, pawn, pawn, pawn
	for (int i = pictureobjs::bPAWN_ONE; i <= pictureobjs::bPAWN_EIGHT; ++i)
	{
		temp = IMG_Load("res/high/blackpawn.png");

		if (temp == NULL) 
		{
			std::cout << "cannot load the" << i << "'th black pawn" << std::endl;
			return false;
		}

		//Filling texture with the image using a surface
		this->gTexture[i] = SDL_CreateTextureFromSurface(this->renderer, temp);

		//Deleting the temporary surface
		SDL_FreeSurface(temp);
		temp = NULL;


		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::bPAWN_ONE) * 80 + 20;
		this->rect[i].y = 500;
	}

	//loading exotic pieces like king, queen, bishop, knight and rook
	//rook, knight, bishop, queen, king, bishop, knight, rook

	for (int i = pictureobjs::bROOK_ONE; i <= pictureobjs::bROOK_TWO; ++i)
	{
		temp = this->getImage(i);

		if (temp == NULL)
		{
			std::cout << "cannot load the" << i << "'th black exotic piece" << std::endl;
			return false;
		}

		//Filling texture with the image using a surface
		this->gTexture[i] = SDL_CreateTextureFromSurface(this->renderer, temp);

		//Deleting the temporary surface
		SDL_FreeSurface(temp);
		temp = NULL;


		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::bROOK_ONE) * 80 + 20;
		this->rect[i].y = 580;
	}

	return true;
}

bool SDL_Handler::initWhitePieces()
{
	SDL_Surface* temp;
	//pawn, pawn, pawn, pawn pawn, pawn, pawn, pawn
	for (int i = pictureobjs::wPAWN_ONE; i <= pictureobjs::wPAWN_EIGHT; ++i) 
	{
		temp = IMG_Load("res/high/whitepawn.png");

		if (temp == NULL) 
		{
			std::cout << "cannot load the" << i << "'th white pawn" << std::endl;
			return false;
		}

		//Filling texture with the image using a surface
		this->gTexture[i] = SDL_CreateTextureFromSurface(this->renderer, temp);

		//Deleting the temporary surface
		SDL_FreeSurface(temp);
		temp = NULL;


		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::wPAWN_ONE) * 80 + 20;
		this->rect[i].y = 100;
	}

	//loading exotic pieces like king, queen, bishop, knight and rook

	//rook, knight, bishop, queen, king, bishop, knight, rook
	for (int i = pictureobjs::wROOK_ONE; i <= pictureobjs::wROOK_TWO; ++i)
	{
		temp = this->getImage(i);

		if (temp == NULL)
		{
			std::cout << "cannot load the" << i << "'th white exotic piece" << std::endl;
			return false;
		}

		//Filling texture with the image using a surface
		this->gTexture[i] = SDL_CreateTextureFromSurface(this->renderer, temp);

		//Deleting the temporary surface
		SDL_FreeSurface(temp);
		temp = NULL;


		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::wROOK_ONE) * 80 + 20;
		this->rect[i].y = 20;
	}

	return true;
}

bool SDL_Handler::initFontAndText()
{
	this->gFont = TTF_OpenFont("res/fonttypes/arial.ttf", 15);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	if (this->GAMEobj == NULL)this->loadThisText("-", "-");

	else this->loadThisText(this->GAMEobj->playerTurnString(), this->GAMEobj->getMessage());

	return true;
}

void SDL_Handler::loadThisText(std::string playerTurn, std::string message)
{
	SDL_Color textColor = { 255, 255, 255 };

	SDL_Surface* textSurface = NULL;
	//set player turn
	textSurface = TTF_RenderText_Blended_Wrapped(this->gFont, playerTurn.c_str(), textColor, 160);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		this->mTexture[textObj::PLAYER_TURN] = SDL_CreateTextureFromSurface(this->renderer, textSurface);
		if (this->mTexture[textObj::PLAYER_TURN] == NULL)
		{
			printf("Unable to create texture from rendered text for player turn! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			this->playerTurnW = textSurface->w;
			this->playerTurnH = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	textSurface = NULL;


	//set message
	textSurface = TTF_RenderText_Blended_Wrapped(this->gFont, message.c_str(), textColor, 160);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface for message! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		this->mTexture[textObj::PLAYER_MESSAGE] = SDL_CreateTextureFromSurface(this->renderer, textSurface);
		if (this->mTexture[textObj::PLAYER_MESSAGE] == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			this->messageW = textSurface->w;
			this->messageH = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	textSurface = NULL;
}

SDL_Surface* SDL_Handler::getImage(int numToCompare)
{
	if (numToCompare == pictureobjs::bROOK_ONE || numToCompare == pictureobjs::bROOK_TWO) return IMG_Load("res/high/blackrook.png");
	if (numToCompare == pictureobjs::bKNIGHT_ONE || numToCompare == pictureobjs::bKNIGHT_TWO) return IMG_Load("res/high/blackknight.png");
	if (numToCompare == pictureobjs::bBISHOP_ONE || numToCompare == pictureobjs::bBISHOP_TWO) return IMG_Load("res/high/blackbishop.png");
	if (numToCompare == pictureobjs::bQUEEN) return IMG_Load("res/high/blackqueen.png");
	if (numToCompare == pictureobjs::bKING) return IMG_Load("res/high/blackking.png");

	if (numToCompare == pictureobjs::wROOK_ONE || numToCompare == pictureobjs::wROOK_TWO) return IMG_Load("res/high/whiterook.png");
	if (numToCompare == pictureobjs::wKNIGHT_ONE || numToCompare == pictureobjs::wKNIGHT_TWO) return IMG_Load("res/high/whiteknight.png");
	if (numToCompare == pictureobjs::wBISHOP_ONE || numToCompare == pictureobjs::wBISHOP_TWO) return IMG_Load("res/high/whitebishop.png");
	if (numToCompare == pictureobjs::wQUEEN) return IMG_Load("res/high/whitequeen.png");
	if (numToCompare == pictureobjs::wKING) return IMG_Load("res/high/whiteking.png");
	return NULL;
}

void SDL_Handler::drawHighLightedTile(std::vector<XYpos> vector, SDL_Rect rect, int iVal, int jVal)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		if (vector[i].x == rect.x && vector[i].y == rect.y)
		{
			if (i % 2 == 0)
			{
				SDL_SetRenderDrawColor(this->renderer, 154, 243, 243, 255);
				return;
			}
			else
			{
				SDL_SetRenderDrawColor(this->renderer, 46, 202, 202, 255);
				return;
			}
		}
	}

	//else draw the normal colors
	if ((iVal + jVal) % 2 == 0)
	{//light brown-ish colour
		SDL_SetRenderDrawColor(this->renderer, 210, 180, 140, 255);
		return;
	}
	else 
	{//dark maroon-ish colour
		SDL_SetRenderDrawColor(this->renderer, 165, 42, 42, 255);
		return;
	}
}

void SDL_Handler::upgradePossiblePawnToQueen()
{
	int num = this->currentlySelectedPieceInObjArr;

	SDL_Surface* temp = NULL;

	if (num == pictureobjs::bPAWN_ONE || num == pictureobjs::bPAWN_TWO || num == pictureobjs::bPAWN_THREE ||
		num == pictureobjs::bPAWN_FOUR || num == pictureobjs::bPAWN_FIVE || num == pictureobjs::bPAWN_SIX || 
		num == pictureobjs::bPAWN_SEVEN || num == pictureobjs::bPAWN_EIGHT)
	{

		temp = IMG_Load("res/high/blackqueen.png");

		if (temp == NULL) 
		{
			std::cout << "cannot load the queen for black pawn" << std::endl;
			return;
		}

		//Filling texture with the image using a surface
		if (this->gTexture[num] != NULL)
		{
			SDL_DestroyTexture(this->gTexture[num]);
			this->gTexture[num] = NULL;
			this->gTexture[num] = SDL_CreateTextureFromSurface(this->renderer, temp);
		}

		//Deleting the temporary surface
		if (temp != NULL) 
		{
			SDL_FreeSurface(temp);
			temp = NULL;
		}
	}
	else if (num == pictureobjs::wPAWN_ONE || num == pictureobjs::wPAWN_TWO || num == pictureobjs::wPAWN_THREE ||
		num == pictureobjs::wPAWN_FOUR || num == pictureobjs::wPAWN_FIVE || num == pictureobjs::wPAWN_SIX ||
		num == pictureobjs::wPAWN_SEVEN || num == pictureobjs::wPAWN_EIGHT)
	{

		temp = IMG_Load("res/high/whitequeen.png");

		if (temp == NULL)
		{
			std::cout << "cannot load the queen for white pawn" << std::endl;
			return;
		}

		//Filling texture with the image using a surface
		if (this->gTexture[num] != NULL)
		{
			SDL_DestroyTexture(this->gTexture[num]);
			this->gTexture[num] = NULL;
			this->gTexture[num] = SDL_CreateTextureFromSurface(this->renderer, temp);
		}

		//Deleting the temporary surface
		if (temp != NULL) 
		{
			SDL_FreeSurface(temp);
			temp = NULL;
		}
	}
}

void SDL_Handler::undoQueenUpgrade(previousMove olddata)
{
	SDL_Surface* temp = NULL;
	//check if the piece was not a pawn and was not in co-ords 0 or 7 on the board

	if (olddata.pieceType != 'p')return;

	if (olddata.posInArr == pictureobjs::bPAWN_ONE || olddata.posInArr == pictureobjs::bPAWN_TWO || olddata.posInArr == pictureobjs::bPAWN_THREE ||
		olddata.posInArr == pictureobjs::bPAWN_FOUR || olddata.posInArr == pictureobjs::bPAWN_FIVE || olddata.posInArr == pictureobjs::bPAWN_SIX ||
		olddata.posInArr == pictureobjs::bPAWN_SEVEN || olddata.posInArr == pictureobjs::bPAWN_EIGHT)
	{

		if (olddata.oldY != 100)return;

		temp = IMG_Load("res/high/blackpawn.png");

		if (temp == NULL) 
		{
			std::cout << "cannot load the old black pawn" << std::endl;
			return;
		}

		//Filling texture with the image using a surface
		if (this->gTexture[olddata.posInArr] != NULL) 
		{
			SDL_DestroyTexture(this->gTexture[olddata.posInArr]);
			this->gTexture[olddata.posInArr] = NULL;
			this->gTexture[olddata.posInArr] = SDL_CreateTextureFromSurface(this->renderer, temp);
		}

		//Deleting the temporary surface
		if (temp != NULL)
		{
			SDL_FreeSurface(temp);
			temp = NULL;
		}
	}
	else if (olddata.posInArr == pictureobjs::wPAWN_ONE || olddata.posInArr == pictureobjs::wPAWN_TWO || olddata.posInArr == pictureobjs::wPAWN_THREE ||
		olddata.posInArr == pictureobjs::wPAWN_FOUR || olddata.posInArr == pictureobjs::wPAWN_FIVE || olddata.posInArr == pictureobjs::wPAWN_SIX ||
		olddata.posInArr == pictureobjs::wPAWN_SEVEN || olddata.posInArr == pictureobjs::wPAWN_EIGHT)
	{

		if (olddata.oldY != 500)return;

		temp = IMG_Load("res/high/whitepawn.png");

		if (temp == NULL) 
		{
			std::cout << "cannot load the old white pawn" << std::endl;
			return;
		}

		//Filling texture with the image using a surface
		if (this->gTexture[olddata.posInArr] != NULL)
		{
			SDL_DestroyTexture(this->gTexture[olddata.posInArr]);
			this->gTexture[olddata.posInArr] = NULL;
			this->gTexture[olddata.posInArr] = SDL_CreateTextureFromSurface(this->renderer, temp);
		}

		//Deleting the temporary surface
		if (temp != NULL) 
		{
			SDL_FreeSurface(temp);
			temp = NULL;
		}
	}
}

bool SDL_Handler::restartGame()
{
	if (this->GAMEobj != NULL)
	{
		delete this->GAMEobj;
		this->GAMEobj = NULL;
		this->GAMEobj = new game();
	}
	else return false;
	//realligning black pieces
	//pawns
	for (int i = pictureobjs::bPAWN_ONE; i <= pictureobjs::bPAWN_EIGHT; ++i)
	{
		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::bPAWN_ONE) * 80 + 20;
		this->rect[i].y = 500;
	}
	//exotic pieces
	//loading exotic pieces like king, queen, bishop, knight and rook
	//rook, knight, bishop, queen, king, bishop, knight, rook
	for (int i = pictureobjs::bROOK_ONE; i <= pictureobjs::bROOK_TWO; ++i)
	{
		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::bROOK_ONE) * 80 + 20;
		this->rect[i].y = 580;
	}
	
	//realligning white pieces
	//pawns
	//pawn, pawn, pawn, pawn pawn, pawn, pawn, pawn
	for (int i = pictureobjs::wPAWN_ONE; i <= pictureobjs::wPAWN_EIGHT; ++i)
	{
		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::wPAWN_ONE) * 80 + 20;
		this->rect[i].y = 100;
	}
	//exotic pieces
	//rook, knight, bishop, queen, king, bishop, knight, rook
	for (int i = pictureobjs::wROOK_ONE; i <= pictureobjs::wROOK_TWO; ++i)
	{
		this->rect[i].w = 80;
		this->rect[i].h = 80;

		this->rect[i].x = (i - pictureobjs::wROOK_ONE) * 80 + 20;
		this->rect[i].y = 20;
	}

	if (this->GAMEobj == NULL)
	{
		this->GAMEobj = new game();
	}
	else return false;
	//clearing text up
	this->loadThisText(this->GAMEobj->playerTurnString(), this->GAMEobj->getMessage());

	return true;
}