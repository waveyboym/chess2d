#include "bishop.h"

bool bishop::can_bishop_check_king(int currentX, int currentY, char teamcolor, piece*** currentboard)
{
    /*****BISHOP****/
    //top-left diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(piece::checkIfValid(currentX - i, currentY - i, currentboard))
        {
            if(currentboard[currentY - i][currentX - i]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY - i][currentX - i]->getTeamColour() != teamcolor)
            {
                if (currentboard[currentY - i][currentX - i]->getPieceType() == 'B')
                {
                    piece::posVect.push_back(currentX - i);
                    piece::posVect.push_back(currentY - i);
                    return true;
                }
                else break;
            }
        }
    }
    
    //top-right diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(piece::checkIfValid(currentX + i, currentY - i, currentboard))
        {
            if(currentboard[currentY - i][currentX + i]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY - i][currentX + i]->getTeamColour() != teamcolor)
            {
                if(currentboard[currentY - i][currentX + i]->getPieceType() == 'B') 
                {
                    piece::posVect.push_back(currentX + i);
                    piece::posVect.push_back(currentY - i);
                    return true;
                }
                else break;
            }
        }
    }

    //bottom-left diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(piece::checkIfValid(currentX - i, currentY + i, currentboard))
        {
            if(currentboard[currentY + i][currentX - i]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY + i][currentX - i]->getTeamColour() != teamcolor)
            {
                if(currentboard[currentY + i][currentX - i]->getPieceType() == 'B') 
                {
                    piece::posVect.push_back(currentX - i);
                    piece::posVect.push_back(currentY + i);
                    return true;
                }
                else break;
            }
        }
    }

    //bottom-right diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(piece::checkIfValid(currentX + i, currentY + i, currentboard))
        {
            if(currentboard[currentY + i][currentX + i]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY + i][currentX + i]->getTeamColour() != teamcolor)
            {
                if(currentboard[currentY + i][currentX + i]->getPieceType() == 'B')
                {
                    piece::posVect.push_back(currentX + i);
                    piece::posVect.push_back(currentY + i);
                    return true;
                }
                else break;
            }
        }
    }

    //all test cases failed thus king cannot be check by a bishop
    return false;
}

bishop::bishop(int newX, int newY, char teamcolour, char piecetype)
    : piece(teamcolour, piecetype)
{
    this->x_pos = newX;
    this->y_pos = newY;
}

void bishop::changeX_and_Y_Pos(int newX, int newY)
{
    this->x_pos = newX;
    this->y_pos = newY;
}

void bishop::checkOpenSpots(piece*** currentboard)
{
    bool nofurthersearch = false;
    char currentTeamColour = this->getTeamColour();
    //top-left diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos - i, this->y_pos - i, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos - i, this->y_pos - i, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos - i, this->y_pos - i};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blocking
    }
    nofurthersearch = false;
    //top-right diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos + i, this->y_pos - i, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos + i, this->y_pos - i, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos + i, this->y_pos - i};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blocking
    }
    nofurthersearch = false;
    //bottom-left diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos - i, this->y_pos + i, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos - i, this->y_pos + i, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos - i, this->y_pos + i};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blocking
    }
    nofurthersearch = false;
    //bottom-right diagonal
    for(int i = 1 ; i < 8; ++i)
    {
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos + i, this->y_pos + i, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos + i, this->y_pos + i, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos + i, this->y_pos + i};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blocking
    }
    nofurthersearch = false;
}