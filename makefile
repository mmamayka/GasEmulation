# linker flags
LDFLAGS := -lm -lsfml-graphics -lsfml-window -lsfml-system -pg

# compiler flags
CFLAGS  := -O2 -march='skylake' -msse3 -msse2 -msse -mfma  \
	 -std=c++20 -fno-stack-protector -msse4.1 -msse4.2 -mssse3 \
	 -mavx -mavx2 -mno-vzeroupper -pg
	 #-mno-vzeroupper

# used compiler
CC      := g++

# path to doxygen generated docs
DOCPATH := doc-html

# object files path
OBJPATH := obj

# source path
SRCPATH := src

# binary path
BINPATH := bin

# binary name
BINNAME := gas-simulation

# doxygen config name
DOXCONF := doxygen

# build project and documentation
run: build 
	./$(BINPATH)/$(BINNAME)

# build project only
build: $(BINPATH)/$(BINNAME)

# build documentation only
doc: $(DOCPATH)

# cleanup the project (remove object, binary and documentation files)
clean:
	-rm -rf $(OBJPATH)/*
	-rm -rf $(BINPATH)/*
	-rm -rf $(DOCPATH)/*

# dirty magic section

_CFILES := $(wildcard $(SRCPATH)/*.cpp)
_HFILES := $(wildcard $(SRCPATH)/*.hpp)
_OFILES := $(patsubst $(SRCPATH)/%.cpp, $(OBJPATH)/%.o, $(_CFILES))
_DFILES := $(patsubst $(SRCPATH)/%.cpp, $(OBJPATH)/%.d, $(_CFILES))

# TODO: fix dublication
ifneq ($(filter run build, $(MAKECMDGOALS)),)
include $(_DFILES)
endif

ifeq ($(MAKECMDGOALS), )
include $(_DFILES)
endif

$(DOCPATH): $(_CFILES) $(_HFILES)
	doxygen $(DOXCONF)

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJPATH)/%.d: $(SRCPATH)/%.cpp
	$(CC) -MM $< | sed 's/.*:/$(OBJPATH)\/$*.o $(OBJPATH)\/$*.d:/g' > $@

$(BINPATH)/$(BINNAME): $(_OFILES)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: all clean doc build

