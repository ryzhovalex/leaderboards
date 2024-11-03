set shell := ["nu", "-c"]

run: compile
    @ ./bin/main.exe

compile:
    @ mkdir bin
    @ cc main.c -lws2_32 -o bin/main.exe

client_connect:
    python client.py
