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
	ofstream ofs(argv[3]);
	
	string temp;
	string temp_1;
	
	map<string,int> hash_NC;
	map<string,int>::iterator iter;
	
	
	ifs.open(argv[1]);//SP_136_NC.txt
	while(getline(ifs,temp))
	{
		hash_NC[temp]=1;
	}
	ifs.close();
		
	int i;
	string temp_genome;
	vector<string> vec_atcg;
	map<string,vector<string> > hash_atcg;//genome name --> actg sequences
	map<string,vector<string> >::iterator iter_atcg;
	
	ifs.open(argv[2]);//SP_136_cds.fa
	while(getline(ifs,temp))
	{
		if(temp[0]=='>')
		{
			if(vec_atcg.size()!=0)
			{
				iter_atcg=hash_atcg.find(temp_genome);
				if(iter_atcg==hash_atcg.end())
				{
					hash_atcg[temp_genome]=vec_atcg;
					vec_atcg.clear();
				}
				if(iter_atcg!=hash_atcg.end())
				{
					cout<<"error:"<<temp_genome<<"\n";
					vec_atcg.clear();
				}
			}
			temp_genome=temp;
			
		}
		if(temp[0]!='>')
		{
			vec_atcg.push_back(temp);
		}
	}
	ifs.close();
	
	if(vec_atcg.size()!=0)
	{
		iter_atcg=hash_atcg.find(temp_genome);
		if(iter_atcg==hash_atcg.end())
		{
			hash_atcg[temp_genome]=vec_atcg;
			vec_atcg.clear();
		}
		if(iter_atcg!=hash_atcg.end())
		{
			cout<<"error:"<<temp_genome<<"\n";
		}
	}
	//hash_atcg complete;
	
	
	for(iter_atcg=hash_atcg.begin();iter_atcg!=hash_atcg.end();iter_atcg++)
	{
		iter=hash_NC.find(iter_atcg->first);
		if(iter!=hash_NC.end())//find
		{
			ofs<<iter_atcg->first<<"\n";
			vec_atcg=iter_atcg->second;
			for(i=0;i<vec_atcg.size();i++)
			{
				ofs<<vec_atcg[i]<<"\n";
			}
		}
	}
	
	
	hash_NC.clear();
	hash_atcg.clear();
	vec_atcg.clear();
	return 0;
}



