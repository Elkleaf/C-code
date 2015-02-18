//Matthew Elko, Jon Clay
//323 assignment 4 due 10/3
//infix to postfix


#include <iostream>
#include <string>
#include <ctype.h>
#include <stack>
#include <sstream>

using namespace std;

bool IsOperator(string s, int i);



int main()
{
	string token;
	string answer;
	string temp;
	double counter = 0;
	char choice = 'y';
	stack<char> operators;
	stringstream ss;
	

	
	

	while(choice == 'y' || choice == 'Y')
	{
		
		cout << "enter a postfix expression to evaluate ";
		cin >> token;
		for(int i = 0; i<token.length(); i++)
		{
			if(isalpha(token[i]))
			{
				temp = token[i];
				answer.append(temp);
			}

		
			else if(IsOperator(token, i))
			{
				operators.push(token[i]);

			}

			else if(token[i] == ')')
			{
				while(!operators.empty())
				{
					if(operators.top() == '(')
					{
						operators.pop();
					}
					temp = operators.top();
					operators.pop();
					answer.append (temp);
				}
			}

			else if(token[i] == '$')
			{
				while(!operators.empty())
				{
					temp = operators.top();
					operators.pop();
					answer.append(temp);
				}
			}


			
			
		}

			cout << answer << " is the answer" << endl;
			cout << "would you like to enter another one? y/n: ";
			cin >> choice;
			answer.clear();

	}

	cout << "Have a FANtastic day. if you aren't doing anything later would you want to hang out? :)" << endl;
	

	return 0;

	

}


bool IsOperator(string s, int i)
{
	bool result;
	switch(s[i])
	{
		case '+':
		case '/':
		case '*':
		case '-':
			result = true;
			break;
		default:
			result = false;
			break;
	}

	return result;
}


//***********INPUT/OUTPUT!***************************
/*
enter a postfix expression to evaluate a*(b+c*(a-b))+d$
abcab-*+*d+ is the answer
would you like to enter another one? y/n: y
enter a postfix expression to evaluate c*(a-b))-d*a$
cab-*da*- is the answer
would you like to enter another one? y/n: n
*/


//void Calculate(string s, stack<char> &mystack);
/*void Calculate (string s, stack<char> &mystack)
{
	double a;
	double b;
	switch(s[i])
	{
	case'+':
		a = mystack.top();
		mystack.pop();
		b = mystack.top();
		mystack.pop();
		mystack.push(a+b);
		break;
	case'*':
		a = mystack.top();
		mystack.pop();
		b = mystack.top();
		mystack.pop();
		mystack.push(a*b);
		break;
	case'/':
		a = mystack.top();
		mystack.pop();
		b = mystack.top();
		mystack.pop();
		mystack.push(b/a);
		break;
	case'-':
		a = mystack.top();
		mystack.pop();
		b = mystack.top();
		mystack.pop();
		mystack.push(b-a);
		break;
	default:
		cout << "there was an error in the calculation " << endl;
		break;

	}
}
*/