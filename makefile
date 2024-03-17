objFile: 
	g++ main.c intro.c `pkg-config --cflags gtk+-3.0` -o test.o `pkg-config --cflags --libs opencv4` `pkg-config --libs gtk+-3.0 opencv4` -lopencv_imgcodecs

run: objFile
	./test.o
