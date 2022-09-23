[![Build and Unit Test](https://github.com/cpp-core/util/actions/workflows/build.yaml/badge.svg)](https://github.com/cpp-core/util/actions/workflows/build.yaml)

# Utilities


## At A Glance


## Installation

    git clone https://github.com/cpp-core/depends
	mkdir depends/build && cd depends/build
    CC=clang-mp-11 CXX=clang++-mp-11 cmake -DCMAKE_INSTALL_PREFIX=$HOME/opt -DUTIL_TEST=ON ..
	make util-check # Run tests
	make util       # Build and install
