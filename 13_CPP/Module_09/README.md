# CPP08

### Main topics:

```
File I/O, error handling, associative containers (different containers for each exercise)
```

## ex00 – BitcoinExchange
Read a CSV file containing historical Bitcoin prices and compute the USD value for given dates and amounts.
- I used `std::map<std::string, double>` to store the date as the key and the Bitcoin price as the value. This allows for efficient lookups based on dates.
- For file reading, I used `std::ifstream` to read both the CSV file and the input file line by line.
- I implemented error handling to manage invalid dates, negative values, and values exceeding 1000.
- The program parses each line of the input file, extracts the ***date*** and ***value*** (how many Bitcoins I have), looks up the corresponding Bitcoin ***price*** from the map (the closest previous date if the exact date is not found), and calculates the total USD ***value***.
- The output is formatted to show the ***date***, the ***amount*** of Bitcoin, and the calculated USD ***value***.


### The Calculation:
```
For line: "2011-01-02 | 3"

Step 1: Extract date and value
   date = "2011-01-02"
   value = 3

Step 2: Look up the Bitcoin price on that date from data.csv
   findPrice("2011-01-02") → searches the map
   Returns: 0.3 (Bitcoin was worth $0.30 on Jan 2, 2011)

Step 3: Calculate total USD value
   total_usd = exchange_rate × value
   total_usd = 0.3 × 3 = 0.9

Step 4: Output
   "2011-01-02 => 3 = 0.9"
   ↑                ↑   ↑
   date         your Bitcoins  total USD value
```


## ex01 – RPN
Implement a Reverse Polish Notation (RPN) calculator that evaluates expressions using a stack.
- I used `std::stack<int>` because its LIFO (Last In, First Out) structure is ideal for evaluating RPN expressions.
- For stack we need `push()`, `pop()`, and `top()` methods to manage operands and results.
- When we construct the RPN with argument, we parse the input string token by token (using `std::istringstream` which splits the string by spaces). After evaluating all tokens, there should be exactly one value left in the stack == the final _result.

### Example:
```
Input: "3 4 + 2 * 7 /"

Step 1: Push 3 onto the stack.					Stack: [3]
Step 2: Push 4 onto the stack.					Stack: [3, 4]
Step 3: Encounter '+',
        pop 4 and 3, compute 3 + 4 = 7,
        push 7 back onto the stack.				Stack: [7]
Step 4: Push 2 onto the stack.					Stack: [7, 2]
Step 5: Encounter '*',
        pop 2 and 7, compute 7 * 2 = 14,
        push 14 back onto the stack.			Stack: [14]
Step 6: Push 7 onto the stack.					Stack: [14, 7]
Step 7: Encounter '/',
        pop 7 and 14, compute 14 / 7 = 2,
        push 2 back onto the stack.				Stack: [2]
Final Result: 2
```


## ex02 – PmergeMe
OMG...

two good resources:
- [OG book (page 184 => 196)](https://seriouscomputerist.atariverse.com/media/pdf/book/Art%20of%20Computer%20Programming%20-%20Volume%203%20(Sorting%20&%20Searching).pdf)
- [Ford-Johnson Algorithm: Human Explanation & Visualisation](https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91)