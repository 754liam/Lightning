all:
	g++ -o main engine/matcher.cpp engine/orderbook.cpp tests/functionality.cpp -I engine

clean:
	rm -f main