prog:main.o Personne.o enemy.o minimap.o
	gcc main.o Personne.o enemy.o minimap.o -o prog -lSDL -lSDL_image -lSDL_ttf

main.o: main.c
	gcc -c main.c -g
personne.o: Personne.c 
	gcc -c personne.c -g 
enemy.o: enemy.c 
	gcc -c enemy.c -g 
minimap.o:minimap.c
	gcc -c minimap.c -g 



