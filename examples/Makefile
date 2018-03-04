# Makefile for test suits.
# Email: lijiansong@ict.ac.cn

# Targets
CONTAINER := container
OPERATOR := operator
TRAITS := traits
NDARRAY := ndarray

# Compiler
CXX := clang++

# Compiler flags
CXX_FLAGS := -std=c++11 -w

# Include directories
NANO_INC := ../third_party/
ND_INC := ../include

# Rules
ndarray_foo.o: ndarray_foo.cpp
	$(CXX) -I $(ND_INC) -I $(NANO_INC) $(CXX_FLAGS) -o $@ -c $<

container_foo.o: container_foo.cpp
	$(CXX) -I $(ND_INC) -I $(NANO_INC) $(CXX_FLAGS) -o $@ -c $<

operation_foo.o: operation_foo.cpp
	$(CXX) -I $(ND_INC) -I $(NANO_INC) $(CXX_FLAGS) -o $@ -c $<

traits_foo.o: traits_foo.cpp
	$(CXX) -I $(ND_INC) -I $(NANO_INC) $(CXX_FLAGS) -o $@ -c $<

ndarray: ndarray_foo.o
	$(CXX) -o $(NDARRAY) $+

traits: traits_foo.o
	$(CXX) -o $(TRAITS) $+

operation: operation_foo.o
	$(CXX) -o $(OPERATOR) $+

container: container_foo.o
	$(CXX) -o $(CONTAINER) $+

clean:
	@rm -rf *.ll
	@rm -rf *.o
	@rm -rf $(CONTAINER)
	@rm -rf $(NDARRAY)
	@rm -rf $(OPERATOR)
	@rm -rf $(TRAITS)
