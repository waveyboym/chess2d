#include "board.h"
#include "../gamepieces/pieces/pawn/pawn.h"
#include "../gamepieces/pieces/rook/rook.h"
#include "../gamepieces/pieces/knight/knight.h"
#include "../gamepieces/pieces/bishop/bishop.h"
#include "../gamepieces/pieces/queen/queen.h"
#include "../gamepieces/pieces/king/king.h"

/**
* @brief returns a string of a piece depending on the piecetype passed in. 
*The piecetype may be 'K','q','B','k,'r' or 'p'
*and returns a string like king, queen, bishop, knight, rook or pawn respectively
* @param piecetype piecetype of a piece on the board
* @return std::string
*/
std::string determinePieceName(char piecetype)
{
    if(piecetype == 'p')return "pawn";
    else if(piecetype == 'r') return "rook";
    else if(piecetype == 'k')   return "knight";
    else if(piecetype == 'B') return "bishop";
    else if(piecetype == 'q') return "queen";
    else return "king";//'K'
}

std::string determineTeamColor(char teamcolor)
{
    if(teamcolor == 'b')return "black";
    else return "white";
}

struct tempKingCoordsStore
{
    int y;
    int x;
};

tempKingCoordsStore getKingXY_Co_Ord(piece*** chessboard, char teamcolor)
{
    tempKingCoordsStore coords = {-1, -1};
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            if(chessboard[i][j] != NULL)
            {
                if(chessboard[i][j]->getPieceType()== 'K' && chessboard[i][j]->getTeamColour() == teamcolor)
                {
                    coords.x = j;
                    coords.y = i;
                    return coords;
                }
            }
        }
    }
    return coords;
}

board::board()
{
    this->board2D = new piece**[this->ROWSIZE];
    for(int i = 0; i < this->ROWSIZE; ++i)
    {
        this->board2D[i] = new piece*[this->COLSIZE];
        for(int j = 0; j < this->COLSIZE; ++j)
        {
            this->board2D[i][j] = NULL;
        }
    }
    this->initialiseBoard();
    this->stackADT = new stack();
    this->blackKingInCheck = false;
    this->whiteKingInCheck = false;
}

board::~board()
{
    if(this->board2D == NULL)return;
    for(int i = 0; i < this->ROWSIZE; ++i)
    {
        for(int j = 0; j < this->COLSIZE; ++j)
        {
            if(this->board2D[i][j] != NULL) delete this->board2D[i][j];
        }
        if(this->board2D[i] != NULL) delete[] this->board2D[i];
    }
    delete [] this->board2D;
    this->board2D = NULL;

    this->stackADT->~stack();
}

void board::initialiseBoard()
{
    //BLACK PIECES

    //pawn
    this->board2D[6][0] = new pawn(0, 6, 'b', 'p');
    this->board2D[6][1] = new pawn(1, 6, 'b', 'p');
    this->board2D[6][2] = new pawn(2, 6, 'b', 'p');
    this->board2D[6][3] = new pawn(3, 6, 'b', 'p');
    this->board2D[6][4] = new pawn(4, 6, 'b', 'p');
    this->board2D[6][5] = new pawn(5, 6, 'b', 'p');
    this->board2D[6][6] = new pawn(6, 6, 'b', 'p');
    this->board2D[6][7] = new pawn(7, 6, 'b', 'p');

    //rook
    this->board2D[7][0] = new rook(0, 7, 'b', 'r');
    this->board2D[7][7] = new rook(7, 7, 'b', 'r');

    //knight
    this->board2D[7][1] = new knight(1, 7, 'b', 'k');
    this->board2D[7][6] = new knight(6, 7, 'b', 'k');

    //bishop
    this->board2D[7][2] = new bishop(2, 7, 'b', 'B');
    this->board2D[7][5] = new bishop(5, 7, 'b', 'B');

    //queen
    this->board2D[7][3] = new queen(3, 7, 'b', 'q');

    //king
    this->board2D[7][4] = new king(4, 7, 'b', 'K');



    //WHITE PIECES

    //pawn
    this->board2D[1][0] = new pawn(0, 1, 'w', 'p');
    this->board2D[1][1] = new pawn(1, 1, 'w', 'p');
    this->board2D[1][2] = new pawn(2, 1, 'w', 'p');
    this->board2D[1][3] = new pawn(3, 1, 'w', 'p');
    this->board2D[1][4] = new pawn(4, 1, 'w', 'p');
    this->board2D[1][5] = new pawn(5, 1, 'w', 'p');
    this->board2D[1][6] = new pawn(6, 1, 'w', 'p');
    this->board2D[1][7] = new pawn(7, 1, 'w', 'p');
    //rook
    this->board2D[0][0] = new rook(0, 0, 'w', 'r');
    this->board2D[0][7] = new rook(7, 0, 'w', 'r');

    //knight
    this->board2D[0][1] = new knight(1, 0, 'w', 'k');
    this->board2D[0][6] = new knight(6, 0, 'w', 'k');

    //bishop
    this->board2D[0][2] = new bishop(2, 0, 'w', 'B');
    this->board2D[0][5] = new bishop(5, 0, 'w', 'B');

    //queen
    this->board2D[0][4] = new queen(4, 0, 'w', 'q');

    //king
    this->board2D[0][3] = new king(3, 0, 'w', 'K');
}

