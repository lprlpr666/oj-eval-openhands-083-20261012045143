all:
	g++ -std=c++17 -O2 -o code main.cpp

clean:
	rm -f code

.PHONY: all clean