#include "trojanmap.h"

#include <math.h>

#include <QFile>
#include <QString>
#include <QStringList>
#include <algorithm>
#include <cfloat>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

Node::Node(){};
Node::Node(const Node &n) {
  id = n.id;
  lat = n.lat;
  lon = n.lon;
  name = n.name;
  neighbors = n.neighbors;
}

/**
 * TrojanMap: Read the map data from the csv file
 *
 */
TrojanMap::TrojanMap() {
  QFile qf(":/map.csv");
  qf.open(QIODevice::ReadOnly);
  qf.readLine();  // read the first line and then drop
  while (!qf.atEnd()) {
    Node node;
    QString line = qf.readLine();
    QStringList word_list;
    word_list << line.split(',');
    node.id = word_list[0].toStdString();
    node.lat = word_list[1].toDouble();
    node.lon = word_list[2].toDouble();
    node.name = word_list[3].toStdString();
    vector<string> nb;
    for (int i = 4; i < word_list.size(); i++) {
      string one_nb = word_list[i].toStdString();
      one_nb.erase(remove_if(one_nb.begin(), one_nb.end(),
                             [](char c) -> bool {
                               return (c == '\'' || c == '"' || c == '[' || c == ']' || c == '\n' || c == ' ');
                             }),
                   one_nb.end());
      nb.push_back(one_nb);
    }
    node.neighbors = nb;
    data[node.id] = node;
  }
  qf.close();
}

/**
 * Autocomplete: Given a parital name return all the possible locations with partial name as the prefix.
 *
 * @param  {string} name     : partial name
 * @return {vector<string>}  : a vector of full names
 */
vector<string> TrojanMap::Autocomplete(string name) {
  vector<string> results;
  if (name.empty()) return results;
  transform(name.begin(), name.end(), name.begin(), ::tolower);
  for (auto &pr : data) {
    string str;
    str.resize(pr.second.name.size());
    transform(pr.second.name.begin(), pr.second.name.end(), str.begin(), ::tolower);
    if (name == str.substr(0, name.size())) {
      results.push_back(pr.second.name);
    }
  }
  return results;
}

