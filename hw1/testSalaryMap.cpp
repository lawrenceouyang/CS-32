#include "SalaryMap.h"
#include <cassert>
using namespace std;

int main()
    {
		SalaryMap SMAP;
		SMAP.add("louis", 5);
		assert(SMAP.salary("louis") == 5);
		SMAP.add("jimmy", 3);
		assert(SMAP.raise("louis", -50));
		assert(SMAP.salary("louis") == 5*(1+(-50.0/100)));
		assert(SMAP.raise("jimmy", 10));
		assert(SMAP.salary("jimmy") == 3*(1+(10.0/100)));
		SMAP.add("vincent", 10);

		//below functions should be false;
		assert(!SMAP.raise("derek", 10));		
		assert(!SMAP.raise("vincent",-200));
		
		SMAP.print();
    }