EXEC = dijkstra
CC = g++
CFLAGS = -c -Wall

$(EXEC):main.o util.o heap.o graph.o node.o vertex.o
	$(CC) -o $(EXEC) main.o util.o heap.o graph.o node.o vertex.o

main.o:main.cpp
	$(CC) $(CFLAGS) main.cpp

util.o:util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

heap.o:heap.h heap.cpp
	$(CC) $(CFLAGS) heap.cpp

graph.o:graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp

node.o:node.h node.cpp
	$(CC) $(CFLAGS) node.cpp

vertex.o:vertex.h vertex.cpp
	$(CC) $(CFLAGS) vertex.cpp

clean:
	rm *.o output