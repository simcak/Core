#!/bin/bash

export DEBUG_FLAG="-DDEBUG=1"

while true; do
	find . \( -name \*.hpp -o -name \*.cpp \)  | entr -cr bash command.entr.sh 
done
