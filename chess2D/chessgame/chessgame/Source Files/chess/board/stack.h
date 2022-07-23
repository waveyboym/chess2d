/**
 * @file stack.h
 * @class stack
 * @author Michael
 * @brief stores a stack of most recently completed moves
 */
#ifndef STACK_H
#define STACK_H

struct previousMove
{
    int newX;
    int newY;
    int oldX;
    int oldY;
    int posInArr;
    int takenPiecePosInArr;
    bool tookOutPiece;
    char pieceType;
    char pieceCol;
    char pieceTakenType;
    char pieceTakenCol;
    previousMove* below;
};

class stack
{
    private:
        /**
        * @brief the node at the top of the stack
        * 
        */
        previousMove* topStack;
    public:

        /**
        * @brief the stack constructor intialises topStack to null
        * 
        * @param none
        * 
        */
        stack();

        /**
        * @brief the stack destructor destroys the stack from memory
        *
        * 
        */
        ~stack();

        /**
        * @brief pushes the mot recently completed move onto the stack
        * 
        * @param newX the new x co-ord to change to
        * @param newX the new y co-ord to change to
        * @param oldX the new x co-ord to change to
        * @param oldY the new y co-ord to change to
        * @param tookPiece the new x co-ord to change to
        * @param piecetype the new y co-ord to change to
        * @param teamcolor the team color of the piece that was captured
        * @param posInArr the position of the piece in the texture and rect array
        * @param takenPiecePosInArr the position of the piece taken in the texture and rect array
        * 
        * @return void
        */
        void push(int newX, int newY, int oldX, int oldY, int posInArr, int takenPiecePosInArr, bool tookPiece, char piecetype, char teamcolor, char takenpiecetype, char takenpicecol);

        /**
        * @brief pushes the mot recently completed move onto the stack
        * 
        * @param structData a struct containing data about the most recently completed move
        * 
        * @return void
        */
        void push(previousMove structData);

        /**
        * @brief returns a struct containing data about the most recently completed move
        * 
        * @param none
        * 
        * @return void
        */
        previousMove pop();

        /**
        * @brief removes all nodes in the stack data structure
        * 
        * @param none
        * 
        * @return void
        */
        void clearStack();

        /**
        * @brief checks if stack is empty and returns true if it is else false
        *
        * @param none
        *
        * @return bool
        */
        bool empty();
};

#endif