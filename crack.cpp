#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<cctype>
#include<string>
#include<algorithm>
#include <cstdio>
#include<ext/stdio_filebuf.h>
#include<sstream>
//#define DEBUG

using namespace std;

int cpassword = 0;
int rule_number[6] = {0};
int corrent_number[6] = {0};
int AddCount = 0;

vector<string> correctly_password;

void MatchPassword(set<string> &pos, string str, int rule)
{
	int scan=0, poa=0;

	//to match guessed password for read password
	set <string>::iterator sop = pos.find(str);

	if (sop != pos.end())
	{
		corrent_number[rule]++;
		correctly_password.push_back(str);
		pos.erase(str);
	}

	if (pos.size() == 0)
	{
		cout << "all password match." << endl;
		exit(1);
	}
}

void PermuteWord(vector<string> &gpassword, set<string> &pos, int &cpassword)
{
	string str;
	string astr;

	char buffer[255];

	//0-9
	for (int i=0; i<gpassword.size(); i++) 
	{
		for (int j=0; j<=999; j++)
		{
			//section 0-9
			if (j<10)
			{
				//0-9
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "%d", j);
				str.append(buffer);
				astr.insert(0, buffer);
				MatchPassword(pos, str, 1);
				MatchPassword(pos, astr, 1);				
				//00-09
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "0%d", j);
				str.append(buffer);
				MatchPassword(pos, str, 1);
				MatchPassword(pos, astr, 1);
				//00-09
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "00%d", j);
				str.append(buffer);
				MatchPassword(pos, str, 1);
				MatchPassword(pos, astr, 1);
				rule_number[1]+=6;
				cpassword+=6;
			}
			else if (j<100)
			{
				//10-99
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "%d", j);
				str.append(buffer);
				MatchPassword(pos, str, 1);
				MatchPassword(pos, astr, 1);
				//010-099
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "0%d", j);
				str.append(buffer);
				MatchPassword(pos, str, 1);
				MatchPassword(pos, astr, 1);
				rule_number[1]+=4;
				cpassword+=4;
			}
			else
			{
				//100-999
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "%d", j);
				str.append(buffer);
				MatchPassword(pos, str, 1);
				MatchPassword(pos, astr, 1);
				rule_number[1]+=2;
				cpassword+=2;
			}
		}
	}
}

void RCLetters(vector<string> &gpassword, set<string> &poa, int &cpassword)
{
    string str;

    for (int i=0; i<gpassword.size(); i++)
    {
		//replace: l -> 1
		str = gpassword[i];
    	string::size_type pos = 0;
    	while ( (pos = str.find('l', pos)) != string::npos ) 
		{
        	str.replace( pos, 1, "1");
			MatchPassword(poa, str, 2);
        	pos++;
    	}

		//replace: o -> 0
		str = gpassword[i];
    	pos = 0;
    	while ( (pos = str.find('o', pos)) != string::npos ) 
		{
        	str.replace( pos, 1, "0");
			MatchPassword(poa, str, 2);
        	pos++;
    	}
		
		//replace: s -> 5
		str = gpassword[i];
    	pos = 0;
    	while ( (pos = str.find('s', pos)) != string::npos ) 
		{
        	str.replace( pos, 1, "5");
			MatchPassword(poa, str, 2);
        	pos++;
    	}

		//replace: s -> $
		str = gpassword[i];
    	pos = 0;
    	while ( (pos = str.find('s', pos)) != string::npos ) 
		{
        	str.replace( pos, 1, "$");
			MatchPassword(poa, str, 2);
        	pos++;
    	}
		rule_number[2]+=4;
		cpassword+=4;		
	}
}

void AddSpecialChar(vector<string> &gpassword, set<string> &poa, int &cpassword)
{
    string str;
	char buffer[255];

    for (int i=0; i<gpassword.size(); i++)
    {
		//getSpecChar
		for (int j=33; j<=47; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			MatchPassword(poa, str, 3);
			rule_number[3]++;
			cpassword++;
		}
		//getSpecChar
		for (int j=58; j<=64; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			MatchPassword(poa, str, 3);
			rule_number[3]++;
			cpassword++;
		}
		//getSpecChar
		for (int j=91; j<=96; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			MatchPassword(poa, str, 3);
			rule_number[3]++;
			cpassword++;
		}
		//getSpecChar
		for (int j=123; j<=126; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			MatchPassword(poa, str, 3);
			rule_number[3]++;
			cpassword++;
		}
	}
}

