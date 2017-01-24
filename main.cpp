#include <cstdio>
#include <string>
#include <algorithm>
#include "rds.h"
#include "graph.h"
#include "verifier.h"

using namespace std;

void show_usage(const char* argv)
{
  printf("Usage: %s [options] <dimacs input file>\nAvailable options:\n", argv);
  printf("Maximum Solvers:\n\t-c\tClique\n\t-s\tStable set\n\t-d n\tn-defective clique\n");
  printf("\t-iuc\tIndependent Union of Cliques\n");
  printf("Vertex ordering:\n");
  printf("\t-vd\tdegree from large to small\n");
  printf("\t-vd2\t2-neighborhood from large to small\n");
  printf("\t-vr\trandom ordering\n");
  printf("\t-vc n\tn-color ordering\n");
  printf("\t-vrev\treverse ordering\n");
  printf("-h|-?\tdisplay this help\n");
}

int main(int argc, char* argv[])
{
  printf("Russian-Doll-Search\nCopyright Eugene Lykhovyd, 2017\n");
  if(argc < 2 || string(argv[1]) == "-h" || string(argv[1]) == "-?") {
    show_usage(argv[0]);
  } else {
    graph * g = from_dimacs(argv[argc-1]); // last argument must be filename
    if(!g)
    {
      fprintf(stderr, "Failure: no input graph, exiting...\n");
      return 1;
    }
    verifier* v = 0;
    for(int i = 1; i < argc-1; ++i)
    {
      // so ugly, but switch refuses to compare strings
      if(string(argv[i]) == "-c") { if(v) delete v; v = new clique(); }
      else if (string(argv[i]) == "-s") { if(v) delete v; v = new stable(); }
      else if (string(argv[i]) == "-d") { if(v) delete v; v = new defective_clique(atoi(argv[i+1])); i++; }
      else if (string(argv[i]) == "-iuc") { if(v) delete v; v = new iuc(); }

      else if (string(argv[i]) == "-vd") { g->reorder_degree(); }
      else if (string(argv[i]) == "-vd2") { g->reorder_2nb(); }
      else if (string(argv[i]) == "-vr") { g->reorder_random(); }
      else if (string(argv[i]) == "-vc") { g->reorder_color(atoi(argv[i+1])); i++; }
      else if (string(argv[i]) == "-vrev") { g->reorder_rev(); }
      else {
          fprintf(stderr, "Wrong parameter: %s\n", argv[i]);
          if(v) delete v; delete g; return 1;
      }
    }
    vector<uint> res_p;
    uint res = rds(v, g, res_p);
    printf("Solution verification: ");
    if(v->check_solution(g, res_p))
      printf("CORRECT\n");
    else
      printf("INCORRECT\n");
    g->restore_order(res_p);
    sort(res_p.begin(), res_p.end());
    printf("---------------------------------\nSolution:\n");
    for(uint i = 0; i < res_p.size(); ++i)
      printf("%u ", res_p[i]+1);
    printf("\nRDS returned res = %d\n", res);
    delete g;
  }

  return 0;
}