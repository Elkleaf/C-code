#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstring>
using namespace std;
//Purpose: Adding and deleting comments and spaces in a file

void DeleteComments(vector<string>&);
void AddSpaces(vector<string>, vector<string>&);
void output(vector<string>);


int main()
{
	ifstream myfile;
	string token;
	vector<string> lines;
	vector<string> RevisedLines;


	myfile.open("file.txt");
	while(getline(myfile,token))
	{
		lines.push_back(token);
	}

	myfile.close();

	DeleteComments(lines);
	AddSpaces(lines, RevisedLines);
	output(RevisedLines);




	return 0;
}


void DeleteComments(vector<string> &lines)
{
	size_t pos;
	size_t pos2;
	int temp = 0;

	for(int i =0; i<lines.size(); i++)
	{
		pos = lines[i].find("(*");
		pos2 = lines[i].find("*)");
		if(pos != string::npos && pos2 == string::npos)
		{
			lines[i].erase(pos, string::npos);
			temp++;

		}
		
		else if(pos == string::npos && pos2 != string::npos)
		{
			lines.erase(lines.begin()+i);
			temp--;
		}
		else if(pos!=string::npos && pos2 != string::npos)
		{
			lines[i].erase(pos,pos2+2);
		}
		else if(temp == 1)
		{
				
				lines.erase(lines.begin()+i);
				i--;
		}
		
	}
		
		
	
}

void AddSpaces(vector<string> lines, vector<string>& RevisedLines)
{
	string token;
	char specialToken [12] = {',',';','(',')','{','}','=','+','-','/','*', '\"'};
	
	//goes through each line, first loop
	for(int i=0; i< lines.size(); i++)
	{
		token = lines[i];

		//goes through each character in each line, second loop
		for(int j =0; j<token.size();j++)
		{

			//compares each character in each line to the specialToken array, third loop
			for(int k =0; k<12;k++)
			{
				if(token[j]==specialToken[k])
				{
					cout<<token<<endl;
					token.insert(j+1,1,' ');
					token.insert(j,1,' ');
					j++;
					break;
				}


			}//end third loop

			//checks for input symbols
			if(token[j] == '>')
			{
				if(token.compare(j-3,5,"cin>>")==0)
				{
					token.insert(j+2,1,' ');
					token.insert(j,1,' ');
					j=j+3;
				}
				else if(token.compare(j,2,">>")==0)
				{
					token.insert(j+2, 1, ' ');
					token.insert(j, 1, ' ');
						j = j+3;
				}
				
			}
			//checks for output symbols
			else if(token[j]=='<')
			{
				if(token.compare(j-4,6,"cout<<") == 0)
				{
					token.insert(j+2,1,' ');
					token.insert(j,1,' ');
					j = j+3;
				}
				else if(token.compare(j,2,">>")==0)
				{
					token.insert(j+2,1,' ');
					token.insert(j,1,' ');
					j = j+3;
				}
			}
		}//end second loop

		RevisedLines.push_back(token);

	}//end first loop
}


void output(vector<string> RevisedLines)
{
	ofstream outfile;
	string token;
	bool noTokens = false;
	int braces =0;
	int indent = false;


	outfile.open("Output.txt");
	//for loop to go through each line
	for(int i = 0; i <RevisedLines.size(); i++)
	{
		istringstream convert (RevisedLines[i]);
		noTokens = false;
		indent = false;

		//while you can convert the sstream to a token string
		while (convert >> token)
		{
			noTokens = true;
			if(token.find("{") != string::npos)
			{
				outfile << token;
				braces++;
			}
			else if(token.find("}") != string::npos)
			{
				outfile << token;
				braces--;
			}
			else
			{
				if(braces !=0)
				{
					if(indent ==false)
					{
						for(int j=0; j < braces; j++)
						{
							outfile << "\t";
						}
						indent = true;
					}
				}

				outfile << token << " ";
			}
		}//end while

		if(noTokens == true)
		{
			outfile << endl;
		}
	}//end for

	outfile.close();

}