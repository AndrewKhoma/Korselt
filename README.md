# Korselt
Provide simple library on C++ to check whether the number is a Carmichael number.

# How to run

* Install CMake version higher or equal 3.8.0 and C++ that supports c++14 standard.
* Run Korselt criterion:
  ```
  cmake .
  make
  cd korselt
  ./korselt <number from 0 to 10^18>
  ```
* Run google tests:
  ```
  cmake .
  make
  cd tests
  ./google_test
  ```