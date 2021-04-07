#include "trojanmap.h"

Node::Node(){};
Node::Node(const Node &n) {
  id = n.id;
  lat = n.lat;
  lon = n.lon;
  name = n.name;
  neighbors = n.neighbors;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
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
  transform(name.begin(), name.end(), name.begin(), ::tolower);
  for (auto &pr : data) {
    string str(pr.second.name);
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
  for (auto &pr : data) {
    if (pr.second.name == name) {
      return make_pair(pr.second.lon, pr.second.lat);
    }
  }
  return make_pair(0, 0);
}

pair<double, double> TrojanMap::GetPositionFromID(const string &id) {
  for (auto &pr : data) {
    if (pr.first == id) {
      return make_pair(pr.second.lon, pr.second.lat);
    }
  }
  return make_pair(0, 0);
}

/**
 * CalculateDistance: Get the distance between 2 nodes.
 *
 * @param  {Node} a  : node a
 * @param  {Node} b  : node b
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const Node &a, const Node &b) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c; where 3961 is the approximate radius of the earth at the latitude of Washington D.C. in miles
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2), 2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2), 2.0);
  double c = 2 * asin(min(1.0, sqrt(p)));
  return c * 3961;
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
 * Travelling salesman problem: Given a list of locations, return the shortest path which visit all the places and back
 * to the start point.
 *
 * @param  {vector<string>} input                : a list of locations needs to visit
 * @return {pair<double, vector<vector<string>>} : a pair of total distance and the all the progress to get final path
 */
pair<double, vector<vector<string>>> TrojanMap::TravellingTrojan(vector<string> &location_ids) {
  vector<vector<string>> path;
  vector<string> cur_path;
  double min_dis = 0, cur_dis = 0;
  TravellingTrojan_(location_ids, path, cur_path, cur_dis, min_dis);
  return make_pair(min_dis, path);
}

void TrojanMap::TravellingTrojan_(vector<string> &ids, vector<vector<string>> &paths, vector<string> &cur_path,
                                  double &cur_dis, double &min_dis) {
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
    if (find(cur_path.begin(), cur_path.end(), ids[i]) == cur_path.end()) {
      double delta_dis = CalculateDistance(data[cur_path.back()], data[ids[i]]);
      cur_dis += delta_dis;
      cur_path.push_back(ids[i]);
      TravellingTrojan_(ids, paths, cur_path, cur_dis, min_dis);
      cur_path.pop_back();
      cur_dis -= delta_dis;
    }
  }
}

vector<string> TrojanMap::CalculateShortestPath_Dijkstra(string location1_name, string location2_name) {
  vector<string> path;
  unordered_map<string, double> dis(data.size());  // <ID, distance>
  string id1 = GetID(location1_name), id2 = GetID(location2_name);

  // initialization
  for (auto &pr : data) {
    dis[pr.first] = DBL_MAX;
  }

  // update with the distance to the neighbors of id1
  for (auto &id : data[id1].neighbors) {
    dis[id] = CalculateDistance(data[id1], data[id]);
  }

  path.push_back(id1);

  while (path.size() < data.size()) {
    double min_dis = DBL_MAX * 0.9;

    // find an unvisited neighbor with min distance
    string u;
    for (auto &pr : dis) {
      auto a = find(path.begin(), path.end(), pr.first);
      if (path.end() == a) {  // this is unvisited
        if (pr.second < min_dis) {
          min_dis = pr.second;
          u = pr.first;
        }
      }
    }
    path.push_back(u);
    if (u == id2) break;  // the destination has been found

    // update with the distance to the neighbors of u
    for (auto &id : data[u].neighbors) {
      dis[id] = min(dis[id], min_dis + CalculateDistance(data[u], data[id]));
    }
  }
  return path;
}
