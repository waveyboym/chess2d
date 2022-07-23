/**
 * @file bishop.h
 * @class bishop
 * @author Michael
 * @brief inherits from piece
 */
#ifndef BISHOP_H
#define BISHOP_H
#include "../piece.h"

class bishop : public piece
{
    private:

        /**
        * @brief the x co-ord of this king
        * 
        */
        int x_pos;

        /**
        * @brief the y co-ord of this king
        * 
        */
        int y_pos;
    public:

        /**
        * @brief the bishop constructor intialises the various member variables
        * 
        * @param newX the x co-ord to set the x co-ord member variable
        * @param newY the y co-ord to set the y co-ord member variable
        * @param teamcolor the team color of a piece whether it may be 'b' for black or 'w' for white
        * @param piecetype the piece type of a piece
        * 
        */
        bishop(int newX, int newY, char teamcolour, char piecetype);
        
        /**
        * @brief changes the x and y co-ord member variables to the passed in arguments
        * 
        * @param newX the new x co-ord to change to
        * @param newX the new y co-ord to change to
        * 
        * @return void
        */
        void changeX_and_Y_Pos(int newX, int newY);

        /**
        * @brief attempts to find spots this piece may move to depending on the piecetype and it's allowed moves
        * 
        * @param currentboard a pointer to the 2d board array of piece objects
        * 
        * @return void
        */
        void checkOpenSpots(piece*** currentboard);

        //static functions
        /**
        * @brief checks if a bishop can check the king on the board if the king moved to passed in x and y co-ords
        * 
        * @param x the x co-ord to check
        * @param y the y co-ord to check
        * @param teamcolor the team color of the piece calling this function whether 'b' for black or 'w' for white
        * @param currentboard a pointer to the 2d board array of piece objects
        *
        * 
        * @return bool
        */
        static bool can_bishop_check_king(int currentX, int currentY, char teamcolor, piece*** currentboard);
};

#endif