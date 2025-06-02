#переменные
CXX = g++
CXXFLAGS = -Wall -Werror -Wpedantic -g -std=c++11
#LDFLAGS = -lgtest -lgtest_main -pthread

PREF_SRC = ./src/
PREF_OBJ = ./obj/
PREF_SH = ./sh/

# Список всех исходников
SRC = $(wildcard $(PREF_SRC)*.cpp)

#Список всех объектных файлов
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

#Исполняемуе файлы
TARGET_MAIN = output
TARGET_PARALLEL = outputParallel

#Общие файлы
COMMON_SRC = $(filter-out $(PREF_SRC)main.cpp $(PREF_SRC)mainParallel.cpp, $(wildcard $(PREF_SRC)*.cpp))

COMMON_OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(COMMON_SRC))

#Объектники
OBJ_MAIN = $(PREF_OBJ)main.o $(COMMON_OBJ)
OBJ_PARALLEL = $(PREF_OBJ)mainParallel.o $(COMMON_OBJ)

#Cкрипт проверки
TEST_SCRIPT = $(PREF_SH)test.sh

#Правило по умолчанию
all: $(TARGET_MAIN) $(TARGET_PARALLEL)

# Создание папки для объектных файлов
$(PREF_OBJ):
	mkdir -p $(PREF_OBJ)

#Правило сборки main
$(TARGET_MAIN): $(PREF_OBJ) $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) $(OBJ_MAIN) -o $(TARGET_MAIN)
	
#Правило сборки mainParallel
$(TARGET_PARALLEL): $(PREF_OBJ) $(OBJ_PARALLEL)
	$(CXX) $(CXXFLAGS) $(OBJ_PARALLEL) -o $(TARGET_PARALLEL)

#Правило для компиляции
$(PREF_OBJ)%.o: $(PREF_SRC)%.cpp | $(PREF_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Правило тестов
test: $(TARGET_MAIN) $(TARGET_PARALLEL) | $(PREF_SH)
	@if [ -f "$(TEST_SCRIPT)" ]; then \
		echo "Running benchmark tests..."; \
		chmod +x $(TEST_SCRIPT); \
		$(TEST_SCRIPT) $(ARGS); \
	else \
		echo "Error: Benchmark script not found at $(TEST_SCRIPT)"; \
		echo "Create the script first or run 'make install-script'"; \
		exit 1; \
	fi

#Правило очистки
clean:
	rm -f $(PREF_OBJ)*.o
cleanall: clean
	rm -f $(TARGET_MAIN) $(TARGET_PARALLEL)

#Правило для запуска тестов
run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

run-parallel: $(TARGET_PARALLEL)
	./$(TARGET_PARALLEL)

# Format rule
format:
	find src/ -name '*.cpp' -exec astyle --options=stylr.astylerc {} \;

.PHONY: all clean cleanall run format


