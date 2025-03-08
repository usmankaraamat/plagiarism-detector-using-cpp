#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Menu.h"  
#include <cstring>       
#include <algorithm>                                                       // all includes for program

using namespace std;

string file1, file2, file3, file4, file5;
float finalsamewords(0), finalsamephrases(0), totalwords(0), totalphrases(0);            // global variables to store updated values (I like to live dangerously)
string array_one[10000][5]; // #juggar array to store similar clauses
int same_count[5]; // keeps track of number same phrases in in each file 
int samew_count[5]; // keeps track of number same phrases in in each file
float similarity_count[5]; // keeps track of similarity index in each file
int tracker(0); // keeps track of file currently being processed



void remove_spaces(string& phrase)                                            // program to remove spaces from word
{
	string str;
	str = phrase;

	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	phrase = str;
}




void ask(string name, string& file)                                                    // file handeling tool to get and verify file name
{
	while(true)
	{
	cout << "Enter the name of " << name << "." << endl;
	cin >> file;
	system("CLS");
	
	ifstream check(file);
	if(check.fail())
	{
		std::cout << "Could not open file.";
		system("Pause");
		check.close();
		system("CLS");
		continue;
		
	}
	
	else
	{
		check.close();
		break;
	}
	
    }
}




void get_word(ifstream& file, string& word)                                                    //gets a single word from file
{
	char cursor;
	word = "";
	int control(0);
	
	cursor = file.get();
	if(cursor == ' ' || cursor == '\n')
	{
		while(cursor == ' ' || cursor == '\n') cursor = file.get();

	}

	while(true)
	{
		if(cursor == '\n' || cursor == ' ' || cursor == ',' || cursor == '!' || cursor == '?' || cursor == ':' || cursor == '.' || cursor == ';') break;
		if(file.eof()) break;
		word += cursor;
		cursor = file.get();
    }
}



void word_check(ifstream& file, int& words)                              // function to check number of words in a file
{
	words = 0;
	string cursor;
	
	while(!file.eof())
	{
		get_word(file, cursor);
		if(!file.eof())	words ++;
	}


	 file.clear();
     file.seekg(0);
}



int seek_word(ifstream& file, string word)                                                                  // checks if a word is present in file
{
	string cursor;
	
	while(true)
	{
		
		
		get_word(file, cursor);
		
			if (file.eof())
		{
	
			file.clear();
            file.seekg(0);
			break;
		} 
		
		
		
		if (cursor == word) 
		{
			file.clear();
            file.seekg(0);
			return (1);
		}
		
	
		

		
	}

	return (0);
}

void get_phrase(ifstream& file, string& sentence)                                         // gets a phrase from file
{
	char cursor;
	sentence = "";

	cursor = file.get();
	if(cursor == ' ' || cursor == '\n')
	{
		while(cursor == ' ' || cursor == '\n') cursor = file.get();

	}
	
    sentence += cursor;
	
	while(true)
	{
		cursor = file.get();
		if (cursor == '\n' || cursor == ' ') 
		{
			sentence += " "; 
			continue;
		}
		if(file.eof()) break;
		if (cursor == '.' || cursor == '!' || cursor == ';' || cursor == ':' || cursor == '?'|| cursor == ',') break;
		sentence += cursor;
    }
}


void get_phrase_n(ifstream& file, string& sentence)                                         // gets a phrase from file without blank spaces
{
	char cursor;
	sentence = "";

	cursor = file.get();
	if(cursor == ' ' || cursor == '\n')
	{
		while(cursor == ' ' || cursor == '\n') cursor = file.get();

	}
	
    sentence += cursor;
	
	while(true)
	{
		cursor = file.get();
		if (cursor == '\n' || cursor == ' ') 
		{
			continue;
		}
		if(file.eof()) break;
		if (cursor == '.' || cursor == '!' || cursor == ';' || cursor == ':' || cursor == '?'|| cursor == ',') break;
		sentence += cursor;
    }
}





