Try comparing assembly instruction with `-O0` and `-O3`:
```
gcc -g -std=c99 -O0 -c norestrict.c
gcc -g -std=c99 -O0 -c norestrict.c
```


Using the `-S` option to gcc or g++ will run the preprocessor, perform the
initial compilation, and stop before the assembler runs.

If you want to use an object file instead and get the assembler unstructions
from there then use
```
objdump -S --disassemble code > code.dump
```

This option works best if debugging option is enabled for the object file (-g
at compilation time) and the file hasn't been stripped.
