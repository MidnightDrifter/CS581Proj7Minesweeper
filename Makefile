PRG=gnu.exe
OSTYPE := $(shell uname)
ifeq ($(OSTYPE),Linux)
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

GCC=g++
GCCFLAGS=-O2 -Wall -Wextra -std=c++11 -pedantic -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder
DEFINE=-DINLINE_FIELD

VALGRIND_OPTIONS=-q --leak-check=full
DIFF_OPTIONS=-y --strip-trailing-cr --suppress-common-lines

OBJECTS0=field.cpp analyzer.cpp
DRIVER_ONLINE=driver-online.cpp

demo driver1 driver2 driver3:
	g++  $@.cpp $(OBJECTS0) $(GCCFLAGS) $(GCCOPTIMIZE) $(INCLUDE) $(DEFINE) -o $@.exe

#for online
gcc0:
	g++ $(DRIVER_ONLINE) $(OBJECTS0) $(GCCFLAGS) $(DEFINE) -o $(PRG)
0 1 2 3 4 5 6 7:
	@echo "should run in less than 6000 ms"
	./$(PRG) $@ >studentout$@
	@echo "lines after the next are mismatches with master output -- see out$@"
	diff out$@ studentout$@ $(DIFF_OPTIONS)
clean:
	rm -f *.exe *.o *.obj
