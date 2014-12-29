CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lX11 -pthread

Aurora: Aurora.o DesktopManager.o
	$(CC) -o Aurora Aurora.o DesktopManager.o $(LDFLAGS)
Aurora.o: Aurora.cpp DesktopManager.cpp
	$(CC) $(CFLAGS) Aurora.cpp ${LDFLAGS}
DesktopManager.o: DesktopManager.cpp
	$(CC) $(CFLAGS) DesktopManager.cpp ${LDFLAGS}
clean:
	rm *.o
	rm Aurora
