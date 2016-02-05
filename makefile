# Find out if we running windows
UNAME = $(shell uname -o)
ifeq ($(OS),Windows_NT)
	EXEEXT = .exe
	COMPILE_OPT = -lopengl32 -lglu32 -lfreeglut -Wl,--subsystem,windows
else
	COMPILE_OPT = -lGL -lglut -lGLU
endif

# TESTS = sample1_unittest

# #############################TEST section##################

# GTEST_DIR = gtest-1.7.0
# USER_DIR = .

# GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
#                 $(GTEST_DIR)/include/gtest/internal/*.h
# GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# CPPFLAGS += -isystem $(GTEST_DIR)/include
# CXXFLAGS += -g -Wall -Wextra -pthread





all: main $(TESTS)

test: $(TESTS)
main: bullet.o main.o utils.o lodepng.o game.o plane.o
	g++ main.o utils.o lodepng.o game.o bullet.o plane.o $(COMPILE_OPT) -o main
main.o: main.cpp
	g++ -c main.cpp
utils.o: utils.cpp
	g++ -c utils.cpp
lodepng.o: lodepng.cpp
	g++ -c lodepng.cpp
game.o: game.cpp
	g++ -c game.cpp
bullet.o: bullet.cpp
	g++ -c bullet.cpp	
plane.o: plane.cpp
	g++ -c plane.cpp
run:
	./main

ifeq ($(UNAME), Msys)
	EXEEXT = .exe
endif

#Do not touch - Internal Gtest targets
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

sample1.o : sample1.cc sample1.h $(GTEST_HEADERS)
	g++ $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1.cc

sample1_unittest.o : sample1_unittest.cc sample1.h $(GTEST_HEADERS)
	g++ $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1_unittest.cc

sample1_unittest : sample1.o sample1_unittest.o gtest_main.a
	g++ $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


clean:
	rm *.o main$(EXEEXT)
# $(TESTS)$(EXEEXT) gtest_main.a
