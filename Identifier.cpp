#include <iostream>
#include <string>
#include <cctype>
using namespace std;
//test to see if a string is an identifier
bool testForID(string token);

int main()
{
	string token;
	string blank;
	char resume;
	do{
		cout<<"Enter a string: ";
		getline(cin, token);
		bool YesNo = testForID(token);
		if (YesNo)
			cout<<token<<" is an identifier"<<endl;
		else
			cout<<token<<" is not an identifier"<<endl;

		cout<<"Continue(y/n)?";
		cin.get(resume);
		getline(cin, blank);
		tolower(resume);
	}while(resume == 'y');

}

bool testForID(string s)
{
	bool result = true;
	if (isalpha(s[0]) || s[0] == '_')
	{
		for (int i=1; i < s.length(); i++)
		{
			if(isalnum(s[i]) || s[i] == '_')
				continue;
			else
				result = false; break;
		}
	}
	else
		result = false; 

	return result;

}