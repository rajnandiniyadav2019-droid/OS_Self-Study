#!/bin/bash

# Check if directory argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory_path>"
    exit 1
fi

DIR=$1

# Check if directory exists
if [ ! -d "$DIR" ]; then
    echo "Error: Directory does not exist!"
    exit 1
fi

# Create directories for each file type
mkdir -p "$DIR/txt_files"
mkdir -p "$DIR/pdf_files"
mkdir -p "$DIR/c_files"

# Move files into respective directories
for file in "$DIR"/*; do
    if [ -f "$file" ]; then
        case "$file" in
            *.txt)
                mv "$file" "$DIR/txt_files/"
                ;;
            *.pdf)
                mv "$file" "$DIR/pdf_files/"
                ;;
            *.c)
                mv "$file" "$DIR/c_files/"
                ;;
        esac
    fi
done

echo "Files organized successfully!"
