# target
EXE=snek3

# main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW -I/mingw64/include/opencv4
LIBS=-lopencv_videoio -lopencv_core -lglfw3 -lglew32 -lglu32 -lopengl32 -lm -std=c++2a -pthread
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations  -DUSEGLEW -I/usr/include/opencv4
LIBS=-lopencv_videoio -lopencv_core -lglfw -lglew -framework Cocoa -framework OpenGL -framework IOKit -std=c++2a -pthread
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall -I/usr/include/opencv4
LIBS=-lopencv_videoio -lopencv_core -lglfw -lGLU -lGL -lm -std=c++2a -pthread
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

window/window.a:
	cd window && $(MAKE)

main.o: main.cpp window/window.hpp player.hpp
player.o: player.cpp player.hpp gameobject.hpp

.cpp.o:
	g++ -c $(CFLG) -I /usr/include/opencv4 $<

snek3:main.o player.o window/window.a
	g++ $(CFLG) -o $@ $^ $(LIBS)

# Clean
clean:
	cd window && $(CLEAN)
	$(CLEAN)