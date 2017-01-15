// Removes2005.cpp : Defines the entry point for the console application.
//

#include <iostream> 
#include <fstream>
#include <list> 
#include <string> 
#include <cctype> 
using namespace std; 


void dounique(char* inputfile, char* outputfile)
{
fstream rawinput;
rawinput.open(inputfile,fstream::in);
fstream uniqueoutput;
uniqueoutput.open(outputfile,fstream::out);
char rawinline[512];
char lastline[512];
lastline[0]='\0';
while (rawinput.getline(rawinline,510))
{
bool isdupe = true; // Assume duplicate, prove not a duplicate.
if (strlen(lastline)!=strlen(rawinline)) isdupe=false;
if (isdupe)
{
bool ismismatch = false; // Assume no mismatch, prove that it is a mismatch.
for (int itr = 0; itr < strlen(rawinline);++itr)
{
if (rawinline[itr] != lastline[itr])
{
ismismatch=true;
}
}
if (ismismatch) isdupe=false;
}
if (isdupe)
{}
else
{
uniqueoutput.write(rawinline, strlen(rawinline));
uniqueoutput << endl;
strcpy(lastline, rawinline);
}
}
rawinput.close();
uniqueoutput.close();
}


void dolowercase(char* inputfile, char* outputfile)
{
fstream casedinput;
casedinput.open(inputfile,fstream::in);
fstream lowercaseoutput;
lowercaseoutput.open(outputfile,fstream::out);
char rawcasedline[512];
while (casedinput.getline(rawcasedline,510))
{
int rawlen = strlen(rawcasedline);
for (int itr = 0; itr < rawlen; ++itr)
{
char thischar = rawcasedline[itr];
if (thischar >= 'A' && thischar <= 'Z') thischar += ('a'-'A');
rawcasedline[itr]=thischar;
}
lowercaseoutput.write(rawcasedline, strlen(rawcasedline));
lowercaseoutput << endl;
}
casedinput.close();
lowercaseoutput.close();
}


void dosort(char* inputfile, char* outputfile)
{
fstream unsortedinput;
unsortedinput.open(inputfile,fstream::in);
fstream sortedoutput;
sortedoutput.open(outputfile,fstream::out);
long addresscount=0;
list<string> addresslist; 
list<string>::iterator addressit;
char addressline[512];
while (unsortedinput.getline(addressline,510))
{
addresslist.push_back (addressline); 
++addresscount;
}
if (addresscount == 0)
{
//do nothing
}
else
{
addresslist.sort(); 
addressit = addresslist.begin();
for (long addresspos = 0; addresspos < addresscount; ++addresspos)
{
sortedoutput << *addressit << endl;
//sortedoutput.write(*addressit, strlen(*addressit));
++addressit;
}
}
unsortedinput.close();
sortedoutput.close();
return;
}


void dosplitcommas(char* inputfile, char* outputfile)
{
fstream unfilteredinput;
unfilteredinput.open(inputfile,fstream::in);
fstream filteredoutput;
filteredoutput.open(outputfile,fstream::out);



char checkline[256];
while (unfilteredinput.getline(checkline,255))
{
//split commas first
int commacount = 0;
for (unsigned int it1 = 0; it1 < strlen(checkline);++it1)
{
if (checkline[it1]==',') ++commacount;
}
if (commacount > 0)
{
unsigned int leftchar = 0;
unsigned int rightchar = strlen(checkline);
char templine[512];
unsigned int itr4,itr3,itr2;
for (itr2 = 0; itr2 < commacount; ++itr2)
{
for (itr3 = leftchar; itr3 < strlen(checkline); ++itr3)
{
if (checkline[itr3]==',')  //flush the entry to the left of the comma
{
rightchar=itr3;
for (itr4 = leftchar; itr4 < rightchar; ++itr4)
{
templine[itr4-leftchar]=checkline[itr4];
}
templine[rightchar-leftchar]='\0';
filteredoutput << templine  << endl;
leftchar = rightchar;
if (strlen(checkline)-1 > itr3) leftchar = itr3+1; //put it past the , if there's room
rightchar = strlen(checkline);
break; //Continue with next comma section.
}
}
}
//Do last section to the right of the last comma
for (itr4 = leftchar; itr4 < strlen(checkline); ++itr4)
{
templine[itr4-leftchar]=checkline[itr4];
}
templine[strlen(checkline)-leftchar]='\0';
filteredoutput << templine  << endl;
}
else
{
filteredoutput << checkline << endl;
}
}
unfilteredinput.close();
filteredoutput.close();
return;
}


