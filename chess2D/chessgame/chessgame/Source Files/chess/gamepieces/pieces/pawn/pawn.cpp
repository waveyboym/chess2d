#include "pawn.h"

bool pawn::can_pawn_check_king(int currentX, int currentY, char teamcolor, piece*** currentboard)
{
    /*****CHECKING PAWN****/
    if(teamcolor == 'w')
    {//check black pieces on opposing team
        //check right diagonal
        if(piece::checkIfValid(currentX + 1, currentY + 1, currentboard)
        && currentboard[currentY + 1][currentX + 1]->getTeamColour() != teamcolor) 
        {
            piece::posVect.push_back(currentX + 1);
            piece::posVect.push_back(currentY + 1);
            return true;
        }
        //check left diagonal
        if(piece::checkIfValid(currentX - 1, currentY + 1, currentboard)
        && currentboard[currentY + 1][currentX - 1]->getTeamColour() != teamcolor) 
        {
            piece::posVect.push_back(currentX - 1);
            piece::posVect.push_back(currentY + 1);
            return true;
        }
    }
    else if(teamcolor == 'b')
    {//check white pieces on opposing team
        //check right diagonal
        if(piece::checkIfValid(currentX + 1, currentY - 1, currentboard)
        && currentboard[currentY - 1][currentX + 1]->getTeamColour() != teamcolor) 
        {
            piece::posVect.push_back(currentX + 1);
            piece::posVect.push_back(currentY - 1);
            return true;
        }
        //check left diagonal
        if(piece::checkIfValid(currentX - 1, currentY - 1, currentboard)
        && currentboard[currentY - 1][currentX - 1]->getTeamColour() != teamcolor) 
        {
            piece::posVect.push_back(currentX - 1);
            piece::posVect.push_back(currentY - 1);
            return true;
        }
    }

    //all tests failed so no pawn can check the king in this position
    return false;
}

pawn::pawn(int newX, int newY, char teamcolour, char piecetype)
    : piece(teamcolour, piecetype)
{
    this->x_pos = newX;
    this->y_pos = newY;
}

void pawn::changeX_and_Y_Pos(int newX, int newY)
{
    this->x_pos = newX;
    this->y_pos = newY;
}

void pawn::checkOpenSpots(piece*** currentboard)
{

    if(this->teamColor == 'w')
    {
        //check one position ahead
        if(checkValidity(this->x_pos, this->y_pos + 1) && currentboard[this->y_pos + 1][this->x_pos] == NULL)
        {
            XYcoords newCoords = {this->x_pos, this->y_pos + 1};
            this->mylist->push_back(newCoords);

            //check two positions ahead
            if(checkValidity(this->x_pos, this->y_pos + 2) && this->y_pos + 2 <= 3
                && currentboard[this->y_pos + 2][this->x_pos] == NULL)
            {
                    XYcoords newCoords = {this->x_pos, this->y_pos + 2};
                    this->mylist->push_back(newCoords);
            }
        }
        //check right diagonal
        if(checkValidity(this->x_pos + 1, this->y_pos + 1) && (currentboard[this->y_pos + 1][this->x_pos + 1] != NULL
         && currentboard[this->y_pos + 1][this->x_pos + 1]->getTeamColour() == 'b'))
        {
            XYcoords newCoords = {this->x_pos + 1, this->y_pos + 1};
            this->mylist->push_back(newCoords);
        }
        //check left diagonal
        if(checkValidity(this->x_pos - 1, this->y_pos + 1) && (currentboard[this->y_pos + 1][this->x_pos - 1] != NULL
         && currentboard[this->y_pos + 1][this->x_pos - 1]->getTeamColour() == 'b'))
        {
            XYcoords newCoords = {this->x_pos - 1, this->y_pos + 1};
            this->mylist->push_back(newCoords);
        }
    }
    else if(this->teamColor == 'b')
    {
        //check one position ahead
        if(checkValidity(this->x_pos, this->y_pos - 1) && currentboard[this->y_pos - 1][this->x_pos] == NULL)
        {
            XYcoords newCoords = {this->x_pos, this->y_pos - 1};
            this->mylist->push_back(newCoords);

            //check two positions ahead
            if(checkValidity(this->x_pos, this->y_pos - 2) && this->y_pos - 2 >= 4
            && currentboard[this->y_pos - 2][this->x_pos] == NULL)
            {
                XYcoords newCoords = {this->x_pos, this->y_pos - 2};
                this->mylist->push_back(newCoords);
            }
        }
        
        //check right diagonal
        if(checkValidity(this->x_pos + 1, this->y_pos - 1) && (currentboard[this->y_pos - 1][this->x_pos + 1] != NULL
         && currentboard[this->y_pos - 1][this->x_pos + 1]->getTeamColour() == 'w'))
        {
            XYcoords newCoords = {this->x_pos + 1, this->y_pos - 1};
            this->mylist->push_back(newCoords);
        }
        //check left diagonal
        if(checkValidity(this->x_pos - 1, this->y_pos - 1) && (currentboard[this->y_pos - 1][this->x_pos - 1] != NULL
         && currentboard[this->y_pos - 1][this->x_pos - 1]->getTeamColour() == 'w'))
        {
            XYcoords newCoords = {this->x_pos - 1, this->y_pos - 1};
            this->mylist->push_back(newCoords);
        }
    }
}