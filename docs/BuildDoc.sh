#!/bin/bash

echo $(pwd)

verbosity=""
while [[ "$1" =~ ^- && ! "$1" == "--" ]]; do case $1 in
  -v | --verbose )
    verbosity="1"
    ;;
esac; shift; done

if [[ $verbosity -eq 0 ]]; then
  exec 3>&1 &>/dev/null
else
  exec 3>&1
fi

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

if [[ ! -e "env" ]]; then
  echo -e "Creating python virtual environment..." >&3
  python3 -m venv env

  if [[ $? -ne 0 ]] ; then
    echo -e "${RED}Could not create virtualenv${RESET}" >&3
    exit 1
  fi

fi

echo -e "Entering python virtual environment..." >&3
source env/bin/activate

echo "Installing dependencies..." >&3
python3 -m pip install breathe sphinx_rtd_theme

if [[ $? -ne 0 ]] ; then
    echo -e "${RED}Could not install dependencies${RESET}" >&3
    exit 1
  fi

echo "Deleting old documentation files..." >&3
rm -rf xml

echo "Extracting xml data with doxygen..." >&3
doxygen Doxyfile

if [[ $? -ne 0 ]] ; then
    echo -e "${RED}Could not use Doxygen. Make sure it is installed and a Doxyfile exists${RESET}" >&3
    exit 1
  fi

echo "Deleting old documentation build..." >&3
rm -rf build

echo "Building html..." >&3
make html

if [[ $? -ne 0 ]] ; then
    echo -e "${RED}Could not build html. Make sure the sphinx Makefile exists${RESET}" >&3
    exit 1
  fi

echo -e "${GREEN}Documentation built at $(pwd)/build/html/index.html !${RESET}" >&3

deactivate
exit 0