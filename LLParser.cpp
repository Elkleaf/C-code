#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <iomanip>
#include <cctype>
#include <cstring>
using namespace std;

void readfile(vector<string> &vector);
bool check_id(string s);
void error_handler(stack<string> s, int &check, vector<string> v, int i);
void output_stack(stack<string> s);
bool is_number(string& s);
bool read_grammar(int table[][17], string s, stack<string> &stack);
int convertToInt(string input);
void pushCharacters(stack<string>& stack, int conversion_num);
bool isTerminal(string input);
void format(string filename);
void DeleteComments(vector<string>&);
void AddSpaces(vector<string>, vector<string>&);
void output(vector<string>);
void ConvertToCPP();

int main()	
{
	stack<string> p_stack;
	stack<string> stack;
	string filename;

	cout << "Enter the filename: ";
	cin >> filename;

	format(filename);
	
	vector<string> tokenizer;
	vector<string> id_vector; // stores declared identifiers here
	readfile(tokenizer); // read the given file "input.txt"

	bool pname_check = false; // checks if pname has passed
	bool begin_check = false; // checks if BEGIN has passed
	bool ident_check = false; // checks if identifiers were declared
	bool var_check = false; // checks if the word VAR has passed
	bool end_para = false;
	bool begin_para = false;
	bool equal_check = false;
	

	int semicolon_check = 0;

	int table[23][17] =	
					{ 20,20,20,20,20,20,19,22,32,20,26,27,28,21,20,20,20,
						20,1,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
						20,2,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
						33,2,14,14,14,14,19,14,32,14,14,14,14,20,20,20,20,
						20,3,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
						20,4,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
						20,20,20,20,20,20,19,22,32,34,26,14,28,20,20,20,20,
						20,5,20,20,20,20,19,22,32,20,26,27,28,20,5,20,20,
						20,6,20,20,20,20,19,22,32,20,26,27,28,20,6,20,14,
						20,7,20,20,20,20,19,22,32,20,26,27,28,20,23,20,20,
						20,20,20,20,20,20,19,22,32,20,26,27,28,20,25,20,20,
						20,1,20,20,20,20,19,22,29,20,26,27,28,20,20,20,20,
						20,8,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
						10,10,20,20,20,20,10,22,32,20,26,27,28,20,20,20,20,
						20,20,11,12,20,20,19,14,32,20,14,27,28,20,20,20,20,
						9,9,20,20,20,20,9,22,32,20,26,27,28,20,20,20,20,
						20,20,14,14,16,17,19,14,32,20,14,27,28,20,20,20,20,
						30,20,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
						30,20,14,14,14,14,19,14,32,20,14,27,28,20,20,20,20,
						31,1,20,20,20,20,18,22,32,20,26,27,28,20,20,20,20,
						20,20,20,20,20,20,19,22,32,20,26,27,28,20,20,24,20,
						15,20,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
						20,2,20,20,20,20,19,22,32,20,26,27,28,20,20,20,20,
					};
	string s;
	stack.push("END."); // pushing this has last token since END. is going to be read last
	stack.push("S"); // starting non-terminal
	int i = 0; // counter for vector (tokenizer)
	while (i != tokenizer.size())
	{
		
		cout<<"STACK: ";
		output_stack(stack);
		cout<<endl;
		p_stack = stack;

		if (tokenizer[0] != "PROGRAM") {
			cout<<"PROGRAM SPELLED WRONG OR MISSING"<<endl;
			exit(0);
		}


		//cout<<tokenizer[tokenizer.size()-1]<<endl;
		if (tokenizer[tokenizer.size()-1] != "END.")
		{
			cout<<"END. SPELLED WRONG OR MISSING "<<endl;
			exit(0);
		}

		//check semicolon before END.
		if (tokenizer[tokenizer.size()-2] != ";") {
			cout<<"MISSING ;"<<endl;
			exit(0);
		}

		error_handler(p_stack, semicolon_check, tokenizer, i);
	

		// if a string inside " " is read, skip it
		if (stack.top() == "STRING") {
			i++;
			stack.pop();
			while (tokenizer[i] != "\""){
				i++;
			}
		}

		if (tokenizer[i] == "(")
		{
			begin_para = true;
			int q = i;
			q++;
			while (tokenizer[q] != ";")
			{
				if (tokenizer[q] == ")")
					end_para = true;
				q++;
			}
			if (!end_para)
			{
				cout<<"MISSING )"<<endl;
				exit(0);
			}
			end_para = false;
		}
		if (tokenizer[i] == ")") {
			if (!begin_para) {
				cout<<"MISSING ("<<endl;
				exit(0);
			}
			begin_para = false;
		}


		s = tokenizer[i]; // grab string from tokenizer
		cout<<"STRING: "<<s<<endl;
		// if var is read push DECLIST onto stack
		if (s == "VAR") {
			stack.push("DECLIST");
			i++;
			s = tokenizer[i];
		}

		// if BEGIN is read push STATLIST onto stack
		if (s == "BEGIN")
		{
			stack.push("STATLIST");
			i++;
			s = tokenizer[i];
			begin_check = true; // begin has been read
		}
		// if begin has been read and string isn't a terminal 
		if (begin_check && !isTerminal(s))
		{
			
			for (int p = 0; p != id_vector.size(); p++)
			{
				// checking declared identifiers
				if (s == id_vector[p])
				{
					ident_check = true;
					if (tokenizer[i-1] == ";" || tokenizer[i-1] == "BEGIN")
					{
						if (tokenizer[i+1] != "=")
						{
							cout<<"MISSING ="<<endl;
							exit(0);
						}
					}
				}
			}	
			// if it is just a number that multiplies, divides, etc 
			if (is_number(s)) {
				s = "NUM";
				ident_check = true;
			}
			if (!ident_check) {
				
				cout<<"INVALID IDENTIFIER: "<<s<<endl;
				exit(0);
			}
			s = "var"; // if id is ok, replace as var
			ident_check = false; //reset checker

				
		}
		
		if(check_id(s) && !begin_check) {
			
			if (!pname_check)
				{
					s = "PNAME";
					pname_check = true;
				}
			else if (!var_check)
				{
					id_vector.push_back(s);
					if (tokenizer[i+1] != ",")
					{	
							
						if (tokenizer[i+1] == "INTEGER" )
						{
							cout<<"MISSING :"<<endl;
							exit(0);
						
						}
						if (tokenizer[i+1] != ":"){
							cout<<"MISSING ,"<<endl;
							exit(0);
						}
							
					}
					s = "var"; // replace identifier with var

					//if (begin_check)
						//var_check = true;
				}
			else
				s = "NOPENOPENOPE";
		}
		// if string is accepted by grammar, go to the next one 
		if (read_grammar(table, s, stack))
			i++;
		else	
			return 0;
	}

}


