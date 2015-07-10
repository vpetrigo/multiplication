CXX = clang++
CXX_FLAGS = -std=c++14 -O3
MUL_LIB_DIR = Mul_lib
MUL_LIB_SRC = mul_lib.cpp
MUL_LIB_HDR = mul_lib.hpp

MUL_LIB_O = $(patsubst %.cpp,Mul_lib/%.o,$(MUL_LIB_SRC))
MUL_LIB_DEP = $(MUL_LIB_DIR)/$(MUL_LIB_HDR)

EX_SRC = mul.cpp
EX_OBJ = mul.o

all: $(MUL_LIB_O) $(EX_OBJ)
	$(CXX) $? -o mul
	
$(MUL_LIB_O): $(MUL_LIB_DIR)/$(MUL_LIB_SRC) $(MUL_LIB_DEP)
	$(CXX) -c $< $(CXX_FLAGS) -o $(MUL_LIB_O) -I $(MUL_LIB_DIR)
	
$(EX_OBJ): $(EX_SRC) $(MUL_LIB_DEP)
	$(CXX) -c $< $(CXX_FLAGS) -I $(MUL_LIB_DIR)
	
clean:
	@rm *.o -rf
	@rm $(MUL_LIB_DIR)/*.o -rf
	@rm *.exe