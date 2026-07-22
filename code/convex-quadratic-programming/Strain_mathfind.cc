#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector> 
#include <iomanip> 
#include <map> 
#include "QuadProg++.hh"

using namespace QuadProgPP;

int main (int argc, char *const argv[]) 
{
	Matrix<double> G, CE, CI;
	Vector<double> g0, ce0, ci0, x;
	
	std::map<std::string,std::vector<std::vector<std::string> > > hash_species;
	std::map<std::string,std::vector<std::vector<std::string> > >::iterator iter_s;
	std::vector<std::vector<std::string> > Vec_time;
	std::vector<std::string> vec_time;
	
	std::string temp;
	std::string temp_1;
	std::string temp_species;
	std::ifstream ifs;
	std::istringstream istr;
	std::ofstream ofs(argv[5]);
	
	//G
	Vec_time.clear();
	vec_time.clear();
	ifs.open(argv[1]);
	while(getline(ifs,temp))
	{
		if(temp[0]=='*')
		{
			if(vec_time.size()==0)
			{
				temp_species=temp;
			}
			if(vec_time.size()!=0)
			{
				Vec_time.push_back(vec_time);
				hash_species[temp_species]=Vec_time;
				vec_time.clear();
				Vec_time.clear();
				temp_species=temp;
			}	
		}
		if(temp[0]!='*')
		{
			vec_time.push_back(temp);
		}
	}
	ifs.close();
	
	Vec_time.push_back(vec_time);
	hash_species[temp_species]=Vec_time;
	vec_time.clear();
	Vec_time.clear();
	
	//CE
	Vec_time.clear();
	vec_time.clear();
	ifs.open(argv[2]);
	while(getline(ifs,temp))
	{
		if(temp[0]=='*')
		{
			if(vec_time.size()==0)
			{
				temp_species=temp;
			}
			if(vec_time.size()!=0)
			{
				iter_s=hash_species.find(temp_species);
				if(iter_s==hash_species.end())
				{
					std::cout<<"error 1:"<<temp_species<<"\n";
				}
				if(iter_s!=hash_species.end())
				{
					Vec_time=iter_s->second;
					Vec_time.push_back(vec_time);
					hash_species[temp_species]=Vec_time;
					vec_time.clear();
					Vec_time.clear();
					temp_species=temp;
				}	
			}	
		}
		if(temp[0]!='*')
		{
			vec_time.push_back(temp);
		}
	}
	ifs.close();
	
	iter_s=hash_species.find(temp_species);
	if(iter_s==hash_species.end())
	{
		std::cout<<"error 1:"<<temp_species<<"\n";
	}
	if(iter_s!=hash_species.end())
	{
		Vec_time=iter_s->second;
		Vec_time.push_back(vec_time);
		hash_species[temp_species]=Vec_time;
		vec_time.clear();
		Vec_time.clear();
		temp_species=temp;
	}	
	
	//ce
	Vec_time.clear();
	vec_time.clear();
	ifs.open(argv[3]);
	while(getline(ifs,temp))
	{
		if(temp[0]=='*')
		{
			if(vec_time.size()==0)
			{
				temp_species=temp;
			}
			if(vec_time.size()!=0)
			{
				iter_s=hash_species.find(temp_species);
				if(iter_s==hash_species.end())
				{
					std::cout<<"error 1:"<<temp_species<<"\n";
				}
				if(iter_s!=hash_species.end())
				{
					Vec_time=iter_s->second;
					Vec_time.push_back(vec_time);
					hash_species[temp_species]=Vec_time;
					vec_time.clear();
					Vec_time.clear();
					temp_species=temp;
				}	
			}	
		}
		if(temp[0]!='*')
		{
			istr.str(temp);
			while(istr>>temp_1)
			{
				vec_time.push_back(temp_1);	
			}
			istr.clear();
		}
	}
	ifs.close();
	
	iter_s=hash_species.find(temp_species);
	if(iter_s==hash_species.end())
	{
		std::cout<<"error 1:"<<temp_species<<"\n";
	}
	if(iter_s!=hash_species.end())
	{
		Vec_time=iter_s->second;
		Vec_time.push_back(vec_time);
		hash_species[temp_species]=Vec_time;
		vec_time.clear();
		Vec_time.clear();
		temp_species=temp;
	}

	//CI
	Vec_time.clear();
	vec_time.clear();
	ifs.open(argv[4]);
	while(getline(ifs,temp))
	{
		if(temp[0]=='*')
		{
			if(vec_time.size()==0)
			{
				temp_species=temp;
			}
			if(vec_time.size()!=0)
			{
				iter_s=hash_species.find(temp_species);
				if(iter_s==hash_species.end())
				{
					std::cout<<"error 1:"<<temp_species<<"\n";
				}
				if(iter_s!=hash_species.end())
				{
					Vec_time=iter_s->second;
					Vec_time.push_back(vec_time);
					hash_species[temp_species]=Vec_time;
					vec_time.clear();
					Vec_time.clear();
					temp_species=temp;
				}	
			}	
		}
		if(temp[0]!='*')
		{
			vec_time.push_back(temp);
		}
	}
	ifs.close();
	
	iter_s=hash_species.find(temp_species);
	if(iter_s==hash_species.end())
	{
		std::cout<<"error 1:"<<temp_species<<"\n";
	}
	if(iter_s!=hash_species.end())
	{
		Vec_time=iter_s->second;
		Vec_time.push_back(vec_time);
		hash_species[temp_species]=Vec_time;
		vec_time.clear();
		Vec_time.clear();
		temp_species=temp;
	}
//hash_species completed
//************convex quadratic programming*********
	for(iter_s=hash_species.begin();iter_s!=hash_species.end();iter_s++)
	{
		temp_species=iter_s->first;
		ofs<<temp_species<<"\n";
		Vec_time=iter_s->second;
		
		int n=Vec_time[2].size();//the number of pseudo
		int m=Vec_time[0].size()-n;//the number of strains without up
//std::cout<<"n:"<<n<<"\n";
//std::cout<<"m:"<<m<<"\n";
		int t=n+m;
		int i;
		int j;

//std::cout<<"G"<<"\n";		
		vec_time=Vec_time[0];
		G.resize(t, t);
		{
			for(i=0;i<vec_time.size();i++)
			{
				temp=vec_time[i];
				j=0;
				istr.str(temp);
				while(istr>>temp_1)
				{
					G[i][j]=atof(temp_1.c_str());
					j++;
//std::cout<<G[i][j]<<"\t";
				}
				istr.clear();
//std::cout<<"\n";
			}
		}
//std::cout<<"G"<<"\n";
//std::cout<<G<<"\n";	

	
//std::cout<<"g0"<<"\n";	
		g0.resize(t);
		{
			for(i=0;i<t;i++)
			{
				g0[i]=0;
//std::cout<<g0[i]<<"\t";
			}	
		}
//std::cout<<"\n";


//std::cout<<"CE"<<"\n";
		vec_time=Vec_time[1];
		CE.resize(t, n);
		{
			for(i=0;i<vec_time.size();i++)
			{
				temp=vec_time[i];
				j=0;
				istr.str(temp);
				while(istr>>temp_1)
				{
					CE[i][j]=atof(temp_1.c_str());
					j++;
//std::cout<<CE[i][j]<<"\t";
				}
				istr.clear();
//std::cout<<"\n";
			}
		}
		
		
//std::cout<<"ce0"<<"\n";		
		vec_time=Vec_time[2];
		ce0.resize(n);
		{
			for(i=0;i<n;i++)
			{
				temp_1=vec_time[i];
//std::cout<<"temp_1"<<temp_1<<"\t";
				ce0[i]=atof(temp_1.c_str());
//std::cout<<"ce0[i]:"<<ce0[i]<<"\t";
			}
		}
//std::cout<<"\n";
		
		
//std::cout<<"CI"<<"\n";			
		vec_time=Vec_time[3];
		CI.resize(t, m);
		{
			for(i=0;i<vec_time.size();i++)
			{
				temp=vec_time[i];
				j=0;
				istr.str(temp);
				while(istr>>temp_1)
				{
					CI[i][j]=atof(temp_1.c_str());
					j++;
//std::cout<<CI[i][j]<<"\t";
				}
				istr.clear();
//std::cout<<"\n";
			}
		}
		
	
//std::cout<<"ci0"<<"\n";			
		ci0.resize(m);
		{
			for(int i=0;i<m;i++)
			{
				ci0[i]=0;
//std::cout<<ce0[i]<<"\t";
			}
		}
//std::cout<<"\n";		
		
/*		
std::cout<<"G"<<"\n";
std::cout<<G<<"\n";
std::cout<<"g0"<<"\n";
std::cout<<g0<<"\n";
std::cout<<"CE"<<"\n";
std::cout<<CE<<"\n";
std::cout<<"ce0"<<"\n";
std::cout<<ce0<<"\n";
std::cout<<"CI"<<"\n";
std::cout<<CI<<"\n";
std::cout<<"ci0"<<"\n";
std::cout<<ci0<<"\n";
*/

    	ofs<< "f: " << solve_quadprog(G, g0, CE, ce0, CI, ci0, x) <<"\n";
		ofs<< "x: " << x;

//std::cout<<"right 2"<<"\n";			
		for(i=0;i<m;i++)
		{
			ofs<<x[i]<<"\t";
		}
		ofs<<"\n";
	}
	
	vec_time.clear();
	Vec_time.clear();
	hash_species.clear();
}	


	
