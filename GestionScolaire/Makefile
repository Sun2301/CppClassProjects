# Compilateur
CXX = g++

# Flags de compilation
CXXFLAGS = `wx-config --cxxflags` -Iinclude -std=c++11 -Wall
LDFLAGS = `wx-config --libs`

# Dossiers
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = bin
OBJ_DIR = $(BUILD_DIR)/obj

# Fichiers sources
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/frames/*.cpp) \
          $(wildcard $(SRC_DIR)/dialogs/*.cpp) \
          $(wildcard $(SRC_DIR)/models/*.cpp) \
          $(wildcard $(SRC_DIR)/database/*.cpp)

# Fichiers objets
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Nom de l'exécutable
TARGET = $(BUILD_DIR)/EPAC

# Règle principale
all: $(TARGET)

# Créer l'exécutable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "✓ Compilation réussie! Exécutable: $(TARGET)"

# Compiler les fichiers .cpp en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "✓ Compilé: $<"

# Nettoyer les fichiers compilés
clean:
	rm -rf $(BUILD_DIR)
	@echo "✓ Nettoyage terminé"

# Exécuter le programme
run: all
	./$(TARGET)

# Afficher la structure du projet
tree:
	@echo "Structure du projet:"
	@find . -type f -not -path "./bin/*" -not -path "./.git/*" | sort

.PHONY: all clean run tree