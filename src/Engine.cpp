
#include "../headers/Engine.hpp"
#include <iostream>

#define RESET "\033[0m"
#define WHITE "\033[0;30m\033[47m"
#define BLACK "\033[37m\033[40m"
#define WHITE_PIECE_ON_WHITE "\033[0;34m\033[47m" //Niebieskie literki
#define BLACK_PIECE_ON_WHITE "\033[0;31m\033[47m" //Czerwone
#define WHITE_PIECE_ON_BLACK "\033[0;34m\033[40m"
#define BLACK_PIECE_ON_BLACK "\033[0;31m\033[40m"
#define _king 1
#define _queen 2


void Engine::play()
{
    while (continuing == true)
    {
        system("clear");
        debugDisplay();
        playGame();
    }
}

void Engine::printLine(int row, bool colour) const
{
    Map map;

    if (colour)
    {
        for (int i = 0; i < 4; i++)
        {
            std::cout << WHITE << "      " << BLACK << "      ";
        }
        std::cout << "\n";
        for (int i = 0; i < 8; i++)
        {
            if (eBoard[row][i].whichPiece.black == true)
            {
                if (i%2 == 0)
                {
                    std::cout << WHITE << "  " << BLACK_PIECE_ON_WHITE << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << WHITE << "  " << RESET;
                }
                else
                {
                    std::cout << BLACK << "  " << BLACK_PIECE_ON_BLACK << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << BLACK << "  " << RESET;
                }
            }
            else if (eBoard[row][i].whichPiece.black == false)
            {
                if (i%2 == 0)
                {
                    std::cout << WHITE << "  " << WHITE_PIECE_ON_WHITE << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << WHITE << "  " << RESET;
                }
                else
                {
                    std::cout << BLACK << "  " << WHITE_PIECE_ON_BLACK << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << BLACK << "  " << RESET;
                }
            }
        }
        std::cout << "\n";
        for (int i = 0; i < 4; i++)
        {
            std::cout << WHITE << "      " << BLACK << "      ";
        }
        std::cout << "\n";
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            std::cout << BLACK << "      " << WHITE << "      ";
        }
        std::cout << "\n";
        for (int i = 0; i < 8; i++)
        {
            if (eBoard[row][i].whichPiece.black == true)
            {
                if (i%2 == 0)
                {
                    std::cout << BLACK << "  " << BLACK_PIECE_ON_BLACK << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << BLACK << "  " << RESET;
                }
                else
                {
                    std::cout << WHITE << "  " << BLACK_PIECE_ON_WHITE << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << WHITE << "  " << RESET;
                }
            }
            else if (eBoard[row][i].whichPiece.black == false)
            {
                if (i%2 == 0)
                {
                    std::cout << BLACK << "  " << WHITE_PIECE_ON_BLACK << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << BLACK << "  " << RESET;
                }
                else
                {
                    std::cout << WHITE << "  " << WHITE_PIECE_ON_WHITE << map.magicPieceName(eBoard[row][i].whichPiece.piecesNames) << WHITE << "  " << RESET;
                }
            }
        }
        std::cout << "\n";
        for (int i = 0; i < 4; i++)
        {
            std::cout << BLACK << "      " << WHITE << "      ";
        }
        std::cout << "\n";
    }
}


void Engine::debugDisplay() const
{
    if (whoseMove)
    {
        std::cout << "Ruch " << WHITE << "białych!" << RESET;
    }
    else
    {
        std::cout << "Ruch " << BLACK << "czarnych!" << RESET;
    }
    std::cout << "\n\n";
    for (int lane = 0; lane < 8; lane++)
    {
        if (lane%2 == 0)
        {
            printLine(lane, false);
        }
        else
        {
            printLine(lane, true);
        }
    }
}

bool Engine::ifThereIsFigure (int y, int x) const
{
    if (eBoard[y][x].whichPiece.isAlive == true)
    {
        return true;
    }
    std::cout << "Tutaj nie ma figury!";
    return false;
}


void Engine::movePiece(int moveToY, int moveFromY, int moveToX, int moveFromX)
{
    if (checkIfExists(moveToY, moveToX))
    {
        if (ifThereIsFigure(moveFromY, moveFromX))
        {
            eBoard[moveToY][moveToX].whichPiece = eBoard[moveFromY][moveFromX].whichPiece;
            eBoard[moveFromY][moveFromX].whichPiece.isAlive = false;
            eBoard[moveFromY][moveFromX].whichPiece.piecesNames = Blank;
            eBoard[moveFromY][moveFromX].whichPiece.points = 0;
        }
    }
}

