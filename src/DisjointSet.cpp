#include "DisjointSet.h"

DisjointSet::DisjointSet(unsigned int data):parent(this),data(data),rank(0){
	
}

DisjointSet::~DisjointSet()
{
}

DisjointSet* DisjointSet::find_set(){
	if (this->parent!=this){
		this->parent= this->parent->find_set();
	}
	return this->parent;
}

DisjointSet* DisjointSet::merge_set(DisjointSet *other_set){
	DisjointSet *parent_this, *parent_other, *merged_parent;
	parent_this=this->find_set();
	parent_other=other_set->find_set();
	
	if(parent_this==parent_other){
		return parent_this;
	}
	
	if(parent_this->rank < parent_other->rank){
		parent_this->parent=parent_other;
		merged_parent=parent_other;
	} else if(parent_this->rank > parent_other->rank){
		parent_other->parent=parent_this;
		merged_parent=parent_this;
	} else {
		parent_other->parent=parent_this;
		parent_this->rank+=1;
		merged_parent=parent_this;
	}
	return merged_parent;
}

unsigned int DisjointSet::get_data(){
	return this->data;
}
