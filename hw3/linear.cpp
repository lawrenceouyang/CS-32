#include <cassert>
#include <iostream>
using namespace std;

    // Return true if any of the array elements is negative, false
	// otherwise.
bool anyNegative(const double a[], int n)
{
	if (n <= 0)
		return false;
	if (*a < 0)
		return true;
	anyNegative(a+1,n-1);
}

	// Return the number of negative elements in the array.
int countNegatives(const double a[], int n)
{
	if (n <= 0)
		return 0;
	if (*a < 0)
		return (1 + countNegatives(a+1,n-1));
	else
		return countNegatives(a+1,n-1);
}

	// Return the subscript of the first negative element in the array.
	// If no element is negative, return -1.
int firstNegative(const double a[], int n)
{
	if (n <= 0)
		return -1;
	if (*a < 0)
		return 0;
	if (firstNegative(a+1, n-1) == -1)
		return -1;
	else
		return firstNegative(a+1,n-1)+1;
}

	// Return the subscript of the smallest element in the array.  If
	// more than one element has the same smallest value, return the
	// smallest subscript of such an element.  If the array has no
	// elements to examine, return -1.
int indexOfMin(const double a[], int n)
{
	if (n <= 0)
		return -1;
	if (n == 1)
		return 0;
	int smallestOfRest = indexOfMin(a+1,n-1)+1;
	if (*a <= *(a + smallestOfRest))
		return 0;
	else
		return smallestOfRest;
}

	// If all n2 elements of a2 appear in the n1 element array a1, in
	// the same order (though not necessarily consecutively), then
	// return true; otherwise (i.e., if the array a1 does not include
	// a2 as a not-necessarily-contiguous subsequence), return false.
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 <= 0)
		return true;
	if (n1 <= 0 || n2 > n1)
		return false;
	if (*a1 == *a2)
		return includes(a1+1,n1-1,a2+1,n2-1);
	else
		return includes(a1+1,n1-1,a2,n2);

}

//int main() //do more test cases later
//{
//	double numbers[5] = {0,1,2,3,4};
//	double numbers2[3] = {1,2,4};
//	cout << anyNegative(numbers,5)<< endl;
//	cout << countNegatives(numbers,5) << endl;
//	cout << firstNegative(numbers,5) << endl;
//	cout << indexOfMin(numbers,5) << endl;
//	assert(!includes(numbers, 0, numbers2, 1));
//}