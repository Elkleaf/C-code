#include <cctype>
#include <sstream>
#include <iostream>
#include <deque>
#include <string>

using namespace std;
void getToken(string, deque<char>);
void convertToPostfix(char, deque<char>&);

int main()
{
	deque<char> stack;
	stack.push_back('&'); // character used to gauge end of stack
	
	char yesNo;
	do
	{
		string infix;
		cout<<"Enter an infix expression with $ at the end: ";
		cin>>infix;
		getToken(infix, stack);
		cout<<"Continue?(y/n): ";
		cin>>yesNo;
		tolower(yesNo);
	}while(yesNo == 'y');
	return 0;
}

void getToken(string infix, deque<char> stack)
{
	char token;
	istringstream ss(infix);
	while (ss>>token){
		convertToPostfix(token, stack);
	}

}
void convertToPostfix(char token, deque<char> &stack)
{
	if (token == '*')
		stack.push_back(token);
	else if(token == '+'){
		
		if (stack.back() == '*') {
			cout<<stack.back();
			stack.pop_back();
		}
		stack.push_back(token);

	}
	else if(token == ')'){
		while(stack.back() != '('){
			cout<<stack.back();
			stack.pop_back();
		}
		stack.pop_back();
	}
	else if(token == '(')
		stack.push_back(token);
	else if(token == '-'){
		if (stack.back() == '*') {
			cout<<stack.back();
			stack.pop_back();
		}
		stack.push_back(token);
	}
	else if (token == '$'){
		while (stack.back() != '&'){
			cout<<stack.back();
			stack.pop_back();
		}
	}
	else
		cout<<token;
}