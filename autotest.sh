#!/bin/bash

TEST_COMPILE_SCRIPT=tests/test_compile.sh
TEST_COMPILE_NO_MAIN_SCRIPT=tests/test_compile_no_main.sh
TEST_STAGE1_DIR=tests/stage1

make test
if [ $? -ne 0 ]; then
    exit 1
fi

valgrind --leak-check=full --error-exitcode=1 ./tests/test_stage1
if [ $? -ne 0 ]; then
    exit 1
fi

valgrind --leak-check=full --error-exitcode=1 ./tests/test_stage2
if [ $? -ne 0 ]; then
    exit 1
fi

./$TEST_COMPILE_SCRIPT $TEST_STAGE1_DIR gen_main_return_0 0
./$TEST_COMPILE_SCRIPT $TEST_STAGE1_DIR gen_main_return_42 42
./$TEST_COMPILE_NO_MAIN_SCRIPT $TEST_STAGE1_DIR gen_no_main

exit 0
