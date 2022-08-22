CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := hashmap

EXTRA_FLAGS := $(EXTRA_FLAGS)  # command line flags
ifdef LINEAR_PROBING
EXTRA_FLAGS := $(EXTRA_FLAGS) -DLINEAR_PROBING
endif

CFLAGS := -std=c++17 -Wall -O3 $(EXTRA_FLAGS)  # -g

SOURCES := $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))

# library references
# LIB := -lboost_program_options

# include external sources (e.g. -I/usr/local/cuda/include)
INC := $()

run: $(TARGET)
	@echo "\033[1;37mRunning" $(TARGET) "\033[0m"; 
	./$(TARGET)

$(TARGET): $(OBJECTS)
	@echo "\033[1;37mLinking" $(TARGET) "\033[0m"
	$(CC) $^ -o $(TARGET) $(LIB)
	@echo "\033[1;37mCompiled successfully\033[0m"

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "\033[1;37mBuilding" $@ "\033[0m"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "\033[1;37mCleaning...\033[0m"; 
	$(RM) -r $(BUILDDIR) $(TARGET)


.PHONY: clean