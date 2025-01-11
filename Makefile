PROGRAM = caca-palavras

CC = gcc

C_SOURCES = ./*.c

C_FLAGS = -std=c11 -Wall -pedantic

run:
	$(CC) $(C_FLAGS) $(C_SOURCES) -o $(PROGRAM)
	./$(PROGRAM)
