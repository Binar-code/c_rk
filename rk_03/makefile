FLAGS := -Wall -Werror

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

.PHONY: build run clean obj

build: obj
	gcc $(FLAGS) -std=gnu99 -o app.exe $(OBJ)
obj:
	gcc $(FLAGS) -c $(SRC)
run : build
	./app.exe
clean:
	find . -type f -name "*.exe" -delete
	find . -type f -name "*.o" -delete
	find . -type f -name "out.txt" -delete