void output_stack(stack<string> s)
{
	while(!s.empty())
	{
		string w = s.top();
		cout << w << "  ";
		s.pop();
	}
}

void format(string filename)
{
	ifstream file;
	string token;
	vector<string> lines;
	vector<string> RevisedLines;


	file.open(filename);
	while(getline(file,token))
	{
		lines.push_back(token);
	}

	file.close();

	DeleteComments(lines);
	AddSpaces(lines, RevisedLines);
	output(RevisedLines);
}

void readfile(vector<string> &tokenizer)
{
	
	ifstream file;
	string s2;
	string s;
	file.open("Output.txt");
	while(!file.eof()) {
		file>>s;
		tokenizer.push_back(s);
	}
	file.close();
	file.open("Output.txt");
	
	

}

bool read_grammar(int table[][17], string s, stack<string> & stack)
{
	string input;
	//string o_string = s;
	
	int i = 0;
	int conversion_num;
	while (!stack.empty()) {
		input = stack.top();
		cout<<"CURRENT STACK: "<<input<<endl;
		
		
		if (isTerminal(input)) {
			if (s == input) {
					
					stack.pop();
					//o_string.erase(o_string.begin()); 
					cout<<"TERMINAL: "<<input<<endl;
					if (s == "END.") {
						cout<<"\nGRAMMAR ACCEPTED\n"<<endl;
						exit(0);
					}
					
					return 1;
					
					
			}
			else {
				cout<<"MISUSING: "<<input<<endl;exit(0);
			}
		}
		else {
			
			conversion_num = table[convertToInt(input)][convertToInt(s)];
			if (conversion_num != 20) {
				stack.pop();
				pushCharacters(stack, conversion_num);
				

			}
			else {	
				cout<<"\nGRAMMER NOT ACCEPTED\n"<<endl;
				return 0;
				
			}
		}
	}


}

