CC := g++
CFLAGS := -Wall -Wextra -Wcast-align -Wfloat-equal -Wpointer-arith -Wundef -O2 -fstack-protector -DCUBE_WIDTH=5 -DCHARMAP_COMPRESSED
LIBS := -L../../ -lledcube

EXENAME := terminal_test

SOURCEDIR := .

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

.PHONY: all clean

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXENAME) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCEDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	@rm $(OBJECTS)
