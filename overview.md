# Snake Game

## Overview
We want to create a terminal-based version of the game "Snake" with a focus on performance and optimized for further additions.

## Rules
Here are some basic rules for the game:
* When gameplay starts, there should be a snake that is 3 characters long on a game board.
* The snake should be controllable by pressing either the arrow keys or WSAD.  When the player inputs, the snake should immediately change direction.  Pushing in the direction that the snake is going or the opposite direction from the one that the snake is going should not do anything.
* The game board's playable space is 40 characters wide and 30 characters high.  Surrounding the playable space should be walls that the snake cannot pass through.
* There should be a piece of food on the board, it should be randomly placed in the area of the playable space.
* When the head of the snake reaches the food, the food is eaten and is destroyed, then a new piece of food is randomly placed somewhere else on the board's playable space.  This should not include any spot on the board occupied by the snake.
* When the snake eats a piece of food, increase the size of the snake by 1.
* Above the top wall of the board, there should be a score UI displaying two scores:  the player's current score and the high score.
* When the snake eats a piece of food, increase the current score by 10.  If the player's score is higher than the high score, the high score should also be updated.
* If the size of the snake takes up the entirety of the playable space, UI should pop up congratulating the player on beating the level.  From here, pressing any control (the arrow keys or WSAD) should start the next level.  The next level should reset the size of the snake to 3 characters long and retain the player's current score.  The snake should also go slightly faster compared to the previous level.
* If the snake crashes into a wall or itself, UI should pop up telling the player that the game is over and display the player's final score.  The UI should also prompt the player to play again by pressing any control (the arrow keys or WSAD).  If they play again, reset the player's score and set the snake to go at the initial speed.

## Technology
This application should have the following constraints:
* Language: C++
* SCM: Git
* Must include README.md containing build and run instructions as well as details on how to play the game
* Use PDCurses for Terminal I/O
* Use G++ for the compiler
* Use CMake as our build system generator