#include <UnitTest++.h>
#include "DisjointSet.h"
SUITE(disjoint_set){
	TEST(constructor){
		DisjointSet a(20);
	}
	TEST(find_set){
		DisjointSet a(20);
		CHECK_EQUAL(a.find_set(),&a);
	}
	TEST(merge_set){
		DisjointSet a(20),b(40),c(80);
		unsigned int previous_rank;
		previous_rank = a.find_set()->rank;
		a.merge_set(&b);
		CHECK_EQUAL(a.find_set(),b.find_set());
		CHECK_EQUAL(a.find_set()->rank,previous_rank+1);
		CHECK_EQUAL(b.find_set()->rank,previous_rank+1);
		
		b.merge_set(&c);
		CHECK_EQUAL(a.find_set(),c.find_set());
		
		previous_rank = a.find_set()->rank;
		b.merge_set(&c);
		CHECK_EQUAL(a.find_set()->rank, previous_rank);
	}
}