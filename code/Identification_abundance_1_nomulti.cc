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
	ofstream ofs(argv[3]);//read
	

	
	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	int sum;
	map<string,int> hash;
	map<string,int>::iterator iter;
	
	map<string,int> hash_multi;
	map<string,int>::iterator iter_multi;
	
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1;//1 read
		istr.clear();
		
		iter=hash_multi.find(temp_1);
		if(iter==hash_multi.end())
		{
			hash_multi[temp_1]=1;
		}
		if(iter!=hash_multi.end())
		{
			cout<<"error:"<<temp_1<<"\n";;
		}	
	}
	ifs.close();
	
	
	
	
	
	ifs.open(argv[2]);
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2;//1 read; 2 genome and pattern
		istr.clear();
		
		iter_multi=hash_multi.find(temp_1);
		if(iter_multi==hash_multi.end())//remove multi-mapped reads
		{
			iter=hash.find(temp_2);
			if(iter==hash.end())
			{
				hash[temp_2]=1;
			}
			if(iter!=hash.end())
			{
				hash[temp_2]++;
			}
		}			
	}
	ifs.close();
	
	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		ofs<<iter->first<<"\t"<<iter->second<<"\n";
	}
	

	return 0;
	
}














