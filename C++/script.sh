#!/bin/bash
for FILE in *; do
if [ -f "$FILE" ]; then
if echo "$FILE" | grep -q ".cpp"; then
CUT=$(echo $FILE | sed -e "s/\(.*\)\.cpp/\1/")
echo "add_executable($CUT $FILE)"
fi
fi
done