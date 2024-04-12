FLAGS = -fdiagnostics-generate-patch -fdiagnostics-path-format=inline-events  \
-Og -ggdb -std=c++17 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations   \
-Wc++14-compat -Wuseless-cast -Wmissing-declarations -Wcast-align -Wcast-qual \
-Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy  \
-Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security              \
-Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor       \
-Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self       \
-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo                     \
-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn       \
-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override              \
-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code         \
-Wunused -Wvariadic-macros -Wno-literal-suffix                                \
-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast            \
-Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation               \
-fstack-protector -fstrict-overflow -flto-odr-type-merging                    \
-fno-omit-frame-pointer -Wstack-usage=8192                                    \
-fsanitize=address,bool,bounds,enum,float-cast-overflow,$\
float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,$\
object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,$\
undefined,unreachable,vla-bound,vptr

SOURCES := $(wildcard *.cpp)
LIBS 	= ../source/InputText.cpp ../source/MyFunctions.cpp
SOURCES += $(wildcard $(LIBS))
OBJ_DIR = Disassembler_apps

<<<<<<< HEAD
VPATH := ./:../source
=======
all: Disassembler
	
Disassembler: clean InputText.o Disasmreg.o main.o
		
		g++ InputText.o Disasmreg.o main.o -o DisassemblerV3 	$(FLAGS)

InputText.o:

		g++ ../source/InputText.cpp -c -o InputText.o $(FLAGS) 
>>>>>>> 778f7e15a4bb0a8725f9af5831c17a27412326c9

OBJECTS := $(addprefix $(OBJ_DIR)/, $(notdir $(patsubst %.cpp,%.o,$(SOURCES))))

EXECUTABLE = Disassembler

.PHONY: all 
all: $(EXECUTABLE) 

$(EXECUTABLE): $(OBJECTS)
	@g++ $(OBJECTS) -o $(EXECUTABLE) $(FLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@g++ $^ -c -o $@ $(FLAGS)

.PHONY: clean
clean: 
	rm -rf $(OBJ_DIR)/*.o 
	rm $(EXECUTABLE)

run:
	./$(EXECUTABLE) ../Output/AssemblerArrCode.txt ../Output/DisassmeblerArrCode.txt