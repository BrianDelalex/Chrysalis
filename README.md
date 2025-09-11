# Summary
Chrysalis is a C compiler for x86_64 assembly. In other words it translates C code to x86_64 assembly (NASM syntax).
It is built purely for the joy of learning about compiler design and this is not meant to be used.

# Roadmap
As the roadmap keeps getting bigger, I've moved it to its [own page](https://github.com/BrianDelalex/Chrysalis/wiki/Roadmap).

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
