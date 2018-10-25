#ifndef _RDS_H
#define _RDS_H

#include <vector>
#include <string>
#include "verifiers/verifier.hpp"
#include "rds_utils.hpp"

typedef unsigned int uint;

class graph;

//Russian-Doll-Search
// input: verifier v, graph g, vector for storing the result res
// time limit in seconds
// output: maximum subgraph size in g satisfying v
// res contains the solution, use graph::restore_order to get original nodes
uint rds(verifier* v, graph* g, algorithm_run& runtime);
void print_lb_atomic(int signal);

#endif
