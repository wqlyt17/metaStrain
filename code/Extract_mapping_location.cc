#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#include<map>
#include<algorithm>

using namespace std;

int main(int argc,char* argv[])
{
	ifstream ifs;
	istringstream istr;
	ofstream ofs(argv[2]);

	
	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	string temp_4;
	string temp_5;
	string temp_6;
	vector<char> s1_letter;
	vector<int> s1_number;
	int region_l;
	int region_r;
	int tag;
	int t_1;
	
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		if(temp[0]!='@')
		{			
			istr.str(temp);
			istr>>temp_1>>temp_2>>temp_3>>temp_4>>temp_5>>temp_6;
			istr.clear();
			if(temp_6!="*")//对每个有mapping结果的read进行遍历
			{				
				s1_letter.clear();
				s1_number.clear();
				

				ofs<<">"<<temp_1<<"\n";//output read name
				ofs<<temp_3<<"\t";//output the name of the reference which this read maps to
				
				t_1=0;
				for(int i=0;i<temp_6.size();i++)
				{
					if((temp_6[i]>='A')&&(temp_6[i]<='Z'))
					{
						s1_letter.push_back(temp_6[i]);
						s1_number.push_back(atoi(temp_6.substr(t_1,i-t_1).c_str()));
						t_1=i+1;
					}
				}	
					
				
				region_l=atoi(temp_4.c_str());
				region_r=region_l;
				for(int i=0;i<s1_letter.size();i++)
				{
					if((s1_letter[i]=='M')||(s1_letter[i]=='D')||(s1_letter[i]=='M'))
					{
						region_r=region_r+s1_number[i];
					}
				}
				region_r=region_r-1;
				ofs<<region_l<<"\t"<<region_r<<"\n";			
			}	
		}
	}
	ifs.close();
	



	s1_letter.clear();
	

	return 0;
	
}