void Engine::playGame()
{
    int moveToY, moveToX, moveFromY, moveFromX;
    std::cout << "Podaj rząd figury do przesunięcia: ";
    std::cin >> moveFromY;
    std::cout << "Podaj kolumnę figury do przesunięcia: ";
    std::cin >> moveFromX;
    std::cout << "Podaj rząd gdzie ustawić figurę: ";
    std::cin >> moveToY;
    std::cout << "Podaj kolumnę gdzie ustawić figurę";
    std::cin >> moveToX;

    moveFromY = moveFromY - 1;
    moveFromX = moveFromX - 1;
    moveToY = moveToY - 1;
    moveToX = moveToX - 1;

    if ((whoseMove == true && eBoard[moveFromY][moveFromX].whichPiece.black == true) || (whoseMove == false && eBoard[moveFromY][moveFromX].whichPiece.black == false))
    {
        std::cout << "Ruch oponenta!\n";
    }
    else if (ifThereIsFigure(moveToY, moveToX) == true)
    {
        if (capturePiece(moveFromY, moveFromX, moveToY, moveToX) == true)
        {
            whoseMove = !whoseMove;
        }
    }
    else if (checkLegality(moveToX, moveToY, moveFromX, moveFromY) == true)
    {   
        whoseMove = !whoseMove;
        movePiece(moveToY, moveFromY, moveToX, moveFromX);
    }
}

bool Engine::checkIfExists(int y, int x) const
{
    if ((y >= 0 && y < 8) && (x >= 0 && x < 8))
    {
        return true;
    }
    std::cout << "Podaj właściwe koordynaty!";
    return false;
}

bool Engine::checkLegality(int x, int y, int wx, int wy)
{
    if (eBoard[wy][wx].whichPiece.isAlive == true)
    { 
        switch (eBoard[wy][wx].whichPiece.piecesNames)
        {
            case King:
            //if (eBoard[y][x].whichPiece.isBlack == false)
                if (checkCastling(wy, wx, y, x) == true)
                {
                    return false;
                }
                else if ((((x - wx) >=-1 && (x - wx) <= 1)) && ((y - wy) >= -1 && (y - wy) <= 1))
                {
                    return true;
                }
                break;
            case Queen:
                if (
                    ((x - wx) == (y - wy))||
                    ((wx - x) == (wy - y))||
                    ((wx - x) == (y - wy))||
                    (wx == x)||
                    (wy == y)
                )
                {
                    if (scanForMove(wy, wx, y, x))
                    {
                        return true;
                    }
                }
                break;
            case Knight:
                if ((((wx - x) * (wy - y)) == 2) || ((wx - x) * (wy - y)) == -2)
                {
                    return true;
                }
                break;
            case Bishop:
                if (((x - wx) == (y - wy))||
                    ((wx - x) == (wy - y))||
                    ((wx - x) == (y - wy)))
                {
                    if (scanForMove(wy, wx, y, x) == true)
                    {
                        return true;
                    }
                }
                break;
            case Rook:
                if ((wx == x) || (wy == y))
                {
                    if (scanForMove(wy, wx, y, x) == true)
                    {
                        return true;
                    }
                } 
                break;
            case Pawn:
                if (eBoard[wy][wx].whichPiece.black == false)
                {
                    if ((wx == x) && (wy == y + 1))
                    {
                        if (scanForMove(wy, wx, y, x) == true)
                        {
                            return true;
                        }
                    }
                    else if (eBoard[wy][wx].whichPiece.alredyMoved == false)
                    {
                        if ((wx == x) && (wy == y + 2))
                        {
                            if (scanForMove(wy, wx, y, x) == true)
                            {
                                return true;
                            }
                        }
                    }
                }
                else
                {
                    if ((wx == x) && (wy == y - 1))
                    {
                        if (scanForMove(wy, wx, y, x) == true)
                        {
                            return true;
                        }
                    }
                    else if (eBoard[wy][wx].whichPiece.alredyMoved == false)
                    {
                        if ((wx == x) && (wy == y - 2))
                        {
                            if (scanForMove(wy, wx, y, x) == true)
                            {
                                return true;
                            }
                        }
                    }
                }
                break;
            case Blank:
                return false;
                break;
            default:
                break;
        }
    }
    return false;
}


