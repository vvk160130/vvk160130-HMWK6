# Name - Vishnu Kunadharaju
# Course Number - 3377
# Section Number - 501 
# HMWK - 6
# Email: vvk160130@utdallas.edu 

CXX = g++
CXXFLAGS = -Wall -std=c++11 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses

#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

PROJECTNAME = Program6

# This is what the executable will be named 

EXECFILE = programsix

OBJS = cdkexample.o

all: $(EXECFILE)


# Removes unnecessary files 

clean:

	rm -f $(OBJS) $(EXECFILE) 


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)



# creates a backup 

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

	
