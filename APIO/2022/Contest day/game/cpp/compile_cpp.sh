#!/bin/bash

TASK=game

g++ -std=gnu++17 -o ${TASK} grader.cpp ${TASK}.cpp
