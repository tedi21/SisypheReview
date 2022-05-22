CXX=em++
CXXFLAGS=-s WASM=1 -std=c++17 -D_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR -O2
CC=emcc
CCFLAGS=-s WASM=1 -DSQLITE_ENABLE_FTS3 -DSQLITE_ENABLE_FTS3_PARENTHESIS -O2
LDFLAGS=-s WASM=1 -O2
LIBRARY=/home/teddy/developpement/Libraries
LIBOBJ=../
ROOT=/home/teddy/developpement/repositories/SisypheReview
EXEC=tdscript.html

ENCODING_PATH=$(ROOT)/CodeGeneration/encoding
ENCODING_INC=-I$(ENCODING_PATH)
ENCODING_SRC=$(wildcard $(ENCODING_PATH)/impl/*.cpp)

INTERPRETER_PATH=$(ROOT)/Common/Interpreter
INTERPRETER_INC=-I$(ROOT)/Sisyphe/interpreter/config -I$(INTERPRETER_PATH) -I$(ROOT)/Common/Exception -I$(ROOT)/CodeGeneration/factory -I$(ROOT)/CodeGeneration/generator
INTERPRETER_SRC=$(ROOT)/Common/Interpreter/Interpreter.cpp

PARSER_INC=-I$(ROOT)/Sisyphe/interpreter/plugins/libparsePlg/interpreter/src

SQLITE_PATH=$(ROOT)/Common/Sqlite
SQLITE_INC=-I$(SQLITE_PATH)
SQLITE_SRC=$(SQLITE_PATH)/sqlite3.c

CPPBASE_PATH=$(ROOT)/Sisyphe/cppbase/src 
CPPBASE_INC=-I$(ROOT)/Sisyphe/cppbase/src -I$(ROOT)/Sisyphe/cppbase/src/interpreter -I$(ROOT)/Common/Sqlite/interpreter -I$(ROOT)/Common/Pointer 
CPPBASE_SRC=$(wildcard $(ROOT)/Sisyphe/cppbase/src/*.cpp)

VPATH=$(ENCODING_PATH)/impl $(INTERPRETER_PATH) $(CPPBASE_PATH) $(SQLITE_PATH)
INC=$(INTERPRETER_INC) $(CPPBASE_INC) $(ENCODING_INC) $(PARSER_INC) $(SQLITE_INC) -I$(LIBRARY)/boost_1_66_0 -I$(LIBRARY)/log4cpp/include
LIB=$(LIBOBJ)/log4cpp/liblog4cpp.a $(LIBOBJ)/boost_1_66_0/libboost_date_time.bc $(LIBOBJ)/boost_1_66_0/libboost_filesystem.bc $(LIBOBJ)/boost_1_66_0/libboost_regex.bc $(LIBOBJ)/boost_1_66_0/libboost_system.bc
SRC=$(ENCODING_SRC) $(INTERPRETER_SRC) $(CPPBASE_SRC) $(wildcard *.cpp)
OBJ=$(notdir $(SRC:.cpp=.bc)) $(notdir $(SQLITE_SRC:.c=.bc))

all: $(EXEC)

tdscript.html: $(OBJ)
	@mkdir -p out
	$(CXX) $(LDFLAGS) $(addprefix obj/,$^) $(LIB) -o out/$@  --preload-file data@/ --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1  --bind -s DISABLE_EXCEPTION_CATCHING=0 -s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1 -s 'EXPORT_NAME="createModule"'

%.bc: %.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o obj/$@ -s DISABLE_EXCEPTION_CATCHING=0

%.bc: %.c
	@mkdir -p obj
	$(CC) $(CCFLAGS) $(INC) -c $< -o obj/$@

.PHONY: clean mrproper

clean:
	@rm -rf obj

mrproper: clean
	@rm -rf out
