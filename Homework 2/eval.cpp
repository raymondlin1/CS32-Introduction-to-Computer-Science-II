#include "Map.h"
#include <stack>
#include <string>
#include <iostream>
#include <cassert>
#include <cctype>
using namespace std;

bool hasPrecedence(char op1, char op2);
bool isOperand(char c);
bool isOperator(char c);
bool hasValidSyntax(string s);
string elimWhiteSpace(string s);
string infixToPostfix(string infix);
int evalPostfix(string postfix, const Map &values);

int evaluate(string infix, const Map& values, string& postfix, int& result)
// Evaluates an integer arithmetic expression
//   If infix is a syntactically valid infix integer expression whose
//   only operands are single lower case letters (whether or not they
//   appear in the values map), then postfix is set to the postfix
//   form of the expression; otherwise postfix may or may not be
//   changed, result is unchanged, and the function returns 1.  If
//   infix is syntactically valid but contains at least one lower
//   case letter operand that does not appear in the values map, then
//   result is unchanged and the function returns 2.  If infix is
//   syntactically valid and all its lower case operand letters
//   appear in the values map, then if evaluating the expression
//   (using for each letter in the expression the value in the map
//   that corresponds to it) attempts to divide by zero, then result
//   is unchanged and the function returns 3; otherwise, result is
//   set to the value of the expression and the function returns 0.

{
	if (infix == "")
		return 1;
	infix = elimWhiteSpace(infix);
	bool validSyntax = hasValidSyntax(infix);

	if (validSyntax)
	{
		postfix = infixToPostfix(infix);
		//check if values are mapped
		for (int j = 0; j < postfix.size(); j++)
		{
			if (isOperand(postfix[j]) && !values.contains(postfix[j]))
				return 2;
		}

		//check if divide by zero
		
		for (int k = 0; k < infix.size() - 1; k++)
		{
			char temp1 = infix[k];
			int temp2;
			if (infix[k + 1] == '(')
			{
				string x = "";
				int n = k + 2;
				while (infix[n] != ')')
				{
					x += infix[n];
					n++;
				}
				temp2 = evalPostfix(infixToPostfix(x), values);
			}
			else
				values.get(infix[k + 1], temp2);
			
			if (temp1 == '/' && temp2 == 0)
				return 3;
		}
		
	}
	else {
		return 1;
	}
	result = evalPostfix(postfix, values);
	return 0;
}

bool hasValidSyntax(string s)
{
	int nOperator = 0;
	int nOperand = 0;
	int nOpen = 0;
	int nClosed = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (isOperand(s[i]))
			nOperand++;
		else if (isOperator(s[i]))
			nOperator++;
		else if (s[i] == '(')
			nOpen++;
		else if (s[i] == ')')
			nClosed++;

		if (i == 0)
		{
			if (s[i] == ')' || isOperator(s[i]))
				return false;
		}
		else if (i > 0)
		{
			if (isOperand(s[i - 1]) && !isOperator(s[i]) && s[i] != ')' )
				return false;
		}			
	}

	if (nOpen != nClosed)
		return false;
	if (nOperator != nOperand - 1)
		return false;
	return true;
}

bool hasPrecedence(char op1, char op2)
{
	if (op1 == '(' || op1 == ')')
	{
		if (op2 == '(' || op2 == ')')
		{
			return false;
		}
		return true;
	}
	else if (op1 == '*' || op1 == '/' || op1 == '%')
	{
		if (op2 == '(' || op2 == ')' || op2 == '*' || op2 == '/' || op2 == '%')
		{
			return false;
		}
		return true;
	}
	else
	{
		if (op2 == '+' || op2 == '-')
		{
			return false;
		}
		return false;

	}
}

bool isOperand(char c)
{
	if ((c >= 'a' && c <= 'z'))
		return true;
	return false;
}

bool isOperator(char c)
{
	if (c == '*' || c == '/' || c == '%' || c == '+' || c == '-')
		return true;
	return false;
}

string elimWhiteSpace(string s)
{
	string result = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			result += s[i];
		}
	}
	return result;
}

string infixToPostfix(string infix)
{
	infix = elimWhiteSpace(infix);
	string postfix = "";
	stack<char>	op;
	for (int i = 0; i < infix.size(); i++)
	{
		switch (infix[i])
		{
		case '(':
			op.push(infix[i]);
			break;
		case ')':
			while (op.top() != '(' && !op.empty())
			{
				postfix = postfix + op.top();
				op.pop();
			}
			op.pop();
			break;
		case '+':
		case '-':
		case '/':
		case '*':
		case '%':
			while (!op.empty() && op.top() != '(' && hasPrecedence(op.top(), infix[i]))
			{
				postfix = postfix + op.top();
				op.pop();
			}
			op.push(infix[i]);
			break;
		default:
			postfix += infix[i];
		}

	}
	while (!op.empty())
	{
		postfix += op.top();
		op.pop();
	}
	return postfix;
}

int evalPostfix(string postfix, const Map &values)
{
	stack<int> operands;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (isOperand(postfix[i]))
		{
			int val;
			values.get(postfix[i], val);
			operands.push(val);
		}
		else
		{
			int operand1 = operands.top();
			operands.pop();
			int operand2 = operands.top();
			operands.pop();
			switch (postfix[i])
			{
			case '+':
				operands.push(operand1 + operand2);
				break;
			case '-':
				operands.push(operand2 - operand1);
				break;
			case '*':
				operands.push(operand1 * operand2);
				break;
			case '/':
				operands.push(operand2 / operand1);
				break;
			case '%':
				operands.push(operand2 % operand1);
				break;
			default:
				break;

			}
		}
	}
	return operands.top();
}

int main()
{
	char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
	int  vals[] = { 3,  -9,   6,   2,   4,   1 };
	Map m;
	for (int k = 0; vars[k] != '#'; k++)
		m.insert(vars[k], vals[k]);
	string pf;
	int answer;
	assert(evaluate("a+ e", m, pf, answer) == 0 &&
		pf == "ae+"  &&  answer == -6);
	answer = 999;
	assert(evaluate("", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
	// unary operators not allowed:
	assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
	assert(evaluate("a*b", m, pf, answer) == 2 &&
		pf == "ab*"  &&  answer == 999);
	assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
		pf == "yoau-*+"  &&  answer == -1);
	answer = 999;
	assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
		pf == "oyy-/"  &&  answer == 999);
	assert(evaluate(" a  ", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	assert(evaluate("((a))", m, pf, answer) == 0 &&
		pf == "a"  &&  answer == 3);
	cout << "Passed all tests" << endl;
}