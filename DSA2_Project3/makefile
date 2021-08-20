useDijktra.exe: useDijktra.o dijkstra.o heap.o hash.o
	g++ -o useDijktra.exe useDijktra.o dijkstra.o heap.o hash.o

useDijktra.o: useDijktra.cpp dijkstra.h
	g++ -c useDijktra.cpp 

dijkstra.o: dijkstra.cpp dijkstra.h
	g++ -c dijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

debug:
	g++ -g -o useDijktraDebug.exe useDijktra.cpp dijkstra.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups