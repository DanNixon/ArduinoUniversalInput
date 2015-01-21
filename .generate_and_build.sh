#!/bin/bash

# Generates a inotool project and builds it
# Only really to be used for Travi

PATH=`echo $PATH | sed -e 's/:\.\/node_modules\/\.bin//g'`

result=0

build()
{
  ino build -v -m $1
  code=$?
  if [ $code -ne 0 ]; then
    echo "Build for $1 failed with code $code"
    result=$code
  fi
}

current_dir=$(pwd)

project_dir="$1"
project_name=$(basename $project_dir)

# Generate the inotool project
./arduino_to_ino.sh -v -a "$project_dir" -i "$project_name" -l UniversalInput -l UniversalButtons -l UniversalJoysticks

cd "$project_name"

# Do some test builds
build "uno"
build "mega2560"

cd $current_dir
rm -r "$project_name"

exit $result
