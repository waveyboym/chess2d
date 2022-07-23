#include "game.h"

/**
* @brief validates that the entered x and y co-ords are indeed on the board and that they don't refer to a null spot on the board
* @param x x co-ord to verify   if in array bounds and is not a null spot in array
* @param y y co-ord to verify if in array bounds and is not a null spot in array
* @param board2d the game board for checking if x and y co-ord don't refer to a null spot on the board
* 
* @return bool
*/
bool checkValidity(int x, int y, piece*** board2d)
{
    if(x < 0 || x >= 8)return false;
    if(y < 0 || y >= 8)return false;
    if(board2d[y][x] == NULL)return false;
    return true;
}

int playersnum(int num)
{
    if(num == 1)return 2;
    else return 1;
}

char playercolor(int num)
{
    if(num == 1)return 'b';
    else return 'w';
}

game::game() { this->currentPlayerTurn = 1; this->boardgame = new board(); this->message = "pick a piece to start the game"; }

game::~game(){delete this->boardgame;}

previousMove game::undoPrevMove()
{
    previousMove olddata = this->boardgame->undoPreviousMove();
    olddata.newX = this->getBoardPosFromIndex(olddata.newX);
    olddata.newY = this->getBoardPosFromIndex(olddata.newY);
    olddata.oldX = this->getBoardPosFromIndex(olddata.oldX);
    olddata.oldY = this->getBoardPosFromIndex(olddata.oldY);
    this->currentPlayerTurn = playersnum(this->currentPlayerTurn);

    return olddata;
}

bool game::correctPlayerPieceSelected(int currentX, int currentY)
{
    //its player ones turn but selected white piece
    if(this->currentPlayerTurn == 1 && this->boardgame->getTeamColourBoard(currentX, currentY) == 'w')
    {
        this->message = "you tried to select player 2's white pieces";
        return false;
    }
    //its player twos turn but selected black piece
    if(this->currentPlayerTurn == 2 && this->boardgame->getTeamColourBoard(currentX, currentY) == 'b')
    {
        this->message = "you tried to select player 1's black pieces";
        return false;
    }
    return true;
}

bool game::selectThisPiece(int x_co_ord, int y_co_ord)
{
    this->vect.clear();
    int x = this->getIndexFromBoard(x_co_ord);
    int y = this->getIndexFromBoard(y_co_ord);

    if (checkValidity(x, y, this->boardgame->getBoard())) 
    {
        if (this->correctPlayerPieceSelected(x, y)) 
        {
            this->vect = this->boardgame->findOpenSpots(x, y);
            this->convertVectDataToBoardPos();
            return true;
        }
    }
    else 
    {
        this->message = "you cannot select this position, it is invalid";
    }

    return false;
}

std::vector<XYpos> game::getVector(){return this->vect;}

int game::getIndexFromBoard(int num)
{
    if (num == 20)return 0;
    else if (num == 100)return 1;
    else if (num == 180)return 2;
    else if (num == 260)return 3;
    else if (num == 340)return 4;
    else if (num == 420)return 5;
    else if (num == 500)return 6;
    else if (num == 580)return 7;
    else return -1;
    return 0;
}

int game::getBoardPosFromIndex(int num)
{
    if (num == 0)return 20;
    else if (num == 1)return 100;
    else if (num == 2)return 180;
    else if (num == 3)return 260;
    else if (num == 4)return 340;
    else if (num == 5)return 420;
    else if (num == 6)return 500;
    else if (num == 7)return 580;
    else return -1;
}

void game::convertVectDataToBoardPos()
{
    std::vector<XYpos> temp;

    for (int i = 0; i < this->vect.size(); ++i) 
    {
        XYpos obj;
        obj.x = getBoardPosFromIndex(this->vect[i].x);
        obj.y = getBoardPosFromIndex(this->vect[i].y);
        temp.push_back(obj);
    }
    this->vect = temp;
}

bool game::checkIfCoordsInVec(int x, int y)
{
    for (int i = 0; i < this->vect.size(); ++i) 
    {
        if (this->vect[i].x == x && this->vect[i].y == y)return true;
    }
    return false;
}

bool game::movePieceToCoords(int oldX, int oldY, int newX, int newY, int posInObjArr, int pieceTakenposInObjArr)
{
    this->vect.clear();
    int OLDx = this->getIndexFromBoard(oldX);
    int OLDy = this->getIndexFromBoard(oldY);

    int NEWx = this->getIndexFromBoard(newX);
    int NEWy = this->getIndexFromBoard(newY);

    this->message = this->boardgame->changePosition(OLDx, OLDy, NEWx, NEWy, posInObjArr, pieceTakenposInObjArr);

    if (this->boardgame->isKingInCheck(playercolor(this->currentPlayerTurn))
        || this->boardgame->isKingStillInCheck(playercolor(this->currentPlayerTurn))) 
    {
        this->message = "you cannot play that move when your king is in risk of being checked";
        this->boardgame->undoPreviousMove();
        return false;
    }

    if ((NEWy == 0 || NEWy == 7) && this->boardgame->getPieceTypeBoard(NEWx, NEWy) == 'p') 
    {
        this->boardgame->upgradePawnToQueen(NEWx, NEWy, this->boardgame->getTeamColourBoard(NEWx, NEWy));
        this->message += " pawn upgraded to queen";
    }


    if (this->currentPlayerTurn == 1) { this->currentPlayerTurn = 2; }
    else if (this->currentPlayerTurn == 2) { this->currentPlayerTurn = 1; }

    return true;
}

bool game::kingInCheck()
{
    //check if the now players turn is in check with no possible way of getting out
    //end the game if true else continue;
    if (this->boardgame->gameOver(playercolor(this->currentPlayerTurn))) 
    {
        //game is over
        this->message = "[Player " + std::to_string(playersnum(this->currentPlayerTurn)) + "]: has won the game.press r to restart or close the window to end the game";
        return true;
    }
    else return false;
}

bool game::emptyStack()
{
    if (this->boardgame->anyPrevMovesAvailable())return false;
    else return true;
}

std::string game::getMessage()
{
    return this->message;
}

std::string game::playerTurnString()
{
    return "Player " + std::to_string(this->currentPlayerTurn) + "'s turn";
}

void game::clearoutVector()
{
    this->vect.clear();
}