bool Engine::checkCastling(int kingY, int kingX, int kingMoveY, int kingMoveX)
{
    if (eBoard[kingY][kingX].whichPiece.black == true)
    {
        if (eBoard[kingY][kingX].whichPiece.alredyMoved == false)
        {
            if (kingMoveX == 5)
            {
                if (eBoard[0][7].whichPiece.alredyMoved == false)
                {
                    makeCastlingTrue(0, 4, kingMoveY, kingMoveX, 0, 7, kingY, kingX);
                    return true;
                }
            }
            else if (kingMoveX == 1)
            {
                if (eBoard[0][0].whichPiece.alredyMoved == false)
                {
                    makeCastlingTrue(0, 2, kingMoveY, kingMoveX, 0, 0, kingY, kingX);
                    return true;
                }
            }
        }
    }
    else if (eBoard[kingY][kingX].whichPiece.black == false)
    {
        if (eBoard[kingY][kingX].whichPiece.alredyMoved == false)
        {
            if (kingMoveX == 5)
            {
                if (eBoard[7][7].whichPiece.alredyMoved == false && scanForMove(7,7,7,4) == true)
                {
                    makeCastlingTrue(7, 4, kingMoveY, kingMoveX, 7, 7, kingY, kingX);
                    return true;
                }
            }
            else if (kingMoveX == 1)
            {
                if (eBoard[7][0].whichPiece.alredyMoved == false && scanForMove(7,0,7,2) == true)
                {
                    makeCastlingTrue(7, 2, kingMoveY, kingMoveX, 7, 0, kingY, kingX);
                    return true;
                }
            }          
        }
    }
    return false;
}

void Engine::makeCastlingTrue(int rookY, int rookX, int kingY, int kingX, int wrookY, int wrookX, int wkingY, int wkingX)
{
    movePiece(rookY, wrookY, rookX, wrookX);
    movePiece(kingY, wkingY, kingX, wkingX);
}

