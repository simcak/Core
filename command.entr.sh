#!/bin/bash

export DEBUG_FLAG="-DDEBUG=1"

make re && ./ircserv 6697 h
