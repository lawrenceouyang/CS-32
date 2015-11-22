#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool clearSpaces(string& s);                                          //Clears spaces in infix & checks all characters
bool syntaxCheck(const string& s, const char& c, const int& i);       //Checks operator syntax errors
bool applyOperator(const char& s, const bool& b1, const bool& b2);    //Apply the operator

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
	int pLeft = 0, pRight = 0;                          //Counts number of parantheses pairs
	postfix = "";
	stack<char> operation;
	if(!clearSpaces(infix))                             //Clear spaces/checks for alpha characters
		return 1;

	for (unsigned int i = 0; i < infix.size(); i++)
	{
		if (isdigit(infix[i]))                          //Operand
			postfix += infix[i];
		else if (infix[i] == '(')                       //Open Parenthesis
		{
			if (i != 0)
				if (isdigit(infix[i-1]))                //Checks for digits before parenthesis
					return 1;
			operation.push(infix[i]);
			pLeft++;
		}
		else if (infix[i] == ')')                       //Closed Parenthesis
		{
			if (pLeft < pRight)                         //Checks for proper number of parenthesis
				return 1;

			while (operation.top() != '(')
			{
				postfix += operation.top();
				operation.pop();
			}
			operation.pop();
			pRight++;
		}
		else if (infix[i] == '!')
		{
			if(!syntaxCheck(infix, infix[i], i))
				return 1;
			operation.push(infix[i]);
		}
		else if (infix[i] == '&' || infix[i] == '|')
		{
			if(!syntaxCheck(infix, infix[i], i))
				return 1;
			
			while (infix[i] == '&' && !operation.empty() && operation.top() != '(' && operation.top() != '|')
				{
					postfix += operation.top();
					operation.pop();
				}
			while (infix[i] == '|' && !operation.empty() && operation.top() != '(') 
				{
					postfix += operation.top();
					operation.pop();
				}
			operation.push(infix[i]);
		}
	}

	if (pLeft != pRight)                                  //check for incorrect parenthesis syntax
		return 1;

	while (!operation.empty())
	{
		postfix += operation.top();
		operation.pop();
	}                                                     //End of infix to postfix

	stack<bool> boolStack;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (isdigit(postfix[i]))
		{
			boolStack.push(values[postfix[i]-48]);
		}
		else if (postfix[i] == '!')
		{
			bool op = boolStack.top();
			boolStack.pop();
			boolStack.push(!op);
		}
		else
		{
			bool op2 = boolStack.top();
			boolStack.pop();
			bool op1 = boolStack.top();
			boolStack.pop();
			boolStack.push(applyOperator(postfix[i], op1, op2));
		}
	}
	result = boolStack.top();

	return 0;
}

bool clearSpaces(string& s)
{
	string temp = "";
	for (unsigned int i = 0; i < s.size();i++)           //Clear spaces for easier functions
	{
		if (s[i] != ' ')
			temp += s[i];
		if (!isdigit(s[i]) && s[i] != '!' && s[i] != '|' && s[i] != '&' 
			&& s[i] != ' ' && s[i] != '(' && s[i] != ')')//Checks for non-functional chars
			return false;
	}
	s = temp;

	bool testop1 = false, testop2 = false;
	for (unsigned int i = 0; i < s.size(); i++)         //Checks for both an operator and operand
	{
		if (!isdigit(s[i]) || (s.size() == 1 && isdigit(s[0]))) //Second check for only digit and no operators
			testop1 = true;
		if (isdigit(s[i]))
			testop2 = true;
	}
	return testop1 & testop2;
}

bool syntaxCheck(const string& s, const char& c, const int& i)
{
	switch (c)
	{
	case '!':
		if (i == s.size()-1) return false;                   //Checks for unary at end
		if (i != 0 && isdigit(s[i-1])) return false; break;  //Checks for digits before unary
	case '|':
	case '&':
		if (i == 0 || i == s.size()-1) return false;         //Checks for operator and beginning or end
		if (!isdigit(s[i+1]) && s[i+1] != '(' && s[i+1] != '!' 
			&& !isdigit(s[i-1]) && s[i-1] != ')') return false; break; //Checks for operands before and after operator
	default: return true;
	}
	return true;
}

bool applyOperator(const char& s, const bool& b1, const bool& b2)
{
	if (s == '|')
		return(b2|b1);
	if (s == '&')
		return(b2&b1);

	return false;
}

//int main()
//{
//	bool ba[10] = {
//	//  0      1      2      3      4      5      6      7      8      9
//	true,  true,  true,  false, false, false, true,  false, true,  false
//	};
//	string pf;
//	bool answer;
//	assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
//	assert(evaluate("8|", ba, pf, answer) == 1);
//	assert(evaluate("4 5", ba, pf, answer) == 1);
//	assert(evaluate("01", ba, pf, answer) == 1);
//	assert(evaluate("()", ba, pf, answer) == 1);
//	assert(evaluate("2(9|8)", ba, pf, answer) == 1);
//	assert(evaluate("2(&8)", ba, pf, answer) == 1);
//	assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
//	assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
//			&&  pf == "43!03&&|"  &&  !answer);
//	assert(evaluate("", ba, pf, answer) == 1);
//	assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
//	ba[2] = false;
//	ba[9] = true;
//	assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
//	assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
//	cout << "Passed all tests" << endl;
//}