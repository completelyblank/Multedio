objFile: 
	g++ -w main.c preset.c intro.c station.c upload.c slider.c getStarted.c brightness.c exposure.c tint.c vignette.c noiseReduction.c colorGrading.c crop.c temperature.c batch.c continue.c `pkg-config --cflags gtk+-3.0` -o test.o `pkg-config --cflags --libs opencv4` `pkg-config --libs gtk+-3.0 opencv4` -lopencv_imgcodecs

run: objFile
	./test.o
