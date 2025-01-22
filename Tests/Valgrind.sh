#! /bin/bash

# Set Valgrind command options
val="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes"
bin="Cub3d"
mapsDir="Assets/Maps/Invalid/"
logFile="log.txt"
valgrindErrors="definitely lost|indirectly lost|possibly lost|Invalid read|invalid access|segfault|address not mapped|stack overflow|heap corruption|ERROR SUMMARY: [1-9][0-9]* errors"

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

echo -e "${BLUE}--------CUB3D VALGRIND TEST-----------${RESET}"

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

# Function to run Valgrind on each map file
RunningValgrind() {
    failedCount=0
    passedCount=0
    for map in "$mapsDir"*; do
        # Get only the file name (no path)
        mapName=$(basename "$map")
        
        # Run valgrind and capture output
        valgrindOutput=$($val ./"$bin" "$map" 2>&1)

        # Check if there is any of the errors listed in valgrindErrors with regex
        if echo "$valgrindOutput" | grep -E "$valgrindErrors" > /dev/null; then
            # Log the failed map details in the log file
            echo -e "${RED}$mapName FAILED${RESET}"
            echo "Logging the result into $logFile"
            echo "$valgrindOutput" >> "$logFile" 2>&1
            echo -e "\n\n" >> "$logFile"
            ((failedCount++))
        else
            # Passed
            echo -e "${GREEN}$mapName passed${RESET}"
            ((passedCount++))
        fi
    done

    # Summary of results
    echo -e "\n${YELLOW}Summary:${RESET}"
    echo -e "${GREEN}Passed: $passedCount${RESET} maps"
    echo -e "${RED}Failed: $failedCount${RESET} maps"
    echo -e "\nFor more detailed error information, please check the log file: ${BLUE}$logFile${RESET}"
}

RunningValgrind

echo -e "${BLUE}End of Valgrind Testing${RESET}"
