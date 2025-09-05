# Summary
Chrysalis is a C compiler for x86_64 assembly. In other words it translates C code to x86_64 assembly (NASM syntax).
It is built purely for the joy of learning about compiler design and this is not meant to be used.

# Roadmap
I'm using the method described in this [suite of posts](https://norasandler.com/2017/11/29/Write-a-Compiler.html) that is based on Abdulaziz Ghuloum’s ["An Incremental Approach to Compiler Construction"](http://scheme2006.cs.uchicago.edu/11-ghuloum.pdf) as a roadmap.
So the project will be divided into stages and each stage will implement new language features.

## Stage 1
At the end of this stage, the compiler should be able to compile a simple program with a main function that returns an integer. (See example below)
```
int main()
{
    return 2;
}
```
This stage is made of several steps:
- [x] Chrysalis can tokenize (or lex) all stage 1 examples in the test suite.
- [x] Chrysalis can parse a list of tokens to return an AST (abstract syntax tree).
- [x] Using the AST, Chrysalis can generate x86_64 assembly code.

## Stage 2
At the end of this stage, the compiler should be able to compile a simple program with a main function that returns an integer from a variable on the stack. (See example below)
```
int main()
{
    int retval = 0;

    return retval;
}
```
Language support addition:
- Creating `int` variables.
- Assigning integer literal to `int` variables.
- Using `int` variable in `return` statements.  

Requirement for stage2 validation:
- [] Chrysalis can tokenize (or lex) all stage 2 examples in the test suite.
- [] Chrysalis can parse a list of tokens to return an AST.
- [] The parser is made more general.
- [] Using the AST, Chrysalis can generate x86_64 assembly code for stage 2 test files.
- [] No regression - all previous stages tests still pass.

## Future work
At the end of a stage, I decide what I want to do next.  
The features coming after Stage 2 are yet to be decided.

# How to build
## Dependencies
- GCC
- Make
- [Unity](https://github.com/ThrowTheSwitch/Unity) - C unit testing framework

> [!NOTE]
> Unity has been added as a submodule of this repository. Just make sure to pull submodules.
>``` $ git submodule update --init --recursive ```


## Build and run
```
$ make
$ ./chrysalis
```

## Test
```
$ make run_tests
```
