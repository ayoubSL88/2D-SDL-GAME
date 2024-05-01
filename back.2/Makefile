# Règle de construction de l'exécutable
prog: main.o entity.o
	gcc main.o entity.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

# Règle de compilation pour main.o
main.o: main.c entity.h
	gcc -c main.c

# Règle de compilation pour entity.o
entity.o: entity.c entity.h
	gcc -c entity.c
# Règle de compilation pour back.o
back.o: back.c back.h
	gcc -c back.c

# Règle de dépendance pour back.c
back.c: back.h


