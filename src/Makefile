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
CFLAGS = -Wall -g -static
LDFLAGS = -lstdc++

# define any directories containing header files, and build the 
# corresponding flags to use in the compilation line and the list
# of files to use as depedencies
INCDIRS = $(shell find ../include -type d)
INCFLAGS = $(shell for incpath in $(INCDIRS); do echo -I$${incpath}; done)
INCLUDES = $(wildcard $(shell for incpath in $(INCDIRS); do echo $${incpath}/*.h; done))

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lstdc++

# define the C source files
SRCS = $(wildcard *.cpp ./MPI/*.cpp ./MPI/MPICH/*.cpp ./MPI/MVAPICH/*.cpp)

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.cpp=.o)

# define the executable and static archive files
MAIN = main
ARCHIVE = ../lib/libaituning.a

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#
.PHONY: clean

all:    $(ARCHIVE)

# A more sophisticated approach would let the object files depend only from
# the actual dependencies, but that needs to be built outside of Makefile, see
# https://stackoverflow.com/questions/2394609/makefile-header-dependencies and 
# particularly [the second answer](https://stackoverflow.com/a/30142139/25891)
# for details
%.o: %.cpp $(INCLUDES)
	$(CXX) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(ARCHIVE): $(OBJS)
	$(AR) rcs $@ $?

$(MAIN): $(OBJS)
	$(CXX) $(CFLAGS) $(INCFLAGS) $? -o $@ $(OBJS) $(LFLAGS) $(LIBS)

clean:
	-$(RM) $(OBJS) *~ $(MAIN) $(ARCHIVE)
