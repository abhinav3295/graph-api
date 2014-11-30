#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include <set>
#include <stdexcept>
#include <string>
using namespace std;
typedef unsigned int node_t;
struct edge_t{
	node_t start;
	node_t end;
	edge_t(node_t start, node_t end);
};

class Graph
{
	map<node_t,set<node_t> > outgoing_adjacency_list;
	map<node_t,set<node_t> > incoming_adjacency_list;
	set<node_t> node_list;
	const bool directed_graph;
public:
	Graph(bool directed_graph=false);
	Graph(vector<edge_t>  edge_list,bool directed_graph=false);
	Graph(char* edge_list_file, bool directed_graph=false);
	~Graph();
	bool add_edge(edge_t edge);
	bool remove(edge_t edge);
	vector<edge_t> get_edges(void);
	vector<edge_t> get_incoming_edges(node_t node);
	vector<edge_t> get_outgoing_edges(node_t node);
	
	set<node_t> get_nodes(void);
	vector<node_t> get_root_nodes(void);
	vector<node_t> get_leaf_nodes(void);
	
	// Graph Algorithms
	static vector<node_t> toposort(Graph graph);
};

class GraphException: public runtime_error{
	public: 
		explicit GraphException(const string& msg):runtime_error(msg){};
};
#endif // GRAPH_H
