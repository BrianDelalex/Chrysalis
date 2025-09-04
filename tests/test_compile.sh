#!/bin/bash

STAGE=$1

ASM_DIR="${STAGE}/output_files"

BASE_FILENAME="${ASM_DIR}/${2}"

EXPECTED_EXIT_CODE=$3

ASM_FILE="${BASE_FILENAME}.asm"

OBJECT_FILE="${BASE_FILENAME}.o"

BINARY="${BASE_FILENAME}"

nasm -felf64 -o $OBJECT_FILE $ASM_FILE
if [ $? -ne 0 ]; then
    echo "Unable to create ${OBJECT_FILE}."
    exit 1
fi

ld -o $BINARY $OBJECT_FILE
if [ $? -ne 0 ]; then
    echo "Unable to link ${BINARY}."
    exit 2
fi

./$BINARY
EXIT_CODE=$?
if [ $EXIT_CODE -ne $EXPECTED_EXIT_CODE ]; then
    echo "Compilation test for file ${ASM_FILE} - Invalid exit code expected ${EXPECTED_EXIT_CODE} got ${EXIT_CODE}."
    exit 3
fi

echo "Compilation test for file ${ASM_FILE} - SUCCESS."

exit 0
