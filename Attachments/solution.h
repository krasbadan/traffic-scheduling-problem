#include "bits/stdc++.h"
using namespace std;
/*
The link_t type is a vector contains 6 integers as below:
    node 1 ID
    node 2 ID
    the cost of the link between node 1 and node 2 (bidirectional)
    the capacity of the link (bidirectional)
    the utilized bandwidth from node1 to node2 (unidirectional)
    the utilized bandwidth from node2 to node1 (unidirectional)
*/
using link_t = vector< int >;

void Solution(int n, int m, vector< link_t > links, int tau, int K);