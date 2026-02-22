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
	ofstream ofs_1(argv[3]);
	

	
	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	float avgrage;
	float sum;
	map<string,vector<float> > hash_genome;//genome --> the read num of each pattern of this genome
	map<string,vector<float> >::iterator iter;
	vector<float> vec_time;
	
	
	int i;
	
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3;//1 genome; 2 pattern; 3 read num
		istr.clear();
		
		iter=hash_genome.find(temp_1);
		if(iter==hash_genome.end())
		{
			vec_time.clear();
			vec_time.push_back(atof(temp_3.c_str()));
			hash_genome[temp_1]=vec_time;
		}
		if(iter!=hash_genome.end())
		{
			vec_time=iter->second;
			vec_time.push_back(atof(temp_3.c_str()));
			hash_genome[temp_1]=vec_time;
		}	
	}
	ifs.close();
	
	for(iter=hash_genome.begin();iter!=hash_genome.end();iter++)
	{
		ofs<<iter->first<<"\t";
		vec_time=iter->second;
		ofs_1<<iter->first<<"\t"<<vec_time.size()<<"\n";
		sum=0;
		for(i=0;i<vec_time.size();i++)
		{
			sum=sum+vec_time[i];
			ofs_1<<vec_time[i]<<"\t";
		}
		avgrage=sum/vec_time.size();
		ofs<<avgrage<<"\n";
		ofs_1<<"\n";
	}
	

	hash_genome.clear();
	return 0;
	
}














