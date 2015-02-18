#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include <sstream>


using namespace std;
bool IsTerminal(char x);
void ConvertoToInt(char x, char a, int& numberX, int& numberA);
void PushTable(int x, stack<char>& Tstack, vector<char>& Ostack);
void OutputVector(vector<char> Ostack);
void OutputString(string input, int index);
int main()
{
	//create a stack of char to hold the Non-terminals (E, Q, T etc..),
	stack<char> Tstack;
	
	//create a vector of char to hold the same values as the stack, but you will just use it to ouput the stack
	vector<char> Ostack;
	//create the reference table, a 2D array, fill it with numbers 0-9
	int Table [5][8] = {
		{1, 0, 0, 0, 0, 1, 0, 0},
		{0, 2, 3, 0, 0, 0, 4, 4},
		{5, 0, 0, 0, 0, 5, 0, 0},
		{0, 4, 4, 6, 7, 0, 4, 4},
		{8, 0, 0, 0, 0, 9, 0, 0}};

	int numberX;
	int numberA;
	char letterX;
	char letterA;
	int index = 0;
	bool accepted = false;
	//push a $ onto the stack
	Tstack.push('$');
	Ostack.push_back('$');
	//create the input string with the $ at the end
	string input = "(i+i)*i$";
	//push the start symbol E onto the stack
	Tstack.push('E');
	Ostack.push_back('E');
	OutputVector(Ostack);
	OutputString(input, index);
	//while the stack is not emptpy
	while(!Tstack.empty())
	{
			//so x is going to = the top of the stack (stack.top())
			letterX = Tstack.top();
			OutputVector(Ostack);
			cout << "    ";
			//'a' is going to = a character of the input string
			letterA = input[index]; 
			
			if(IsTerminal(letterX))//write a function IsTerminal(char x)
			{
				
				if(letterX == letterA)
				{
					//pop the stack and go to the next character in the input string
					Tstack.pop();
					Ostack.pop_back();
					if(letterX == '$' && letterA == '$')
					{
						accepted = true;
					}
					index++;
					//then output the input string 
					OutputString(input, index);
				}

				else 
				{
					cout << "something is wrong in the neighborhood";
					break;
				}
			}
			else
			{
				ConvertoToInt(letterX, letterA, numberX, numberA);
				if(Table[numberX][numberA] != 0)//table[x][a] is a not blank (like a blank space on the sheet of paper
				{
					//pop the stack
					Tstack.pop();
					Ostack.pop_back();
					//push the table[x][a] onto the stack in reverse order (for -TQ, you push the Q and T and -)
					
					PushTable(Table[numberX][numberA], Tstack, Ostack);
					OutputString(input, index);
						
				}
				else 
				{
						cout << "call the ghostbusters";
						break;
				}
			}
		
	  }
	if(accepted)
	{
		cout << "the motherfucking string is accepted usingthis language";
	}
	return 0;
}


bool IsTerminal(char x)
{
	bool isit = false;
	switch (x)
	{
		case 'i':
		case '*':
		case '+':
		case '-':
		case '/':
		case '(':
		case ')':
		case '$':
			isit=true;
			break;
		default:
			break;

			

	}
	return isit;
}

void ConvertoToInt(char x, char a, int& numberX, int& numberA)
{
	switch(x)
	{
		case'E':
			numberX=0;
			break;
		case'Q':
			numberX=1;
			break;
		case'T':
			numberX=2;
			break;
		case'R':
			numberX=3;
			break;
		case'F':
			numberX=4;
			break;
		default:
			break;
	}

	switch(a)
	{
		case'i':
			numberA =0;
			break;
		case'+':
			numberA=1;
			break;
		case'-':
			numberA=2;
			break;
		case'*':
			numberA=3;
			break;
		case'/':
			numberA=4;
			break;
		case'(':
			numberA=5;
			break;
		case')':
			numberA=6;
			break;
		case'$':
			numberA=7;
			break;

		default:
			break;


	}
}

void PushTable(int x, stack<char>& Tstack, vector<char>& Ostack)
{
	switch(x)
	{
		case 1:
			Tstack.push('Q');
			Ostack.push_back('Q');
			Tstack.push('T');
			Ostack.push_back('T');
			break;
		case 2:
			Tstack.push('Q');
			Ostack.push_back('Q');
			Tstack.push('T');
			Ostack.push_back('T');
			Tstack.push('+');
			Ostack.push_back('+');
			break;
		case 3:
			Tstack.push('Q');
			Ostack.push_back('Q');
			Tstack.push('T');
			Ostack.push_back('T');
			Tstack.push('-');
			Ostack.push_back('-');
			break;
		case 4:
			break;
		case 5:
			Tstack.push('R');
			Ostack.push_back('R');
			Tstack.push('F');
			Ostack.push_back('F');
			break;
		case 6:
			Tstack.push('R');
			Ostack.push_back('R');
			Tstack.push('F');
			Ostack.push_back('F');
			Tstack.push('*');
			Ostack.push_back('*');
			break;
		case 7:
			Tstack.push('R');
			Ostack.push_back('R');
			Tstack.push('F');
			Ostack.push_back('F');
			Tstack.push('/');
			Ostack.push_back('?');
			break;
		case 8:
			Tstack.push('i');
			Ostack.push_back('i');
			break;
		case 9:
			Tstack.push(')');
			Ostack.push_back(')');
			Tstack.push('E');
			Ostack.push_back('E');
			Tstack.push('(');
			Ostack.push_back('(');
			break;
		default:
			break;
			

	}
}

void OutputVector(vector<char> Ostack)
{
	for(int i = 0; i < Ostack.size(); i++)
	{
		cout << Ostack[i];
	}
	
}


void OutputString(string input, int index)
{
	for(int i = index; i<input.length(); i++)
	{
		cout << input[i];
	}
	cout << endl;
}



 