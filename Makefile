
SRC = main.cpp
CMPOBJ = ./a.out

start: cmp
	$(CMPOBJ)

cmp:
	g++ $(SRC) -O2