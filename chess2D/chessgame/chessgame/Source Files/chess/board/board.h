/**
 * @file board.h
 * @class board
 * @author Michael
 * @brief aggregrates from piece and stack
 */
#ifndef BOARD_H
#define BOARD_H
#include "../gamepieces/pieces/piece.h"
#include "stack.h"

class board
{
    private:

        /**
        * @brief a 2d dynamic array of piece objects
        * 
        */
        piece*** board2D;

        /**
        * @brief a stack which holds detail about the most recently completed move at the top
        * 
        */
        stack* stackADT;

        /**
        * @brief the row sizes and column sizes of the board
        * 
        */
        const static int ROWSIZE = 8, COLSIZE = 8;

        /**
        * @brief places all 32 chess pieces on the board in their correct positions
        * @param none
        * 
        * @return void
        */
        void initialiseBoard();

        /**
        * @brief is used as a flag for indicating if the king is in a posiible check
        * 
        */
        bool whiteKingInCheck, blackKingInCheck;
    public:

        /**
        * @brief board constructor, creates an 8x8 board and sets up all the pieces on the board
        * 
        * @param none
        * 
        */
        board();

        /**
        * @brief board deconstructor, deallocates the memory used by the board,
        *  the output array and the static arrays in piece.cpp
        * 
        * 
        */
        ~board();

        /**
        * @brief returns a pointer to the entire 2d board array
        * 
        * @param none
        * 
        * @return piece***
        */
        piece*** getBoard();

        /**
        * @brief attempts to find open spots on the board to move the piece 
        * that is currently located on the co-ords passed in as the parameters,
        *  then places these open spots in a linked list for later usage
        * 
        * @param currentX the x-cord of the piece on the board
        * @param currentY the y-cord of the piece on the board
        * 
        * @return std::vector<XYpos>
        */
        std::vector<XYpos> findOpenSpots(int currentX, int currentY);

        /**
        * @brief gets the piece type, whether it may be a king, queen, bishop, knight, rook or pawn
        * and returns a char like 'K','q','B','k,'r' or 'p' respectively
        * 
        * @param currentX the x-cord of the piece on the board
        * @param currentY the y-cord of the piece on the board
        * 
        * @return char
        */
        char getPieceTypeBoard(int currentX, int currentY);

        /**
        * @brief gets the team colour of the piece on the board whether it may be 'b' for black or 'w' for white
        * 
        * @param currentX the x-cord of the piece on the board
        * @param currentY the y-cord of the piece on the board
        * 
        * @return char
        */
        char getTeamColourBoard(int currentX, int currentY);

        /**
        * @brief checks if the king is still in check, returns true if it is
        * 
        * @param teamcolor the team color to check for
        * 
        * @return bool
        */
        bool isKingStillInCheck(char teamcolor);

        /**
        * @brief changes the position of the piece on the board to the new co-ords
        * 
        * @param oldX the x-cord of the piece on the board
        * @param oldY the y-cord of the piece on the board
        * @param newX the new x-cord to move the piece to
        * @param newY the new y-cord to move the piece to
        * @param posInObjArr the position of the piece in the texture and rect array
        * @param pieceTakenposInObjArr the position of the piece taken in the texture and rect array
        * 
        * @return std::string
        */
        std::string changePosition(int oldX, int oldY, int newX, int newY, int posInObjArr, int pieceTakenposInObjArr);

        /**
        * @brief upgrades the pawn to a queen on the board
        * 
        * @param currentX the x-cord of the piece on the board
        * @param currentY the y-cord of the piece on the board
        * @param teamcolor the team color of the piece on the board
        * 
        * @return void
        */
        void upgradePawnToQueen(int currentX, int currentY, char teamcolor);

        /**
        * @brief undoes a pawn to queen upgrade if one did happen
        *
        * @param olddata a struct containing information abput the most recently completed move
        *
        * @return void
        */
        void undoPawnToQueenUpgrade(previousMove olddata);

        /**
        * @brief checks if the king is in check, returns true if it is
        * 
        * @param teamcolor the team color to check for
        * 
        * @return bool
        */
        bool isKingInCheck(char teamcolor);

        /**
        * @brief undoes the previously/most recently completed move and returns false if the operation failed and true if it worked
        * 
        * @param none
        * 
        * @return previousMove
        */
        previousMove undoPreviousMove();

        /**
        * @brief checks if the undo move stack has any data
        *
        * @param none
        *
        * @return bool
        */
        bool anyPrevMovesAvailable();

        /**
        * @brief checks if the game is over for the current team, so if the game is over and teamcolor is 'w', then the white team has lost
        *
        * @param teamcolor
        *
        * @return bool
        */
        bool gameOver(char teamcolor);

};

#endif