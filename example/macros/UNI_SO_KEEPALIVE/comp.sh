#!/bin/bash
gcc main.c --static > /dev/null 2>&1
x86_64-w64-mingw32-gcc main.c -static -lws2_32 > /dev/null 2>&1
./a.out
wine a.exe
