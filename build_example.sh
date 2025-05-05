#!/usr/bin/env bash
echo GameBreaker Compiler

mypath=""

if [$1 -eq ""]; then
    read -p "Input the directory to your source code: " $mypath
else
    mypath=$1;
fi

if [$mypath -eq ""]; then 
    exit
fi

echo Got the source code directory, it is $mypath
echo Okay, building...

g++ -o game.o -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lm -O2 `pkg-config --cflags --libs gtk+-3.0` -B gb/*.cpp -B $mypath
