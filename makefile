main:main.o tools.o gtk_pubfun.o
	g++ -g -o main `pkg-config --cflags --libs gtk+-2.0` -export-dynamic main.o tools.o gtk_pubfun.o
main.o:main.cpp
	g++ -c -g -o main.o `pkg-config --cflags --libs gtk+-2.0` -export-dynamic main.cpp
tools.o:tools.cpp
	g++ -c -g -o tools.o `pkg-config --cflags --libs gtk+-2.0` -export-dynamic tools.cpp 
gtk_pubfun.o:gtk_pubfun.cpp
	g++ -c -g -o gtk_pubfun.o `pkg-config --cflags --libs gtk+-2.0` -export-dynamic gtk_pubfun.cpp
clean:
	rm -f *.o main *~