void dofilter1(char* inputfile, char* outputfile)
{
fstream unfilteredinput;
unfilteredinput.open(inputfile,fstream::in);
fstream filteredoutput;
filteredoutput.open(outputfile,fstream::out);
char localchars[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&'*+-/=?^_`{|}~.";
char domainchars[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-.";
int localcharslen=strlen(localchars);
int domaincharslen=strlen(domainchars);
char checkline[256];
int countatsign = 0;
while (unfilteredinput.getline(checkline,255))
{
countatsign=0;
int badchar = 0;
//Block non-ASCII characters; block characters: <, >.
int checklinelen = strlen(checkline);
for (unsigned int j = 0; j < checklinelen;++j)
{
unsigned int thischar= (int) checkline[j];
if (thischar == '@')
{
countatsign++;
if (countatsign>1) badchar = 1;
}
else
{
if (countatsign==0)
{
bool hitgood = false;  // start unfound, prove found in list
for (int itr = 0; itr < localcharslen; ++itr)
{
if (thischar==localchars[itr]) hitgood=true;
}
if (!hitgood) badchar=1;
}
else
{
bool hitgood = false;  // start unfound, prove found in list
for (int itr = 0; itr < domaincharslen; ++itr)
{
if (thischar==domainchars[itr]) hitgood=true;
}
if (!hitgood) badchar=1;
}
}
}
// if badchar then do not output address line.
if (!badchar)
{
filteredoutput << checkline << endl;
}
}
unfilteredinput.close();
filteredoutput.close();
return;
}


void dofilter2(char* inputfile, char* outputfile)
{
fstream unfilteredinput;
unfilteredinput.open(inputfile,fstream::in);
fstream filteredoutput;
filteredoutput.open(outputfile,fstream::out);
char checkmail[512];
int atcount;
int atproblem;
while (unfilteredinput.getline(checkmail,510))
{
atcount = 0;
atproblem = 0;
for (unsigned int it4 = 0; it4 < strlen(checkmail); ++it4)
{
if (checkmail[it4] == '@')
{
if (it4 == 0 || it4 == strlen(checkmail))
{
atproblem = 1;
}
else
{
atcount+=1;
}
}
}
if (atproblem == 0 && atcount== 1) filteredoutput << checkmail << endl;
}  
}


void dotrimwhitespace(char* inputfile, char* outputfile)
{
fstream untrimmedinput;
untrimmedinput.open(inputfile,fstream::in);
fstream trimmedoutput;
trimmedoutput.open(outputfile,fstream::out);



char checkline[256];
char outline[256];
while (untrimmedinput.getline(checkline,255))
{
outline[0]='\0';
int leftgood=0;
bool skipout=false;
for (unsigned int itr = 0; (!skipout) && (itr < strlen(checkline)); ++itr)
{
if (!(checkline[itr]=='\t' || checkline[itr]==' '))
{
skipout=true;
}
else
{
++leftgood;
}
}
int rightgood=strlen(checkline)-1;
skipout=false;
for (unsigned int itr = strlen(checkline)-1; (!skipout) && (itr >= 0); --itr)
{
if (!(checkline[itr]=='\t' || checkline[itr]==' '))
{
skipout=true;
}
else
{
--rightgood;
}
}
if ((rightgood-leftgood) >=0)
{
outline[(rightgood-leftgood)+1]='\0';
for (unsigned itr = leftgood; itr <= rightgood; ++itr)
{
outline[itr-leftgood]=checkline[itr];
}
trimmedoutput.write(outline,strlen(outline));
trimmedoutput << endl;
}
}
untrimmedinput.close();
trimmedoutput.close();
return;
}


void dostorecase(char* inputfile, char* outputfile)
{
fstream casedinput;
casedinput.open(inputfile,fstream::in);
fstream casemapoutput;
casemapoutput.open(outputfile,fstream::out);



char checkline[512];
char lowercasecopy[256];
while (casedinput.getline(checkline,255))
{
//Store a map of the lowercase to the original case address
for (unsigned int itr = 0; itr < strlen(checkline); ++itr)
{
char thischar = checkline[itr];
if (thischar >= 'A' && thischar <= 'Z') thischar += ('a'-'A');
lowercasecopy[itr]=thischar;
}
lowercasecopy[strlen(checkline)]='\0';
casemapoutput.write(lowercasecopy, strlen(lowercasecopy));
for (int itr4 = 0; itr4 < (255-strlen(checkline)); ++itr4) casemapoutput << " ";
casemapoutput.write(checkline, strlen(checkline));
casemapoutput << endl;
}
casedinput.close();
casemapoutput.close();
return;
}


void doremove(char* inputaddresses, char* inputremoves, char* outputfile)
{
fstream inaddresslist;
inaddresslist.open(inputaddresses,fstream::in);
fstream removeinput;
removeinput.open(inputremoves,fstream::in);
fstream finaloutput;
finaloutput.open(outputfile,fstream::out);



long addresscount = 0;
long removecount = 0;
char addressline[256];
list<string> addresslist; 
list<string>::iterator addressit;
while (inaddresslist.getline(addressline,255))
{
addresslist.push_back (addressline); 
++addresscount;
}
list<string> removeslist; 
list<string>::iterator removesit; 
while (removeinput.getline(addressline,255))
{
removeslist.push_back (addressline); 
++removecount;
}
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
}
else if (*removesit > *addressit)
{
// address is less than remove so there is no remove for this address, so output this address as good
finaloutput << *addressit << endl;
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
finaloutput << *addressit << endl;
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



inaddresslist.close();
removeinput.close();
finaloutput.close();
} 


void dorestorecase(char* uncasedinputfile, char* casemapinputfile, char* outputfile)
{
fstream finallower;
finallower.open(uncasedinputfile,fstream::in);
fstream casemap2;
casemap2.open(casemapinputfile,fstream::in);
fstream caseout;
caseout.open(outputfile,fstream::out);


// For each address in the finallist.txt, move forward in the case map .txt file
// until it matches, then pull out the 2nd half of the line and output that
// to have a correctly capitalized file.
char finalline[256];
char mapline[512];
char leftline[256];
char rightline[256];
while (finallower.getline(finalline,255))
{
bool hitone = false;
//caseout << finalline << endl; //Debug
while (hitone==false && (casemap2.getline(mapline,510)))
{
int maplen = strlen(mapline)-255;
for (int itr2=0;itr2<maplen;++itr2)
{
leftline[maplen]='\0';
rightline[maplen]='\0';
leftline[itr2]=mapline[itr2];
rightline[itr2]=mapline[255+itr2];
}
bool mismatch = false;
if (strlen(finalline)!=maplen) mismatch=true;
if (!mismatch)
{
for (int itr3=0;itr3<maplen;++itr3)
{
if ((leftline[itr3]!=finalline[itr3])&&(leftline[itr3]!=(finalline[itr3]+'a'-'A'))) mismatch=true;
} 
}
if (!mismatch)
{
caseout << rightline << endl;
hitone=true;
}
}
}



finallower.close();
casemap2.close();
caseout.close();
return;
} 
int main(int argc, char* argv[])
{ 
//clean up the list - turn , separated into new lines
//make sure its 7 bit ascii and not control characters



//Tool input/output requirements:
//dounique requires sorted data
//doremove requires lowercase data for both removes and address list.
//dostorecase and dorestorecase require that the output list of dostorecase be in the
// same sort order (on lowercase first column output)
// as the input list for dorestorecase (which is lowercase).


dosplitcommas("addresses.txt","_temp_addresses11.txt");
dotrimwhitespace("_temp_addresses11.txt","_temp_addresses12.txt");
dofilter1("_temp_addresses12.txt","_temp_addresses13.txt");
dofilter2("_temp_addresses13.txt","_temp_addresses14.txt");


dolowercase("_temp_addresses14.txt","_temp_addresses21.txt");
dostorecase("_temp_addresses14.txt","_temp_addresses31.txt");


dosort("_temp_addresses31.txt","_temp_addresses32.txt");



dosort("_temp_addresses21.txt","_temp_addresses22.txt");
dounique("_temp_addresses22.txt","_temp_addresses23.txt");



dosplitcommas("removes.txt","_temp_removes1.txt");
dotrimwhitespace("_temp_removes1.txt","_temp_removes2.txt");
dofilter1("_temp_removes2.txt","_temp_removes3.txt");
dofilter2("_temp_removes3.txt","_temp_removes4.txt");
dolowercase("_temp_removes4.txt","_temp_removes5.txt");
dosort("_temp_removes5.txt","_temp_removes6.txt");
dounique("_temp_removes6.txt","_temp_removes7.txt");



doremove("_temp_addresses23.txt","_temp_removes7.txt","_temp_finallist1.txt");



dorestorecase("_temp_finallist1.txt","_temp_addresses32.txt","_temp_finallist2.txt");
dosort("_temp_finallist2.txt","finallist.txt");



return 0; 
}