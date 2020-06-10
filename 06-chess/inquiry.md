### The code relies on virtual functions. Could the code have been written without virtual functions?
Technically maybe, if we use static casting to access the appropriate class methods. 

### Capturingmove calls a protected virtual function but is not virtual in itself. Noncapturingmoves/Capturingmoves are public virtual functions. What is your opinion of that design difference? Write your thoughts.
The first variant looks better, but it does call a virtual function, so in the end the result is the same. The first variant does require less code, which I appreciate.

### Should ChessPiece have been an abstract class?
In my opinion, yes. I see no point in being able to instantiate a ChessPiece object.

### There was no separate unit test for each function in this assignement, instead you tested several functions at once with different boards. What are the benefits and drawbacks for this kind of testing compared to unit tests?
Assuming that the implementation depends on the logic of the coder, this might end up with the coder being lazy or simply forgetting some logic that propagates to the unittests that he or she writes. Instead using full boards we get a quick overview of the chess board logics, especially if one prints all the boards.

### What is the problem with a diamond inheritance?
The problem arises when a subclass inherits from two superclasses, which in turn each inherit from another superclass. If there is a method in the top level superclass that mid-level superclasses overrides, and D does not override it, from which mid-level superclass does the derived class inherit from?

### What do you think of the general design of this code? What could be improved?
In this design the chesspieces and the board are closed to each other, and are operating independently, which messes up proper memory management when the board needs to control the pieces, but the pieces also do not want to relinquish this control (ie pieces also want to control stuff). We need to adopt a MVC scheme if this is to work painlessly. 

### What was most difficult to do in this assignement?
The losing chess part.... The assignment is not designed for an easy and clean implementation of a playable chess...