int CTwoWords(vector<string> &gpassword, set<string> &poa, int &cpassword)
{
    string str;
    string concatenation;

    char buffer[255];

    for (int i=0; i<gpassword.size(); i++)
    {
    	for (int j=i+1; j<gpassword.size(); j++)
    	{
			if (i == j) continue;

			//Concatenating two words
			//styple:1
			str = gpassword[i];
			concatenation = gpassword[j];
			str.append(concatenation);
			MatchPassword(poa, str, 4);
			//reverse
			str = gpassword[i];
			concatenation.append(str);
			MatchPassword(poa, concatenation, 4);

			//styple:2
			str = gpassword[i];
			concatenation = gpassword[j];
			str.append("_");
			str.append(concatenation);
			MatchPassword(poa, str, 4);
			//reverse
			str = gpassword[i];
			concatenation.append("_");
			concatenation.append(str);
			MatchPassword(poa, concatenation, 4);

			//styple:3
			str = gpassword[i];
			concatenation = gpassword[j];
			str.append("&");
			str.append(concatenation);
			MatchPassword(poa, str, 4);
			//reverse
			str = gpassword[i];
			concatenation.append("&");
			concatenation.append(str);
			MatchPassword(poa, concatenation, 4);

			//styple:4
			str = gpassword[i];
			concatenation = gpassword[j];
			str.append("#");
			str.append(concatenation);
			MatchPassword(poa, str, 4);
			//reverse
			str = gpassword[i];
			concatenation.append("#");
			concatenation.append(str);
			MatchPassword(poa, concatenation, 4);

			rule_number[4]+=8;
			cpassword+=8;
		}

		if (rule_number[4] >= 200000000) return 1;
	}

	return 0;
}

void PrintInfo(set<string> &poa, int &cpassword)
{
	string str;
	//printf information message
	cout << "\n          PasswordCracker Information:" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "Total number of passwords constructed: " << cpassword << endl;
	cout << "Total number of passwords guessed correctly:  " 
 	     << correctly_password.size() << endl;

	sort(correctly_password.begin(), correctly_password.end());

	cout << "List of passwords guessed correctly:  " << endl;
    for (int i=0; i<correctly_password.size(); i++)
    {
		cout << correctly_password[i] << endl;
	}	

	cout << "----------------------------------------------------" << endl;
}

void PrintEchoRuleInfo(int rule)
{
	AddCount = AddCount + corrent_number[rule];
	//print echo rules for information
    cout << "\nCreating passwords using rule " << rule+1 << "..." << endl;
    cout << rule_number[rule] << " passwords created; "
		 << AddCount << " passwords matched"
		 << endl;
}

int main(int argc, char **argv)
{
    string str, astr;
	vector<string> gpassword;
	set<string> rpassword;
    char tmp[80]="";
    stringstream ssconvert;
	int rep = 0;

	//argc must equal 3
	if (argc != 3)
    {
        cout << "format: crack.x word_file password_file" << endl;
        exit(1);
    }

	//reading word_file txt
    FILE *wordfile = fopen64(argv[1], "r");
    FILE *pfile = fopen64(argv[2], "r");

    if (wordfile == NULL || pfile == NULL)
    {
        cout << "file is empty."<<endl;
        return 0;
    }

	//loading password file
    while (fgets( tmp, 80, pfile)!=NULL)
    {
		//getline(pfile, str);
        ssconvert << tmp;
        ssconvert >> str;

		rpassword.insert(str);
    }
	fclose(pfile);

	//loading word file
    while (fgets( tmp, 80, wordfile)!=NULL)
    {
        ssconvert << tmp;
        ssconvert >> str;
 
		//rule1: each word is considered as a potential password 
		gpassword.push_back(str);
		MatchPassword(rpassword, str, 0);
		rule_number[0]++;

		//rule6
		//lower
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		MatchPassword(rpassword, str, 5);

		//upper
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		MatchPassword(rpassword, str, 5);

		rule_number[5]+=2;
		cpassword = cpassword + 3;
    }    
	fclose(wordfile);

	PrintEchoRuleInfo(0);

	//generate guessed passwords, rule 2
	PermuteWord(gpassword, rpassword, cpassword);
	PrintEchoRuleInfo(1);
	
	//generate guessed passwords, rule 3
	RCLetters(gpassword, rpassword, cpassword);
	PrintEchoRuleInfo(2);
	
	//generate guessed passwords, rule 4
	AddSpecialChar(gpassword, rpassword, cpassword);
	PrintEchoRuleInfo(3);
	
	//generate guessed passwords, rule 5
	rep = CTwoWords(gpassword, rpassword, cpassword);

	if (rep == 1)
	{
		cout << "rule 5 exit,\n"
			 <<  "created 200,000,000 passwords for rule 5..."
			 << endl;

	}
	
	//print message for rule 5
	PrintEchoRuleInfo(4);

	//print message for rule 6
	PrintEchoRuleInfo(5);

	PrintInfo(rpassword, cpassword);

    return 0;

}
