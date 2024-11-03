set shell := ["nu", "-c"]

run: compile
    @ ./bin/main.exe

compile:
    @ mkdir bin
    @ cc main.c -o bin/main.exe
