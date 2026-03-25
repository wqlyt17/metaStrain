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
	string temp_2;
	string temp_3;
	string temp_4;
	string temp_5;
	string temp_6;
	

	
	map<string,int> hash;
	map<string,int>::iterator iter;
	
	map<string,string> hash_p_g;
	map<string,string>::iterator iter_p_g;
	
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
				iter=hash.find(temp_1);
				if(iter==hash.end())
				{
					hash[temp_1]=1;
				}
				if(iter!=hash.end())
				{
					hash[temp_1]++;
				}
				
				iter_p_g=hash_p_g.find(temp_1);
				hash_p_g[temp_1]=temp_3;
			}
		}
	}
	ifs.close();


	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		if(iter->second==1)
		{
			ofs<<iter->first<<"\t"<<hash_p_g[iter->first]<<"\n";
		}
	}

	
	hash.clear();
	hash_p_g.clear();
	return 0;
}



