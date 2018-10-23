# Makefile for test suits.
# Email: lijiansong@ict.ac.cn

# Targets
CONTAINER := container
OPERATOR := operation
TRAITS := traits
NDARRAY := ndarray
VECTOR := vector
TEST_ALL := test_all
FOO := foo

# Compiler
#CXX := clang++
CXX := g++

# Compiler flags
CXX_FLAGS := -std=c++11 -w
DEBUG_FLAGS := SEPARATE_TEST

# Include directories
ND_INC := ../include

# Boost unit test library
BOOST_LIB := -lboost_unit_test_framework

# Rules
test: ndarray_foo.o vector_foo.o traits_foo.o operation_foo.o container_foo.o test_all.o
	$(CXX) -o $(TEST_ALL) $+ $(BOOST_LIB)

ndarray: CXX_FLAGS += -D$(DEBUG_FLAGS)
ndarray: ndarray_foo.o
	$(CXX) -o $(NDARRAY) $+ $(BOOST_LIB)

vector: CXX_FLAGS += -D$(DEBUG_FLAGS)
vector: vector_foo.o
	$(CXX) -o $(VECTOR) $+ $(BOOST_LIB)

traits: CXX_FLAGS += -D$(DEBUG_FLAGS)
traits: traits_foo.o
	$(CXX) -o $(TRAITS) $+ $(BOOST_LIB)

operation: CXX_FLAGS += -D$(DEBUG_FLAGS)
operation: operation_foo.o
	$(CXX) -o $(OPERATOR) $+ $(BOOST_LIB)

container: CXX_FLAGS += -D$(DEBUG_FLAGS)
container: container_foo.o
	$(CXX) -o $(CONTAINER) $+ $(BOOST_LIB)

foo: foo.o
	$(CXX) -o $(FOO) $+

test_all.o: test_all.cpp
	$(CXX) -I $(ND_INC) $(CXX_FLAGS) -o $@ -c $<

ndarray_foo.o: ndarray_foo.cpp
	$(CXX) -I $(ND_INC) $(CXX_FLAGS) -o $@ -c $<

vector_foo.o: vector_foo.cpp
	$(CXX) -I $(ND_INC) $(CXX_FLAGS) -o $@ -c $<

foo.o: foo.cpp
	$(CXX) -I $(ND_INC) $(CXX_FLAGS) -o $@ -c $<

container_foo.o: container_foo.cpp
	$(CXX) -I $(ND_INC) $(CXX_FLAGS) -o $@ -c $<

operation_foo.o: operation_foo.cpp
	$(CXX) -I $(ND_INC) $(CXX_FLAGS) -o $@ -c $<

traits_foo.o: traits_foo.cpp
	$(CXX) -I $(ND_INC) $(CXX_FLAGS) -o $@ -c $<

clean:
	@rm -rf *.ll
	@rm -rf *.s
	@rm -rf *.o
	@rm -rf $(CONTAINER)
	@rm -rf $(NDARRAY)
	@rm -rf $(VECTOR)
	@rm -rf $(OPERATOR)
	@rm -rf $(TRAITS)
	@rm -rf $(TEST_ALL)
	@rm -rf $(FOO)
