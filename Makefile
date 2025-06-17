# Compilador
CXX = g++
CXXFLAGS = -Wall -std=c++17 \
           -I./src/model \
           -I./src/model/patient \
           -I./src/model/triage \
           -I./src/model/triage_queue \
           -I./src/controller/patient \
           -I./src/controller/triage \
           -I./src/view/patient \
           -I./src/view/triage \
           -I./src/view/triage_queue

# Diretórios
SRC_DIR = src
BUILD_DIR = build

# Fontes
SRCS = $(wildcard $(SRC_DIR)/main.cpp) \
       $(wildcard $(SRC_DIR)/model/patient/*.cpp) \
       $(wildcard $(SRC_DIR)/model/triage/*.cpp) \
       $(wildcard $(SRC_DIR)/model/triage_queue/*.cpp) \
       $(wildcard $(SRC_DIR)/controller/patient/*.cpp) \
       $(wildcard $(SRC_DIR)/controller/triage/*.cpp) \
       $(wildcard $(SRC_DIR)/view/patient/*.cpp) \
       $(wildcard $(SRC_DIR)/view/triage/*.cpp) \
       $(wildcard $(SRC_DIR)/view/triage_queue/*.cpp)

# Objetos
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executável final
TARGET = $(BUILD_DIR)/app

# Regra padrão
all: $(TARGET)

# Como construir o executável
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Como compilar arquivos .cpp -> .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos de build
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean