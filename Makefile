CC		:= gcc
C_FLAGS := -g -Wall -Wextra -std=c11 -pthread

LIBRARIES	:= -lm

EXECUTABLE1	:= matrixmult_process.out
EXECUTABLE2	:= matrixmult_thread.out

all: $(EXECUTABLE1) $(EXECUTABLE2)

clean:
	-$(RM) $(EXECUTABLE1) $(EXECUTABLE2)

run: all
	./$(EXECUTABLE1) ./$(EXECUTABLE2)

$(EXECUTABLE1): matrixmult_process.c
	$(CC) $(C_FLAGS) $^ -o $@ $(LIBRARIES)

$(EXECUTABLE2): matrixmult_thread.c
	$(CC) $(C_FLAGS) $^ -o $@ $(LIBRARIES)