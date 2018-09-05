#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CXX = mpic++
MPICXX = mpic++
# define any compile-time flags
CFLAGS = -Wall -g
LDFLAGS = -lstdc++

# define any directories containing header files other than /usr/include
#
INCLUDES = $(shell for incpath in `find ../include -type d`; do echo -I$${incpath}; done)

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lstdc++

# define the C source files
SRCS = $(wildcard main.cpp ./MPI/*.cpp ./MPI/MPICH/*.cpp)

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o)

# define the executable file 
MAIN = main

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#
.PHONY: depend clean

all:    $(MAIN)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $? -o $@

$(MAIN): $(OBJS)
	$(CXX) $(CFLAGS) $(INCLUDES) $? -o $@ $(OBJS) $(LFLAGS) $(LIBS)

clean:
	-$(RM) $(OBJS) *~ $(MAIN)