bool Engine::scanForMove(int fromY, int fromX, int toY, int toX)
{
    Map map;
    switch (eBoard[fromY][fromX].whichPiece.piecesNames)
    {
        case Rook:
            if ((fromX - toX) < 0)
            {
                while (fromX < toX)
                {
                    if (eBoard[fromY][fromX + 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromX++;
                }
                return true;
            }
            else if ((fromX - toX) > 0)
            {
                while (fromX > toX)
                {
                    if (eBoard[fromY][fromX - 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromX--;
                }
                return true;
            }
            else if ((fromY - toY) < 0)
            {
                while (fromY < toY)
                {
                    if (eBoard[fromY + 1][fromX].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY++;
                }
                return true;
            }
            else if ((fromY - toY) > 0)
            {
                while (fromY > toY)
                {
                    if (eBoard[fromY - 1][fromX].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                   fromY--;
                }
                return true;
            }
            break;
        case Bishop:
            if (((fromY - toY) < 0) && ((fromX - toX) < 0))
            {
                while (fromY < toY && fromX < toX)
                {
                    if (eBoard[fromY + 1][fromX + 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY++;
                    fromX++;
                }
                return true;
            }
            else if (((fromY - toY) < 0) && ((fromX - toX) > 0))
            {
                while (fromY < toY && fromX > toX)
                {
                    if (eBoard[fromY + 1][fromX - 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY++;
                    fromX--;
                }
                return true;
            }
            else if (((fromY - toY) > 0) && ((fromX - toX) > 0))
            {
                while (fromY > toY && fromX > toX)
                {
                    if (eBoard[fromY - 1][fromX - 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY--;
                    fromX--;
                }
                return true;
            }
            else if (((fromY - toY) > 0) && ((fromX - toX) < 0))
            {
                while (fromY > toY && fromX < toX)
                {  
                    if (eBoard[fromY - 1][fromX + 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY--;
                    fromX++;
                }
                return true;
            }
            break;
        case Pawn:
            if ((fromY - toY) < 0)
            {
                while (fromY < toY)
                {
                    if (eBoard[fromY + 1][fromX].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY++;
                }
                return true;
            }
            else if ((fromY - toY) > 0)
            {
                while (fromY > toY)
                {
                    if (eBoard[fromY - 1][fromX].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY--;
                }
                return true;
            }
            break;
        case Queen:
            if (((fromX - toX) < 0) && ((fromY - toY) == 0))
            {
                while (fromX < toX)
                {
                    if (eBoard[fromY][fromX + 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromX++;
                }
                return true;
            }
            else if (((fromX - toX) > 0) && ((fromY - toY) == 0))
            {
                while (fromX > toX)
                {
                    if (eBoard[fromY][fromX - 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromX--;
                }
                return true;
            }
            else if (((fromY - toY) < 0) && ((fromX - toX) == 0))
            {
                while (fromY < toY)
                {
                    if (eBoard[fromY + 1][fromX].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY++;
                }
                return true;
            }
            else if (((fromY - toY) > 0) && ((fromX - toX) == 0))
            {
                while (fromY > toY)
                {
                    if (eBoard[fromY - 1][fromX].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY--;
                }
                return true;
            }
            else if (((fromY - toY) < 0) && ((fromX - toX) < 0))
            {
                while (fromY < toY && fromX < toX)
                {
                    if (eBoard[fromY + 1][fromX + 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY++;
                    fromX++;
                }
                return true;
            }
            else if (((fromY - toY) < 0) && ((fromX - toX) > 0))
            {
                while (fromY < toY && fromX > toX)
                {
                    if (eBoard[fromY + 1][fromX - 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY++;
                    fromX--;
                }
                return true;
            }
            else if (((fromY - toY) > 0) && ((fromX - toX) > 0))
            {
                while (fromY > toY && fromX > toX)
                {
                    if (eBoard[fromY - 1][fromX - 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY--;
                    fromX--;
                }
                return true;
            }
            else if (((fromY - toY) > 0) && ((fromX - toX) < 0))
            {
                while (fromY > toY && fromX < toX)
                {  
                    if (eBoard[fromY - 1][fromX + 1].whichPiece.isAlive == true)
                    {
                        return false;
                    }
                    fromY--;
                    fromX++;
                }
                return true;
            }
            break;
        case King:
        //no nic tu nie ma do sprawdzania kurwa xD
            break;
        case Blank:
        //tutaj tez
            break;
        case Knight:
        //no i tutaj to juz wgl 
            break;
    }
    return false;
}


bool Engine::capturePiece(int wasY, int wasX, int willY, int willX)
{
    if (willY - wasY > 0 && willX - wasX > 0)
    {
        if (checkLegality(willX - 1, willY - 1, wasX, wasY))
        {
            if (whoseMove == true)
            {
                playerScore += eBoard[willY][willX].whichPiece.points;
            }
            else
            {
                secondScore += eBoard[willY][willX].whichPiece.points;
            }
            movePiece(willY, wasY, willX, wasX);
            return true;
        }
    }
    else if (willY - wasY > 0 && willX - wasX < 0)
    {
        if (checkLegality(willX + 1, willY - 1, wasX, wasY))
        {
            if (whoseMove == true)
            {
                playerScore += eBoard[willY][willX].whichPiece.points;
            }
            else
            {
                secondScore += eBoard[willY][willX].whichPiece.points;
            }
            movePiece(willY, wasY, willX, wasX);
            return true;
        }
    }
    else if (willY - wasY < 0 && willX - wasX > 0)
    {
        if (checkLegality(willX + 1, willY - 1, wasX, wasY))
        {
            std::cout << "Eurlo201";
            if (whoseMove == true)
            {
                playerScore += eBoard[willY][willX].whichPiece.points;
            }
            else
            {
                secondScore += eBoard[willY][willX].whichPiece.points;
            }
            movePiece(willY, wasY, willX, wasX);
            return true;
        }
    }
    else if (willY - wasY < 0 && willX - wasX < 0)
    {
        if (checkLegality(willX + 1, willY + 1, wasX, wasY))
        {
            if (whoseMove == true)
            {
                playerScore += eBoard[willY][willX].whichPiece.points;
            }
            else
            {
                secondScore += eBoard[willY][willX].whichPiece.points;
            }
            movePiece(willY, wasY, willX, wasX);
            return true;
        }
    }
    return false;
}

bool Engine::checkPromotion(int wasY, int wasX, int willY, int willX)
{
    return false;
}