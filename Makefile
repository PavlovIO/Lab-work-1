#переменные
CXX = g++
CXXFLAGS = -Wall -Werror -Wpedantic -g -std=c++11
#LDFLAGS = -lgtest -lgtest_main -pthread

PREF_SRC = ./src/
PREF_OBJ = ./obj/

# Список всех исходников
SRC = $(wildcard $(PREF_SRC)*.cpp)

#Список всех объектных файлов
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

#Исполняемый файл
TARGET = output

#Правило по умолчанию
all: $(TARGET)

# Создание папки для объектных файлов
$(PREF_OBJ):
	mkdir -p $(PREF_OBJ)

#Правило сборки
$(TARGET): $(PREF_OBJ) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) #$(LDFLAGS)

#Правило для компиляции
$(PREF_OBJ)%.o: $(PREF_SRC)%.cpp | $(PREF_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Правило очистки
clean:
	rm -f $(PREF_OBJ)*.o
cleanall: clean
	rm -f $(TARGET)

#Правило для запуска тестов
run: $(TARGET)
	./$(TARGET)

# Format rule
format:
	find src/ -name '*.cpp' -exec astyle --options=stylr.astylerc {} \;

.PHONY: all clean cleanall run format


