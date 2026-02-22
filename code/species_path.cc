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
	ofstream ofs(argv[4]);
	
	string path=argv[2];
	float threshold=atof(argv[3]);//species with top abundance

	string temp;
	string temp_1;
	string temp_2;
	
	float sum=0;

	
	
	ifs.open(argv[1]);//meta_sample_species.txt
	while(getline(ifs,temp))
	{
		istr.str(temp);
		istr>>temp_1>>temp_2;
		istr.clear();
		
		sum++;
		if(sum<=threshold)
		{
			ofs<<path<<temp_1<<"\n";
		}
		
	}
	ifs.close();

	return 0;
}



