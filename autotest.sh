#!/bin/bash

TEST_COMPILE_SCRIPT=tests/test_compile.sh
TEST_COMPILE_NO_MAIN_SCRIPT=tests/test_compile_no_main.sh
TEST_STAGE1_DIR=tests/stage1
TEST_STAGE2_DIR=tests/stage2

if [ -n "$MEMCHECK" ]; then
    VALGRIND="valgrind --leak-check=full --error-exitcode=1"
else
    VALGRIND=
fi

make clean
make test
if [ $? -ne 0 ]; then
    exit 1
fi

$VALGRIND ./tests/test_stage1
if [ $? -ne 0 ]; then
    exit 1
fi

$VALGRIND ./tests/test_stage2
if [ $? -ne 0 ]; then
    exit 1
fi

echo "---- Compilation test stage1 ----"
./$TEST_COMPILE_SCRIPT $TEST_STAGE1_DIR gen_main_return_0 0
./$TEST_COMPILE_SCRIPT $TEST_STAGE1_DIR gen_main_return_42 42
./$TEST_COMPILE_NO_MAIN_SCRIPT $TEST_STAGE1_DIR gen_no_main

echo "---- Compilation test stage2 ----"
./$TEST_COMPILE_SCRIPT $TEST_STAGE2_DIR gen_main_return_identifier 0
./$TEST_COMPILE_SCRIPT $TEST_STAGE2_DIR gen_main_return_identifier_42 42
./$TEST_COMPILE_SCRIPT $TEST_STAGE2_DIR gen_post_decl_assign_0 0
./$TEST_COMPILE_SCRIPT $TEST_STAGE2_DIR gen_post_decl_assign_42 42

exit 0
