CXX=g++
LD=g++

LIBS=-lGL -lGLU -lglut -lopencv_core -lopencv_features2d -lopencv_flann \
-lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml \
-lopencv_objdetect -lopencv_video

CXXFLAGS:=-fpermissive
CXXFLAGS+=$(FLAGS)
CXXFLAGS+=$(LIBS)

OUT=arkanoid

.PHONY: all
all:
	$(CXX) $(CXXFLAGS) -c *.cpp
	$(LD) $(CXXFLAGS) -o $(OUT) *.o

.PHONY: clean
clean:
	rm *.o
	rm $(OUT)
