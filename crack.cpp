#include<iostream>
#include<fstream>
#include <vector>

#define DEBUG

using namespace std;

struct CorrPassword
{
	string cpassword;
	bool match;
};

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
	char asii;
	char buffer[255];

    for (int i=0; i<gpassword.size(); i++)
    {
		//getSpecChar
		for (int j=(int) '!'; j<=15; j++)
		{
			str = gpassword[i];
			sprintf(buffer, "%c", (char) j);
			str.append(buffer);
			cout << str << endl;			
		}
	}
}


int main(int argc, char **argv)
{
    string str;
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

    while (!wordfile.eof())
    {
        wordfile >> str;
		//rule1: each word is considered as a potential password 
		gpassword.push_back(str);
		MatchPassword(rpassword, str);
		cpassword++;
    }    
	wordfile.close();

	/*
	for (vector<string>::iterator it = gpassword.begin(); it!=gpassword.end(); ++it) 
	{
    	cout << *it << endl;
	}	
	*/

	//generate guessed passwords, rule 2
	//PermuteWord(gpassword, rpassword, cpassword);
	
	//generate guessed passwords, rule 3
	//RCLetters(gpassword, rpassword, cpassword);
	
	//generate guessed passwords, rule 4
	AddSpecialChar(gpassword, rpassword, cpassword);
	
    return 0;

}
