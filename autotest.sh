#!/bin/bash

TEST_COMPILE_SCRIPT=tests/test_compile.sh
TEST_COMPILE_NO_MAIN_SCRIPT=tests/test_compile_no_main.sh
TEST_STAGE1_DIR=tests/stage1
TEST_STAGE2_DIR=tests/stage2
TEST_STAGE3_DIR=tests/stage3

if [ -n "$MEMCHECK" ]; then
    VALGRIND="valgrind --leak-check=full --error-exitcode=1"
else
    VALGRIND=
fi

mkdir -p "${TEST_STAGE1_DIR}/output_files"
mkdir -p "${TEST_STAGE2_DIR}/output_files"
mkdir -p "${TEST_STAGE3_DIR}/output_files"

make clean
make test
if [ $? -ne 0 ]; then
    exit 1
fi

CMD="${VALGRIND} ./tests/test_stage1"
eval $CMD
if [ $? -ne 0 ]; then
    exit 1
fi

CMD="${VALGRIND} ./tests/test_stage2"
eval $CMD
if [ $? -ne 0 ]; then
    exit 1
fi

CMD="${VALGRIND} ./tests/test_stage3"
eval $CMD
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

echo "---- Compilation test stage3 ----"
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_main_assign_var_to_var 10
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_simple_add 5
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_add3 6
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_big_add 66
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_add_identifier 6
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_add_two_identifier 6
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_final_add 34
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_add_postdecl 22

./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_return_add 5
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_return_add3 6
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_return_add_identifier 6
./$TEST_COMPILE_SCRIPT $TEST_STAGE3_DIR gen_return_add_two_identifier 6

exit 0
