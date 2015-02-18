#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include <sstream>


using namespace std;

void ConvertoToInt(string x, char a, int& numberX, int& numberA);
/*
function to convert a string variable, and a character variable to numbers,
you will then store the numbers into the numberX and numberA variables and
you will use those two int variables to access the specific indexd of the reference table
*/
void OutputVector(vector<char> Ostack);
void OutputString(string input, int index);
void Rules(stack<string>& x, string tablevalue, string table[][11]);
/*
function that basically just contains if statments that check to see what rule we got from the table and
will pop the stack however many times the rule indicates we should 
and will push everything we need to push onto the stack after we have figured out what rule we have
*/
int main()
{
	//create a stack of string to hold the states, nonterminals and input
	stack<string> Tstack;
	
	//create a vector of char to hold the same values as the stack, but you will just use it to ouput the stack
	vector<char> Ostack;
	//create the reference table, a 2D array, fill it with strings containing, numbers and states and rules
	string Table [16][11] = {
		{"s5", "0", "0", "0", "0", "s4", "0", "0", "1", "2", "3"},
		{"0", "s6", "s7", "0", "0", "0", "0", "acc", "0", "0", "0"},
		{"0", "r3", "r3", "s8", "s9", "0", "r3", "r3", "0", "0", "0"},
		{"0", "r6", "r6", "r6", "r6", "0", "r6", "r6", "0", "0", "0"},
		{"s5", "0", "0", "0", "0", "s4", "0", "0", "10", "2", "3"},
		{"0", "r8", "r8", "r8", "r8", "0", "r8", "r8", "0", "0", "0"},
		{"s5", "0", "0", "0", "0", "s4", "0", "0", "0", "11", "3"},
		{"s5", "0", "0", "0", "0", "s4", "0", "0", "0", "12", "3"},
		{"s5", "0", "0", "0", "0", "s4", "0", "0", "0", "0", "13"},
		{"s5", "0", "0", "0", "0", "s4", "0", "0", "0", "0", "14"},
		{"0", "s6", "s7", "0", "0", "0", "s15", "0", "0", "0", "0"},
		{"0", "r1", "r1", "s8", "s9", "0", "r1", "r1", "0", "0", "0"},
		{"0", "r2", "r2", "s8", "s9", "0", "r2", "r2", "0", "0", "0"},
		{"0", "r4", "r4", "r4", "r4", "0", "r4", "r4", "0", "0", "0"},
		{"0", "r5", "r5", "r5", "r5", "0", "r5", "r5", "0", "0", "0"},
		{"0", "r7", "r7", "r7", "r7", "0", "r7", "r7", "0", "0", "0"}};
		

	int numberX;
	int numberA;
	string stringX;
	char letterA;
	string tablevalue;
	size_t pos;
	int index = 0;
	bool accepted = false;
	bool start = true;
	char state;
	stringstream ss;
	string temp;
	//push a 0 onto the stack
	Tstack.push("0");
	//Ostack.push_back('0');
	//create the input string with the $ at the end
	string input = "(i+i)/i$";
	//push the start symbol E onto the stack
	//OutputVector(Ostack);
	//OutputString(input, index);
	//while the stack is not emptpy
	while(!Tstack.empty())
	{
		if(start)//the first of the 3 big if statements
		{
			//this if statement checks to see if we are in the very 1st iteration of the loop
			//and will only go into this if statement in the first iteration of the loop
			start = false;
			letterA= input[index];
			index++;
			stringX=Tstack.top();
			Tstack.pop();
			ConvertoToInt(stringX, letterA, numberX, numberA);
			tablevalue = Table[numberX][numberA];
			pos = tablevalue.find("s");
			//searches the string 'tablevalue to see if it has an 's' for state
			if(pos != string::npos)
			{
				state = 's';
				Tstack.push(stringX);
				ss << letterA;
				ss >> temp;
				Tstack.push(temp);
				tablevalue.erase(0,pos+1);
				//erases the s in 's4' so we can just push the number of the state onto the stack
				Tstack.push(tablevalue);
				
			}
			else if(tablevalue == "0")
			{
				accepted = false;
				break;
			}

			
		}//end of first big if statement
		else if(state == 's')// the second of the 3 big if statements
		{
			//if the last thing that we pushed onto the stack was a state, then we will enter here
			letterA=input[index];
			index++;
			stringX = Tstack.top();
			Tstack.pop();
			ConvertoToInt(stringX, letterA, numberX, numberA);
			tablevalue = Table[numberX][numberA];
			pos = tablevalue.find("s");
			//searches the string 'tablevalue to see if it has an 's' for state
			if(pos != string::npos)
			{
				state = 's';
				Tstack.push(stringX);
				ss << letterA;
				ss >> temp;
				Tstack.push(temp);
				tablevalue.erase(0,pos+1);
				//erases the s in 's4' so we can just push the number of the state onto the stack
				Tstack.push(tablevalue);

			}
			else if(Table[numberX][numberA] =="acc")
			{
				accepted = true;
				break;
			}
			else if(Table[numberX][numberA] =="0")
			{
				accepted = false;
				break;
			}
			
			else
			{
				pos = tablevalue.find("r");
				//searches the string 'tablevalue to see if it has an 'r' for rule
				if(pos != string::npos)
				{
					state = 'r';
					Tstack.push(stringX);
					Rules(Tstack, tablevalue, Table);
				}
			}

		}//end of second big if statement
		else if(state == 'r')//the third of the 3 big if statements
		{
			//if the last thing we put onto the stack was a rule, then we enter here
			stringX = Tstack.top();
			Tstack.pop();
			ConvertoToInt(stringX, letterA, numberX, numberA);
			tablevalue = Table[numberX][numberA];
			pos = tablevalue.find("s"); 
			//searches the string 'tablevalue to see if it has an 's' for state
			if(pos != string::npos)
			{
				state = 's';
				Tstack.push(stringX);
				ss << letterA;
				ss >> temp;
				Tstack.push(temp);
				tablevalue.erase(0,pos+1);
				//erases the s in 's4' so we can just push the number of the state onto the stack
				Tstack.push(tablevalue);
				
			}
			else if(Table[numberX][numberA] =="acc")
			{
				accepted = true;
				break;
			}
			else if(Table[numberX][numberA] =="0")
			{
				accepted = false;
				break;
			}			
			else
			{
				pos = tablevalue.find("r");
				//searches the string 'tablevalue to see if it has an 'r' for rule
				if(pos != string::npos)
				{
					state = 'r';
					Tstack.push(stringX);
					Rules(Tstack, tablevalue, Table);
				}
			}
		}//end of the 3rd big if statement
			
	  }//end while loop
	if(accepted)
	{
		cout << "the motherfucking string is accepted using this language. Peace niggah im out. ONE LOVE" << endl;
	}
	return 0;
}

