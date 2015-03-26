Crypto System based on "Fully Homomorphic Encryption without Bootstrapping" by Brakerski, Gentry and Vaikuntanathan

# How To Compile And Run
1. Set HElib dir as an env var. (e.g. export HELIB=/path/to/HElib
2. g++ <nameOfTargetFile.cpp> $HELIB/src/fhe.a -I$HELIB/src -o App -L/usr/local/lib -lntl -lgmp -std=c++11
3. run program via ./App
