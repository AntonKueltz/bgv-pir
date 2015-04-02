# About
This is a [Private Information Retrieval (PIR)](http://en.wikipedia.org/wiki/Private_information_retrieval) implementation built on top of [HElib](https://github.com/shaih/HElib/). HElib implements the crypto system described in [Fully Homomorphic Encryption without Bootstrapping](http://eprint.iacr.org/2011/277.pdf) by Brakerski, Gentry and Vaikuntanathan. The description of this specific PIR protocol can be found in [this paper](https://personal.cis.strath.ac.uk/changyu.dong/papers/pir.pdf). Distribution is under the terms of the [GNU General Public License](http://www.gnu.org/licenses/gpl.html) (GPL).

# Setup & Dependencies
### Installing HElib
I have included a script (install_HElib) that can be run from terminal to install HElib and all of it's dependencies. If the script doesn't work you can always refer [here](https://github.com/shaih/HElib/blob/master/INSTALL.txt) for manual installation instructions. A common issue is that the makefile does not use the `-std=c++11` flag to compile HElib. To fix this the following should be done:

1. uncomment line 18 of HElib/src/Makefile and add " -std=c++11" to the end of the line.
2. remove "=40" from line 1394 in HElib/src/NumbTh.cpp (c++11 doesn't like this for some reason).

### Environment Config
In order to build the program the makefile needs to know where the HElib directory is. Set the HElib directory as an environment variable. (e.g. `export HELIB=/path/to/HElib`, I recommend putting this in your bash profile). You should also have a C++ compiler that supports C++11 (e.g. Clang 3.3 and later, GCC 4.7 and later).

# Building & Running
To build the program simply run `make` in the src directory (Currently the makefile only supports building in OS X, Linux support is coming!). This will produce an executable named PIR, which can be run.
### Parameters
There are several parameters that can be passed to the executable. The first one is the query index, which indicates which element in the DB to retrieve. This value can be anywhere in the range [0, # of DB elements). The second parameter denotes the order of the finite field that all database elements are in. This value MUST be a prime. The defaults are query index = 0 and finite field order = 2 (i.e. all DB elements are either 0 or 1).

# Acknowledgements
This work would not be possible without the awesome [HElib](https://github.com/shaih/HElib) and [NTL](http://www.shoup.net/ntl/) libraries. For more information on them you can start [here](https://eprint.iacr.org/2014/106.pdf) and [here](http://www.cs.dartmouth.edu/~ccpalmer/classes/cs50/Content/Resources/refman.pdf).

# TL;DR
```
./install_HElib
cd src
make
./PIR [query index] [finite field order]
```