string TrojanMap::GetID(const string &name) {
  for (auto &pr : data) {
    if (pr.second.name == name) {
      return pr.first;
    }
  }
  return "";
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {string} name          : location name
 * @return {pair<double,double>}  : (lat, lon)
 */
pair<double, double> TrojanMap::GetPosition(const string &name) {
  if (name.empty()) return make_pair(181, 91);
  for (auto &pr : data) {
    if (pr.second.name == name) {
      return make_pair(pr.second.lon, pr.second.lat);
    }
  }
  return make_pair(181, 91);
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 *
 * @param  {Node} a  : node a
 * @param  {Node} b  : node b
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const Node &a, const Node &b) {
  // Use Haversine Formula
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(min(1.0, sqrt(p)));
  return c * 3961;  // where 3961 is the approximate radius of the earth at the latitude of Washington D.C. in miles
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 *
 * @param  {vector<string>} path : path
 * @return {double}              : path length
 */
double TrojanMap::CalculatePathLength(const vector<string> &path) {
  double sum = 0;
  for (unsigned long i = 0; i < path.size() - 1; i++) {
    sum += CalculateDistance(data[path[i]], data[path[i + 1]]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {string} id1                   : id which represents the place you start from
 * @param  {string} id2                   : id which represents the place you will go to
 * @return {pair<double, vector<string>>} : a pair of total distance and the all the progress to get final path
 */
pair<double, vector<string>> TrojanMap::Dijkstra(string id1, string id2) {
  vector<string> path;
  // dis: <id, <id's_predecessor, distance_from_id1_to_id>
  unordered_map<string, pair<string, double>> dis(data.size());
  // q: <distance_from_id1_to_id, id>
  priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> q;
  bool is_id2_visited = false;
  if (id1 == "" || id2 == "") return make_pair(-1, path);

  // initialization
  for (auto &pr : data) {
    dis[pr.first] = make_pair("", DBL_MAX);
  }
  dis[id1].second = 0;
  q.push(make_pair(0, id1));

  // update distance
  double path_dis = DBL_MAX;
  while (!q.empty()) {
    string id = q.top().second;
    if (id == id2) {
      is_id2_visited = true;
      path_dis = q.top().first;
      break;
    }
    q.pop();
    for (auto nb_id : data[id].neighbors) {
      double new_dis = dis[id].second + CalculateDistance(data[id], data[nb_id]);
      if (new_dis < dis[nb_id].second) {
        dis[nb_id] = make_pair(id, new_dis);
        q.push(make_pair(new_dis, nb_id));
      }
    }
  }

  if (!is_id2_visited) return make_pair(-1, path);

  // backtrack predecessors of id2
  string id = id2;
  while (id != "") {
    path.push_back(id);
    id = dis[id].first;
  }
  reverse(path.begin(), path.end());
  return make_pair(path_dis, path);
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest path which visit all the places and back
 * to the start point.
 *
 * @param  {vector<string>} input                : a list of locations needs to visit
 * @return {pair<double, vector<vector<string>>} : a pair of total distance and the all the progress to get final path
 */
pair<double, vector<vector<string>>> TrojanMap::TSP(vector<string> &location_ids) {
  vector<vector<string>> path;
  if (location_ids.size() <= 1) return make_pair(-1, path);
  vector<string> cur_path;
  double min_dis = 0, cur_dis = 0;
  TSP(location_ids, path, cur_path, cur_dis, min_dis);
  return make_pair(min_dis, path);
}

void TrojanMap::TSP(vector<string> &ids, vector<vector<string>> &paths, vector<string> &cur_path, double &cur_dis,
                    double &min_dis) {
  // each cur_path starts from ids[0]
  if (cur_path.empty()) {
    cur_dis = 0;
    cur_path.push_back(ids[0]);
  }

  // each cur_path ends at ids[0]
  if (cur_path.size() == ids.size()) {
    double delta_dis = CalculateDistance(data[cur_path.back()], data[ids[0]]);
    if (min_dis == 0 || cur_dis + delta_dis < min_dis) {
      min_dis = cur_dis + delta_dis;
      cur_path.push_back(ids[0]);
      paths.push_back(cur_path);  // save cur_path to path in descending order
      cur_path.pop_back();
    }
    return;
  }

  // early backtracking
  if (min_dis && cur_dis >= min_dis) {
    return;
  }

  // iterate children
  for (unsigned long i = 1; i < ids.size(); i++) {
    if (count(cur_path.begin(), cur_path.end(), ids[i]) == 0) {
      double delta_dis = CalculateDistance(data[cur_path.back()], data[ids[i]]);
      cur_dis += delta_dis;
      cur_path.push_back(ids[i]);
      TSP(ids, paths, cur_path, cur_dis, min_dis);
      cur_path.pop_back();
      cur_dis -= delta_dis;
    }
  }
}

pair<double, vector<vector<string>>> TrojanMap::TSP_2opt(vector<string> &location_ids) {
  vector<vector<string>> paths;  // store the progress
  int size = location_ids.size();

  // initialize the path
  vector<string> initial_path;
  double initial_length = 0;
  initial_path.assign(location_ids.begin(), location_ids.end());
  initial_path.push_back(location_ids[0]);
  paths.push_back(initial_path);
  for (unsigned long i = 0; i < initial_path.size() - 1; i++) {
    initial_length += CalculateDistance(data[initial_path[i]], data[initial_path[i + 1]]);
  }

  // 2-opt, get a shorter path
  vector<string> cur_path = initial_path;
  double change_length;
  double min_change;
  bool isImproved = true;
  int left;
  int right;
  while (isImproved) {
    isImproved = false;
    min_change = 0;
    left = 0;
    right = 0;
    for (int i = 1; i < size - 1; i++) {
      for (int j = i + 1; j < size; j++) {
        change_length = CalculateDistance(data[cur_path[i - 1]], data[cur_path[j]]) +
                        CalculateDistance(data[cur_path[i]], data[cur_path[j + 1]]) -
                        CalculateDistance(data[cur_path[i - 1]], data[cur_path[i]]) -
                        CalculateDistance(data[cur_path[j]], data[cur_path[j + 1]]);
        if (change_length < min_change) {
          min_change = change_length;
          left = i;
          right = j;
          isImproved = true;
        }
      }
    }
    // generate the shorter path and put it in paths
    if (isImproved) {
      UpdatePaths(paths, cur_path, left, right);
    }
  }

  // generate final length
  double final_length = 0;
  for (unsigned long i = 0; i < paths[paths.size() - 1].size(); i++) {
    if (i == paths[paths.size() - 1].size() - 1) {
      final_length += CalculateDistance(data[paths[paths.size() - 1][i]], data[paths[paths.size() - 1][0]]);
    } else {
      final_length += CalculateDistance(data[paths[paths.size() - 1][i]], data[paths[paths.size() - 1][i + 1]]);
    }
  }

  pair<double, vector<vector<string>>> results(final_length, paths);
  return results;
}

void TrojanMap::UpdatePaths(vector<vector<string>> &paths, vector<string> &cur_path, int left, int right) {
  swap(cur_path[left], cur_path[right]);
  paths.push_back(cur_path);
}
