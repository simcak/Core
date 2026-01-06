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


### The Calculation
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