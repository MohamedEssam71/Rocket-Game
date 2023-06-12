# Rocket-Game
AI Rocket Game based on Minimax Algorithm

## Game Rules
- Players take turns moving their rockets forward.
- The game offers the choice to play against another human or against the computer.
- Develop the game with two players, and then add a computer player that uses backtracking to decide the best move.
![RocketGame](https://github.com/MohamedEssam71/Rocket-Game/assets/101371937/378d1427-9ac4-4af2-af1d-38b3481d3df1)

## Game Tree and Backtracking
Similar to the Nim game, a game tree represents all the possible moves from a given state. The game tree can be searched using backtracking to find the best move. Here's how the game tree works:
- A good game state is when a player wins the game or if they can move the opponent to a bad state.
- A bad game state is when the current player already lost or if every possible move leads to a good state for the opponent.

## Recursive Algorithm
- A non-leaf node in the game tree is good if it has at least one bad child.
- A non-leaf node is bad if all its children are good.
- By induction, any player that finds the game in a good state on their turn can win the game, even if their opponent plays perfectly.
- Starting from a bad state, a player can only win if their opponent makes a mistake.

## Implementation Details
- Develop the game with two players, allowing human vs. human, or human vs. computer.
- Use backtracking to decide the best move for the computer player.
- Offer the choice to play against another human or against the computer at the start of the game.