void phrase_check(ifstream& file, int& phrases)                              // function to check number of phrases in a file
{
	phrases = 0;
	string cursor;
	
	while(!file.eof())
	{
		get_phrase(file, cursor);
		if(!file.eof())	phrases ++;
	}


	 file.clear();
     file.seekg(0);
}


int seek_phrase(ifstream& file, string sentence)                                        // checks if a sentence is present in file
{
	string cursor;
	string str = sentence;
    remove_spaces(str);                   // removes blankspaces from phrase for better checking


	while(true)
	{
		get_phrase_n(file, cursor);
		if (file.eof())
		{
	
			file.clear();
            file.seekg(0);
          
			return (0);
		} 
	
	
		if (cursor == str) 
		{
	
			file.clear();
            file.seekg(0);
        
			return (1);
		}
		
	
		

		
	}
}



 
void check_similarity(string a, string b)                                                     //checks similarity and generates reports
{
	

	float samewords(0), samephrases(0);
	
	int words1, words2, sen1, phrases1, phrases2;
	string cursor1;
	
	ifstream test(a);
	ifstream reference(b);                                                                        // opens files
	

	
	word_check(test, words1);
	word_check(reference, words2);                                                                     // finds size of file
	totalwords += words2;

	phrase_check(test, phrases1);
	phrase_check(reference, phrases2);  
	totalphrases += phrases2;

	
	const int size(words1);
	std::string swords[size];
	std::string sphrases[size];                                                                    // array to store similar words and sentences
	

    int count = 0;
    while(true)
    {
	get_word(test, cursor1);                                                                       // structure that finds and stores common words
	
    if (seek_word(reference, cursor1)) 
	{
	swords[count] = cursor1;
	count++; 	
	samewords++;
    }
     
    if(test.eof())
    {
    	test.clear();
    	test.seekg(0);
    	break;
	}
     
    }
    
    samew_count[tracker] = samewords; // updates samewords value
    
    sen1 = 0;
    samephrases = 0;
    int count2 = 0;
    
    
    while(true)
    {
    
	get_phrase(test, cursor1);	
    	
     if(test.eof())
    {
    	test.clear();                                                                             // structure that finds and stores similar phrases
    	test.seekg(0);
    	break;
	}	
    	
    sen1++;	
	
	
    if (seek_phrase(reference, cursor1)) 
	{
	sphrases[count2] = cursor1;
	array_one[count2][tracker] = cursor1;   // stores phrase in global array
	count2++; 	
	samephrases++;
    }
	
	
    }
    
	
    
    same_count[tracker] = samephrases; // updates samecount value
    
    
    
    cout << "Number of same words: " << setw(5) << "              Number of same phrases: " << endl;
    cout << "**************************************************************" << std::endl;
    cout << "      " << samewords << setw(45) << samephrases << endl << endl;

	finalsamephrases += samephrases;
	finalsamewords += samewords;                           // adds same phrases to global same phrase count

    
 
    cout << "Number of words in " << a << ": " << words1 << endl;
    cout << "Number of words in " << b << ": " << words2 << endl << endl;                                                 // output formatter

    
   float index = (((samewords)/(words1))*100);
   cout << "Total phrases in "<< a << ": " << (sen1) << endl;
   cout << "Similarity index: " << index << "%" << endl << endl;
   similarity_count[tracker] = index;
   
   
   
   
    int choice;
    Menu second("get list of same words and phrases", "continue to next report");                                               // choice switch for detatiled report
    choice = second.call();
    
    
    if(choice == 1)
	{
		cout << "Same words:" << endl;
		
		while (count != -1)
		{
			cout << setw(3) << swords[count] << endl;
			count--;
		}
		
		
		
		cout << endl << "Same phrases:" << endl << endl;;
		
		while (count2 != -1)
		{
			cout << setw(3) << sphrases[count2] << endl;
			count2--;
		}
		
		
		
	} 
	
	test.close();
	reference.close();                             // closes files

    tracker++;  // updates tracker value
	cout << endl << endl;;
    system("pause");
    system("CLS");
}



