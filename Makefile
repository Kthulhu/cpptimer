CXX ?=
CXX_FLAGS = -std=c++14 -O3
tests = tests/test

all: $(tests)
.PHONY: all

$(tests): %: %.cpp timer.hpp
	$(CXX) $(CXX_FLAGS) -I"./" $< -o $@

clean:
	rm $(tests)
