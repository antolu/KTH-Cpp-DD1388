# Lab 7 the knapsack problem

Implement different solutions to the following knapsack problem. 

Inside the dwarven cavern there are several (unlimited for the purpose
of this assignment) gold bars of different quality, weight and value. 

| weight (kg) | value | density value/kg |
| --- | --- | --- |
| 28 | 17 | 1.65  |
| 21 | 13 | 1.62  |
| 22 | 14 | 1.57  |
| 23 | 15 | 1.533 |
| 29 | 19 | 1.526 |
| 24 | 16 | 1.5   |

You have a knapsack that can only hold N kg and want to fill it with as much gold value as possible.

## Greedy solution 1

Implement a solution using a greedy strategy. Fill the knapsack with
the most valuable gold bar regardless of weight until no longer
possible. Then fill the knapsack with the second most valuable gold bar and so on.

Initialize a map with the weight and values. 

```c++
  std::map<int, int> weight_and_values = {
    {16, 24},
    {19, 29},
    {15, 23},
    {14, 22},
    {13, 21},
    {17, 28},
  };
```

Print out the map contents in reverse order (iterate using rbegin()). 

#### In what order are the mapitems printed?

#### What is the underlying data structure std::map uses?

Implement a generic function *greedytake* that takes two set iterators, a
knapsackweight and returns a string with information on how much gold
you took, how much it weighs and which kind of gold bars were taken.
Use a stringstream to build your string answer.

```cpp
template <typename S>
string greedytake(S start, S end, int N) {
//...
   std::stringstream ss;
   int weight = start->first;
   int value  = start->second;
//...
   return ss.str();
```

Sample output
```
knappsacksize = 32 got value 50 = 1*29 + 1*21 used weight 32/32 =  1*19 + 1*13
knappsacksize = 50 got value 58 = 2*29 used weight 38/50 = 2*19
```


## Greedy solution 2

Another greedy solution would be to take the gold bars that have the most value/kg.
Use the previous function with a set of gold bars sorted on density.

Start by implementing a lambda function *densitycompare* that given two pairs of ints
(weight, value) returns if one pair is more valuable than the other.

```cpp
  std::function<bool(std::pair<int, int>, std::pair<int, int>)> 
    densitycompare = [] (pair(int, int //...
```

Then create and fill a set *valuedensities* with the previous weight and values using the comparison lambda function.

```cpp
  std::set<std::pair<int, int>, std::function<bool(std::pair<int, int>, std::pair<int, int>)> > 
	valuedensities(weight_and_values.begin(), weight_and_values.end(), densitycompare);
```

You can use a type definition of your lambda function to make your code a little more readable. 

```cpp
   typedef std::function<bool(std::pair<int, int>, std::pair<int, int>)> densitycomparefunction;
```

Call *greedytake* again with the *valuedensities* set. 

#### Which is the first knapsackweight where the second greedy solution is better than the first?

#### What is the difference between a std::set and a std::map?

#### What is the difference between a std::set and a std::unordered_set?


## dynamic programming solution

Implement a generic template function *dynamictake* that takes two set iterators and a knapsack maximum weight 
and returns a vector of optimal accumulated values and the latest added gold bar weight.

```cpp
template <class T>
vector< pair<int, int> > dynamictake(T begin, T end, int N) {
//...
```

Dynamic programming calculates the optimal solution by using already
calculated values.  Iterate over all knappsack weights from 1 to
N. For each knapsack weight iterate over *weight_and_values*
to find the optimal accumulated value. The first values would be.

| knappsackweight | accumulated value | gold bar weight |
| --- | --- | --- |
| 0 | 0 | 0 | 
| 1 | 0 | 0 | 
| 2 | 0 | 0 | 
| 3 | 0 | 0 | 
| 4 | 0 | 0 | 
| 5 | 0 | 0 | 
| 6 | 0 | 0 | 
| 7 | 0 | 0 | 
| 8 | 0 | 0 | 
| 9 | 0 | 0 | 
| 10 | 0 | 0 | 
| 11 | 0 | 0 | 
| 12 | 0 | 0 | 
| 13 | 21 | 13 | 
| 14 | 22 | 14 | 
| 15 | 23 | 15 | 
| 16 | 24 | 16 | 
| 17 | 28 | 17 | 
| 18 | 28 | 17 | 
| 19 | 29 | 19 | 
| 20 | 29 | 19 | 

For every new knappsackweight, iterate over *weight_and_values*. If
you add a particular gold bar you have the *knappsackweight* - *the
gold bars weight* left. Look up the accumulated value at that weight
and see if adding this gold bar would maximize the current accumulated value.

For instance att knappsackweight 26 you can put one gold bar
weighing 13. The already calculated accumulated gold at 13 is 21 thus
making the total accumulated gold 42. Putting any other heavier gold
bar would yield less.

| knappsackweight | accumulated value | gold bar weight |
| --- | --- | --- |
| 26 | 42 | 13 | 
| 27 | 43 | 14 | 
| 28 | 44 | 15 | 
| 39 | 63 | 13 | 
| 40 | 64 | 14 | 
| 41 | 65 | 15 | 
| 42 | 66 | 16 | 
| 43 | 70 | 17 | 

At knappsackweight 43 the optimal gold bar to put in weighs 17. 43 - 17 = 26. At knappsackweight 26 the optimal gold bar is 13. After which 13 remains. 
Thus at knappsackweight 43 the optimal solution is three gold bars 1*17 + 2*13 weighing 43 in total and accumlated value of 28+21+21=70.
 
#### Find five knappsack values where the optimal solution is equal to greedy solution 1

#### Find five knappsack values where the optimal solution is equal to greedy solution 2


You are free to implement any other functions you need. 
