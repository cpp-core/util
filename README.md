[![Build and Unit Test](https://github.com/melton1968/cxx-core-util/actions/workflows/build.yaml/badge.svg)](https://github.com/melton1968/cxx-core-util/actions/workflows/build.yaml)

# Utilities


## At A Glance


## Installation

### Using cxx-depends (Recommended)

    git clone git@github.com:melton1968/cxx-depends
	mkdir cxx-depends/build && cd cxx-depends/build
    CC=clang-mp-11 CXX=clang++-mp-11 cmake -DCMAKE_INSTALL_PREFIX=$HOME/opt -DCORE_FP_TEST=ON ..
	make cxx_core_util_check # Run tests
	make cxx_core_util       # Build and install
	
### Standalone

	git clone git@github.com:melton1968/cxx-core-util
	mkdir cxx-core-util/build && cd cxx-core-util/build
    CC=clang-mp-11 CXX=clang++-mp-11 cmake -DCMAKE_INSTALL_PREFIX=$HOME/opt -DCORE_FP_TEST=ON ..
	make check    # Run tests
	make install  # Install
	
Compiling and running the tests requires cxx_core_stream, fmt,
googletest and json to be installed. This happens automagically when
using cxx-depends.
	
	
