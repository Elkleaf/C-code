#include <iostream>
#include <stack>
#include <string>
#include <iomanip>
using namespace std;

void read_grammar(int table[][8], string s, stack<char> stack);
void outputStack(stack<char> stack);
int convertToInt(char input);
void pushCharacters(stack<char>& stack, int conversion_num);
bool isTerminal(char input);

int main()
{
	stack<char> stack;
	
	int table[5][8] =	
					{ 1, 0, 0, 0, 0, 1, 0, 0,
					  0, 2, 3, 0, 0, 0, 4, 5,
					  6, 0, 0, 0 , 0, 6, 0, 0,
					  0, 7, 8, 9, 10, 0, 4, 5,
					  11, 0, 0, 0, 0, 12, 0, 0
					};
	string s;
	stack.push('$'); // end marker

	cout<<"Enter string: ";
	cin>>s;
	if (s.back() != '$') // checks for end marker on string
		s = s + '$'; // adds it if marker not found
	read_grammar(table, s, stack);
}

void read_grammar(int table[][8], string s, stack<char> stack)
{
	char input;
	string o_string = s; // output string, not one being read
	stack.push('E');
	int i = 0;
	int conversion_num;
	cout<<"\n  STACK\t\tINPUT\n ";
	while (!stack.empty()) {
		input = stack.top();
		outputStack(stack);
		
		cout<<"\t\t"<<o_string<<endl;
		if (isTerminal(input)) {
			if (s[i] == input) {
					stack.pop();
					o_string.erase(o_string.begin());
					if (s[i] == '$') 
						cout<<"\nGRAMMAR ACCEPTED\n"<<endl;
					i++;	
					
					
			}
		}
		else {
			conversion_num = table[convertToInt(input)][convertToInt(s[i])];
			if (conversion_num != 0) {
				stack.pop();
				pushCharacters(stack, conversion_num);

			}
			else {	
				cout<<"\nGRAMMER NOT ACCEPTED\n"<<endl;
				return;
				
			}
		}
	}


}

void outputStack(stack<char> stack)
{
	char rstack[50] = "";
	int i = 0;
	cout<<endl;
	cout<<" ";
	
	while (!stack.empty()) {
		rstack[i] = stack.top();
		stack.pop();
		i++;
	}
	for (int q = i; q >= 0; q--)
		cout<<rstack[q];
	cout<<endl;
}
void pushCharacters(stack<char>& stack, int conversion_num)
{
	if (conversion_num == 1) {
		stack.push('Q');
		stack.push('T');
	}
	else if (conversion_num == 2) {
		stack.push('Q');
		stack.push('T');
		stack.push('+');
	}
	else if (conversion_num == 3) {
		stack.push('Q');
		stack.push('T');
		stack.push('-');
	}
	else if (conversion_num == 4) 
		return;
	else if (conversion_num == 5)
		return;
	else if (conversion_num == 6) {
		stack.push('R');
		stack.push('F');
	}
	else if (conversion_num == 7) 
		return;
	else if (conversion_num == 8) 
		return;
	else if (conversion_num == 9) {
		stack.push('R');
		stack.push('F');
		stack.push('*');
	}
	else if (conversion_num == 10){
		stack.push('R');
		stack.push('F');
		stack.push('/');
	}
	else if (conversion_num == 11)
		stack.push('i');
	else if (conversion_num == 12){
		stack.push(')');
		stack.push('E');
		stack.push('(');
	}
	else
		cout<<"Error_"<<endl;


}

int convertToInt(char input)
{
	if (input == 'E' || input == 'i')
		return 0;
	else if (input == 'Q' || input == '+')
		return 1; 
	else if (input == 'T' || input == '-')
		return 2;
	else if (input == 'R' || input == '*')
		return 3;
	else if (input == 'F' || input == '/')
		return 4;
	else if (input == '(')
		return 5;
	else if (input == ')')
		return 6;
	else if (input == '$')
		return 7;
	else{
		cout<<endl;
		cout<<"ERROR"<<endl;
	}
}

bool isTerminal(char input)
{
	switch (input){
	case 'i': return 1; break;
	case ')': return 1; break;
	case '(': return 1; break;
	case '$': return 1; break;
	case '*': return 1; break;
	case '+': return 1; break;
	case '-': return 1; break;
	default: return 0; break;
	}


}