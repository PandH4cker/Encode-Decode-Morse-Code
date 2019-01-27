CC = gcc
EXEC = EncodeDecodeMorseCode

EncodeDecodeMorseCode:main.o morseDecypher.o graphic.o
	$(CC) -o $(EXEC) main.o morseDecypher.o graphic.o -lSDL2 -lSDL2_image -lSDL2_ttf -std=c99
	./$(EXEC) --help

main.o:main.c ../headers/morse.h ../headers/graphic.h
	$(CC) -o main.o -c main.c -std=c99

morseDecypher.o:morseDecypher.c ../headers/morse.h
	$(CC) -o morseDecypher.o -c morseDecypher.c -std=c99

graphic.o:graphic.c ../headers/graphic.h
	$(CC) -o graphic.o -c graphic.c -std=c99

clean:
	rm -rf *.o

mrproper:clean
	rm -rf $(EXEC)
