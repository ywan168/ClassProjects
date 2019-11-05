

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int isHit (int page, int num_frame, std::vector<int> pgmemo)
{
	int hit = 0;
	for (int j = 0; j < num_frame; j++)
	{
		if (pgmemo[j]== page)
		{
			hit = 1; break;
		}
	}
	return hit;
}
int getHitIndex(int page, int num_frame, std::vector<int> pgmemo)
{
	int hitind=-1;
	for (int k = 0; k < num_frame; k++)
	{
		if (pgmemo[k] == page)
		{
			hitind = k; break;
		}
	}
	return hitind;
}

int main(int argc, char** argv) 
{
	std::string input_file = "default";
	if (argc ==2)
	{
		input_file = argv[1];
	}
	else 
	{
		cout <<"Please check your argument." <<endl;
		cout <<"The first argument should be input file name." <<endl;
		return 0;
	}
	std::ifstream infile;
	infile.open(input_file);
	std::vector<int> pages; //page references list
	std::vector<int> Rbit; //reference bit list
	std::vector<int> Mbit; //modifiy bit list
	std::vector<std::string> ops;
	int nf; //number of frame
	int count;
	int mypages;  //read from file
	std::string myops; //read from file
	int pagefault = 0; //number of page fault
	int clock = 0; //clock pointer
	int swapin = 0; //number of swap in
	int swapout = 0; // number of swap out

	cout <<"Enter the number of available frames: " <<endl; 
	cin >> nf;
	for (int i = 0; i<nf; i++)  //initialize reference/modify bit
	{
		Rbit.push_back(0);
		Mbit.push_back(0);     
	}
	std::vector<int> pmemo;      //current page in memory
	for (int i = 0; i < nf; i++)
		pmemo.push_back(99999);
	if(!infile)
	{
		cout <<"Error finding input file" << endl;
		exit(0);
	}
	count = 0;
	while(true)
	{
                infile >> myops >> mypages;
		if( infile.eof() ) break;
		pages.push_back(mypages);
		ops.push_back(myops);
		count++;
	}
	// displace the number of page references
	cout <<"The number of page referneces in file is "<< pages.size() << endl;
	for (int i = 0; i < pages.size(); i++)
	{
            if(ops[i]=="R")
	    {
		if(isHit(pages[i],nf,pmemo))
		{
			    int hitindex = getHitIndex(pages[i], nf, pmemo);
			    if(hitindex!=-1)
			    {
			       if (Rbit[hitindex] == 0)
			       {
			           Rbit[hitindex] = 1;
			       }
			    }
		}
		else 
		{
		        pagefault++;
			if (Rbit[clock] == 1)
			{
			     do 
			     {
			          Rbit[clock] = 0;
				  clock++;
				  if (clock == nf)
				      clock = 0;
			     } while (Rbit[clock] != 0);
			}
			if (Rbit[clock] == 0)
			{
				     if (Mbit[clock] == 0)
				     {
					     swapin++;

				     }
				     else
				     {
					     swapin++;
					     swapout++;
				     }
			             pmemo[clock] = pages[i];
			             Rbit[clock] = 0;
				     Mbit[clock] = 0; // set Mbit to zero for new item
			             clock++;
			}
	                if (clock == nf)
	                   clock = 0;
	         }
	      }
	      if(ops[i]=="W")
	      {
	      	if(isHit(pages[i],nf,pmemo))
		{
			    int hitindex = getHitIndex(pages[i], nf, pmemo);
			    if(hitindex!=-1)
			    {
			       if (Rbit[hitindex] == 0)
			       {
			           Rbit[hitindex] = 1;
			       }
			    }
			    if(Mbit[hitindex]==0)
			    {
			       Mbit[hitindex] =1; 
			    }
		} 
		else 
		{
			pagefault++;
			if (Rbit[clock] == 1)
			{
			     do 
			     {
			          Rbit[clock] = 0;
				  clock++;
				  if (clock == nf)
				      clock = 0;
			     } while (Rbit[clock] != 0);
			}
			if(Rbit[clock]==0)
			{
			     if(Mbit[clock]==1)
			     {
			          swapout++;
				  swapin++;
			     }
			     if(Mbit[clock]==0)
			     {
			          swapin++;
				  Mbit[clock]=1;
			     }
			}
                        pmemo[clock] = pages[i];
			Rbit[clock] = 0;
			clock++;
		}   
	      }
	}
	
	// displace the number of page faults
	cout<< "The total number of page faults is " << pagefault << endl;
	cout<<"The total number of swap in pages is " <<swapin <<", and time units are "<<5*swapin<<endl;
	cout<<"The total number of swap out pages is " <<swapout <<", and time units are "<<10*swapout<<endl;
	return 0;
}
