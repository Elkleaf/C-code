#include <iostream>
#include <string> 
#include <ctype.h> 

using namespace std; 

int main()
{
	string input;
	int state = 0;
	int counter = 0;
	int table[5][2] = {1,2,
					   1,3,
					   4,2,
					   4,4,
					   4,4};
	int col;

	cout << "please input a string of containing only the letters 'a' and 'b': ";
	cin >> input;

	while (counter < input.length())
	{
		switch (input[counter])
		{
		case 'a':
			col= 0;
			break;
		case 'b':
			col = 1;
			break;
		default:
			cout << "rejected" << endl;
		}

		state = table[state][col];
		counter++;
	}

	if(state== 1 || state == 2 || state == 3)
	{
		cout << input << " is accepted" << endl;
	}
	else
	{
		cout << input << " is rejected" << endl;
	}

	



	return 0;
}