CC = clang++
FLAGS = -Wextra -Wall
OBJ = main.o database.o
LIB = sqlite3
BINARY = output

build: ${OBJ}
	${CC} ${OBJ} -l ${LIB} -o ${BINARY}

main.o: main.cpp
	${CC} ${flags} -c main.cpp

database.o: database.cpp
	${CC} ${flags} -c database.cpp

clean:
	@echo "Cleaning Executables ..."
	rm ${OBJ} ${BINARY}

clean_all:
	@echo "Clean Slate..."
	rm ${OBJ} ${BINARY} *.db
