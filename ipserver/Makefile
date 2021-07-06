CC=gcc
CPP=g++

SOURCE_DIR = 

SOURCE = $(wildcard $(addsuffix /*.c,$(SOURCE_DIR)))
SOURCE += $(wildcard $(addsuffix /*.cpp,$(SOURCE_DIR)))
HEADER = $(wildcard $(addsuffix /*.h,$(SOURCE_DIR)))

LDFLAGS= -lm -lpthread
LIBRALY_PATH = -L../lib/collection_class/ -lcollection_class
INCLUDE_PATH = -I../lib/collection_class/
CFLAGS = -Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

OBJ = $(addsuffix .o,$(basename $(SOURCE)))

$(info SOURCE = $(SOURCE))
$(info OBJ = $(OBJ))
$(info HEADER = $(HEADER))

all: main.out

main.out: main.o $(OBJ) $(HEADER) Makefile
	$(CPP) $(INCLUDE_PATH) $(CFLAGS) $(OBJ) main.o $(LIBRALY_PATH) $(LDFLAGS) -o $@ 

%.o: %.cpp $(HEADER) Makefile
	$(CPP) $(INCLUDE_PATH) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER) Makefile
	$(CC) $(INCLUDE_PATH) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf main.out $(OBJ)
