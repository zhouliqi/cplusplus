# C++ Study

## Valgrind

> Valgrind is an instrumentation framework for building dynamic analysis tools. [see here](https://valgrind.org/)

```bash
# install
sudo apt-get install valgrind
```

```bash
# usage
valgrind --tool=memcheck --leak-check=yes ./a.out
```

## Disassembly

```bash
g++ -c -o main main.cc

objdump -d main
```

