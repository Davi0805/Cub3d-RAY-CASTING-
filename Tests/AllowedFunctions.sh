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
    "__errno_location@GLIBC_2.2.5"
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
    
    # MiniLibX functions
    "mlx_init"
    "mlx_new_window"
    "mlx_pixel_put"
    "mlx_loop"
    "mlx_key_hook"
    "mlx_mouse_hook"
    "mlx_expose_hook"
    "mlx_loop_hook"
    "mlx_string_put"
    "mlx_xpm_file_to_image"
    "mlx_xpm_to_image"
    "mlx_put_image_to_window"
    "mlx_get_data_addr"
    "mlx_new_image"
    "mlx_destroy_window"
    "mlx_destroy_image"
    "mlx_hook"
    "mlx_do_sync"
    
    # System functions used by MiniLibX (X11)
    "__memset_chk@GLIBC_"
    "calloc@GLIBC_"
    "getenv@GLIBC_"
    "gethostname@GLIBC_"
    "shmat@GLIBC_"
    "shmctl@GLIBC_"
    "shmdt@GLIBC_"
    "shmget@GLIBC_"
    "strlen@GLIBC_"
    "strncmp@GLIBC_"
    "XAutoRepeatOff"
    "XAutoRepeatOn"
    "XChangeWindowAttributes"
    "XCloseDisplay"
    "XCopyArea"
    "XCreateColormap"
    "XCreateGC"
    "XCreateImage"
    "XCreatePixmap"
    "XCreateWindow"
    "XDestroyWindow"
    "XFlush"
    "XFreeGC"
    "XFreePixmap"
    "XGetVisualInfo"
    "XGetWMNormalHints"
    "XInternAtom"
    "XkbKeycodeToKeysym"
    "XMapRaised"
    "XNextEvent"
    "XOpenDisplay"
    "XPending"
    "XPutBackEvent"
    "XPutImage"
    "XSetClipOrigin"
    "XSetErrorHandler"
    "XSetWMNormalHints"
    "XSetWMProtocols"
    "XShmAttach"
    "XShmCreateImage"
    "XShmCreatePixmap"
    "XShmDetach"
    "XShmPixmapFormat"
    "XShmPutImage"
    "XShmQueryVersion"
    "XStoreName"
    "XSync"
    "XWindowEvent"
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