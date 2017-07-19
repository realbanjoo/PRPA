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
  g.P_greedy_Spanner(10);
    return 0;
}

