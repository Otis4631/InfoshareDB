main:main.o libtools.so ./bin/tools.o ./bin/gtk_pubfun.o
	g++ -g -o main -L /lib64/ -ltools `pkg-config --cflags --libs gtk+-2.0` -export-dynamic bin/main.o
main.o:main.cpp
	g++ -c -g -o bin/main.o `pkg-config --cflags --libs gtk+-2.0` -export-dynamic main.cpp
tools.o:tools.cpp
	g++ -c -g tools.cpp -fPIC  -o bin/tools.o `pkg-config --cflags --libs gtk+-2.0` -export-dynamic
gtk_pubfun.o:gtk_pubfun.cpp
	g++ -c -g -o bin/gtk_pubfun.o `pkg-config --cflags --libs gtk+-2.0` -export-dynamic gtk_pubfun.cpp -fPIC
libtools.so:tools.o gtk_pubfun.o
	g++ -shared -fPIC -o lib/libtools.so bin/tools.o bin/gtk_pubfun.o
	cp lib/libtools.so /lib64
clean:
	rm -f bin/*.o main *~

