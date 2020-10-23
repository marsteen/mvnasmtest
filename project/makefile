
#
# Source Files
#
.SUFFIXES: .cpp .asm

CCFILES  = main.cpp
ASMFILES = test.asm

#
# Flags
#

CPPFLAGS  =
LINKFLAGS = 

#
# Rules
#


.cpp.o:
	g++ -c $(CPPFLAGS) -std=c++11 -o$@ $<  


.asm.o:
	nasm -g -f elf64 -o$@ $<  

#
# Objects
#

CCOBJECTS   = $(CCFILES:.cpp=.o)
ASMOBJECTS  = $(ASMFILES:.asm=.o)

#
# Target
#

TARGET = nasm-test
default: $(TARGET)

#
# Linking
#

$(TARGET): $(CCOBJECTS) $(ASMOBJECTS)
	g++ -o $(TARGET) $(CCOBJECTS) $(ASMOBJECTS)
	
