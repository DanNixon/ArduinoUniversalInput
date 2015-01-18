#!/bin/bash

# Tool for converting Arduino IDE projects to inotool projects

OPTIND=1

current_dir=$(pwd)

# Get some input
verbose=0
arduino_project_dir=""
ino_project_dir=""
libraries=()

while getopts "h?va:i:l:" opt; do
  case "$opt" in
    h|\?)
      echo "A tool for converting Arduino IDE projects to intotool projects."
      echo "-h Help"
      echo "-v Verbose"
      echo "-a Path to Arduino project"
      echo "-i Path to inotool project to be created"
      echo "-l Path to an Arduino library used"
      exit 0
      ;;
    v)
      verbose=1
      ;;
    a)
      arduino_project_dir="$OPTARG"
      ;;
    i)
      ino_project_dir="$OPTARG"
      ;;
    l)
      libraries+=("$OPTARG")
      ;;
  esac
done

shift $((OPTIND-1))
[ "$1" = "--" ] && shift

# Do verbose stuff
if [ $verbose -eq 1 ]; then
  echo $arduino_project_dir
  echo $ino_project_dir
  echo ${libraries[@]}
fi

# CHeck the inotool project folder does not already exist
if [ -d "$ino_project_dir" ]
then
  echo "Inotool directory already exists"
  exit 1
fi

# Make the inotool project
mkdir -p "$ino_project_dir"
cd "$ino_project_dir"
ino init
rm src/*
cd "$current_dir"

# Copy the source
cp -r "$arduino_project_dir"/* "$ino_project_dir"/src

# Copy libraries, exclusing the examples folder
for lib_dir in ${libraries[@]}; do
  lib_name=$(basename "$lib_dir")
  ino_lib_dir="$ino_project_dir"/lib/"$lib_name"
  mkdir "$ino_lib_dir"
  find "$lib_dir"/* -type f -not -path "*/examples*" -execdir cp {} "$ino_lib_dir" \;
done
