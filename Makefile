CC := g++
CFLAGS := -Wall -Wextra -Wcast-align -Wfloat-equal -Wpointer-arith -Wshadow -Wundef -O2 -fstack-protector -DCUBE_WIDTH=5 -DTEST_NOTEENSY
LIBS :=

LIBNAME := ledcube
LIBFILE := lib$(LIBNAME).a

ZIP := zip
ZIPFILE := libledcube.zip

SOURCEDIR := .

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
HEADERS := $(shell find $(SOURCEDIR) -name '*.h')
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))

.PHONY: all zip clean

all: $(OBJECTS)
	ar rcs $(LIBFILE) $(OBJECTS)

$(OBJECTS): $(SOURCEDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

zip:
	$(ZIP) -r $(ZIPFILE) $(SOURCES) $(HEADERS) examples/* keywords.txt readme.txt

clean:
	-@rm $(OBJECTS)
	-@rm $(ZIPFILE)
	-@rm $(LIBFILE)