bool is_number(string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool check_id(string s)
{
	
	int i = 0;
	if (s[i] == 'a' || s[i] == 'b' ||s[i] == 'c' || s[i] == 'd' || s[i] == 'e' || s[i] == 'f')
	{
		i++;
		while (i != s.length()) {
			if (s[i] == 'a' || s[i] == 'b' ||s[i] == 'c' || s[i] == 'd' || s[i] == 'e' || s[i] == 'f')
				i++;
			else if (isdigit(s[i]))
				i++;
			else {
					cout<<"NOT A VALID IDENTIFIER";
					return 0;
			}
		}
		return 1;
	}
	else
		return 0;
}

void pushCharacters(stack<string>& stack, int conversion_num)
{
	if (conversion_num == 1) {
		stack.push("ID");
	}
	else if (conversion_num == 2) {
		stack.push("var");
	}
	else if (conversion_num == 3) {
		stack.push("TYPE");
		stack.push(":");
		stack.push("DEC");
	}
	else if (conversion_num == 4) {
		stack.push("Y");
		stack.push("ID");
	}
	else if (conversion_num == 5){
		stack.push("Z");
		stack.push(";");
		stack.push("STAT");
	}
	else if (conversion_num == 6) {
		stack.push("STATLIST");
	}
	else if (conversion_num == 7) 
		stack.push("ASSIGN");
	else if (conversion_num == 8) {
		stack.push("E");
		stack.push("=");
		stack.push("var");
	}
	else if (conversion_num == 9)  {
		stack.push("R");
		stack.push("F");
	}
	else if (conversion_num == 10)  {
		stack.push("Q");
		stack.push("T");
	}
	else if (conversion_num == 11)  {
		stack.push("Q");
		stack.push("T");
		stack.push("+");
	}
	else if (conversion_num == 12)  {
		stack.push("Q");
		stack.push("T");
		stack.push("-");
	}
	else if (conversion_num == 34)  {
		stack.push("DEC");
		stack.push(",");
	}
	else if (conversion_num == 14)  {
		return;
	}
	else if (conversion_num == 15)  {
		stack.push("DIGIT");
	}
	else if (conversion_num == 16) {
		stack.push("R");
		stack.push("F");
		stack.push("*");
	}
	else if (conversion_num == 17){
		stack.push("R");
		stack.push("F");
		stack.push("/");
	}
	
	else if (conversion_num == 18){
		stack.push(")");
		stack.push("E");
		stack.push("(");
	}
	else if (conversion_num == 19)
	{
		cout<<"UNEXPECTED ("<<endl;
		exit(0);
	}
	else if (conversion_num == 21)  {
		stack.push(";");
		stack.push("PNAME");
		stack.push("PROGRAM");
	}
	else if (conversion_num == 22)  {
		cout<<"UNEXPECTED )"<<endl;
		exit(0);
	}
	else if (conversion_num == 23)  {
		stack.push("<PRINT>");
	}
	else if (conversion_num == 24)  {
		stack.push(";");
		stack.push("INTEGER");
		
	}
	else if (conversion_num == 25)  {
		stack.push(")");
		stack.push("<OUTPUT>");
		stack.push("(");
		stack.push("PRINT");
		
	}
	else if (conversion_num == 26)  {
		cout<<"UNEXPECTED ;"<<endl;
		exit(0);
	}
	else if (conversion_num == 27)  {
		cout<<"UNEXPECTED :"<<endl;
		exit(0);
	}
	else if (conversion_num == 28)  {
		cout<<"UNEXCPECTED ="<<endl;
		exit(0);
	}
	else if (conversion_num == 29)  {
		stack.push("var");
		stack.push(",");
		stack.push("\"");
		stack.push("STRING");
		stack.push("\"");

	}
	else if (conversion_num == 30)  {
		stack.push("A");
		stack.push("DIGIT");
		
		
	}
	else if (conversion_num == 31)  {
		stack.push("NUMB");
		
	}
	else if (conversion_num == 32)  {
		cout<<"UNEXCPECTED \""<<endl;
		exit(0);
	}
	else if (conversion_num == 33)  {
		stack.push("X");
		stack.push("DIGIT");
	}
	else
		cout<<"Error_"<<endl;


}

int convertToInt(string input)
{
	if (input == "S" || input == "DIGIT")
		return 0;
	else if (input == "PNAME" || input == "var")
		return 1; 
	else if (input == "ID" || input == "+")
		return 2;
	else if (input == "X" || input == "-")
		return 3;
	else if (input == "DECLIST" || input == "*")
		return 4;
	else if (input == "DEC" || input == "/")
		return 5;
	else if (input == "Y" || input == "(")
		return 6;
	else if (input == "STATLIST" || input == ")")
		return 7;
	else if (input == "Z" || input == "\"" )
		return 8;
	else if (input == "STAT" || input == ",")
		return 9;
	else if (input == "<PRINT>" || input == ";")
		return 10;
	else if (input == "<OUTPUT>" || input == ":")
		return 11;
	else if (input == "ASSIGN" || input == "=")
		return 12;
	else if (input == "E" || input == "PROGRAM")
		return 13;
	else if (input == "Q" || input == "PRINT")
		return 14;
	else if (input == "T" || input == "INTEGER")
		return 15;
	else if (input == "R" || input == "END.")
		return 16;
	else if (input == "NUMBER")
		return 17;
	else if (input == "A")
		return 18;
	else if (input == "F")
		return 19;
	else if (input == "TYPE")
		return 20;
	else if (input == "DIGIT")
		return 21;
	else if (input == "LETTER")
		return 22;
	else{
		cout<<endl;
		cout<<"ERROR"<<endl;
	}
}

bool isTerminal(string input)
{
	if (input == "PROGRAM")
		return 1;
	else if (input == "END.")
		return 1;
	else if (input == "PNAME")
		return 1;
	else if (input == "var")
		return 1;
	else if (input == "INTEGER")
		return 1;
	else if (input == ";")
		return 1;
	else if (input == ",")
		return 1;
	else if (input == ":")
		return 1;
	else if (input == "NUM")
		return 1;
	else if (input == "=")
		return 1;
	else if (input == "*")
		return 1;
	else if (input == "/")
		return 1;
	else if (input == "\"")
		return 1;
	else if (input == "(")
		return 1;
	else if (input == "PRINT")
		return 1;
	else if (input == ")")
		return 1;
	else if (input == "+")
		return 1;
	else 
		return 0;
}

void error_handler(stack<string> s, int &check, vector<string> v, int i)
{
	int end_para = 0;
	int end_quote = 0;
	if (v[i] == "PRINT")
	{
		int q = i + 1;
		
		
		if (v[i+1] != "(")
		{
			cout<<"MISSING ("<<endl;
			exit(0);
		}
		if (v[i+2] != "\"")
		{
			cout<<"MISSING \""<<endl;
			exit(0);
		}
		if (v[i+1] == "(") {
			while ( v[q] != ";")
			{
				if ( v[q] == ")")
					end_para = 1;
				if ( v[q] == "END.")
					return;
				q++;
			}
			if (end_para = 0)
			{
				cout<<"MISSING )"<<endl;
				exit(0);
			}
		}
		
	}
	
	if (v[i] == "INTEGER"){
		if (v[i+1] != ";") {
			cout<<"MISSING ; "<<endl;
			exit(0);
		}
	}
	if (v[i] == ";") {
		check++;
		
		if (check == 1) {
			if (v[i+1] != "VAR") {
				cout<<"VAR spelled wrong or not there!"<<endl;
				exit(0);
			}
			
			
			if (v[i] == ":") {
				if (v[i+1] != "INTEGER") {
					cout<<"INTEGER spelled wrong or not there!"<<endl;
					exit(0);
				}
			}
		}
		else if (check == 2) {
			if (v[i+1] != "BEGIN") {
				cout<<"BEGIN spelled wrong or not there!"<<endl;
				exit(0);
			}
		}
		
		else {
			if (v[i] == ";")
			{
				if (v[i+1] != "PRINT" ) {
					if (check_id(v[i+1]))
						return;
					if (v[i+1]=="END.")
						return;
					else
						cout<<"PRINT mispelled or missing!"<<endl;
			
				}
			}
		}
	}
	if (v[i] == "VAR")
	{
		if (v[i-1] != ";")
		{
			cout<<"MISSING ;"<<endl;
			exit(0);
		}
	}

	



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

void ConvertToCPP()
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
}
