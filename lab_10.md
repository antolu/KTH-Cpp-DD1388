# A very small adventure game

Implement a text adventure game. The game parses input from the
command line. Let the game have three connected rooms. The player
starts the game in room one, has to interact with something/someone in
room two and exits/wins the game using something from room two
interacting with something/someone in room three.

Example of game play:

```

You stand in a forest. The sky is clear and birds are singing. To the
north is a castle and to the east is a clearing.
> loooook
You cannot do that
> look
You stand in a forest. The sky is clear and birds are singing. To the
north is a castle and to the east is a clearing.
exits:
north - a castle
east  - a clearing
> look birds
The birds looks back at you singing
> say hello
Nobody answers
> go east
You stand in a clearing. There is a fat ogre sitting here wielding a heavy sword.
To the you see northwest is a castle.
> look troll
The ogre looks back at you ominously.
> say hello to troll
The troll says
-"good day to you, you look tasty"
> tickle troll
The troll giggles and drops his sword
> look
You stand in a clearing. There is a fat ogre sitting here.
To the northwest is a castle. On the ground is a heavy sword
exits:
northwest - a castle
west - forest
> take sword
You pick up a heavy sword
> get sword
There is no sword here
> go northwest
There is a castle here. In front of the castle is a black knight.
> say hello to knight
The black knight answers
-"None, shall pass"
> attack knight
You attack the knight with your bare hands. The knight hits you with a
morning star. THAT HURT!
> wield sword
You wield a heavy sword.
> attack knight
With one mighty blow you defeat the knight. The castle is yours for the taking.
You win the game.

```

## The parser

Write your command line parser using
an
[unordered_map](http://en.cppreference.com/w/cpp/container/unordered_map) where
the name of each possible command is key and the value is a function
pointer to which you send the rest of the command line. You are free
to send additional parameters.

Your game must be able to handle some command lines that contain more
than two words.

Your game must handle at least one synonym (get/take in the example)

You are free to use shortcuts like 'n' instead of 'go north'.

## The game

Personalize your game content. Write your own room/item descriptions.
You need at minimum three rooms, an item/person with which to win, and
two things/persons to interact with in room 2 and 3.


## Design

You are free to use anything from the standard c++ library. Implement
your own classes and functions to solve this assignment. You may use
global variables but use as few globals as possible. For instance a
vector containing the rooms could be a global variable.

## Questions

#### How would you have solved the command line parser without using an unordered_set with commands?


#### How would you prefer implementing a command line parser?


#### What global variables did you use?


#### Describe how you solved ownership of items? Where are items contained?



#### What did you learn from this assignment?
