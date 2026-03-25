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
	
	map<string,int> hash_NC;
	map<string,int>::iterator iter;
	
	
	ifs.open(argv[1]);//SP_136_NC.txt
	while(getline(ifs,temp))
	{
		hash_NC[temp]=1;
	}
	ifs.close();
	
	
	
	
	int i;
	int j;
	string temp_genome;
	string temp_gene;
	vector<string> vec_atcg;
	vector<string> vec_gene;
	
	map<string,vector<string> > hash_gene;//genome name --> gene name
	map<string,vector<string> >::iterator iter_gene;
	map<string,vector<string> > hash_gene_atcg;//gene name -> gene sequences
	map<string,vector<string> >::iterator iter_atcg;
	
	ifs.open(argv[2]);//SP_136_cds.fa
	while(getline(ifs,temp))
	{
		if(temp[0]=='>')//gene 
		{
			if(vec_atcg.size()!=0)//gene sequene
			{
//1 put this gene name to its genome, 2 put this gene sequences to its gene name 
				iter_gene=hash_gene.find(temp_genome);//1 put this gene name to its genome
				if(iter_gene==hash_gene.end())
				{
					vec_gene.clear();
					vec_gene.push_back(temp_gene);
					hash_gene[temp_genome]=vec_gene;
				}
				if(iter_gene!=hash_gene.end())
				{
					vec_gene=iter_gene->second;
					vec_gene.push_back(temp_gene);
					hash_gene[temp_genome]=vec_gene;
				}
				
				iter_atcg=hash_gene_atcg.find(temp_gene);//2 put this gene sequences to its gene name
				if(iter_atcg==hash_gene_atcg.end())
				{
					hash_gene_atcg[temp_gene]=vec_atcg;
					vec_atcg.clear();
				}
				if(iter_atcg!=hash_gene_atcg.end())
				{
					cout<<"error:"<<temp_gene;
					vec_atcg.clear();
				}
			}
			istr.str(temp);
			istr>>temp_1>>temp_2;
			istr.clear();
			temp_genome=temp_2;
			temp_gene=temp;
			
		}
		if(temp[0]!='>')
		{
			vec_atcg.push_back(temp);
		}
	}
	ifs.close();
	
	if(vec_atcg.size()!=0)//gene sequene
	{
//1 put this gene name to its genome, 2 put this gene sequences to its gene name 
		iter_gene=hash_gene.find(temp_genome);//1 put this gene name to its genome
		if(iter_gene==hash_gene.end())
		{
			vec_gene.clear();
			vec_gene.push_back(temp_gene);
			hash_gene[temp_genome]=vec_gene;
		}
		if(iter_gene!=hash_gene.end())
		{
			vec_gene=iter_gene->second;
			vec_gene.push_back(temp_gene);
			hash_gene[temp_genome]=vec_gene;
		}
				
		iter_atcg=hash_gene_atcg.find(temp_gene);//2 put this gene sequences to its gene name
		if(iter_atcg==hash_gene_atcg.end())
		{
			hash_gene_atcg[temp_gene]=vec_atcg;
			vec_atcg.clear();
		}
		if(iter_atcg!=hash_gene_atcg.end())
		{
			cout<<"error:"<<temp_gene;
			vec_atcg.clear();
		}
	}
	//hash_gene complete;
	//hash_gene_atcg complete
	
	
	for(iter_gene=hash_gene.begin();iter_gene!=hash_gene.end();iter_gene++)
	{
		iter=hash_NC.find(iter_gene->first);
		if(iter!=hash_NC.end())//find this genome
		{
			vec_gene=iter_gene->second;
			for(i=0;i<vec_gene.size();i++)
			{
				iter_atcg=hash_gene_atcg.find(vec_gene[i]);
				if(iter_atcg==hash_gene_atcg.end())
				{
					cout<<"error:"<<vec_gene[i]<<"-no find"<<"\n";
				}
				if(iter_atcg!=hash_gene_atcg.end())
				{
					ofs<<vec_gene[i]<<"\n";
					vec_atcg=iter_atcg->second;
					for(j=0;j<vec_atcg.size();j++)
					{
						ofs<<vec_atcg[j]<<"\n";
					}
				}
			}
		}
	}
	
	
	
	hash_gene.clear();
	hash_gene_atcg.clear();
	vec_atcg.clear();
	vec_gene.clear();
	hash_NC.clear();
	
	return 0;
}



