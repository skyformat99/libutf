#!/bin/bash

if [ ! -e "travis-ci/build.bash" ]; then
	echo "must use this script from project's root directory"
	exit 1
fi

mkdir -p build/standard && cd build/standard
cmake ../..
cmake --build .
ctest --verbose --output-on-failure
cd ../..