//this function just contains all the rules for the language
//so we use this function to check how many times we need to pop the 
//stack and what to push onto the stack
void Rules(stack<string>& x, string tablevalue, string table[][11])
{
	string top;
	int col;
	int row;
	if(tablevalue == "r1" || tablevalue == "r2")
	{
		for(int i = 0; i < 6; i++)
		{
			x.pop();
		}
		top = x.top();
		x.pop();
		ConvertoToInt(top, 'E', row, col);
		tablevalue = table[row][col];
		x.push(top);
		x.push("E");
		x.push(tablevalue);
	}
	else if(tablevalue == "r3")
	{
		for(int i = 0; i < 2; i++)
		{
			x.pop();
		}
		top = x.top();
		x.pop();
		ConvertoToInt(top, 'E', row, col);
		tablevalue = table[row][col];
		x.push(top);
		x.push("E");
		x.push(tablevalue);
		
	}
	else if(tablevalue == "r4" || tablevalue == "r5")
	{
		for(int i = 0; i < 6; i++)
		{
			x.pop();
		}
		top = x.top();
		x.pop();
		ConvertoToInt(top, 'T', row, col);
		tablevalue = table[row][col];
		x.push(top);
		x.push("T");
		x.push(tablevalue);
	}
	else if(tablevalue == "r6")
	{
		for(int i = 0; i < 2; i++)
		{
			x.pop();
		}
		top = x.top();
		x.pop();
		ConvertoToInt(top, 'T', row, col);
		tablevalue = table[row][col];
		x.push(top);
		x.push("T");
		x.push(tablevalue);
	}
	else if(tablevalue == "r7")
	{
		for(int i = 0; i < 6; i++)
		{
			x.pop();
		}
		top = x.top();
		x.pop();
		ConvertoToInt(top, 'F', row, col);
		tablevalue = table[row][col];
		x.push(top);
		x.push("F");
		x.push(tablevalue);
	}
	else if(tablevalue == "r8")
	{
		for(int i = 0; i < 2; i++)
		{
			x.pop();
		}
		top = x.top();
		x.pop();
		ConvertoToInt(top, 'F', row, col);
		tablevalue = table[row][col];
		x.push(top);
		x.push("F");
		x.push(tablevalue);
		

	}
}

//this function will help us convert the string x variable (which is the top of the stack)
//and the input character to number values so we can then use these number values to 
//access the specific index in our table
void ConvertoToInt(string x, char a, int& numberX, int& numberA)
{
	if(x == "0")
	{
		numberX=0;
	}
	if(x == "1")
	{
		numberX=1;
	}
	if(x == "2")
	{
		numberX=2;
	}
	if(x == "3")
	{
		numberX=3;
	}
	if(x == "4")
	{
		numberX=4;
	}
	if(x == "5")
	{
		numberX=5;
	}
	if(x == "6")
	{
		numberX=6;
	}
	if(x == "7")
	{
		numberX=7;
	}
	if(x == "8")
	{
		numberX=8;
	}
	if(x == "9")
	{
		numberX=9;
	}
	if(x == "10")
	{
		numberX=10;
	}
	if(x == "11")
	{
		numberX=11;
	}
	if(x == "12")
	{
		numberX=12;
	}
	if(x == "13")
	{
		numberX=13;
	}
	if(x == "14")
	{
		numberX=14;
	}
	if(x == "15")
	{
		numberX=15;
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
		case'E':
			numberA=8;
			break;
		case'T':
			numberA=9;
			break;
		case'F':
			numberA=10;
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



 