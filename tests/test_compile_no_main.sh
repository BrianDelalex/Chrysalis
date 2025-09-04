#!/bin/bash

STAGE=$1

ASM_DIR="${STAGE}/output_files"

BASE_FILENAME="${ASM_DIR}/${2}"

ASM_FILE="${BASE_FILENAME}.asm"

OBJECT_FILE="${BASE_FILENAME}.o"

BINARY=$BASE_FILENAME

nasm -felf64 -o $OBJECT_FILE $ASM_FILE
if [ $? -ne 0 ]; then
    echo "Unable to create ${OBJECT_FILE}."
    exit 1
fi

exec 3>&1
LD_ERROR=$(ld -o $BINARY $OBJECT_FILE 2>&1 1>&3)
exec 3>&-
if [[ "$LD_ERROR" == *"cannot find entry symbol _start;"* ]];then
     echo "Compilation test for file ${ASM_FILE} - SUCCESS."
    exit 0
else
    echo "ld has found an entry symbol _start which is unexpected."
    exit 1
fi