std::string board::changePosition(int oldX, int oldY, int newX, int newY, int posInObjArr, int pieceTakenposInObjArr)
{
    previousMove newdata;
    newdata.oldX = oldX;
    newdata.oldY = oldY;
    newdata.newX = newX;
    newdata.newY = newY;
    newdata.posInArr = posInObjArr;
    newdata.takenPiecePosInArr = pieceTakenposInObjArr;
    newdata.pieceCol = this->board2D[oldY][oldX]->getTeamColour();
    newdata.pieceType = this->board2D[oldY][oldX]->getPieceType();
    newdata.pieceTakenCol = 'e';
    newdata.pieceTakenType = 'e';
    newdata.tookOutPiece = false;


    std::string message = "-";


    if(this->board2D[newY][newX] != NULL)
    {
        message = "eliminated: " + determineTeamColor(this->board2D[newY][newX]->getTeamColour()) + " " + determinePieceName(this->board2D[newY][newX]->getPieceType());
        newdata.pieceTakenCol = this->board2D[newY][newX]->getTeamColour();
        newdata.pieceTakenType = this->board2D[newY][newX]->getPieceType();
        newdata.tookOutPiece = true;
        delete this->board2D[newY][newX];
    }

    this->board2D[newY][newX] = this->board2D[oldY][oldX];
    this->board2D[newY][newX]->changeX_and_Y_Pos(newX, newY);
    this->board2D[oldY][oldX] = NULL;
    this->stackADT->push(newdata);

    return message;
}

void board::upgradePawnToQueen(int currentX, int currentY, char teamcolor)
{
    if(teamcolor == 'b' && currentY == 0)
    {
        std::cout << "upgrading black pawn to queen" << std::endl;
        delete this->board2D[currentY][currentX];
        this->board2D[currentY][currentX] = new queen(currentX, currentY, 'b', 'q');
    }
    else if(teamcolor == 'w' && currentY == 7)
    {
        std::cout << "upgrading white pawn to queen" << std::endl;
        delete this->board2D[currentY][currentX];
        this->board2D[currentY][currentX] = new queen(currentX, currentY, 'w', 'q');
    }
}

void board::undoPawnToQueenUpgrade(previousMove olddata)
{
    if (olddata.pieceType != 'p')
        return;

    if (olddata.pieceCol == 'b' && olddata.oldY == 1)
    {

        delete this->board2D[olddata.oldY][olddata.oldX];
        this->board2D[olddata.oldY][olddata.oldX] = new pawn(olddata.oldX, olddata.oldY, 'b', 'p');
    }
    else if (olddata.pieceCol == 'w' && olddata.oldY == 6) 
    {

        delete this->board2D[olddata.oldY][olddata.oldX];
        this->board2D[olddata.oldY][olddata.oldX] = new pawn(olddata.oldX, olddata.oldY, 'w', 'p');
    }
}

