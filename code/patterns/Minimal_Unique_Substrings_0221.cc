#include <bits/stdc++.h>
using namespace std;
//solve the reverse complementary sequence problem
//Function to print the unique sub-string of length n
vector<string> result(vector<string>& Vec_s,int n)
{
    vector<string> vec_s=Vec_s;
	map<string,int> hash;
	map<string,int>::iterator iter;
	map<string,int>::iterator iter_1;
	
	//add
	map<string,string> hash_reverse;//substring (_1_2_) -> reverse of this substring (_-2_-1_)
	map<string,string>::iterator iter_r;
	string temp_reverse;
	stringstream ss_r;
	//add
	
	vector<string> vec_unique;
	stringstream ss;
	string temp;
	string temp_time;
	int N=vec_s.size()-n+1;
	for(int i=0;i<N;i++)
	{
		ss.clear();
		ss_r.clear();
		temp.clear();
		ss<<"_";
		for(int j=i;j<i+n;j++)
		{
			ss<<vec_s[j]<<"_";
		}
		ss>>temp;	//substring meeting the length n
		
		//add
		ss_r<<"_";
		for(int j=i+n-1;j>=i;j--)
		{
			temp_time=vec_s[j];
			if(temp_time[0]!='-')
			{
				ss_r<<"-"<<temp_time<<"_";
			}
			if(temp_time[0]=='-')//solve:  _-2_-1_ --> _--1_--2_
			{
//cout<<temp_time<<"\n";
				temp_time.erase(0,1);
//cout<<"temp_time.erase:"<<temp_time<<"\n";
				ss_r<<temp_time<<"_";
			}
		}
		ss_r>>temp_reverse;
		//add
		
		iter=hash.find(temp);
		if(iter==hash.end())
		{
			hash[temp]=1;
		}
		if(iter!=hash.end())
		{
			hash[temp]++;
		}
		
		//add
		iter_r=hash_reverse.find(temp);
//cout<<"temp:"<<temp<<"\n";
//cout<<"temp_reverse:"<<temp_reverse<<"\n";
		if(iter_r==hash_reverse.end())
		{
			hash_reverse[temp]=temp_reverse;
		}
		//add
	}
	
	for(iter=hash.begin();iter!=hash.end();iter++)
	{
		if(iter->second==1)//unique
		{
			temp=iter->first;
			iter_r=hash_reverse.find(temp);
			temp_reverse=iter_r->second;
			iter_1=hash.find(temp_reverse);
			if(iter_1==hash.end())//unique + no_reverse_problem
			{
				vec_unique.push_back(iter->first);
			}
			if(iter_1!=hash.end())
			{
//				cout<<"temp:"<<temp<<"\n";
			}
		}
	}
	
	return vec_unique;
}
  


int main(int argc,char* argv[])
{
    vector<string> vec_s;
	ifstream ifs;
	istringstream istr;
	ofstream ofs(argv[2]);
	int length_thresold=atoi(argv[3]);//Length threshold;0=all
	string temp;
	string temp_1;
//	map<string,int> hash_gene;//for remove gene arrangement with length=1 (1n2n3n4n5n6)
//	map<string,int>::iterator iter;
	map<string,string> hash_genome;//genome->temp_genome
	map<string,string>::iterator iter_genome;
	string genome;
	string temp_genome;
	
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		if(temp[0]=='>')
		{
			genome=temp;
		}
		if(temp[0]!='>')
		{
			temp_genome="_";
			istr.str(temp);
			while(istr>>temp_1)
			{
				vec_s.push_back(temp_1);
				//iter=hash_gene.find(temp_1);
				//if(iter==hash_gene.end())
				//{
				//	hash_gene[temp_1]=1;
				//}
				temp_genome.append(temp_1);
				temp_genome.push_back('_');
			}
			istr.clear();
			vec_s.push_back("n");
			hash_genome[genome]=temp_genome;
		}
	}
	ifs.close();
//*****vec_s completed 1 12345n1245n62345n

//	for(iter=hash_gene.begin();iter!=hash_gene.end();iter++)
//	{
//		vec_s.push_back(iter->first);
//		vec_s.push_back("n");
//	}
//*****vec_s completed 1 12345n1245n62345n1n2n3n4n5n6		
    vector<string> vec_time;
	vector<string> vec_minimal_unqiue;
	vector<string> vec_unique;
	string::size_type position;
	string::size_type position_1;
	//string temp;
	int i,j,k;
	int tag;
	
	if(length_thresold==0)//consider substrings with all length
	{
		length_thresold=vec_s.size();
	}
	for(i=2;i<=length_thresold;i++)//i is the length of substring; length threshold 
	{
		vec_time=result(vec_s,i);
		for(j=0;j<vec_time.size();j++)//j the number of unique substring with length i
		{
			temp=vec_time[j];
			position=temp.find("n");
			if(position==string::npos)//not contain n
			{
				tag=0;
				for(k=0;k<vec_minimal_unqiue.size();k++)
				{
					position_1=temp.find(vec_minimal_unqiue[k]);
					if(position_1!=string::npos)//not minimal
					{
						tag=1;
					}
				}
				if(tag==0)//minimal && not contain n
				{
					vec_minimal_unqiue.push_back(temp);
				}
				
			}
		}
	}
	//minimal
	
	map<string,vector<string> > hash_genome_mus;
	map<string,vector<string> >::iterator iter_mus;

	
	for(i=0;i<vec_minimal_unqiue.size();i++)
	{
		for(iter_genome=hash_genome.begin();iter_genome!=hash_genome.end();iter_genome++)
		{
			temp=iter_genome->second;
			position=temp.find(vec_minimal_unqiue[i]);
			if(position!=string::npos)//this genome contain minimal unique substring
			{
				iter_mus=hash_genome_mus.find(iter_genome->first);
				if(iter_mus==hash_genome_mus.end())
				{
					vec_time.clear();
					vec_time.push_back(vec_minimal_unqiue[i]);
					hash_genome_mus[iter_genome->first]=vec_time;
				}
				if(iter_mus!=hash_genome_mus.end())
				{
					vec_time=iter_mus->second;
					vec_time.push_back(vec_minimal_unqiue[i]);
					hash_genome_mus[iter_genome->first]=vec_time;
				}
			}
		}
	}
	
	int sum=0;
	for(iter_mus=hash_genome_mus.begin();iter_mus!=hash_genome_mus.end();iter_mus++)
	{
		vec_time=iter_mus->second;
		ofs<<iter_mus->first<<"\t"<<vec_time.size()<<"\n";
		sum++;
		for(i=0;i<vec_time.size();i++)
		{
			ofs<<vec_time[i]<<"\t";
		}
		ofs<<"\n";
	}
	
//	cout<<"noreverse_sum:"<<sum<<"\n";
    return 0;
}