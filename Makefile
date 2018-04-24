# Name - Vishnu Kunadharaju
# Course Number - 3377
# Section Number - 501 
# HMWK - 6

CXX = g++
CXXFLAGS = -Wall 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

PROJECTNAME = Program6

EXECFILE = programsix

OBJS = cdkexample.o

all: $(EXECFILE)

clean:

	rm -f $(OBJS) $(EXECFILE) 


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H.%M.%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME) 
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME) 
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!

	
