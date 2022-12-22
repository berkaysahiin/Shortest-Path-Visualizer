#!/bin/bash

SOURCES="src/main.cpp src/Grid.cpp"
HEADERS="src/Grid.h"
LIBS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"

g++ $SOURCES $HEADERS $LIBS
