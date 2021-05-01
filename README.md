# Trojan-Map  

This Project is based on the final project of EE599 (Computer Principles) in Spring 2021 at University of Southern California.

Author: Haoxin Ma 

## Overview  

  ### Data structure  

  ```c++
  class Node {
   public:
    string id;                 // A unique id assigned to each point
    double lat;                // Latitude
    double lon;                // Longitude
    string name;               // Name of the location
    vector<string> neighbors;  // List of the ids of all neighbor points
  };

  class TrojanMap {
   public:
    map<string, Node> data;    // A map of ids to Nodes
  };
  ```

## Source Code Dependencies 

The developing environment is: Ubuntu 20.04 LTS, gcc 9.3, Qt 5.15.
It is highly recommended to update your environment to the latest stable version.

- ### gcc

  ```shell
  sudo apt update
  sudo apt install build-essential
  ```

- ### Qt

  See https://www.qt.io/download to download and install.

  Additionally, to support OpenGL, please do the following:

  ```shell
  sudo apt update
  sudo apt install libglu1-mesa-dev
  ```

- ### Google Test

  ```shell
  mv gtest_dependency.pri ./googletest
  ```

## Output Preview

  ### Automobile path planning using Dijkstra Algorithm

  ![Picture1](https://user-images.githubusercontent.com/61277885/113846032-a4dafb00-97c8-11eb-8ba9-3b28b566157e.png)

  ### Helicopter path planning (TSP) using brute-force backtracking 

  ![Picture2](https://user-images.githubusercontent.com/61277885/113848234-d654c600-97ca-11eb-8b36-ad71781dd2f8.png)

The 2-opt heuristic algorithm is more efficient but less accurate to get the solution.

## Unit Testing

Use GoogleTest for unit testing in `gtest.cpp`

Here is the output in terminal if everything is ok.

```shell
[==========] Running 12 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from Autocomplete
[ RUN      ] Autocomplete.InvalidInput
[       OK ] Autocomplete.InvalidInput (14 ms)
[ RUN      ] Autocomplete.ValidIInput
[       OK ] Autocomplete.ValidIInput (14 ms)
[----------] 2 tests from Autocomplete (29 ms total)

[----------] 2 tests from GetPosition
[ RUN      ] GetPosition.InvalidInput
[       OK ] GetPosition.InvalidInput (11 ms)
[ RUN      ] GetPosition.ValidInput
[       OK ] GetPosition.ValidInput (11 ms)
[----------] 2 tests from GetPosition (22 ms total)

[----------] 4 tests from Dijkstra
[ RUN      ] Dijkstra.InvalidInput
[       OK ] Dijkstra.InvalidInput (11 ms)
[ RUN      ] Dijkstra.ValidInput1
[       OK ] Dijkstra.ValidInput1 (19 ms)
[ RUN      ] Dijkstra.ValidInput2
[       OK ] Dijkstra.ValidInput2 (15 ms)
[ RUN      ] Dijkstra.ValidInput3
[       OK ] Dijkstra.ValidInput3 (19 ms)
[----------] 4 tests from Dijkstra (65 ms total)

[----------] 4 tests from TSP
[ RUN      ] TSP.InvalidInput
[       OK ] TSP.InvalidInput (10 ms)
[ RUN      ] TSP.ValidInput1
[       OK ] TSP.ValidInput1 (10 ms)
[ RUN      ] TSP.ValidInput2
[       OK ] TSP.ValidInput2 (11 ms)
[ RUN      ] TSP.ValidInput3
[       OK ] TSP.ValidInput3 (149 ms)
[----------] 4 tests from TSP (182 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 4 test suites ran. (300 ms total)
[  PASSED  ] 12 tests.
```

