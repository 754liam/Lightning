# Lightning

## Lightning - a high performance limit order book. 
Lightning is a phenomenon in nature consisting of electrostatic discharges occuring through the atmosphere between two electrically charged regions. I, as many others, have seen lightning - when lightning strikes down from the sky (or up from the ground), it sometimes branches out... taking on a sort of tree-like appearance. Why? Because it seeks the path of least resistance through the air. Similarly, an order book is all about paths of least resistance. A buyer seeks a seller willing to sell for the lowest price, and a seller seeks a buyer willing to buy for the highest price. You can consider any such buyer or seller as lightning: looking for the path of least resistance, or largest gain, for themselves. 


![alt text](images/image.png)

Source: https://www.cboe.com/us/equities/market_statistics/book/aapl/


## Building
mkdir build && cd build

Configure: cmake .. && make

Sanitized: cmake -DCMAKE_CXX_FLAGS="-fsanitize=undefined,address" .. && make

First configure downloads Google Test and Benchmark; it may take a minute.

Rebuild after code change (from inside /build): make

./lightning inside /build to run the server (reads commands from stdin).

Example:
```
CREATE_ACCOUNT 1 5 500
LIMIT_BUY 1 4 3
CREATE_ACCOUNT 2 10 1000
LIMIT_SELL 2 2 10
GET_ACCOUNT 2
QUIT
```

./lightning_tests inside /build to run unit tests.

./lightning_benchmarks inside /build to run benchmarks.