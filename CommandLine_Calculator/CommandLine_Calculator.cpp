#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Calculator
{
public:
	void input();//input getter

private:
	int result;//holds the total
	string expression;
	bool evaluate();
	int getNextNumTotal( int& iterator, int& brackCount);
	
};

bool Calculator::evaluate()
{
	int brackCount = 0;//used to check for any missing closing brackets. should be 0 if not in any
	string tempChar;
	int iterator = 0;//out side loop as used in multiple loops
	bool minus = false;
	bool output = false;

	//-------------------------------------------------
	/*get the first number and puts into result. is handled separatley from the rest as it can be negative starting and the rest can just use the standard */

	if (expression[0] == '-')//first num is minus
	{
		iterator++;
		minus = true;
	}

	while (isdigit(expression[iterator]))//first number
	{
		tempChar += expression[iterator];
		iterator++;
	}
	result = stoi(tempChar);
	if (minus == true)
	{
		result = -result;
	}

	//--------------------------------------------
	try
	{
		while (expression[iterator] != 0)//iterates over the expression until it hits the end
		{
			//only operator should be next

			switch (expression[iterator])
			{
			case '(':
				brackCount++;
				getNextNumTotal( iterator, brackCount);
				break;
				//recursion untill it finds a ')' then return the value
			case '+':
				if (expression[iterator + 1] == '-')//handles if the next number is a negative
				{
					iterator++;
					result += -getNextNumTotal(iterator, brackCount);
				}
				else
				{
					result += getNextNumTotal(iterator, brackCount);
				}
				break;
			case '-':
				if (expression[iterator + 1] == '-')
				{
					iterator++;
					result -= -getNextNumTotal(iterator, brackCount);
				}
				else
				{
					result -= getNextNumTotal(iterator, brackCount);
				}
				break;
			case '*':
				if (expression[iterator + 1] == '-')
				{
					iterator++;
					result *= -getNextNumTotal(iterator, brackCount);
				}
				else
				{
					result *= getNextNumTotal(iterator, brackCount);
				}
				break;
			case '/':
				if (expression[iterator + 1] == '-')
				{
					iterator++;
					result /= -getNextNumTotal(iterator, brackCount);
				}
				else
				{
					result /= getNextNumTotal(iterator, brackCount);
				}
				break;
			case ')':
				brackCount--;
				iterator++;
				break;
			default:
				cout << "somthing when wrong" << endl;
				output = false;
				break;
			}
		}
		if (brackCount == 0)
		{
			output = true;
			cout << expression << " = " << result;
		}
		else
		{
			cout << "Error: Missing bracket";
			output = false;
		}
	}
	catch (const std::exception& e)
	{
		cout << endl << &e << endl;
	}
	return output;
}
//-------------------------



int Calculator::getNextNumTotal( int& iterator, int& brackCount)
{
	/*gets the total for the next number for the operator to be used*/
	int tempNum = 0;
	string tempChar;
	iterator++;//moves past the operator

	if (expression[iterator] == '(')//bracket can come befor a number so needs to be checked for first
	{
		brackCount++;
		tempNum = getNextNumTotal(iterator, brackCount);
	}
	else//number
	{
		while (isdigit(expression[iterator]))
		{
			tempChar += expression[iterator];
			iterator++;
		}
		tempNum = stoi(tempChar);

		switch (expression[iterator])
		{
		case '+':
			if (expression[iterator + 1] == '-')
			{
				iterator++;
				tempNum += -getNextNumTotal(iterator, brackCount);
			}
			else
			{
				tempNum += getNextNumTotal( iterator, brackCount);
			}
			break;
		case '-':
			if (expression[iterator + 1] == '-')
			{
				iterator++;
				tempNum -= -getNextNumTotal( iterator, brackCount);
			}
			else
			{
				tempNum -= getNextNumTotal( iterator, brackCount);
			}
			break;
		case '*':
			if (expression[iterator + 1] == '-')
			{
				iterator++;
				tempNum *= -getNextNumTotal( iterator, brackCount);
			}
			else
			{
				tempNum *= getNextNumTotal( iterator, brackCount);
			}
			break;
		case '/':
			if (expression[iterator + 1] == '-')
			{
				iterator++;
				tempNum /= -getNextNumTotal( iterator, brackCount);
			}
			else
			{
				tempNum /= getNextNumTotal( iterator, brackCount);
			}
			break;
		case ')':
			brackCount--;
			iterator++;
			break;
		case '\0':
			//end of input
			break;
		default:
			cout << "somthing when wrong" << endl;
			break;
		}
	}
	return tempNum;
}

//----------------------
void Calculator::input()
{
	/*basic menu for inputs*/
	bool exitflag = false;
	result = 0;

	while (exitflag == false)
	{
		
		cout << "Enter input 1234567890+-*/(). type q to exit:";

		getline(cin, expression);
		

		if (expression == "q")
		{
			exitflag = true;
		}
		else
		{
			expression.erase(remove_if(expression.begin(), expression.end(), isspace), expression.end());//removes whitespaces

			if (expression.find_first_not_of("1234567890+-*/()") != string::npos)
			{
				cout << "Input contains illegal characters. only use 1234567890+-*/()";
			}
			else
			{
				cout << " | retrun value = " << evaluate() << endl << endl;;
			}
		}
	}
	return;
}
int main()
{
	Calculator calculator;
	cout << "use format of 1 + (2 * 3 - (1 + 1)) \nUse an operator befor any brackets" << endl;
	calculator.input();

	return 0;
}