#!/bin/bash

CC='gcc'
CFLAGS='-std=c99 -Werror'

$CC $CFLAGS -c stack.c
$CC $CFLAGS -c main.c
$CC stack.o main.o -o program
