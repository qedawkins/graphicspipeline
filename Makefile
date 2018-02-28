CXXFLAGS=-Wall -std=c++11
CXX=clang++
DEBUG=-Wall -g
OFILES=frame.o physicspipeline.o graphicspipeline.o main.o
.SUFFIXES: .o .cpp
.PHONY: clean

test: $(OFILES)
	$(CXX) $(DEBUG) $(OFILES) -o test -pthreads
	-rm -f *.o

clean:
	-rm -f *.o *~
