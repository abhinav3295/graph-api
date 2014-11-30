#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
using namespace std;

edge_t::edge_t(node_t start,node_t end):start(start),end(end){
}

Graph::Graph(bool directed_graph) : directed_graph(directed_graph)
{
}

Graph::Graph(vector<edge_t>  edge_list, bool directed_graph) : directed_graph(directed_graph)
{
	for(uint8_t i=0;i<edge_list.size();i++){
		this->add_edge(edge_list[i]);
	}
}

Graph::Graph(char*  edge_list_file, bool directed_graph) : directed_graph(directed_graph)
{
	ifstream graph_input_stream;
	string connected_nodes;
	graph_input_stream.open(edge_list_file);
	if(graph_input_stream.is_open()){
		while(getline(graph_input_stream,connected_nodes)){
			istringstream iss(connected_nodes);
			node_t nodes[2];
			for(int i=0;i<2;i++){
				iss>>nodes[i];
			}
			this->add_edge(edge_t(nodes[0],nodes[1]));
		}
	}else {
		throw GraphException("Cannot read input file");
	}
	graph_input_stream.close();
}


Graph::~Graph()
{
}

bool Graph::add_edge(edge_t edge){
	bool add_success;
	this->node_list.insert(edge.start);
	this->node_list.insert(edge.end);
	add_success = this->outgoing_adjacency_list[edge.start].insert(edge.end).second;
	if(this->directed_graph && add_success){
		add_success = this->incoming_adjacency_list[edge.end].insert(edge.start).second;
	}
	return add_success;
}

bool Graph::remove(edge_t edge){
	bool remove_success;
	remove_success= this->outgoing_adjacency_list[edge.start].erase(edge.end)==1;
	if(this->directed_graph && remove_success){
		remove_success = this->incoming_adjacency_list[edge.end].erase(edge.start)==1;
	}
	return remove_success;
}

vector<edge_t> Graph::get_incoming_edges(node_t node){
	vector<edge_t> incoming_edges;
	map<node_t,set<node_t> > adjacency_list;
	if(this->directed_graph){
		adjacency_list=this->incoming_adjacency_list;
	} else {
		adjacency_list=this->outgoing_adjacency_list;
	}
	for (set<node_t>::iterator itr = adjacency_list[node].begin(); itr != adjacency_list[node].end(); itr++){
		incoming_edges.push_back(edge_t(*itr,node));
	}
	return incoming_edges;
}

vector<edge_t> Graph::get_outgoing_edges(node_t node){
	vector<edge_t> outgoing_edges;
	for (set<node_t>::iterator itr = this->outgoing_adjacency_list[node].begin(); itr != outgoing_adjacency_list[node].end(); itr++){
		outgoing_edges.push_back(edge_t(node,*itr));
	}	
	return outgoing_edges;
}

vector<edge_t> Graph::get_edges(){
	vector<edge_t> edge_list;
	set<node_t>::iterator itr_edge_list;
	map<node_t,set<node_t> >::iterator itr_map;
	for (itr_map=this->outgoing_adjacency_list.begin();itr_map!=this->outgoing_adjacency_list.end();itr_map++){
		for (itr_edge_list = itr_map->second.begin(); itr_edge_list != itr_map->second.end(); itr_edge_list++){
			edge_list.push_back(edge_t(itr_map->first,*itr_edge_list));
		}
	}
	return edge_list;
}

set<node_t> Graph::get_nodes(void){
	return this->node_list;
}

vector<node_t> Graph::get_root_nodes(void){
	vector<node_t> root_node_list;
	set<node_t>::iterator itr;
	for(itr=this->node_list.begin();itr!=this->node_list.end();itr++){
		if(this->incoming_adjacency_list[*itr].size()==0){
			root_node_list.push_back(*itr);
		}
	}
	return root_node_list;
}

vector<node_t> Graph::get_leaf_nodes(void){
	vector<node_t> leaf_node_list;
	set<node_t>::iterator itr;
	for(itr=this->node_list.begin();itr!=this->node_list.end();itr++){
		if(this->outgoing_adjacency_list[*itr].size()==0){
			leaf_node_list.push_back(*itr);
		}
	}
	return leaf_node_list;
}

vector<node_t> Graph::toposort(Graph graph){
	vector<node_t> sorted_nodes;
	queue<node_t> nodes_with_no_incoming_edges;
	vector<node_t> root_nodes = graph.get_root_nodes();
	vector<node_t>::iterator itr;
	for(itr=root_nodes.begin();itr!=root_nodes.end();itr++){
		nodes_with_no_incoming_edges.push(*itr);
	}
	while(nodes_with_no_incoming_edges.size()){
		node_t node=nodes_with_no_incoming_edges.front();
		sorted_nodes.push_back(node);
		vector<edge_t> outgoing_edges=graph.get_outgoing_edges(node);
		vector<edge_t>::iterator itr_out_edge;
		for(itr_out_edge=outgoing_edges.begin();itr_out_edge!=outgoing_edges.end();itr_out_edge++){
			graph.remove(*itr_out_edge);
			if(graph.get_incoming_edges(itr_out_edge->end).size()==0){
				nodes_with_no_incoming_edges.push(itr_out_edge->end);
			}
		}
		nodes_with_no_incoming_edges.pop();
	}
	return sorted_nodes;
}