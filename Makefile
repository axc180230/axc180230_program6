# Angel Castaneda
# Email: axc180230@utdallas.edu
# Course SE 3377.501
# Makefile with Dependencies


# Set up info for C++ implicit rule
CXX = g++
CXXFLAGS = -Wall -g -Wno-write-strings
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

# Project name (for backup)
PROJECTNAME = program6

# Source Files
SRCS = binread.cc #cdk.cc

# Name of the executable
EXEC = Program6

# You normally don't need to change anything below here.
# ======================================================

# Substitution of .cc into .o files
OBJS = $(SRCS:.cc=.o)

# Phony files to ignore if they exist
.Phony: all clean backup

# Rebuilds exe and all supporting files
all: $(EXEC)

# Removes object, dependency, emacs back up, 
# recoevery files, and executable
clean:
	rm -f $(OBJS) *.d *~ \#* $(EXEC)

# Where the magic happens
Makefile: $(SRCS:.cc=.d)

# Pattern for .d (dependency) files
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Rule to link files
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) $(LDLIBS)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

# Include the dependency files
-include $(SRCS:.cc=.d)
