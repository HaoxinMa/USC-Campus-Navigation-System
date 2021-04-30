#ifndef TROJANMAP_H
#define TROJANMAP_H

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
 public:
  string id;                 // A unique id assigned to each point
  double lat;                // Latitude
  double lon;                // Longitude
  string name;               // Name of the location
  vector<string> neighbors;  // List of the ids of all neighbor points

  Node();
  Node(const Node &n);
};

class TrojanMap {
 public:
  map<string, Node> data;

  TrojanMap();
  vector<string> Autocomplete(string name);
  string GetID(const string &name);
  pair<double, double> GetPosition(const string &name);
  double CalculateDistance(const Node &a, const Node &b);
  double CalculatePathLength(const vector<string> &path);
  pair<double, vector<string>> Dijkstra(string id1, string id2);
  pair<double, vector<vector<string>>> TSP(vector<string> &location_ids);
  pair<double, vector<vector<string>>> TSP_2opt(vector<string> &location_ids);

 private:
  void TSP(vector<string> &ids, vector<vector<string>> &paths, vector<string> &cur_path, double &cur_dis,
           double &min_dis);
  void UpdatePaths(vector<vector<string>> &paths, vector<string> &cur_path, int left, int right);
};

#endif // TROJANMAP_H
