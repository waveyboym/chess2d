#include "king.h"
#include "../bishop/bishop.h"
#include "../knight/knight.h"
#include "../pawn/pawn.h"
#include "../queen/queen.h"
#include "../rook/rook.h"

bool king::can_CheckKing(int currentX, int currentY, char teamcolor, piece*** currentboard)
{

    /*******************CHECKING BISHOP, KNIGHT, PAWN, QUEEN, ROOK********************/

    if(bishop::can_bishop_check_king(currentX, currentY, teamcolor, currentboard))return true;
    if(knight::can_knight_check_king(currentX, currentY, teamcolor, currentboard))return true;
    if(pawn::can_pawn_check_king(currentX, currentY, teamcolor, currentboard))return true;
    if(queen::can_queen_check_king(currentX, currentY, teamcolor, currentboard))return true;
    if(rook::can_rook_check_king(currentX, currentY, teamcolor, currentboard))return true;
    
    /*****CHECKING OPPOSING TEAM KING****/
    //top-left diagonal
    if(piece::checkIfValid(currentX - 1, currentY - 1, currentboard)
        && currentboard[currentY - 1][currentX - 1]->getPieceType() == 'K'
        && currentboard[currentY - 1][currentX - 1]->getTeamColour() != teamcolor)
    {
            return true;
    }
    //top-right diagonal
    if(piece::checkIfValid(currentX + 1, currentY - 1, currentboard)
        && currentboard[currentY - 1][currentX + 1]->getPieceType() == 'K'
        && currentboard[currentY - 1][currentX + 1]->getTeamColour() != teamcolor)
    {
            return true;
    }
    //bottom-left diagonal
    if(piece::checkIfValid(currentX - 1, currentY + 1, currentboard)
        && currentboard[currentY + 1][currentX - 1]->getPieceType() == 'K'
        && currentboard[currentY + 1][currentX - 1]->getTeamColour() != teamcolor)
    {
            return true;
    }
    //bottom-right diagonal
    if(piece::checkIfValid(currentX + 1, currentY + 1, currentboard)
        && currentboard[currentY + 1][currentX + 1]->getPieceType() == 'K'
        && currentboard[currentY + 1][currentX + 1]->getTeamColour() != teamcolor)
    {
            return true;
    }

    //checking forward y direction
    if(piece::checkIfValid(currentX, currentY - 1, currentboard)
        && currentboard[currentY - 1][currentX]->getPieceType() == 'K'
        && currentboard[currentY - 1][currentX]->getTeamColour() != teamcolor)
    {
            return true;
    }
    //checking backward y direction
    if(piece::checkIfValid(currentX, currentY + 1, currentboard)
        && currentboard[currentY + 1][currentX]->getPieceType() == 'K'
        && currentboard[currentY + 1][currentX]->getTeamColour() != teamcolor)
    {
            return true;
    }
    //checking left x direction
    if(piece::checkIfValid(currentX - 1, currentY, currentboard)
        && currentboard[currentY][currentX - 1]->getPieceType() == 'K'
        && currentboard[currentY][currentX - 1]->getTeamColour() != teamcolor)
    {
            return true;
    }
    //checking right x direction
    if(piece::checkIfValid(currentX + 1, currentY, currentboard)
        && currentboard[currentY][currentX + 1]->getPieceType() == 'K'
        && currentboard[currentY][currentX + 1]->getTeamColour() != teamcolor)
    {
            return true;
    }

    //the king cannot be checked in this pos so return false
    return false;
}

bool king::can_move_out_of_check(int currentX, int currentY, char teamcolor, piece*** currentboard)
{

    if(checkValidityAndNull(currentX - 1, currentY - 1, currentboard)
        || checkValidityNotNullOppTeam(currentX - 1, currentY - 1, currentboard, teamcolor))
    {

            if(can_CheckKing(currentX - 1, currentY - 1, teamcolor, currentboard) == false)
            {
                return true;
            }
    }
    //top-right diagonal
    if(checkValidityAndNull(currentX + 1, currentY - 1, currentboard)
        || checkValidityNotNullOppTeam(currentX + 1, currentY - 1, currentboard, teamcolor))
    {
            
            if(can_CheckKing(currentX + 1, currentY - 1, teamcolor, currentboard) == false)
            {
                return true;
            }
    }
    //bottom-left diagonal
    if(checkValidityAndNull(currentX - 1, currentY + 1, currentboard)
        || checkValidityNotNullOppTeam(currentX - 1, currentY + 1, currentboard, teamcolor))
    {
            
            if(can_CheckKing(currentX - 1, currentY + 1, teamcolor, currentboard) == false)
            {
                return true;
            }
    }
    //bottom-right diagonal
    if(checkValidityAndNull(currentX + 1, currentY + 1, currentboard)
        || checkValidityNotNullOppTeam(currentX + 1, currentY + 1, currentboard, teamcolor))
    {
            
            if(can_CheckKing(currentX + 1, currentY + 1, teamcolor, currentboard) == false)
            {
                return true;
            }
    }

    //checking forward y direction
    if(checkValidityAndNull(currentX, currentY - 1, currentboard)
        || checkValidityNotNullOppTeam(currentX, currentY - 1, currentboard, teamcolor))
    {
            
            if(can_CheckKing(currentX, currentY - 1, teamcolor, currentboard) == false)
            {
                return true;
            }
    }
    //checking backward y direction
    if(checkValidityAndNull(currentX, currentY + 1, currentboard)
        || checkValidityNotNullOppTeam(currentX, currentY + 1, currentboard, teamcolor)){
            
            if(can_CheckKing(currentX, currentY + 1, teamcolor, currentboard) == false){
                return true;
            }
    }
    //checking left x direction
    if(checkValidityAndNull(currentX - 1, currentY, currentboard)
        || checkValidityNotNullOppTeam(currentX - 1, currentY, currentboard, teamcolor))
    {
            
            if(can_CheckKing(currentX - 1, currentY, teamcolor, currentboard) == false)
            {
                return true;
            }
    }
    //checking right x direction
    if(checkValidityAndNull(currentX + 1, currentY, currentboard)
        || checkValidityNotNullOppTeam(currentX + 1, currentY, currentboard, teamcolor))
    {
            
            if(can_CheckKing(currentX + 1, currentY, teamcolor, currentboard) == false)
            {
                return true;
            }
    }

    return false;
}

