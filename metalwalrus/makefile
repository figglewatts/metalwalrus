IDIR = include
SDIR = Src
CC = g++
CFLAGS = -I$(IDIR) -Wall -std=c++11

ODIR = obj
LDIR = lib

BUILDDIR = build

ASSETDIR = assets

LIBS = -lglut -lGL -lGLU -lGLEW -lm

DEPS := $(shell find $(IDIR) -name '*.h')

SOURCES := $(shell find $(SDIR) $(LDIR) -name '*.cpp')

OBJECT_FILES = $(SOURCES:%.cpp=$(ODIR)/%.o)

MKDIR_P = mkdir -p

# OBJ = $(addprefix $(ODIR)/, $(notdir $(SOURCES:%.cpp=%.o)))

.PHONY: clean directories

all: metalwalrus
	@echo Copying assets...
	@mkdir -p $(BUILDDIR)/$(ASSETDIR)
	cp -a $(ASSETDIR)/. $(BUILDDIR)/$(ASSETDIR)
	@echo Build success!

metalwalrus: $(OBJECT_FILES)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/metalwalrus $^ $(LIBS) -L$(LDIR)

$(OBJECT_FILES): $(ODIR)/%.o: %.cpp $(DEPS)
	@echo Compiling $<
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f metalwalrus
	rm -rf $(BUILDDIR)
	find $(ODIR) -type f -name '*.o' -delete