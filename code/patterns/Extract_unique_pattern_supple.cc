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

string RC(string& Temp)
{
	string temp=Temp;
	string temp_rc;
	for(int i=temp.size()-1;i>=0;i--)
	{
		if(temp[i]=='T')
		{
			temp_rc.push_back('A');
		}
		if(temp[i]=='A')
		{
			temp_rc.push_back('T');
		}
		if(temp[i]=='C')
		{
			temp_rc.push_back('G');
		}
		if(temp[i]=='G')
		{
			temp_rc.push_back('C');
		}
	}
	return temp_rc;
}



int main(int argc,char* argv[])
{
	ifstream ifs;
	istringstream istr;
	istringstream istr_1;
	ofstream ofs(argv[3]);
	ofstream ofs_1(argv[4]);

	string temp;
	string temp_1;
	string temp_2;
	string temp_3;
	string temp_1_1;
	
	string temp_genome;
	string temp_gene;
	string temp_rc;
	string temp_pattern;
	string tag;
	int i;
	vector<string> vec_gene;
	vector<int> vec_location;
	string temp_base;
	int sum_length;
	
	int left_half;
	int right_half;

	map<string,string> hash;//cluster name --> base sequence
	map<string,string>::iterator iter;
	
	ifs.open(argv[1]); //centroid_E.coli52.txt
	while(getline(ifs,temp))
	{
		if(temp[0]=='>')
		{
			istr.str(temp);
			istr>>temp_1>>temp_2;
			istr.clear();
			
			getline(ifs,temp);
			hash[temp_2]=temp;
		}
	}
	ifs.close();
	//hash completed
	
	
	map<string,vector<string> > hash_strain_pseudo;
	map<string,vector<string> >::iterator iter_pseudo;
	map<string,string> hash_pseudo_num;
	map<string,string>::iterator iter_num;
	vector<string> vec_pseudo;
	
	ifs.open(argv[2]);//pseudo_gene_arrangements.txt
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2>>temp_3;
		istr.clear();
		
		hash_pseudo_num[temp_1]=temp_3;
		
		iter_pseudo=hash_strain_pseudo.find(temp_2);
		if(iter_pseudo==hash_strain_pseudo.end())
		{
			vec_pseudo.clear();
			vec_pseudo.push_back(temp_1);
			hash_strain_pseudo[temp_2]=vec_pseudo;
		}
		if(iter_pseudo!=hash_strain_pseudo.end())
		{
			vec_pseudo=iter_pseudo->second;
			vec_pseudo.push_back(temp_1);
			hash_strain_pseudo[temp_2]=vec_pseudo;
		}
		
	}
	ifs.close();
//hash_strain_pseudo,hash_pseudo_num completed	
	
	for(iter_pseudo=hash_strain_pseudo.begin();iter_pseudo!=hash_strain_pseudo.end();iter_pseudo++)
	{
		temp_genome=iter_pseudo->first;	
		vec_pseudo=iter_pseudo->second;
//cout<<"vec_pseudo.size():"<<vec_pseudo.size()<<"\n";
		for(int j=0;j<vec_pseudo.size();j++)
		{
			temp_1=vec_pseudo[j];
//cout<<temp_1<<"\n";
			iter_num=hash_pseudo_num.find(temp_1);
			tag=iter_num->second;
			ofs<<temp_genome<<"_"<<tag<<"\n";
			vec_gene.clear();
			vec_location.clear();
			sum_length=0;
			temp_pattern.clear();
			for(i=0;i<temp_1.size();i++)
			{
				if(temp_1[i]=='_')
				{
					temp_1[i]=' ';//_转空格
				}
			}
			istr_1.str(temp_1);//may be a error
			while(istr_1>>temp_1_1)//temp_1_1 is gene
			{				
				vec_gene.push_back(temp_1_1);
			}
			istr_1.clear();
				
			ofs_1<<temp_genome<<"_"<<tag<<"\t"<<vec_gene.size()<<"\n";
				
			for(i=0;i<vec_gene.size();i++)
			{
				temp_gene=vec_gene[i];
				if(temp_gene[0]!='-')
				{
					iter=hash.find(temp_gene);
					if(iter!=hash.end())
					{
						temp_pattern.append(iter->second);
						temp_base=iter->second;
						vec_location.push_back(sum_length+1);
						sum_length=sum_length+temp_base.size();
						vec_location.push_back(sum_length);
//temp_pattern.push_back('*');
					}
					if(iter==hash.end())
					{
						cout<<"error1:"<<temp_gene<<"\n";
					}
				}
					
				if(temp_gene[0]=='-')//reverse sequence
				{
					temp_gene.erase(0,1);//may be a error	
					iter=hash.find(temp_gene);
					if(iter!=hash.end())
					{
						temp_rc=RC(iter->second);
						temp_pattern.append(temp_rc);
						vec_location.push_back(sum_length+1);
						sum_length=sum_length+temp_rc.size();
						vec_location.push_back(sum_length);
//temp_pattern.push_back('*');
					}
					if(iter==hash.end())
					{
						cout<<"error2:"<<temp_gene<<"\n";
					}
				}
					
			}
				//get temp_pattern
			ofs<<temp_pattern<<"\n";
			for(i=0;i<vec_location.size();i++)
			{
				ofs_1<<vec_location[i]<<"\t";
			}
			ofs_1<<"\n";
			left_half=vec_location[0]+0.5*(vec_location[1]-vec_location[0]+1);
			right_half=vec_location[vec_location.size()-2]+0.5*(vec_location[vec_location.size()-1]-vec_location[vec_location.size()-2]+1);
			ofs_1<<left_half<<"\t"<<right_half<<"\n";	
		}	
	}
	
	ofs.close();
	ofs_1.close();
	hash_pseudo_num.clear();
	hash_strain_pseudo.clear();
	hash.clear();
	vec_gene.clear();
	vec_location.clear();
	vec_pseudo.clear();
	
	return 0;
	
	
}



