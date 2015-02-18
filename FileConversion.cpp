/*
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
void format(vector<string>);


int main()
{
	ifstream myfile;
	string token;
	vector<string> lines;
	vector<string> RevisedLines;


	myfile.open("Output.txt");
	while(getline(myfile,token))
	{
		lines.push_back(token);
	}

	myfile.close();

	//DeleteComments(lines);
	//AddSpaces(lines, RevisedLines);
	output(RevisedLines);




	return 0;
}

void format(vector<string>& lines)
{
	ofstream outfile;
	string temptoken;
	

	for(int i = 0; i<lines.size(); i++)
	{
		size_t pos = lines[i].find("PROGRAM ");

		if(pos != string::npos)
		{
			lines[i].erase(pos, pos+1);
			pos = lines[i].find(";");
			lines[i].erase(pos,pos+1);
			temptoken = lines[i];
			temptoken.append(".cpp");
			outfile.open(temptoken);
		}
		
		if((pos = lines[i].find("VAR"))!= string::npos)
		{

		}
	}
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

}*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream myfile;
	string token;
	ofstream outfile;
	string temp="";
	string filename;
	size_t pos;
	bool pastBegin = false;
	bool pastEnd = false;

	myfile.open("Output.txt");
	while(getline(myfile, token))
	{
		if((pos = token.find("PROGRAM")) != string::npos)
		{
			token.erase(pos, 8);
			pos = token.find(";");
			token.erase(pos,5);
			filename = token;
			filename.append(".cpp");
			outfile.open(filename);
			outfile <<"#include <iostream>" << endl;
			outfile <<"using namespace std;" << endl;
			outfile <<"int main()" << endl;
			outfile << "{ " << endl;
			
		}

		if((pos = token.find("BEGIN")) != string::npos)
		{
			pastBegin = true;
			getline(myfile, token);
		}
		
		if((pos = token.find(":")) != string::npos)
		{
			token.erase(pos, 10);
			token.insert(0,"int ");
			outfile << token << endl;
		}
		
		/*if(token != "BEGIN")
		{
			outfile << token << endl;
		}*/

		if((pos = token.find("END.")) != string::npos)
		{
			outfile << "return 0;" << endl;
			outfile << "} " << endl;
			pastEnd = true;
		}


		if(pastBegin && ! pastEnd)
		{
			if((pos = token.find("PRINT("))!= string::npos)
			{
				token.replace(pos, 6, "cout<<");
				pos = token.find(",");
				token.replace(pos,1, "<<");
				pos = token.find(")");
				token.erase(pos, 1);
				outfile << token << endl;
				

			}
			else
				outfile << token << endl;
		}

	}







	return 0;
}