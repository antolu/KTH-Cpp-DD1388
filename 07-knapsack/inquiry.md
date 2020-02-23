## Answers to questions

> In what order are the mapitems printed?
In reverse order. The heaviest gold bar first. 

> What is the underlying data structure std::map uses?
It is implementation dependent, but most commonly a Red-Blck BST is used, in that war one can iterate the  keys in asc

> Which is the first knapsackweight where the second greedy solution is better than the first?
Greedy algorithm 2 is better than 1 at knapsacksize 30.
Greedy 2: Size: 30, value: 49, 1*13@21=21, 1*17@28=28
Greedy 1: Size: 30, value: 29, 1*19@29=29

> What is the difference between a std::set and a std::map?
Both set and map uses a Red Black Tree for storing information. The only difference between them is that the set stores just the key, while the key stores key and value pairs. 

> What is the difference between a std::set and a std::unordered_set?
Unordered set has no order. Unordered set uses hash table as underlying data structure, while the normal set uses a Red Black Tree. Set has log(n) search time, while unordered_set is O(1) avg.

> Find 5 knapsack values where the optimal solution is equal to greedy solution 1.
The following knapsacks have the same solution, whether greedy1 or dynamically programmed
Size: 13, value: 21, 1*13@21=21
Size: 14, value: 22, 1*14@22=22
Size: 15, value: 23, 1*15@23=23
Size: 16, value: 24, 1*16@24=24
Size: 17, value: 28, 1*17@28=28

> Find five knapsack values where the optimal solution is equal to greedy solution 2.
The following knapsacks have the same solution, whether greedy2 or dynamically programmed
Size: 13, value: 21, 1*13@21=21
Size: 14, value: 22, 1*14@22=22
Size: 15, value: 23, 1*15@23=23
Size: 16, value: 24, 1*16@24=24
Size: 29, value: 45, 1*13@21=21, 1*16@24=24
