#! /bin/bash

# Set Valgrind command options
bin="cub3D"
mapsDir="Assets/Maps/Invalid/"
logFile="log.txt"
sanitizeErrors="heap-use-after-free|stack-use-after-scope|global-buffer-overflow|stack-buffer-overflow|use-after-poison|double free|invalid free|address not mapped|undefined behavior|null pointer|memory leak|detected memory leaks|division by zero|alignment error|object size|shift-exponent|unsigned integer overflow|signed integer overflow|SEGV on unknown address|abort"

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

echo -e "${BLUE}--------CUB3D SANITIZE TEST-----------${RESET}"

# Empty log file at the beginning
echo -n > "$logFile"

# Check if the executable and maps directory exist
if [ ! -f "$bin" ] || [ ! -x "$bin" ]; then
    echo -e "${RED}Executable not found!${RESET}"
    exit 1
fi

if [ ! -d "$mapsDir" ]; then
    echo -e "${RED}Map directory not found!${RESET}"
    exit 1
fi

CheckingSanitize()
{
    failedCount=0
    passedCount=0
    for map in "$mapsDir"*; do
        sanitizeOutput=$(./"$bin" "$map" 2>&1)

        if echo "$sanitizeOutput" | grep -E "$sanitizeErrors" > /dev/null 2>&1; then
            # Log failed map details in the log file
            echo -e "${RED}$mapName FAILED${RESET}"
            echo "Logging the result into $logFile"
            echo "$sanitizeOutput" >> "$logFile" 2>&1
            echo -e "\n\n" >> "$logFile"
            ((failedCount++))
        else
            # Passed
            echo -e "${GREEN}$mapName passed${RESET}"
            ((passedCount++))
        fi
    done

# Summary of results    echo -e "\n${YELLOW}Summary:${RESET}"
    echo -e "${GREEN}Passed: $passedCount${RESET} maps"
    echo -e "${RED}Failed: $failedCount${RESET} maps"
    echo -e "\nFor more detailed error information, please check the log file: ${BLUE}$logFile${RESET}"
}

CheckingSanitize

echo -e "${BLUE}End of Sanitize Testing${RESET}"
