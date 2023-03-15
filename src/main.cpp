#include "../headers/Engine.hpp"
#include "../headers/Board.hpp"
#include <iostream>

int main()
{
    GameBoard gameBoard;
    Engine engine{gameBoard.Board};
    engine.play();
    return 0;
}