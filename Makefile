CC := g++
CFLAGS := -Wall -Wextra -Wcast-align -Wfloat-equal -Wpointer-arith -Wshadow -Wundef -O2 -fstack-protector -DCUBE_WIDTH=5 -DTEST_NOTEENSY
LIBS :=

ZIP := zip
ZIPOUT := libledcube.zip

SOURCEDIR := .

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
HEADERS := $(shell find $(SOURCEDIR) -name '*.h')
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

.PHONY: all zip clean

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXENAME) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCEDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

zip:
	$(ZIP) $(ZIPOUT) $(SOURCES) $(HEADERS) readme.txt

clean:
	@rm $(OBJECTS)
	@rm $(ZIPOUT)
