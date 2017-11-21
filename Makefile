# Makefile wildcards based on example from
# https://stackoverflow.com/questions/7004702/how-can-i-create-a-makefile-for-c-projects-with-src-obj-and-bin-subdirectories
EXE=project
SRCDIR=src
OBJDIR=obj

# Main target
all: $(EXE)

# MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32 -lstdc++ -lSDL -lSDL_image -lSDL_mixer
CLEAN=del *.exe $(OBJDIR)\\*.o 
SRCFILES=$(wildcard $(SRCDIR)\\*.cpp)
OBJECTS=$(SRCFILES:$(SRCDIR)\\%.cpp=$(OBJDIR)\\%.o)
$(OBJECTS) : $(OBJDIR)\\%.o: $(SRCDIR)\\%.cpp
	g++ -c $(CFLG) $(LIBS) -o $@ $<
else
# OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL -lstdc++ -lSDL -lSDL_image -lSDL_mixer
SRCFILES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(SRCFILES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
$(OBJECTS) : $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -c $(CFLG) $(LIBS) -o $@ $<
else
# Linux/Unix/Solaris
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm -lstdc++ -lSDL -lSDL_image -lSDL_mixer
SRCFILES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(SRCFILES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
$(OBJECTS) : $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -c $(CFLG) $(LIBS) -o $@ $<
endif
CLEAN=rm -f $(EXE) $(OBJDIR)/*.o
endif


# Link
project: $(OBJECTS)
	gcc -O3 -o $@ $^ $(LIBS)

# Clean
clean:
	$(CLEAN)
