# Snake Game

## Overview
We want to create a terminal-based version of the game "Snake".  The player is a snake who can move up, down, left, and right (using arrow keys or WSAD controls) and must collect "food" that is randomly placed on the board.  The board should be 30x25 characters in size and should only have one piece of food on the field at a time.  When the snake reaches the piece of food, it is "eaten" (or destroyed) and the snake should get one unit longer, and another piece of food gets generated on the board.  The player's score should also increase by 10 points when the snake "eats" the food.  The score persists until the player loses.  If the snake runs into itself or a wall of the board, the game is over and the player should be given an option to play again.  If the game is over and the player's current score is higher than the current high score, set the high score equal to the player's current score.  If the snake occupies the whole board, the player has won that level and a new level begins, this time with the snake moving slightly faster than the previous level.

## Technology
This application should have the following constraints:
* Language: C++
* SCM: Git
* Must include README.md containing build and run instructions as well as details on how to play the game 