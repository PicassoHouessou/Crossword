#! /bin/bash

user="users"

if [ -e "$user/$1" ]; then
    cp -r "tmp/sauvegardes" "$user/$1"
else
    if [ -e $user ]; then
        cd $user;mkdir $1;cd ..;cp -r "tmp/sauvegardes" "$user/$1"
    else
        mkdir $user;cd $user;mkdir $1;cd ..;cp -r "tmp/sauvegardes" "$user/$1"
    fi
fi



