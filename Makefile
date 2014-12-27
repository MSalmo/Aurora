CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lX11 -pthread

clean:
	rm *.o

Aurora: Aurora.o 
	$(CC) Aurora -o Aurora.o DesktopManager.o $(LDFLAGS)

Aurora.o: Aurora.cpp DesktopManager.cpp
	$(CC) $(CFLAGS) Aurora Aurora.cpp DesktopManager.cpp

