CC := g++
SRCDIR := src
BUILDDIR := build
HANDLERDIR := $(BUILDDIR)/handling
TARGET := bin/run

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -std=c++14
INC := -I include
LFLAGS := -lcurses

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $^ -o $(TARGET)"; $(CC) $^ -o $(TARGET) $(LFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(HANDLERDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
