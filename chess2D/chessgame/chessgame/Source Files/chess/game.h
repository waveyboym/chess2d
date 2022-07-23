/**
 * @file game.h
 * @class game
 * @author Michael
 * @brief aggregrates from board
 */
#ifndef GAME_H
#define GAME_H
#include "board/board.h"

class game
{
    private:

        /**
        * @brief a pointer to a board object
        * 
        */
        board* boardgame;

        /**
        * @brief keeps track of which players turn it is
        * 
        */
        int currentPlayerTurn;

        std::vector<XYpos> vect;

        std::string message;
        
    public:

        /**
        * @brief game constructor initialises the boardgame pointer and starts a new game
        * @param none
        * 
        */
        game();

        /**
        * @brief deletes the boardgame pointer
        * 
        */
        ~game();
  
        /**
        * @brief undoes the most recently completed move
        * @param none
        * 
        * @return previousMove
        */
        previousMove undoPrevMove();

        /**
        * @brief checks that the current player did not attempt to select the other players pieces
        * @param currentX the x co-ord of the selected piece
        * @param currentY the y co-ord of the selected piece
        * 
        * @return bool
        */
        bool correctPlayerPieceSelected(int currentX, int currentY);

        /**
        * @brief chooses a piece located at theses co-ords on the board
        * @param x_co_ord the x co-ord of the selected piece
        * @param y_co_ord the y co-ord of the selected piece
        *
        * @return bool
        */
        bool selectThisPiece(int x_co_ord, int y_co_ord);

        /**
        * @brief returns a vector of open positions
        * @param none
        *
        * @return std::vector<XYpos>
        */
        std::vector<XYpos> getVector();

        /**
        * @brief returns an int mapping on the internal board from the passed in variable
        * @param num the value to convert to internal board mapping
        *
        * @return int
        */
        int getIndexFromBoard(int num);

        /**
        * @brief returns an int mapping on the external board from the passed in variable
        * @param num the value to convert to external board mapping
        *
        * @return int
        */
        int getBoardPosFromIndex(int num);

        /**
        * @brief convert vector data from internal board mapping to external board mapping
        * @param none
        *
        * @return void
        */
        void convertVectDataToBoardPos();

        /**
        * @brief checks if selected co-ords are part of the available positions for a piece to move to
        * @param x x co-ord
        * @param y y co-ord
        *
        * @return bool
        */
        bool checkIfCoordsInVec(int x, int y);

        /**
        * @brief moves a piece to it's new x and y co-ords and returns true if the move was successful else false
        * @param oldX the x co-ord where the piece currently is
        * @param oldY the y co-ord where the piece currently is
        * @param newX the x co-ord to move the piece to
        * @param newY the y co-ord to move the piece to
        * @param posInObjArr the position of the piece in the textures array(stored in case a move is being undone)
        * @param pieceTakenposInObjArr the position of the piece taken out(if any) in the textures array(stored in case a move is being undone)
        *
        * @return bool
        */
        bool movePieceToCoords(int oldX, int oldY, int newX, int newY, int posInObjArr, int pieceTakenposInObjArr);

        /**
        * @brief checks if the king is currently in check, returns true and ends the game if true else false
        * @param none
        *
        * @return bool
        */
        bool kingInCheck();

        /**
        * @brief checks if there are any recently completed moves available. return true if true else false
        * @param none
        *
        * @return bool
        */
        bool emptyStack();

        /**
        * @brief returns a string containing a message regarding the recently completed events
        * @param none
        *
        * @return std::string
        */
        std::string getMessage();

        /**
        * @brief returns a string which says which players turn it is
        * @param none
        *
        * @return std::string
        */
        std::string playerTurnString();

        /**
        * @brief clears the vector object which stores open positions for the currently selceted piece
        * @param none
        *
        * @return void
        */
        void clearoutVector();
};

#endif