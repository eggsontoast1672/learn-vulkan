#!/bin/sh

if [ ! -f build/compile_commands.json ]
then
  cmake -S . -B build
fi

cmake --build build --target run
