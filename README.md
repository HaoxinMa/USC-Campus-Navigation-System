# Trojan-Map  

This is based on the final project of EE599 (Computer Principles) in Spring 2021 at University of Southern California.

Author: Haoxin Ma  
Course Instructor: Arash Saifhashemi  

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
  ```

## Source Code Dependencies 

- ### gcc

  ```shell
  sudo apt update
  sudo apt install build-essential
  ```

- ### git

  ```shell
  sudo apt update
  sudo apt install git
  ```

- ### Qt

  See https://www.qt.io/download  

  ```shell
  sudo apt update
  sudo apt install libglu1-mesa-dev
  ```
