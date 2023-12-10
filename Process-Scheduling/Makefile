# Define source and build directories
scheduling_policies_source = algorithms/source
scheduling_policies_build = algorithms/build

# Define sources and corresponding targets
sources := $(wildcard ${scheduling_policies_source}/*.c)
targets := $(patsubst ${scheduling_policies_source}/%.c, ${scheduling_policies_build}/%, $(sources))

# Default target
all: main scheduling_policies_executables

# Compile source files to executables
scheduling_policies_executables: ${targets}

${scheduling_policies_build}/%: ${scheduling_policies_source}/%.c
	gcc $< -o $@

# Set permissions
permissions:
	chmod 755 algorithms
	chmod 755 main.c
	chmod 755 process.h
	chmod 755 Makefile
	chmod 755 params.txt

# Compile main program
main: main.c
	gcc main.c -o main
input_generator:
	gcc -o inputGenerator inputGenerator.c
	./inputGenerator
# Clean build files
clean:
	rm -rf ${scheduling_policies_build}/*

# Run the program
run: all
	./main params.txt
