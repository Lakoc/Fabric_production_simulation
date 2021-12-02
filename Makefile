CC = g++
CPPFLAGS = -std=c++1z -g -O0 #-O2 #-pedantic -Wall # change -O0 to -O2
LDFLAGS  = -lsimlib -lm
FILES = \
	src/main.cc \
	src/model.cc \
	src/factory.cc \
	src/warpGenerator.cc \
	src/warp.cc \
	src/constants.cc \
	src/stats.cc \

FILES_MAX = \
	src/main.cc \
	src/model.cc \
	src/factory.cc \
	src_max/warpGenerator.cc \
	src/warp.cc \
	src/constants.cc \
	src/stats.cc \


FILES_NON_STOP = \
	src/main.cc \
	src/model.cc \
	src/factory.cc \
	src_nonstop/warpGenerator.cc \
	src/warp.cc \
	src/constants.cc \
	src/stats.cc \


.PHONY: all model

all: model

model:
	$(CC) $(CPPFLAGS) -o model $(FILES) $(LDFLAGS)

run: clean model
	./model $(X) $(U)

max:
	$(CC) $(CPPFLAGS) -o model $(FILES_MAX) $(LDFLAGS)

nonstop:
	$(CC) $(CPPFLAGS) -o model $(FILES_NON_STOP) $(LDFLAGS)

clean:
	rm -f *.dat
