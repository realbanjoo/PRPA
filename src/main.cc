/** main.cc **/
#include <iostream>
#include <vector>

#include "geometric_spanner.hh"
#include "scoped_timer.hh"

int main (int argc, char* argv[])
{
  std::string path;
  unsigned count;
  if (argc < 3)
  {
    count = 50;
    if (argc < 2)
      path = "inputs/input.csv";
    else
      path = argv[1];
  }
  else 
  {
    path = argv[1];
    count = stoi(std::string(argv[2]));
  }

  Geometric_Spanner g(path, count);

  std::cout << "greedy comparison of " << count
    << " cities of " << path << std::endl;
  std::cout << g.points.size() << " cities found" << std::endl;

  double normal;
  {
    ScopedTimer t(normal);
    g.greedy_Spanner(1.05);
  }
  g.clear();
  double opt;
  {
    ScopedTimer t(opt);
    g.OPT_greedy_Spanner(1.05);
  }
  std::cout << "Normal took\t" << normal << " ms." << std::endl;
  std::cout << "Opt took\t" << opt << " ms." << std::endl;
  /*
  std::string s = "50_cities_";
  Geometric_Spanner g("input.csv", 50);
  for (float i = 1; i < 1.5; i+=0.1)
  {
    std::string s2 = s + std::to_string(i).substr(0, 3) + ".dot";
    std::cout << s2 << std::endl;
    g.greedy_Spanner(i);
    g.export_As_Dot(s2);
  }
  for (unsigned i = 2; i < 8; i*=2)
  {
    std::string s2 = s + std::to_string(i) + ".dot";
    std::cout << s2 << std::endl;
    g.greedy_Spanner(i);
    g.export_As_Dot(s2);
  }
  */
  // Longer over 200 cities
  /*
  Geometric_Spanner g("input.csv", 200);
    g.greedy_Spanner(1.1);
    g.export_As_Dot("200_cities_1.1.dot");
    std::cout << std::endl << std::endl << "ended 1.1" << std::endl
      << "Start 1.4" << std::endl << std::endl;
    g.greedy_Spanner(2);
    g.export_As_Dot("200_cities_2.dot");
    std::cout << std::endl << std::endl << "ended 1.4" << std::endl;
    */
  return 0;
}

