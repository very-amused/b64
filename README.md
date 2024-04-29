# b64
A small Base64 encoding/decoding library written with a focus on code quality.

## Building and Linking
```sh
make
```

b64 can be consumed by running `make` to build a static archive at `b64.a`. Alternatively, `src/base64.c` itself (122 SLOC) can be easily added to any project. Add `b64/include` to your include path and `#include <base64.h>`. A runnable demo can be built with `make demo`.

## Project Inclusion
b64 can be added to any Git-managed project as a submodule.
```sh
git submodule add https://github.com/very-amused/b64 b64
```

## Intellisense (clangd)
```sh
make clean; bear -- make
```
