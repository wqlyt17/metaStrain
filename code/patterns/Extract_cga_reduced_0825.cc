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
	string temp_2;
	string temp_3;
	
	map<string,int> hash;
	map<string,int>::iterator iter;


	ifs.open(argv[1]);//analysis_out.txt
	while(getline(ifs,temp))
	{
		hash[temp]=1;
	}
	ifs.close();

//	cout<<"the num of CGAS after fitering:"<<hash.size()<<"\n";
	
	int tag=0;
	int flag=0;
	ifs.open(argv[2]);//pseudo_gene_arrangements.txt
	while(getline(ifs,temp))
	{
		tag++;
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3;
		istr.clear();
		iter=hash.find(temp_3);
		if(iter!=hash.end())//CGAs after filtering
		{
			flag++;
			ofs<<temp_1<<"\t"<<temp_2<<"\t"<<flag<<"\n";
		}
		
	}
	ifs.close();
	
//	cout<<"the num of CGAS before fitering:"<<tag<<"\n";	
	
	hash.clear();
	return 0;
}



