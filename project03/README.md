# Project Description:

In most large coding efforts, a group of programmers with design a project plan and each of them will implement select components with well-defined interfaces.

In this project, you will be acting as a member of a team implementing a board game where players have sets of game pieces fighting each other.  In your role you will implement two classes: GamePiece and GameState. 

# GamePiece Class:

The GamePiece class should be declared in a file called GamePiece.hpp.  Function definitions should be provided in GamePiece.cpp.  This class represents a single playing piece in the game.

This class should contain member variables that track the name of the player that owns this piece, the type of GamePiece it is (the three options are "Warrior", "Scout", or "Wizard"), and a pointer to the GameState object for the current game.

You should have two constructors for this class: one that takes the internal information for the piece (name of the player, type of piece, and pointer to the GameState and the other a copy constructor.  You should NOT have a default constructor.

The ```GetPlayer()``` member function should return a string with the name of the player this piece belongs to.

The ```GetType()``` member function should return a string with the type of piece the object represents.

The ```GetPower()``` member function should return an int that indicates how strong this piece is in battle.  A Warrior has a power of 5.  A Scout has a power of 1.  A Wizard has a power equal to the total number of Wizards on that player's team (Wizards can boost each other's power).

The ```GetSpeed()``` member function should return an int that indicates how many spaces this piece can move.  A Warrior has a speed of 2.  A Scout has a speed of 8.  A Wizard has a speed of 12 minus the total number of Wizards on enemy teams, to a minimum of 1 (Wizards can travel fast by magic, but are slowed by enemy wizards).

You should implement all 6 comparison operators ('==', '!=', '<', '>', '<=', and '>=').  The ordering of pieces should indicate who would win in a fight.  If one piece has a higher "power" score, that piece wins (and is thus greater than the other).  If there is a tie on power, the piece with the higher "speed" wins.  If there is again a tie, the two pieces are tied (i.e., == should return true.)

You should implement the assignment operator ('='), which may completely change the type, owner, or even associated GameState of a piece.

The class should support the ```operator<<``` to write to an ostream. It should print parentheses containing the name of the owning player, the name of the piece, its current power, and its current speed in the following format: ```(Charles,Scout,1,8)```

# GameState Class:

The GameState class should be declared in a file called GameState.hpp.  Function definitions should be provided in GameState.cpp.  This class keeps track of the set of pieces owned by each player.

This class should have a default constructor.

The NumPieces() function should return an int indicating the current number of pieces in the game.  It should also have two overloads: (1) to take a single parameter for player name, returning the number of piece that player has, and (2) to take two parameters for player name and piece type, returning the number of pieces the specified player has of that type.  If a provided player name or type name does not exist, this function should return 0.
