# 15 Puzzle Game Search

## Gameplay
The 15-Puzzle is a game in which a player must slide tiles around on a 4 × 4 grid to reach a goal configuration. If you have never played before, I recommend trying it out here: https://15puzzle.netlify.app/.

There is one empty space that an adjacent tile can be slid into. An alternative (and simpler) view is that we are simply moving the blank square around the grid. Not all actions can be used at all times; for example, the blank tile cannot be shifted up if it is already on the top row!

The transition below illustrates the blank tile being moved to the right.

[ ##### image #### ]

Above Figure: Starting in configuration (a), the agent executes the action right. This moves the blank tile to the right, exchanging its position with F, as seen in (b).
The cost of each move is 1 and the goal of the game is to slide the tiles around to reach some goal configuration, which we will take to be the letters in alphabetical order, with the bottom right corner housing the blank slot as seen below:
