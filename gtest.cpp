#include <gtest/gtest.h>

#include <cmath>

#include "trojanmap.h"

using namespace std;

TEST(Autocomplete, InvalidInput) {
  TrojanMap x;
  vector<string> exp;  // expects null

  // Test for null input
  auto res = x.Autocomplete("");
  EXPECT_EQ(res, exp);

  // Test for random input
  res = x.Autocomplete("this is a random input");
  EXPECT_EQ(res, exp);
}

TEST(Autocomplete, ValidIInput) {
  TrojanMap x;
  vector<string> exp = {"USC Fisher Museum of Art", "USC Village Gym", "USC Parking", "USC Village Dining Hall"};

  auto res = x.Autocomplete("USC");
  EXPECT_EQ(res, exp);

  res = x.Autocomplete("usc");
  EXPECT_EQ(res, exp);

  res = x.Autocomplete("UsC");
  EXPECT_EQ(res, exp);
}

TEST(GetPosition, InvalidInput) {
  TrojanMap x;
  pair<double, double> exp(181, 91);

  // Test for null input
  auto res = x.GetPosition("");
  EXPECT_EQ(res, exp);

  // Test for random input
  res = x.GetPosition("this is a random input");
  EXPECT_EQ(res, exp);
}

TEST(GetPosition, ValidInput) {
  TrojanMap x;

  pair<double, double> exp1(-118.2825307, 34.0167334);
  auto res = x.GetPosition("ChickfilA");
  EXPECT_EQ(res, exp1);

  pair<double, double> exp2(-118.2908339, 34.0317653);
  res = x.GetPosition("Ralphs");
  EXPECT_EQ(res, exp2);

  pair<double, double> exp3(-118.2843512, 34.0257016);
  res = x.GetPosition("Target");
  EXPECT_EQ(res, exp3);
}

TEST(Dijkstra, InvalidInput) {
  TrojanMap x;
  vector<string> exp_path;  // expects null

  // Test for null input
  pair<double, vector<string>> exp = make_pair(-1, exp_path);
  auto res = x.Dijkstra("", "");
  EXPECT_EQ(res, exp);

  // Test for random input
  res = x.Dijkstra("random_id1", "random_id2");
  EXPECT_EQ(res, exp);
}

TEST(Dijkstra, ValidInput1) {
  TrojanMap x;

  // Test from Ralphs to ChickfilA
  vector<string> exp_path = {
      "2578244375", "5559640911", "6787470571", "6808093910", "6808093913", "6808093919", "6816831441", "6813405269",
      "6816193784", "6389467806", "6816193783", "123178876",  "2613117895", "122719259",  "2613117861", "6817230316",
      "3642819026", "6817230310", "7811699597", "5565967545", "123318572",  "6813405206", "6813379482", "544672028",
      "21306059",   "6813379476", "6818390140", "63068610",   "6818390143", "7434941012", "4015423966", "5690152766",
      "6813379440", "6813379466", "21306060",   "6813379469", "6813379427", "123005255",  "6807200376", "6807200380",
      "6813379451", "6813379463", "123327639",  "6813379460", "4141790922", "4015423963", "1286136447", "1286136422",
      "4015423962", "6813379494", "63068643",   "6813379496", "123241977",  "4015372479", "4015372477", "1732243576",
      "6813379548", "4015372476", "4015372474", "4015372468", "4015372463", "6819179749", "1732243544", "6813405275",
      "348121996",  "348121864",  "6813405280", "1472141024", "6813411590", "216155217",  "6813411589", "1837212103",
      "1837212101", "6820935911", "4547476733"};
  pair<double, vector<string>> exp = make_pair(1.53852, exp_path);
  auto res = x.Dijkstra("2578244375", "4547476733");
  EXPECT_LT(fabs(res.first - exp.first), 0.0001);
  EXPECT_EQ(res.second, exp.second);

  // Reverse the input from Ralphs to ChickfilA
  reverse(exp_path.begin(), exp_path.end());
  exp = make_pair(1.53852, exp_path);
  res = x.Dijkstra("4547476733", "2578244375");
  EXPECT_LT(fabs(res.first - exp.first), 0.0001);
  EXPECT_EQ(res.second, exp.second);
}

TEST(Dijkstra, ValidInput2) {
  TrojanMap x;

  // Test from Target to Popeyes Louisiana Kitchen
  vector<string> exp_path = {
      "5237417650", "6813379479", "5237381975", "4399698012", "4399698013", "4399698011", "4399698010", "123044712",
      "4399698009", "4399698008", "123005253",  "6813379513", "6813379517", "6813379521", "123327627",  "4399697999",
      "6813565290", "122719210",  "6813379407", "2613117879", "6813379406", "6807905595", "6787803635", "2613117867",
      "4835551110", "6813565296", "122719205",  "6813565294", "4835551232", "4835551104", "4012842272", "4835551103",
      "123178841",  "6813565313", "122814435",  "6813565311", "4835551228", "6813513565", "4835551090", "4835551081",
      "6813513564", "20400292",   "5556117120", "5556117115", "4835551064", "4012842277", "6813565326", "123241961",
      "6813565322", "4835551070", "5695236164"};
  pair<double, vector<string>> exp = make_pair(0.74044, exp_path);
  auto res = x.Dijkstra("5237417650", "5695236164");
  EXPECT_LT(fabs(res.first - exp.first), 0.0001);
  EXPECT_EQ(res.second, exp.second);

  // Reverse the input from Popeyes Louisiana Kitchen to Target
  reverse(exp_path.begin(), exp_path.end());
  exp = make_pair(0.74044, exp_path);
  res = x.Dijkstra("5695236164", "5237417650");
  EXPECT_LT(fabs(res.first - exp.first), 0.0001);
  EXPECT_EQ(res.second, exp.second);
}

