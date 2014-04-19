.PHONY: print run all

FILE = mpi_example.c
PROG_NAME = prog
PROC = 1

all: build run

build:
	@mpicc $(FILE) -o $(PROG_NAME)

run:
	@echo "You run $(PROC) process"
	@mpirun -n $(PROC) ./$(PROG_NAME)

print:
	@echo "File        = $(FILE)"
	@echo "PROG_NAME   = $(PROG_NAME)"
	@echo "NUMBER_PROC = $(PROC)"

clean:
	rm -f $(PROG_NAME)

rebuild: clean build
