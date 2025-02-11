#!/bin/bash

# Variáveis globais para paths
EXECUTABLE="./Cub3d"
MAPS_DIR="Assets/Maps"
VALID_MAPS_DIR="$MAPS_DIR/Valid"
INVALID_MAPS_DIR="$MAPS_DIR/Invalid"

# Códigos de saída esperados
VALID_EXIT_CODE=0
INVALID_EXIT_CODE=1

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Contador de testes
valid_passed=0
valid_total=0
invalid_passed=0
invalid_total=0

# Arrays to store failed maps
failed_valid_maps=()
failed_invalid_maps=()

# Debug information
echo -e "${YELLOW}Checking executable...${NC}"
if [ -f "$EXECUTABLE" ]; then
    echo -e "${GREEN}Executable found!${NC}"
    ls -l "$EXECUTABLE"
else
    echo -e "${RED}Error: Executable '$EXECUTABLE' not found!${NC}"
    echo "Current directory: $(pwd)"
    echo "Content of parent directory:"
    ls -la ..
    exit 1
fi

# Função para testar mapas
test_map() {
    local map=$1
    local expected_exit_code=$2
    local map_type=$3

    echo -e "${YELLOW}Testing map: ${map}${NC}"
    echo "Executing: $EXECUTABLE \"$map\""
    $EXECUTABLE "$map"
    actual_exit_code=$?

    echo "Exit code received: $actual_exit_code"

    if [ $actual_exit_code -eq $expected_exit_code ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        if [ "$map_type" == "valid" ]; then
            ((valid_passed++))
        else
            ((invalid_passed++))
        fi
    else
        echo -e "${RED}✗ FAIL${NC}"
        echo -e "Expected exit code: $expected_exit_code"
        echo -e "Actual exit code: $actual_exit_code"
        if [ "$map_type" == "valid" ]; then
            failed_valid_maps+=("$map")
        else
            failed_invalid_maps+=("$map")
        fi
    fi
    echo "----------------------------------------"
}

# Verificar se o diretório Maps existe
if [ ! -d "$MAPS_DIR" ]; then
    echo -e "${RED}Error: Directory '$MAPS_DIR' not found!${NC}"
    echo "Current directory: $(pwd)"
    echo "Content of parent directory:"
    ls -la ..
    exit 1
fi

# Testar mapas válidos
echo -e "\n${YELLOW}Testing Valid Maps...${NC}\n"
for map in "$VALID_MAPS_DIR"/*; do
    if [ -f "$map" ]; then
        ((valid_total++))
        test_map "$map" $VALID_EXIT_CODE "valid"
    fi
done

# Testar mapas inválidos
echo -e "\n${YELLOW}Testing Invalid Maps...${NC}\n"
for map in "$INVALID_MAPS_DIR"/*; do
    if [ -f "$map" ]; then
        ((invalid_total++))
        test_map "$map" $INVALID_EXIT_CODE "invalid"
    fi
done

# Relatório final
echo -e "\n${YELLOW}Test Summary:${NC}"
echo -e "Valid Maps: ${GREEN}$valid_passed/$valid_total passed${NC}"
echo -e "Invalid Maps: ${GREEN}$invalid_passed/$invalid_total passed${NC}"

# Print failed maps
if [ ${#failed_valid_maps[@]} -ne 0 ]; then
    echo -e "\n${RED}Failed Valid Maps:${NC}"
    for map in "${failed_valid_maps[@]}"; do
        echo -e "${RED}$map${NC}"
    done
fi

if [ ${#failed_invalid_maps[@]} -ne 0 ]; then
    echo -e "\n${RED}Failed Invalid Maps:${NC}"
    for map in "${failed_invalid_maps[@]}"; do
        echo -e "${RED}$map${NC}"
    done
fi

# Calcular porcentagem total de sucesso
total_passed=$((valid_passed + invalid_passed))
total_tests=$((valid_total + invalid_total))
success_rate=$(( (total_passed * 100) / total_tests ))

echo -e "Overall Success Rate: ${GREEN}$success_rate%${NC}"

# Determinar se todos os testes passaram
if [ $total_passed -eq $total_tests ]; then
    echo -e "\n${GREEN}All tests passed successfully!${NC}"
    exit 0
else
    echo -e "\n${RED}Some tests failed. Please check the output above.${NC}"
    exit 1
fi