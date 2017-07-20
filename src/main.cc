/** main.cc **/
#include <iostream>
#include <vector>

#include "geometric_spanner.hh"
#include "scoped_timer.hh"


int main (int argc, char* argv[])
{
  // Parse parameter of program ( input file, then number max of towns)
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
  long t = 2;
  double s;
  {
    ScopedTimer st(s);
    g.S_greedy_Spanner(t);
  }
  std::vector<Edge> res1 = g.span;
  std::cout << "Serial:" << std::endl
    << " found " << res1.size() << " edges \tin "
    << s << " ms." <<  std::endl;

  g.clear();

  double p;
  {
    ScopedTimer st(p);
    g.P_greedy_Spanner(t);
  }
  std::vector<Edge> res2 = g.span;
  std::cout << "parallel:" << std::endl 
    << " found " << res2.size() << " edges \tin "
    << p << " ms." <<  std::endl;

    return 0;
}

