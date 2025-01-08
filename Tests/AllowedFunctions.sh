#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# List of allowed functions
ALLOWED_FUNCTIONS=(
    # Basic functions
    "close@GLIBC_"
    "free@GLIBC_"
    "malloc@GLIBC_"
    "open@GLIBC_"
    "printf@GLIBC_"
    "puts@GLIBC_2.2.5"
    "perror@GLIBC_"
    "read@GLIBC_"
    "write@GLIBC_"
    "strerror@GLIBC_"
    "exit@GLIBC_"
    "gettimeofday@GLIBC_"
    
    # Math library functions (add specific ones if needed)
    "sin@GLIBC_"
    "cos@GLIBC_"
    "tan@GLIBC_"
    "asin@GLIBC_"
    "acos@GLIBC_"
    "atan@GLIBC_"
    "atan2@GLIBC_"
    "sqrt@GLIBC_"
    "pow@GLIBC_"
    
    # Common system symbols (these are typically allowed)
    "__libc_start_main@GLIBC_"
    "__cxa_finalize@GLIBC_"
    "__gmon_start__"
    "_ITM_registerTMCloneTable"
    "_ITM_deregisterTMCloneTable"
    "__stack_chk_fail@GLIBC_"
)

# Check if executable is provided
if [ "$#" -ne 1 ]; then
    echo -e "${RED}Error: Please provide the executable as an argument${NC}"
    echo "Usage: $0 <executable>"
    exit 1
fi

EXECUTABLE=$1

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable '$EXECUTABLE' not found${NC}"
    exit 1
fi

# Get undefined symbols using nm
UNDEFINED_FUNCS=$(nm -u "$EXECUTABLE")
if [ $? -ne 0 ]; then
    echo -e "${RED}Error: Failed to run nm on '$EXECUTABLE'${NC}"
    exit 1
fi

# Function to check if a symbol is allowed
is_allowed() {
    local symbol=$1
    for allowed in "${ALLOWED_FUNCTIONS[@]}"; do
        if [[ "$symbol" == *"$allowed"* ]]; then
            return 0
        fi
    done
    return 1
}

# Check each undefined symbol
FORBIDDEN_FOUND=0
echo -e "${YELLOW}Checking undefined symbols...${NC}"
echo "----------------------------------------"

while read -r line; do
    # Skip empty lines
    [ -z "$line" ] && continue
    
    # Extract symbol name
    symbol=$(echo "$line" | awk '{print $2}')
    
    # Skip if no symbol found
    [ -z "$symbol" ] && continue
    
    if ! is_allowed "$symbol"; then
        echo -e "${RED}Forbidden function found: $symbol${NC}"
        FORBIDDEN_FOUND=1
    else
        echo -e "${GREEN}Allowed function: $symbol${NC}"
    fi
done <<< "$UNDEFINED_FUNCS"

echo "----------------------------------------"

# Final result
if [ $FORBIDDEN_FOUND -eq 1 ]; then
    echo -e "${RED}❌ Forbidden functions were found!${NC}"
    exit 1
else
    echo -e "${GREEN}✅ All functions are allowed!${NC}"
    exit 0
fi