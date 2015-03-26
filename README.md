# About
This is a [Private Information Retrieval (PIR)](http://en.wikipedia.org/wiki/Private_information_retrieval) implementation built on top of [HElib](https://github.com/shaih/HElib/). HElib implements the crypto system described in [Fully Homomorphic Encryption without Bootstrapping](http://eprint.iacr.org/2011/277.pdf) by Brakerski, Gentry and Vaikuntanathan. The description of this specific PIR protocol can be found in [this paper](https://personal.cis.strath.ac.uk/changyu.dong/papers/pir.pdf).

# Setup & Dependencies
### Installing HElib
I have included a script (install_HElib) that can be run from terminal to install HElib and all of it's dependencies. If the script doesn't work you can always refer [here](https://github.com/shaih/HElib/blob/master/INSTALL.txt) for manual installation instructions.
### Environment Config
In order to build the program the makefile needs to know where the HElib directory is. Set the HElib directory as an environment variable. (e.g. export HELIB=/path/to/HElib, I recommend putting this in your bash profile). You should also have a C++ compiler that supports C++11 (e.g. Clang 3.3 and later, GCC 4.7 and later).

# Building & Running
To build the program simply run make in the src directory (Currently the makefile only supports building in OS X, Linux support is coming!). This will produce an executable named PIR, which can be run.
### Parameters
There are several parameters that can be passed to the executable. The first one is the query index, which indicates which element in the DB to retrieve. This value can be anywhere in the range [0, # of DB elements). The second parameter denotes the order of the finite field that all database elements are in. This value MUST be a prime. The defaults are query index = 0 and finite field order = 2 (i.e. all DB elements are either 0 or 1).

# Acknowledgements
This work would not be possible without the awesome[HElib](https://github.com/shaih/HElib) and [NTL](http://www.shoup.net/ntl/) libraries. For more information on them you can start [here](https://eprint.iacr.org/2014/106.pdf) and [here](http://www.cs.dartmouth.edu/~ccpalmer/classes/cs50/Content/Resources/refman.pdf).

# TL;DR
1. $ ./install_HElib
2. $ cd src
3. $ make
4. $ ./PIR [query index] [finite field order]
