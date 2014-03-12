Notes
-----

*   Strange multiprocessing issues. Patch on top of another thread.

### gcc

*   May need to use `-fno-builtin` to patch some functions like `alloca` and
    `memcpy` which may be optimized by gcc. (C++ only?)
*   Inlining?
*   Read up on standard C/C++ ABI
*   Use `-g` to "reserve" space to overwrite? Linux does something similar for
    ftrace. See also `-p` and `--coverage`. If I use any of them, I break
    ligitimate use.
*   Don't enable optimizations.
