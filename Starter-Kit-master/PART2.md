# Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtu.be/UkeyfabXZxM).

## Minimum Requirements

### Completed

List all the features completed.

1. All basic game features
2. Customizable game board
3. Game dashboard.
4. Customizable map size and number of zombies.
5. Turn based 2d board game.
6. Game title stays in the middle of the board despite changed board dimensions.
7. Alien trail reset after game ends.
8. Play again after game ends.


### To Do

List all the features not yet done. Remove this section if there is no incomplete requirements.

1. Load feature still cannot work properly.

## Additional Features

Describe the additional features that has been implemented.

## Contributions

List down the contribution of each group members.

### Alvin Lim Jun En

1. Randomly generate game board.
2. Create and debug user input and output functions.

### Hoo Jet Yung

1. Zombie movement and attack behaviour.
2. Video demo.
3. Save and load feature.

### Lew Chun Men

1. Implement game classes.
2. Implement all game objects.

## Problems Encountered & Solutions

1. Declared object in if else statement
  - fix: declared objects in main function

2. Encountering Segmentation fault due to a line in Board function "map_[dimY_ - y][x - 1] = ch;"
  - fix: restructuring the code (not really fixed)
  - found an issue in zombie randomly set in board where zombies would sometime be set outside board dimensions cause seg fault.

3. Alien move crashes after moving the first time
  - fix: restructuring the code

4. After the first move alien will look at the next for next action
  - fix: restructuring the code, seperate function for movement and action and implementing switch function.

5. Zombie would sometimes attack alien even outside range.
  - fix: used seperate function for movement and action and changed condition for if else statement.

6. Load cannot work properly
  - cannot find fix.