TEST(Dijkstra, ValidInput3) {
  TrojanMap x;

  // Test from ExpoVermont to LATTCOrtho Institute
  vector<string> exp_path = {
      "4400281325", "6813379567", "123112726",  "6813379571", "7023424984", "123112725",  "4015405540", "213431695",
      "7023430193", "213431822",  "7023424981", "441891112",  "932401855",  "4015405541", "6820935897", "1781230449",
      "4015405542", "4015405543", "1837212104", "123112723",  "6813405278", "348121864",  "348121996",  "6813411585",
      "4015405552", "4399914028", "6820972462", "269633270",  "4015405553", "4399914049", "5472460620", "214470792",
      "1841835270", "4011837222", "1841835282", "122855868",  "63785495",   "6208583983", "4011837227", "122855866",
      "63785502",   "7040336497", "4011837230", "4060116190", "63785514",   "4835549601", "2193435045", "63785522",
      "4400460716", "6816193807", "1732340067", "4400460727", "4400460729", "4400460730", "4400460733", "4400460734",
      "4400460735", "5555281222"};
  pair<double, vector<string>> exp = make_pair(1.48636, exp_path);
  auto res = x.Dijkstra("4400281325", "5555281222");
  EXPECT_LT(fabs(res.first - exp.first), 0.0001);
  EXPECT_EQ(res.second, exp.second);

  // Reverse the input from LATTCOrtho Institute to ExpoVermont
  reverse(exp_path.begin(), exp_path.end());
  exp = make_pair(1.48636, exp_path);
  res = x.Dijkstra("5555281222", "4400281325");
  EXPECT_LT(fabs(res.first - exp.first), 0.0001);
  EXPECT_EQ(res.second, exp.second);
}

// Test for null input
TEST(TSP, InvalidInput) {
  TrojanMap x;
  double exp_length = -1;
  vector<string> input;
  auto res = x.TSP(input);
  EXPECT_EQ(res.first, exp_length);
  EXPECT_EQ(res.second.empty(), true);
}

TEST(TSP, ValidInput1) {
  TrojanMap x;
  double exp_length = 3.74928;
  vector<string> exp_path = {"1873056015", "213332060", "1931345270", "6905329551", "1873056015"};
  vector<string> input = {"1873056015", "6905329551", "213332060", "1931345270"};
  auto res = x.TSP(input);
  EXPECT_LT(fabs(res.first - exp_length), 0.0001);
  auto res_path = (res.second)[res.second.size() - 1];
  bool is_equal1 = res_path == exp_path;
  reverse(res_path.begin(), res_path.end());
  bool is_equal2 = res_path == exp_path;
  EXPECT_EQ(is_equal1 || is_equal2, true);
}

TEST(TSP, ValidInput2) {
  TrojanMap x;
  double exp_length = 4.13936;
  vector<string> exp_path = {"1862312636", "4015405548", "4015203110", "6807439002",
                             "7424270441", "67666219",   "1862312636"};
  vector<string> input = {"1862312636", "7424270441", "67666219", "4015405548", "4015203110", "6807439002"};
  auto res = x.TSP(input);
  EXPECT_LT(fabs(res.first - exp_length), 0.0001);
  auto res_path = (res.second)[res.second.size() - 1];
  bool is_equal1 = res_path == exp_path;
  reverse(res_path.begin(), res_path.end());
  bool is_equal2 = res_path == exp_path;
  EXPECT_EQ(is_equal1 || is_equal2, true);
}

TEST(TSP, ValidInput3) {
  TrojanMap x;
  double exp_length = 4.61742;
  vector<string> exp_path = {"123120189",  "1931345270", "4011837224", "4011837229", "2514542032", "2514541020",
                             "6807909279", "63068532",   "214470792",  "4015477529", "123120189"};
  vector<string> input = {"123120189",  "4011837229", "4011837224", "2514542032", "2514541020",
                          "1931345270", "4015477529", "214470792",  "63068532",   "6807909279"};
  auto res = x.TSP(input);
  EXPECT_LT(fabs(res.first - exp_length), 0.0001);
  auto res_path = (res.second)[res.second.size() - 1];
  bool is_equal1 = res_path == exp_path;
  reverse(res_path.begin(), res_path.end());
  bool is_equal2 = res_path == exp_path;
  EXPECT_EQ(is_equal1 || is_equal2, true);
}
