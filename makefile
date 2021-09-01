# Name of the project
PROJ_NAME=genetic_algorithm
 
# .cpp files
CPP_SOURCE=$(wildcard ./source/*.cpp)
 
# .hpp files
HPP_SOURCE=$(wildcard ./header/*.hpp)
 
# Object files
OBJ=$(subst .cpp,.o,$(subst source,objects,$(CPP_SOURCE)))
 
# Compiler
CC=g++
 
# Flags for compiler
CC_FLAGS=-c                    \
         -g                    \
		 -I                    \
         -Wall                 \
		 -Wextra               \
		 -Wshadow              \
		 -Wundef               \
		 -Wformat=2            \
		 -Wfloat-equal         \
		 -Wcast-align          \
		 -std=c++17            \
		 -march=native         \
		 -O3                   #\
		 -#Wdouble-promotion   \
		 -#Wformat-truncation   \
		 -#Wstrict-prototypes   \
		 -#Wconversion          \
		 -#Wunreachable-code   

# Libraries
LIBS=-lm 

#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^
 
./objects/%.o: ./source/%.cpp ./header/%.hpp
	$(CC) -o $@ $< $(CC_FLAGS)
 
./objects/main.o: ./source/main.cpp $(HPP_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS) $(LIBS)

objFolder:
	@ mkdir -p objects

.PHONY: run

run:
	./$(PROJ_NAME)

.PHONY: debug

debug:
	gdb ./$(PROJ_NAME)

.PHONY: clean

clean:
	@ rm -rf ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects


