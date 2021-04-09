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

## Output Preview

  ### Automobile path planning using Dijkstra Algorithm

  ![Picture1](https://user-images.githubusercontent.com/61277885/113846032-a4dafb00-97c8-11eb-8ba9-3b28b566157e.png)

  ### Helicopter path planning (TSP) using brute-force backtracking 

  ![Picture2](https://user-images.githubusercontent.com/61277885/113848234-d654c600-97ca-11eb-8b36-ad71781dd2f8.png)

## Acknowledgement

Special thanks to:
		Dr. Arash Saifhashemi (Lecturer)
		Dr. Hong-Shuo Chen (Teaching Assistant)
		Huaqian Fu
for their guidance or for bugs reporting to this project.