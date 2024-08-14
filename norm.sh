#!/bin/bash

# Create the new_src and new_include directories if they don't exist
mkdir -p new_src
mkdir -p new_include

# Loop through all .c files in the src directory and format them
for file in src/*.c; do
  python3 -m c_formatter_42 < "$file" > "new_src/$(basename "$file")"
done

# Loop through all .h files in the include directory and format them
for file in include/*.h; do
  python3 -m c_formatter_42 < "$file" > "new_include/$(basename "$file")"
done

# Remove the original src and include directories
rm -rf src
rm -rf include

# Rename new_src to src and new_include to include
mv new_src src
mv new_include include
