# OmokWebService
## Backend Web Based PHP Service for playing Omok with bot.
Build in PHP a Omok wed service. The service should support the following basic functions
- MoveStrategy
  - Selects which strategy is used in the Omok Client
- SmartStrategy
  - This allows for the bot to calculate the best placePlace using arrays to calculate locations on the board
  - Will calculate if the user is about to win / bot is about to win
- RandomStrategy
  - Will pickPlace at random.
  - Checks to see if slots are available for a random place
- Index
  - Provides server responces to check for errors such as isValidPID(valid player ID), isRealMove, isMoveValid, etc.
- Game, Board, Move
  - These are used to set up the game board and the ability to place slots.
