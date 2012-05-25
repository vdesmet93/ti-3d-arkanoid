CXX=g++
LD=g++

LIBS=-lGL -lGLU -lglut

OUT=arkanoid

.PHONY: all
all:
	$(CXX) $(LIBS) -c *.cpp
	$(LD) $(LIBS) -o $(OUT) *.o

.PHONY: clean
clean:
	rm *.o
	rm $(OUT)
