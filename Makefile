# kiss - c++ makefile project #

# executable and directories
EXEC = plot
ODIR = obj

#compile and link flags
CXX    = g++ -std=c++14 -Wall
CFLAGS = -I./
LDFLAGS=-L.
LIBS   = -l:matplotpp.a -lGLU -lGL -lglut -lpthread

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

$(EXEC): $(OBJ)
	$(CXX) -o $(EXEC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LIBS) 

$(ODIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(ODIR) $(EXEC)

$(shell mkdir -p $(ODIR))
