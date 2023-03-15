#pragma once
#include "Board.hpp"

class Engine
{
private:
    GameBoard gameBoard;

    int playerScore;
    int timeLeft;
    int secondScore;
    bool false_move;
    bool whoseMove = true;
    bool continuing = true;


    std::vector < std::vector <Field>> &eBoard;
    GameState gameState;

public:
    Engine(std::vector < std::vector <Field>> &board_) : eBoard(board_) {
        false_move = false;
        gameState = Running;
    };

    GameState checkStateOfGame() const;

    void play();

    bool ifThereIsFigure (int y, int x) const;
    void debugDisplay() const;
    void playGame();
    void movePiece(int x, int y, int wx, int wy);
    bool checkIfExists(int x, int y) const;
    void getPiece(int wasY, int wasX, int willY, int willX);
    void makeCastlingTrue(int rookY, int rookX, int kingY, int kingX, int wrookY, int wrookX, int wkingY, int wkingX);
    void printLine(int row, bool colour) const;
    bool capturePiece(int wasY, int wasX, int willY, int willX);

//Functions for checking interesting parts of chess game \/
    bool scanForMove(int fromY, int fromX, int toY, int toX);
    bool checkLegality(int x, int y, int wx, int wy);
    bool checkCastling(int kingY, int kingX, int kingMoveY, int kingMoveX);
    bool checkPromotion(int wasY, int wasX, int willY, int willX);
    bool checkLane(int wasY, int wasX, int willY, int willX) const;
    bool check50moves();
    bool checkCheck();
    bool checkMate();
};