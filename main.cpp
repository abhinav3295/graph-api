#include <stdio.h>
#include "Graph.h"
#include <vector>

using namespace std;
void print_graph(Graph graph){
	vector<edge_t> edge_list= graph.get_edges();
	for (uint8_t i=0;i<edge_list.size();i++)
		printf("%u %u\n",edge_list[i].start,edge_list[i].end);
}
int main(int argc, char **argv)
{
	Graph graph=Graph("C:\\Users\\Suryavanshi\\Documents\\Projects\\graph-api\\input\\edge_list.txt", true);
	vector<node_t> sorted_verticies=Graph::toposort(graph);
	for(int i=0;i<sorted_verticies.size();i++)
		printf("%u\n",sorted_verticies[i]);
	return 0;
}