void add_entry()                                // gets info to open each file
{
	ask("first file", file1);  
	ask("second file", file2);  
	ask("third file", file3);  
	ask("fourth file", file4);  
	ask("fiifth file", file5);  	
}


void final_report(string& file)           // generates final report based on global variables
{
	ifstream test(file);
	int ttl(0);

	word_check(test, ttl);
	totalwords += ttl;

	ttl = 0;
	phrase_check(test, ttl);
	totalphrases += ttl;

	int index;

	index = ((finalsamewords/totalwords)*100);

	cout << setw(7) << "Total number of similar words found = " << finalsamewords << endl << endl;
	cout << setw(17) <<  samew_count[0] <<"  from file 1" << endl;
	cout << setw(17) <<  samew_count[1] <<"  from file 2" << endl;
	cout << setw(17) <<  samew_count[2] << "  from file 3" << endl;
	cout << setw(17) <<  samew_count[3] <<"  from file 4" << endl;
	cout << setw(17) <<  samew_count[4] <<"  from file 5" << endl << endl << endl << endl;
	
	
	
	cout << setw(14) << "Similarity index = " << index << "%" << endl << endl;
	cout << setw(17) << "Source 1 = " << similarity_count[0] << "%" << endl;
	cout << setw(17) << "Source 2 = " <<similarity_count[1] << "%" << endl;
	cout << setw(17) << "Source 3 = " <<similarity_count[2] <<  "%" <<endl;
	cout << setw(17) << "Source 4 = " <<similarity_count[3] << "%" << endl;
	cout << setw(17) << "Source 5 = " << similarity_count[4] << "%" <<endl << endl << endl << endl;
	

	cout << "Total number of similar phrases = " << finalsamephrases << endl << endl;
	cout << "       " << "Similar phrases / clauses" << "                     Source file" << endl;
	cout << "**********************************************************************" << endl;
	

	int count = 0;
	if( same_count[0] != 0)
	{
		do
		{
			cout << setw(60) << left <<array_one[count][0];                       // prints similar phrases from first file
			cout <<"1" << endl;
		} while (count != (same_count[0] + 1));
		 

	}


	count = 0;
	if( same_count[200] != 0)
	{
		do
		{
			cout << setw(60) << left << array_one[count][1];                       // prints similar phrases from second file
			cout  << "2" << endl;
			count ++;
		} while (count != (same_count[1]));
		 

	}
	

	
	count = 0;
	if( same_count[2] != 0)
	{
		do
		{
			cout << setw(60) << left << array_one[count][2];                       // prints similar phrases from third file
			cout   << "3" << endl;
			count ++;

		} while (count != (same_count[2]));
		 

	}
	
	


	count = 0;
	if( same_count[3] != 0)
	{
		do
		{
			cout << setw(60) << left << array_one[count][3];                       // prints similar phrases from fourth file
			cout << "4" << endl;
			count ++;

		} while (count != (same_count[3]));
		 

	}




	count = 0;
	if( same_count[4] != 0)
	{
		do
		{
			cout << setw(60) << left << array_one[count][4];                       // prints similar phrases from fifth file
			cout <<  "5" << endl;
			count ++;

		} while (count != (same_count[4]));

		 

	}

	cout << endl << endl;



	finalsamephrases = 0; finalsamewords = 0; totalwords = 0; totalphrases = 0; tracker = 0; // resets important global variables
	


	system("pause");
	system("CLS");

}




void exp_rep()                                    // calls similarity check for each file
{
	string inputfile;
	ask("input file" , inputfile);
		
	check_similarity(inputfile, file1);
	check_similarity(inputfile, file2);
	check_similarity(inputfile, file3);
	check_similarity(inputfile, file4);
	check_similarity(inputfile, file5);               
	final_report(inputfile); 
	
}




int main()
{



	while(true)
	{
	
	int choice;

	Menu main("Add document library", "Check document", "Exit");                                       // calls menu object

	choice = main.call();
    switch(choice)
    { 
    	
	case 1: add_entry(); break;
	case 2: exp_rep(); break;                                                                         // main menu switch
	case 3: return(0);
    }
    
    }

return 0;

};

