#include "queen.h"

bool queen::can_queen_check_king(int currentX, int currentY, char teamcolor, piece*** currentboard)
{
    /*****CHECKING ROOK, BISHOP AND QUEEN****/

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
                if(currentboard[currentY - i][currentX - i]->getPieceType() == 'q') 
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
                if(currentboard[currentY - i][currentX + i]->getPieceType() == 'q')
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
                if(currentboard[currentY + i][currentX - i]->getPieceType() == 'q') 
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
                if(currentboard[currentY + i][currentX + i]->getPieceType() == 'q')
                {
                    piece::posVect.push_back(currentX + i);
                    piece::posVect.push_back(currentY + i);
                    return true;
                }
                else break;
            }
        }
    }
    
    for(int i = 1; i < 8; ++i)
    {//checking forward y direction
        if(piece::checkIfValid(currentX, currentY - i, currentboard))
        {
            if(currentboard[currentY - i][currentX]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY - i][currentX]->getTeamColour() != teamcolor)
            {
                if(currentboard[currentY - i][currentX]->getPieceType() == 'q')
                {
                    piece::posVect.push_back(currentX);
                    piece::posVect.push_back(currentY - i);
                    return true;
                }
                else break;//no comprimising piece
            }
        }
    }

    for(int i = 1; i < 8; ++i)
    {//checking backward y direction
        if(piece::checkIfValid(currentX, currentY + i, currentboard))
        {
            if(currentboard[currentY + i][currentX]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY + i][currentX]->getTeamColour() != teamcolor)
            {
                if(currentboard[currentY + i][currentX]->getPieceType() == 'q') 
                {
                    piece::posVect.push_back(currentX);
                    piece::posVect.push_back(currentY + i);
                    return true;
                }
                else break;//no comprimising piece
            }
        }
    }

    for(int i = 1; i < 8; ++i)
    {//checking left x direction
        if(piece::checkIfValid(currentX - i, currentY, currentboard))
        {
            if(currentboard[currentY][currentX - i]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY][currentX - i]->getTeamColour() != teamcolor)
            {
                if(currentboard[currentY][currentX - i]->getPieceType() == 'q') 
                {
                    piece::posVect.push_back(currentX - i);
                    piece::posVect.push_back(currentY);
                    return true;
                }
                else break;//no comprimising piece
            }
        }
    }
    
    for(int i = 1; i < 8; ++i)
    {//checking right x direction
        if(piece::checkIfValid(currentX + i, currentY, currentboard))
        {
            if(currentboard[currentY][currentX + i]->getTeamColour() == teamcolor)
            {
                break;//because friend teammate is protecting top-left diagonal
            }
            else if(currentboard[currentY][currentX + i]->getTeamColour() != teamcolor)
            {
                if(currentboard[currentY][currentX + i]->getPieceType() == 'q')
                {
                    piece::posVect.push_back(currentX + i);
                    piece::posVect.push_back(currentY);
                    return true;
                }
                else break;//no comprimising piece
            }
        }
    }

    //all tests failed thus no queen can check the king in this position
    return false;
}

queen::queen(int newX, int newY, char teamcolour, char piecetype)
    : piece(teamcolour, piecetype)
{
    this->x_pos = newX;
    this->y_pos = newY;
}

void queen::changeX_and_Y_Pos(int newX, int newY){
    this->x_pos = newX;
    this->y_pos = newY;
}

void queen::checkOpenSpots(piece*** currentboard)
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
    for(int i = 1; i < 8; ++i)
    {//checking forward y direction
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos, this->y_pos - i, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos, this->y_pos - i, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos, this->y_pos - i};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blockin
    }
    nofurthersearch = false;
    for(int i = 1; i < 8; ++i)
    {//checking backward y direction
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos, this->y_pos + i, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos, this->y_pos + i, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos, this->y_pos + i};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blocking
    }
    nofurthersearch = false;
    for(int i = 1; i < 8; ++i)
    {//checking left x direction
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos - i, this->y_pos, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos - i, this->y_pos, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos - i, this->y_pos};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blocking
    }
    nofurthersearch = false;
    for(int i = 1; i < 8; ++i)
    {//checking right x direction
        if(nofurthersearch == false && (checkValidityAndNull(this->x_pos + i, this->y_pos, currentboard) ||
            checkValidityNotNullOppTeam(this->x_pos + i, this->y_pos, currentboard, currentTeamColour, &nofurthersearch)))
        {
                XYcoords newCoords = {this->x_pos + i, this->y_pos};
                this->mylist->push_back(newCoords);
        }
        else break;//friend teammate is blocking
    }
    nofurthersearch = false;
}