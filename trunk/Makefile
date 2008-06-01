CXX=g++
CXXFLAGS= -Wall -pedantic
SOURCES=src
LIBS=lib
LDLIBS=-lm
DEBUG=-g

test_lzw: utils.o lzw.o
	$(CXX) test_lzw.cpp utils.o lzw.o -o $@ $(CXXFLAGS) $(LDLIBS) $(DEBUG)

test_lz78: utils.o lz78.o
	$(CXX) test_lzw.cpp utils.o lzw.o -o $@ $(CXXFLAGS) $(LDLIBS) $(DEBUG)

utils.o:
	$(CXX) -c utils.cpp $(CXXFLAGS)

lzw.o:
	$(CXX) -c lzw.cpp $(CXXFLAGS)

lz78.o:
	$(CXX) -c lz78.cpp $(CXXFLAGS)

clean:
	$(RM) -f *~ test_lzw *.o