CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra -pedantic

COMMON_OBJECTS = Person.o
MANAGER_OBJECTS = Person.o StudentManager.o
GENERATOR_OBJECTS = StudentFileGenerator.o
PROGRAMS = students processor generate_students container_benchmark strategy_benchmark

.PHONY: all clean

all: $(PROGRAMS)

students: main.cpp $(MANAGER_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

processor: processor_main.cpp $(MANAGER_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

generate_students: generator_main.cpp $(GENERATOR_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

container_benchmark: container_benchmark.cpp $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

strategy_benchmark: strategy_benchmark.cpp $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

Person.o: Person.cpp Person.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

StudentManager.o: StudentManager.cpp StudentManager.h Person.h StudentException.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

StudentFileGenerator.o: StudentFileGenerator.cpp StudentFileGenerator.h StudentException.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAMS) *.o
