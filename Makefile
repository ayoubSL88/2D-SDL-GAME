prog: mainm.o functions.o option.o
	gcc mainm.o functions.o option.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
	

main.o: mainm.c
	gcc -c main m.c

functions.o: functions.c
	gcc -c functions.c
option.o: option.c
	gcc -c option.c

clean:
	rm -f *.o prog
