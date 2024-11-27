#!/bin/bash

x86_64-w64-mingw32-gcc ../main.c -static -lws2_32


nc -l -p 8080 &

