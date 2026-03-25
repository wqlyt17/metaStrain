#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<cmath>
#include<algorithm>


using namespace std;


int main(int argc,char* argv[])
{
	ifstream ifs;
	istringstream istr;
	ofstream ofs(argv[2]);
	
	string temp;
	string temp_1;
	
	string::size_type p_1;
	string::size_type p_2;
	
	string target_1="Complete";
	string target_2="https://ftp.ncbi.";
	
	int last_location;
	string name;
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		p_1=temp.find(target_1);//complete genome
		if(p_1!=string::npos)
		{
			istr.str(temp);
			while(istr>>temp_1)
			{
				p_2=temp_1.find(target_2);
				
				if(p_2!=string::npos)
				{
					if(!temp_1.empty() && temp_1.back()=='/')
						temp_1.pop_back();
					last_location = temp_1.find_last_of('/');
					name = temp_1.substr(last_location + 1);

					ofs<<temp_1<<"/"<<name<< "\n";

					break;
				}								
	
			}
			istr.clear();
		}		
	}
	ifs.close();
	
	
	return 0;
}



