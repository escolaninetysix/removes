// list::sort 
#include <iostream> 
#include <fstream>
#include <list> 
#include <string> 
#include <cctype> 
using namespace std; 
long addresscount = 0;
long removecount = 0;
// comparison, not case sensitive. 
bool compare_nocase (string first, string second) 
{ 
	unsigned int i=0; 
	while ( (i<first.length()) && (i<second.length()) ) 
	{ 
		if (tolower(first[i])<tolower(second[i])) return true; 
		else if (tolower(first[i])>tolower(second[i])) return false; 
		++i; 
	} 
	if (first.length()<second.length()) return true; 
	else return false; 
} 

int main () 
{ 
	fstream addressesin;
	addressesin.open("addresses.txt",fstream::in);
	fstream removesin;
	removesin.open("removes.txt",fstream::in);
	list<string> addresslist; 
	list<string>::iterator addressit;
	char addressline[256];
	while (addressesin.getline(addressline,256))
	{
		for (int i = 0; i < strlen(addressline);++i)
		{
			if (addressline[i]>='A' && addressline[i]<='Z') addressline[i]+='a'-'A';
		}		
		addresslist.push_back (addressline); 
		++addresscount;
		//cout << addressline << "\n";
	}
	//mylist.push_back ("two"); 
	//mylist.push_back ("Three"); 
	
	addresslist.sort(); 
	
	/*
	 cout << "mylist contains:"; 
	for (addressit=addresslist.begin(); addressit!=addresslist.end(); ++addressit) 
		cout << " " << *addressit; 
	cout << endl; 
	*/
	
	/*mylist.sort(compare_nocase); 
	
	cout << "mylist contains:"; 
	for (it=mylist.begin(); it!=mylist.end(); ++it) 
		cout << " " << *it; 
	cout << endl; */
	
	list<string> removeslist; 
	list<string>::iterator removesit; 
	list<string>::iterator eos; 
	
	char removeline[256];
	while (removesin.getline(removeline,256))
	{
		for (int i = 0; i < strlen(removeline);++i)
		{
			if (removeline[i]>='A' && removeline[i]<='Z') removeline[i]+='a'-'A';
		}
		removeslist.push_back (removeline); 
		++removecount;
	}
	removeslist.sort(); 
	
	/*cout << "mylist contains:"; 
	for (removesit=removeslist.begin(); removesit!=removeslist.end(); ++removesit) 
		cout << " " << *removesit; 
	cout << endl; 
	*/	
	
	// Output lines that have no matching remove
	addressit = addresslist.begin();
	removesit = removeslist.begin();
	long addresspos = 0;
	long removepos = 0;
	int offlist = 0;
	int offremoves = 0;
	while (!offlist)
	{
		if ( *addressit == *removesit)
		{
			// don't print this one, it's left off the list
			if (addresspos>addresscount-2)
			{
				offlist=1;
			}
			else
			{
				++addressit;
				++addresspos;
			}
			if (removepos>removecount-2)
			{	
				offremoves = 1;
			}
			else
			{
				++removesit;
				++removepos;
			}
		}
		else if (*removesit > *addressit)
		{
			// address is less than remove so there is no remove for this address, so output this address as good
			cout << *addressit << endl;
			if (addresspos > addresscount-2)
			{
				offlist=1;
			}
			else
			{
				++addressit;
				++addresspos;
			}
		}
		else if (*addressit > *removesit && offremoves == 0)
		{
			// remove is less than address, so iterate through more removes until at same value.
			if (removepos > removecount-2)
			{
				offremoves=1;// don't advance removes now.
			}
			else
			{
				++removesit;
				++removepos;
			}
		}
		else if ( *addressit > *removesit && offremoves == 1)
		 {
		 cout << *addressit << endl;
		 if (addresspos > addresscount-2)
		 {
		 offlist=1;
		 }
		 else
		 {
		 ++addressit;
		 ++addresspos;
		 }
		 }
	}
	return 0; 
}