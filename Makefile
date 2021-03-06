PROGRAMS	:= todot
CXX 		:= g++
CXXFLAGS	:= -std=c++11 -Wall -g -I./include -I./test
LDFLAGS		:= -Wall -g 
LDLIBS = -lpthread 
#SLIBS=./libjson/libjson.a
#LDLIBS = -lsqlite3


################ DO NOT MODIFY BELOW THIS LINE! ################

# list of all source files (including directories)
SRC := $(wildcard *.cpp)
SRC += $(wildcard */*.cpp)
#list of all soruce code directories
SRC_DIR := $(sort $(dir $(SRC)))

OUT_DIR := bin
OBJ := $(addprefix $(OUT_DIR)/,$(patsubst %.cpp,%.o,$(SRC)))
OBJ_DIR := $(sort $(dir $(OBJ)))

vpath %.cpp $(SRC_DIR)

.PHONY: all
all: $(PROGRAMS)

# generic rule to compile objects
define compile_template
$(1)%.o: %.cpp
	mkdir -p $$(@D)
	$$(CXX) $$(CXXFLAGS) -c $$< -o $$@
endef

# generic rule to compile and link executable
define PROGRAM_template
$(1): $$(OBJ)
	$$(CXX) $$(LDFLAGS) $$^ -Xlinker -zmuldefs -o $$@ $$(SLIBS) $$(LDLIBS)
endef

$(foreach odir,$(OBJ_DIR),$(eval $(call compile_template,$(odir))))
$(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))

.PHONY: check
check:
	@echo $(SRC)
	@echo $(SRC_DIR)
	@echo $(OBJ)
	@echo $(OBJ_DIR)

.PHONY: clean
clean:
	rm -rf $(OUT_DIR) $(PROGRAMS) *.o *~
