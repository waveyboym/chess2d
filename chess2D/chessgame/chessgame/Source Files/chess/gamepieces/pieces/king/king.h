/**
 * @file king.h
 * @class king
 * @author Michael
 * @brief inherits from piece
 */
#ifndef KING_H
#define KING_H
#include "../piece.h"

class king : public piece
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
        * @brief the king constructor intialises the various member variables
        * 
        * @param newX the x co-ord to set the x co-ord member variable
        * @param newY the y co-ord to set the y co-ord member variable
        * @param teamcolor the team color of a piece whether it may be 'b' for black or 'w' for white
        * @param piecetype the piece type of a piece
        * 
        */
        king(int newX, int newY, char teamcolour, char piecetype);

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

        //static function
        /**
        * @brief checks if no pieces from the opposite team can check the king if the king moves to the proposed x and y co-ords
        * 
        * @param currentX the x co-ord to validate
        * @param currentY the y co-ord to validate
        * @param teamcolor the team color of the king piece which called this function
        * @param currentboard a pointer to the current 2d board of piece objects
        * 
        * @return bool
        */
        static bool can_CheckKing(int currentX, int currentY, char teamcolor, piece*** currentboard);

        //static function
        /**
        * @brief checks if the king can move out of check
        * 
        * @param currentX the x co-ord to validate
        * @param currentY the y co-ord to validate
        * @param teamcolor the team color of the king piece which called this function
        * @param currentboard a pointer to the current 2d board of piece objects
        * 
        * @return bool
        */
        static bool can_move_out_of_check(int currentX, int currentY, char teamcolor, piece*** currentboard);

        //static function
        /**
        * @brief checks if any piece save the king from being checked can move out of check
        *
        * @param teamcolor the team color of the king piece which called this function
        * @param currentboard a pointer to the current 2d board of piece objects
        *
        * @return bool
        */
        static bool can_piece_save_king(char teamcolor, piece*** currentboard);
};

#endif