bool board::isKingInCheck(char teamcolor)
{
    tempKingCoordsStore XY = getKingXY_Co_Ord(this->board2D, teamcolor);

    if(XY.x == -1 || XY.y == -1)return true;

    if(!king::can_CheckKing(XY.x, XY.y, teamcolor, this->board2D))
    {
        if(teamcolor == 'b')this->blackKingInCheck = false;
        else if(teamcolor == 'w')this->whiteKingInCheck = false;

        return false;
    }
    if(king::can_move_out_of_check(XY.x, XY.y, teamcolor, this->board2D))
    {

        if(teamcolor == 'b')this->blackKingInCheck = true;
        else if(teamcolor == 'w')this->whiteKingInCheck = true;

        return false;
    }
    return true;
}

bool board::isKingStillInCheck(char teamcolor)
{
    if(teamcolor == 'b')return this->blackKingInCheck;
    else return this->whiteKingInCheck;
}

previousMove board::undoPreviousMove()
{

    previousMove oldData = this->stackADT->pop();
    this->board2D[oldData.oldY][oldData.oldX] = this->board2D[oldData.newY][oldData.newX];
    this->board2D[oldData.oldY][oldData.oldX]->changeX_and_Y_Pos(oldData.oldX, oldData.oldY);

    if(oldData.tookOutPiece == true)
    {
        if(oldData.pieceTakenType == 'p')
        {
            this->board2D[oldData.newY][oldData.newX] = new pawn(oldData.newX, oldData.newY, oldData.pieceTakenCol, 'p');
        }
        else if(oldData.pieceTakenType == 'r')
        {
            this->board2D[oldData.newY][oldData.newX] = new rook(oldData.newX, oldData.newY, oldData.pieceTakenCol, 'r');
        }
        else if(oldData.pieceTakenType == 'k')
        {
            this->board2D[oldData.newY][oldData.newX] = new knight(oldData.newX, oldData.newY, oldData.pieceTakenCol, 'k');
        }
        else if(oldData.pieceTakenType == 'B')
        {
            this->board2D[oldData.newY][oldData.newX] = new bishop(oldData.newX, oldData.newY, oldData.pieceTakenCol, 'B');
        }
        else if(oldData.pieceTakenType == 'q')
        {
            this->board2D[oldData.newY][oldData.newX] = new queen(oldData.newX, oldData.newY, oldData.pieceTakenCol, 'q');
        }
        else if(oldData.pieceTakenType == 'K')
        {
            this->board2D[oldData.newY][oldData.newX] = new king(oldData.newX, oldData.newY, oldData.pieceTakenCol, 'K');
        }
    }
    else this->board2D[oldData.newY][oldData.newX] = NULL;

    this->undoPawnToQueenUpgrade(oldData);

    return oldData;
}

bool board::anyPrevMovesAvailable()
{
    if (this->stackADT->empty())return false;
    else return true;
}

bool board::gameOver(char teamcolor)
{
    tempKingCoordsStore XY = getKingXY_Co_Ord(this->board2D, teamcolor);
    if (XY.x == -1 || XY.y == -1)return true;

    piece::posVect.clear();
    if (!king::can_CheckKing(XY.x, XY.y, teamcolor, this->board2D))return false;
    
    if (king::can_piece_save_king(teamcolor, this->board2D))
    {
        
        piece::posVect.clear();
        return false;
    }

    if (king::can_move_out_of_check(XY.x, XY.y, teamcolor, this->board2D))
    {

        piece::posVect.clear();
        return false;
    }

    piece::posVect.clear();
    return true;
}

piece*** board::getBoard(){ return this->board2D;}

std::vector<XYpos> board::findOpenSpots(int currentX, int currentY)
{
    this->board2D[currentY][currentX]->checkOpenSpots(this->board2D);
    return this->board2D[currentY][currentX]->getOpenPositionsVec();
}

char board::getPieceTypeBoard(int currentX, int currentY){return this->board2D[currentY][currentX]->getPieceType();}

char board::getTeamColourBoard(int currentX, int currentY){return this->board2D[currentY][currentX]->getTeamColour();}