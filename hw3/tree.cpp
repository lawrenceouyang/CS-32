	// Return the number of ways that all n2 elements of a2 appear
	// in the n1 element array a1 in the same order (though not
	// necessarily consecutively).
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0)
		return 1;
	if (n1 <= 0 || n2 > n1)
		return 0;
	if (*a1 == *a2)
	{
		int total = countIncludes(a1+1,n1-1,a2+1,n2-1);
		return total + countIncludes(a1+1,n1-1,a2,n2);
	}
	else
		return countIncludes(a1+1,n1-1,a2,n2);
}

	// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

	// Rearrange the elements of the array so that all the elements
	// whose value is > splitter come before all the other elements,
	// and all the elements whose value is < splitter come after all
    // the other elements.
void split(double a[], int n, double splitter,
	                                int& firstNotGreater, int& firstLess)
{
	if (n < 0)
	    n = 0;
	
	    // It will always be the case that just before evaluating the loop
	    // condition:
	    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	    //  Every element earlier than position firstNotGreater is > splitter
	    //  Every element from position firstNotGreater to firstUnknown-1 is
	    //    == splitter
	    //  Every element from firstUnknown to firstLess-1 is not known yet
	    //  Every element at position firstLess or later is < splitter
	
	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
            if (a[firstUnknown] < splitter)
            {
                firstLess--;
                exchange(a[firstUnknown], a[firstLess]);
            }
            else
            {
                if (a[firstUnknown] > splitter)
                {
                    exchange(a[firstNotGreater], a[firstUnknown]);
                    firstNotGreater++;
                }
                firstUnknown++;
            }
	}
}

	// Rearrange the elements of the array so that
	// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
	// If n <= 1, do nothing.
void order(double a[], int n)
{
	if (n <= 1)
		return;
	int fGreater = 0, fLess = 0;
	split(a,n,*a,fGreater,fLess);
	if (fGreater > 0)
		order(a, n);
	else
		order(a+1, n-1);
}
#include <iostream>
using namespace std;

int main()
{
	double num1[6] = {0,1,3,2,1,3};
	double num2[3] = {0,1,3};

	cout << countIncludes(num1,6,num2,3) << endl;

	//int n1 = 0, n2 = 0;
	double numbers[10]= {0, 5, 5, -5555, 0, -30, -30, 15, 0, 999};
	order(numbers,10);

	for (int i = 0; i < 10; i++)
		cout << numbers[i] << endl;
}