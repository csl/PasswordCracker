#include<iostream>
#include<fstream>
#include<vector>
#include<cctype>
#include<string>
#include <algorithm>

//#define DEBUG

using namespace std;

struct CorrPassword
{
	string cpassword;
	bool match;
};

int CountCorrentPassword(vector<CorrPassword> &pos, vector<string> &copassword)
{

	for (int i=0; i<pos.size(); i++)
    {
        //count for all match
        if (pos[i].match == true)
        {
			copassword.push_back(pos[i].cpassword);
        }		
	}

	return copassword.size();

}
void MatchPassword(vector<CorrPassword> &pos, string str)
{
	int scan=0, poa=0;

    for (int i=0; i<pos.size(); i++)
    {
		//not match
		if (pos[i].match == false && pos[i].cpassword.compare(str) == 0) 
		{
		#ifdef DEBUG
			cout << pos[i].cpassword << " match to " << str << endl;
		#endif
			pos[i].match = true;
			poa=1;
		}
		else
		{
			continue;
		}

		//count for all match
		if (pos[i].match == true)
		{
			scan++;
			if (poa==1) break;
		}
	}

	if (pos.size() == scan)
	{
		cout << "all password match." << endl;
		exit(1);
	}
	
}

void PermuteWord(vector<string> &gpassword, vector<CorrPassword> &pos, int &cpassword)
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
				MatchPassword(pos, str);				
				MatchPassword(pos, astr);				
				//00-09
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "0%d", j);
				str.append(buffer);
				MatchPassword(pos, str);
				MatchPassword(pos, astr);
				//00-09
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "00%d", j);
				str.append(buffer);
				MatchPassword(pos, str);
				MatchPassword(pos, astr);

				cpassword+=6;
			}
			else if (j<100)
			{
				//10-99
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "%d", j);
				str.append(buffer);
				MatchPassword(pos, str);
				MatchPassword(pos, astr);
				//010-099
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "0%d", j);
				str.append(buffer);
				MatchPassword(pos, str);
				MatchPassword(pos, astr);
				cpassword+=4;
			}
			else
			{
				//100-999
            	str = gpassword[i];
				astr = gpassword[i];
				sprintf(buffer, "%d", j);
				str.append(buffer);
				MatchPassword(pos, str);
				MatchPassword(pos, astr);
				cpassword+=2;
			}
		}
	}
}

void RCLetters(vector<string> &gpassword, vector<CorrPassword> &poa, int &cpassword)
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
			MatchPassword(poa, str);
        	pos++;
    	}

		//replace: o -> 0
		str = gpassword[i];
    	pos = 0;
    	while ( (pos = str.find('o', pos)) != string::npos ) 
		{
        	str.replace( pos, 1, "0");
			MatchPassword(poa, str);
        	pos++;
    	}
		
		//replace: s -> 5
		str = gpassword[i];
    	pos = 0;
    	while ( (pos = str.find('s', pos)) != string::npos ) 
		{
        	str.replace( pos, 1, "5");
			MatchPassword(poa, str);
        	pos++;
    	}

		//replace: s -> $
		str = gpassword[i];
    	pos = 0;
    	while ( (pos = str.find('s', pos)) != string::npos ) 
		{
        	str.replace( pos, 1, "$");
			MatchPassword(poa, str);
        	pos++;
    	}

		cpassword+=4;		
	}
}

void AddSpecialChar(vector<string> &gpassword, vector<CorrPassword> &poa, int &cpassword)
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
			MatchPassword(poa, str);
			cpassword++;
		}
		//getSpecChar
		for (int j=58; j<=64; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			MatchPassword(poa, str);
			cpassword++;
		}
		//getSpecChar
		for (int j=91; j<=96; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			MatchPassword(poa, str);
			cpassword++;
		}
		//getSpecChar
		for (int j=123; j<=126; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			MatchPassword(poa, str);
			cpassword++;
		}
	}
}

void CTwoWords(vector<string> &gpassword, vector<CorrPassword> &poa, int &cpassword)
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
			MatchPassword(poa, str);
			//reverse
			str = gpassword[i];
			concatenation.append(str);
			MatchPassword(poa, concatenation);

			//styple:2
			str = gpassword[i];
			concatenation = gpassword[j];
			str.append("_");
			str.append(concatenation);
			MatchPassword(poa, str);
			//reverse
			str = gpassword[i];
			concatenation.append("_");
			concatenation.append(str);
			cout << concatenation << endl;
			MatchPassword(poa, concatenation);

			//styple:3
			str = gpassword[i];
			concatenation = gpassword[j];
			str.append("&");
			str.append(concatenation);
			MatchPassword(poa, str);
			//reverse
			str = gpassword[i];
			concatenation.append("&");
			concatenation.append(str);
			MatchPassword(poa, concatenation);

			//styple:4
			str = gpassword[i];
			concatenation = gpassword[j];
			str.append("#");
			str.append(concatenation);
			MatchPassword(poa, str);
			//reverse
			str = gpassword[i];
			concatenation.append("#");
			concatenation.append(str);
			MatchPassword(poa, concatenation);
		}

	}
}

void PrintInfo(vector<CorrPassword> &poa, int &cpassword)
{
	string str;
	vector<string> correctpassword;

	cout << "\n          PasswordCracker Information:" << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "Total number of passwords constructed: " << cpassword << endl;
	cout << "Total number of passwords guessed correctly:  " 
 	     << CountCorrentPassword(poa, correctpassword) << endl;

	sort(correctpassword.begin(), correctpassword.end());

	cout << "List of passwords guessed correctly:  " << endl;
    for (int i=0; i<correctpassword.size(); i++)
    {
		cout << correctpassword[i] << endl;
	}	

	cout << "----------------------------------------------------" << endl;
}

int main(int argc, char **argv)
{
    string str, astr;
	vector<string> gpassword;
	vector<CorrPassword> rpassword;
	struct CorrPassword cp;

	int cpassword = 0;

	if (argc != 3)
    {
        cout << "format: crack.x word_file password_file" << endl;
        exit(1);
    }

	//reading word_file txt
    ifstream wordfile(argv[1]);
    ifstream pfile(argv[2]);

    if (wordfile.peek() == EOF || pfile.peek() == EOF)
    {
        cout << "file is empty."<<endl;
        return 0;
    }

    while (!pfile.eof())
    {
		pfile >> str;
		cp.cpassword = str;
		cp.match = false;
		rpassword.push_back(cp);
    }
	pfile.close();

    while (!wordfile.eof())
    {
        wordfile >> str;
		//rule1: each word is considered as a potential password 
		gpassword.push_back(str);
		MatchPassword(rpassword, str);

		//rule6
		//lower
		transform(str.begin(), str.end(), str.begin(), ::tolower);
		MatchPassword(rpassword, str);
		//upper
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		MatchPassword(rpassword, str);

		cpassword = cpassword + 3;
    }    
	wordfile.close();

	//generate guessed passwords, rule 2
	PermuteWord(gpassword, rpassword, cpassword);
	
	//generate guessed passwords, rule 3
	RCLetters(gpassword, rpassword, cpassword);
	
	//generate guessed passwords, rule 4
	AddSpecialChar(gpassword, rpassword, cpassword);
	
	//generate guessed passwords, rule 4
	CTwoWords(gpassword, rpassword, cpassword);
	
	PrintInfo(rpassword, cpassword);

    return 0;

}
