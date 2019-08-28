## If the signature of insert was changed like below, how would that affect your code?
```
Node * insert(Node * p, int key, double value);
```
passing a nullptr would no longer work. One would probably have to return the modified trees instead. Otherwise one would not be able to re-point the nullptr to a real node. 
## Which of the two insert variants would you prefer? Motivate.
The one passing a reference to a pointer. Slightly more memory efficient, and more flexible with what to pass as p. 

## How that your are able to pass a value, such as 17, to a const int & parameter ?
int & would not work. applying the const qualifier 

## How do you check if two objects are equal if they only have operator< and not operator==?
```
(a<b) && !(b<a)

## Does a < b and !(b < a) compare the same thing?
!(b < a ) also includes b==a = true

## What was hardest to implement in this assignment?
remove()

## What did you learn from this asignment?
Mostly, the difference between passing pointer, and pass reference to pointer. 
