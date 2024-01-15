#! /bin/bash

user="users"

if [ -e "$user/$1" ]; then
    find "$user/$1" -type f -name *.txt > filepath.txt
fi



