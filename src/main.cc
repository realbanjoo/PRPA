/** main.cc **/
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>

#include "geometric_spanner.hh"
#include "scoped_timer.hh"


namespace opt = boost::program_options;


int main(int argc, char *argv[])
{
  opt::variables_map vm;
  opt::options_description desc("Usage: spanner [OPTIONS] \nThe options are");
  desc.add_options()
    ("help,h", "Give this help list")
    ("count,c", opt::value<unsigned>()->default_value(50),
     "Number of points to take into account (default 50)")
    ("file,f", opt::value<std::string>()->default_value("inputs/input.csv"),
     "Input file (default is inputs/input.csv")
    ("parallel,p", "Whether to run in parallel or not")
    ("serial,s", "Whether to run in serial or not")
    ("elasticity,e", opt::value<double>()->default_value(1.5),
     "Elasticity (default is 1.5)")
    ("theta,t", "Launches theta graph")
    ("cones,k", opt::value<unsigned>()->default_value(2),
     "number of cones for the theta graph")
    ;
  try
  {
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);
    if (vm.count("help"))
    {
      std::cout << desc << '\n';
      return 0;
    }
  }
  catch (opt::error& e)
  {
    std::cerr << e.what() << std::endl
              << desc << std::endl;
    return 1;
  }
  // Parse parameter of program ( input file, then number max of towns)
  std::string path = vm["file"].as<std::string>();
  unsigned count = vm["count"].as<unsigned>();
  double t = vm["elasticity"].as<double>();
  unsigned cones = vm["cones"].as<unsigned>();

  Geometric_Spanner g(path, count);
  if (vm.count("theta"))
  {
    double p;
    {
      ScopedTimer st(p);
      g.S_theta_graph(cones);
    }
    std::vector<Edge> res = g.span;
    std::cout << "Serial theta2:" << std::endl
      << " found " << res.size() << " edges \tin "
      << p << " ms." <<  std::endl;
    g.export_As_Dot("outputs/theta_2.png");
    g.clear();
    cones = 4; 
    {
      ScopedTimer st(p);
      g.S_theta_graph(cones);
    }
    res = g.span;
    std::cout << "Serial theta4:" << std::endl
      << " found " << res.size() << " edges \tin "
      << p << " ms." <<  std::endl;
    g.export_As_Dot("outputs/theta_4.png");
    g.clear();
    cones = 8; 
    {
      ScopedTimer st(p);
      g.S_theta_graph(cones);
    }
    res = g.span;
    std::cout << "Serial theta8:" << std::endl
      << " found " << res.size() << " edges \tin "
      << p << " ms." <<  std::endl;
    g.export_As_Dot("outputs/theta_8.png");
    return 0;
  }
  if (vm.count("parallel") || !vm.count("serial"))
  {
    double p;
    {
      ScopedTimer st(p);
      g.P_greedy_Spanner(t);
    }
    std::vector<Edge> res2 = g.span;
    std::cout << "Parallel:" << std::endl
      << " found " << res2.size() << " edges \tin "
      << p << " ms." <<  std::endl;
  }
  g.clear();
  if (!vm.count("parallel") || vm.count("serial"))
  {
    double s;
    {
      ScopedTimer st(s);
      g.S_greedy_Spanner(t);
    }
    std::vector<Edge> res1 = g.span;
    std::cout << "Serial:" << std::endl
      << " found " << res1.size() << " edges \tin "
      << s << " ms." <<  std::endl;
  }
    return 0;
}

