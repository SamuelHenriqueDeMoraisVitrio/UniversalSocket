#!/bin/bash

rm -f a.*

gcc main.c

#if [ $? -ne 0 ]; then
#    exit 1
#fi

nc -l -p 8080 &
