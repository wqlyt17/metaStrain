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
	string temp_4;
	string temp_5;
	string temp_6;
	string temp_7;
	string temp_8;
	string temp_9;
	int sum;
	string temp_gene;
	string temp_sequence;
	
	map<string,string> hash_1;//gene name --> cluster name
	map<string,string>::iterator iter_1;
	
	map<string,string> hash_2;//cluster name --> base sequence
	map<string,string>::iterator iter_2;
	
	ifs.open(argv[1]); //output_75.uc
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3>>temp_4>>temp_5>>temp_6>>temp_7>>temp_8>>temp_9;//temp_9:  lcl|NC_002695.2_gene_496
		istr.clear();
		if(temp_1=="C")
		{
			iter_1=hash_1.find(temp_9);
			if(iter_1==hash_1.end())
			{
				hash_1[temp_9]=temp_2;
			}
			if(iter_1!=hash_1.end())
			{
				cout<<"error1:"<<temp_9<<"\n";
			}
		}	
	}
	ifs.close();
//cout<<"hash_1.size():"<<hash_1.size()<<"\n";	
	//hash_1 completed
	
	
	temp_sequence.clear();
	ifs.open(argv[2]); //E.coli_52_gene_0.fa
	while(getline(ifs,temp))
	{
		if(temp[0]=='>')
		{
			istr.str(temp);
			istr>>temp_1>>temp_2;//now genename=temp_2; last genename=temp_gene
			istr.clear();
			if(temp_sequence.size()!=0)
			{
				iter_1=hash_1.find(temp_gene);
				if(iter_1!=hash_1.end())//find the centroid gene sequences
				{
					iter_2=hash_2.find(iter_1->second);
					if(iter_2==hash_2.end())
					{
						hash_2[iter_1->second]=temp_sequence;
					}
					if(iter_2!=hash_2.end())
					{
						cout<<"error2:"<<iter_1->second<<"\n";
					}	
				}
			}
			temp_gene=temp_2;
			temp_sequence.clear();
		}
		if(temp[0]!='>')//ATCG
		{
			temp_sequence.append(temp);
		}	
	}
	ifs.close();
	
	if(temp_sequence.size()!=0)
	{
		iter_1=hash_1.find(temp_gene);
		if(iter_1!=hash_1.end())//find the centroid gene sequences
		{
			iter_2=hash_2.find(iter_1->second);
			if(iter_2==hash_2.end())
			{
				hash_2[iter_1->second]=temp_sequence;
			}
			if(iter_2!=hash_2.end())
			{
				cout<<"error2:"<<iter_1->second<<"\n";
			}	
		}
	}
	
	
//cout<<"hash_2.size():"<<hash_2.size()<<"\n";		
	
	for(iter_2=hash_2.begin();iter_2!=hash_2.end();iter_2++)
	{
		ofs<<">cluster"<<"\t"<<iter_2->first<<"\n";
		ofs<<iter_2->second<<"\n";
	}
	
	

	return 0;
}



