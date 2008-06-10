CXX=g++
CXXFLAGS= -Wall -pedantic
SOURCES=src
LIBS=lib
TEST=test
LDLIBS=-lm
DEBUG=-g

all: dicpres

dicpres: utils.o lzw.o lz78.o
	@echo "### Programa principal ###"
	$(CXX) $(SOURCES)/dicpres.cpp $(LIBS)/utils.o $(LIBS)/lzw.o $(LIBS)/lz78.o -o $@ $(CXXFLAGS) $(LDLIBS) $(DEBUG)

test: test_lzw test_lz78 untest_lzw untest_lz78

test_lzw: utils.o lzw.o
	$(CXX) $(SOURCES)/test_lzw.cpp $(LIBS)/utils.o $(LIBS)/lzw.o -o $(TEST)/$@ $(CXXFLAGS) $(LDLIBS) $(DEBUG)

test_lz78: utils.o lz78.o
	$(CXX) $(SOURCES)/test_lz78.cpp $(LIBS)/utils.o $(LIBS)/lz78.o -o $(TEST)/$@ $(CXXFLAGS) $(LDLIBS) $(DEBUG)


untest_lzw: utils.o lz78.o
	$(CXX) $(SOURCES)/untest_lzw.cpp $(LIBS)/utils.o $(LIBS)/lzw.o -o $(TEST)/$@ $(CXXFLAGS) $(LDLIBS) $(DEBUG)


untest_lz78: utils.o lz78.o
	$(CXX) $(SOURCES)/untest_lz78.cpp $(LIBS)/utils.o $(LIBS)/lz78.o -o $(TEST)/$@ $(CXXFLAGS) $(LDLIBS) $(DEBUG)

utils.o:
	$(CXX) -c $(SOURCES)/utils.cpp -o $(LIBS)/$@ $(CXXFLAGS)

lzw.o:
	$(CXX) -c $(SOURCES)/lzw.cpp -o $(LIBS)/$@ $(CXXFLAGS)

lz78.o:
	$(CXX) -c $(SOURCES)/lz78.cpp -o $(LIBS)/$@ $(CXXFLAGS)

clean:
	$(RM) *~ $(TEST)/test_lzw $(TEST)/test_lz78 $(TEST)/untest_lz78 $(TEST)/untest_lzw $(LIBS)/*.o $(TEST)/*~ dicpres