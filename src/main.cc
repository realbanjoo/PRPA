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
    ("output,o", opt::value<std::string>(), "Output file")
    ("file,f", opt::value<std::string>()->default_value("inputs/input.csv"),
     "Input file")
    ("count,c", opt::value<unsigned>()->default_value(60),
     "Number of points to read from the input\n")

    ("serial,s", "Only run in serial")
    ("parallel,p", "Only run in parallel\n")

    ("greedy,g", "Only launch the greedy spanner")
    ("elasticity,e", opt::value<double>()->default_value(1.5),
     "Elasticity of the greedy spanner\n")

    ("theta,t", "Only launch the theta graph")
    ("cones,k", opt::value<unsigned>()->default_value(10),
     "Number of cones division for the theta graph")
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
  if (vm.count("theta") || !vm.count("greedy"))
  {
    if (vm.count("parallel") || !vm.count("serial"))
    {
      double p;
      {
        ScopedTimer st(p);
        g.P_theta_graph(cones);
      }
      std::vector<Edge> res = g.span;
      std::cout << "Parallel theta " << cones << " :" << std::endl
        << " found " << res.size() << " edges \tin "
        << p << " ms." <<  std::endl <<  std::endl;
      if (vm.count("output"))
        g.export_As_Dot(vm["output"].as<std::string>());
      else
        g.export_As_Dot();
      g.clear();
    }
    if (!vm.count("parallel") || vm.count("serial"))
    {
      double s;
      {
        ScopedTimer st(s);
        g.S_theta_graph(cones);
      }
      std::vector<Edge> res = g.span;
      std::cout << "Serial theta " << cones << " :" << std::endl
        << " found " << res.size() << " edges \tin "
        << s << " ms." <<  std::endl <<  std::endl;
      if (vm.count("output"))
        g.export_As_Dot(vm["output"].as<std::string>());
      else
        g.export_As_Dot();
      g.clear();
    }
  }
  if (!vm.count("theta") || vm.count("greedy"))
  {
    if (vm.count("parallel") || !vm.count("serial"))
    {
      double p;
      {
        ScopedTimer st(p);
        g.P_greedy_Spanner(t);
      }
      std::vector<Edge> res = g.span;
      std::cout << "Parallel Greedy " << t << " :" << std::endl
        << " found " << res.size() << " edges \tin "
        << p << " ms." <<  std::endl <<  std::endl;
      if (vm.count("output"))
        g.export_As_Dot(vm["output"].as<std::string>());
      else
        g.export_As_Dot();
      g.clear();
    }
    if (!vm.count("parallel") || vm.count("serial"))
    {
      double s;
      {
        ScopedTimer st(s);
        g.S_greedy_Spanner(t);
      }
      std::vector<Edge> res = g.span;
      std::cout << "Serial Greedy " << t << " :" << std::endl
        << " found " << res.size() << " edges \tin "
        << s << " ms." <<  std::endl <<  std::endl;
      if (vm.count("output"))
        g.export_As_Dot(vm["output"].as<std::string>());
      else
        g.export_As_Dot();
      g.clear();
    }
  }
  return 0;
}

