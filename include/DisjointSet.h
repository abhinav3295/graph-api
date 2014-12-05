#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSet
{
	DisjointSet *parent;
	unsigned int data;
public:
	unsigned int rank;
	DisjointSet(unsigned int data);
	~DisjointSet();
	DisjointSet *find_set();
	DisjointSet *merge_set(DisjointSet *other_set);
	unsigned int get_data();
};

#endif // DISJOINTSET_H
