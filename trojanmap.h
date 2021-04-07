#ifndef TROJANMAP_H
#define TROJANMAP_H

#include <QDebug>
#include <QFile>
#include <QString>
#include <QStringList>
#include <algorithm>
#include <cfloat>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
  pair<double, double> GetPositionFromID(const string &id);
  double CalculateDistance(const Node &a, const Node &b);
  double CalculatePathLength(const vector<string> &path);
  pair<double, vector<vector<string>>> TravellingTrojan(vector<string> &location_ids);
  pair<double, vector<string>> CalculateShortestPath_Dijkstra(string location1_name, string location2_name);

 private:
  void TravellingTrojan_(vector<string> &ids, vector<vector<string>> &paths, vector<string> &cur_path, double &cur_dis,
                         double &min_dis);
};

#endif // TROJANMAP_H
