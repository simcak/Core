#!/bin/bash

while true; do
	find . \( -name \*.hpp -o -name \*.cpp \)  | entr -cr bash command.entr.sh 
done