bool king::can_piece_save_king(char teamcolor, piece*** currentboard)
{
    //change of team color.So if team color is white, then turn it to black because we want white pieces that can
    //possibly take out the black piece threat
    if (teamcolor == 'w') teamcolor = 'b';
    else if(teamcolor == 'b') teamcolor = 'w';

    if (piece::posVect.size() != 2) 
    {
        std::cout << "a fatal error has occured in the can_piece_save_king function" << std::endl;
        return false;
    }

    //repurpose these functions so they can now check instead if any piece can eliminate the piece at the pos specififed in the vector
    if (bishop::can_bishop_check_king(piece::posVect[XYposOfPiece::piece_X], piece::posVect[XYposOfPiece::piece_Y], teamcolor, currentboard))return true;
    if (knight::can_knight_check_king(piece::posVect[XYposOfPiece::piece_X], piece::posVect[XYposOfPiece::piece_Y], teamcolor, currentboard))return true;
    if (pawn::can_pawn_check_king(piece::posVect[XYposOfPiece::piece_X], piece::posVect[XYposOfPiece::piece_Y], teamcolor, currentboard))return true;
    if (queen::can_queen_check_king(piece::posVect[XYposOfPiece::piece_X], piece::posVect[XYposOfPiece::piece_Y], teamcolor, currentboard))return true;
    if (rook::can_rook_check_king(piece::posVect[XYposOfPiece::piece_X], piece::posVect[XYposOfPiece::piece_Y], teamcolor, currentboard))return true;
    return false;
}


king::king(int newX, int newY, char teamcolour, char piecetype)
    : piece(teamcolour, piecetype)
{
    this->x_pos = newX;
    this->y_pos = newY;
}

void king::changeX_and_Y_Pos(int newX, int newY)
{
    this->x_pos = newX;
    this->y_pos = newY;
}

void king::checkOpenSpots(piece*** currentboard)
{
    char currentTeamColour = this->getTeamColour();
    //top-left diagonal
    if(checkValidityAndNull(this->x_pos - 1, this->y_pos - 1, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos - 1, this->y_pos - 1, currentboard, currentTeamColour))
    {

            if(can_CheckKing(this->x_pos - 1, this->y_pos - 1, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos - 1, this->y_pos - 1};
                this->mylist->push_back(newCoords);
            }
    }
    //top-right diagonal
    if(checkValidityAndNull(this->x_pos + 1, this->y_pos - 1, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos + 1, this->y_pos - 1, currentboard, currentTeamColour))
    {
            
            if(can_CheckKing(this->x_pos + 1, this->y_pos - 1, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos + 1, this->y_pos - 1};
                this->mylist->push_back(newCoords);
            }
    }
    //bottom-left diagonal
    if(checkValidityAndNull(this->x_pos - 1, this->y_pos + 1, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos - 1, this->y_pos + 1, currentboard, currentTeamColour))
    {
            
            if(can_CheckKing(this->x_pos - 1, this->y_pos + 1, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos - 1, this->y_pos + 1};
                this->mylist->push_back(newCoords);
            }
    }
    //bottom-right diagonal
    if(checkValidityAndNull(this->x_pos + 1, this->y_pos + 1, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos + 1, this->y_pos + 1, currentboard, currentTeamColour))
    {
            
            if(can_CheckKing(this->x_pos + 1, this->y_pos + 1, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos + 1, this->y_pos + 1};
                this->mylist->push_back(newCoords);
            }
    }

    //checking forward y direction
    if(checkValidityAndNull(this->x_pos, this->y_pos - 1, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos, this->y_pos - 1, currentboard, currentTeamColour))
    {
            
            if(can_CheckKing(this->x_pos, this->y_pos - 1, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos, this->y_pos - 1};
                this->mylist->push_back(newCoords);
            }
    }
    //checking backward y direction
    if(checkValidityAndNull(this->x_pos, this->y_pos + 1, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos, this->y_pos + 1, currentboard, currentTeamColour))
    {
            
            if(can_CheckKing(this->x_pos, this->y_pos + 1, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos, this->y_pos + 1};
                this->mylist->push_back(newCoords);
            }
    }
    //checking left x direction
    if(checkValidityAndNull(this->x_pos - 1, this->y_pos, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos - 1, this->y_pos, currentboard, currentTeamColour))
    {
            
            if(can_CheckKing(this->x_pos - 1, this->y_pos, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos - 1, this->y_pos};
                this->mylist->push_back(newCoords);
            }
    }
    //checking right x direction
    if(checkValidityAndNull(this->x_pos + 1, this->y_pos, currentboard)
        || checkValidityNotNullOppTeam(this->x_pos + 1, this->y_pos, currentboard, currentTeamColour))
    {
            
            if(can_CheckKing(this->x_pos + 1, this->y_pos, currentTeamColour, currentboard) == false)
            {
                XYcoords newCoords = {this->x_pos + 1, this->y_pos};
                this->mylist->push_back(newCoords);
            }
    }
}