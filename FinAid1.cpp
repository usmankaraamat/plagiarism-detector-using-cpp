#include <iostream>	// header file for containing functions for input and output operations
#include <fstream>	//header file for containing functions for input and output operations in files
#include <string>	//header file for containing functions for storing text
#include <iomanip>	//header file for containing functions for parametric manipulators
#include "Menu.h"  	//header file for class
#include <algorithm> //header file for containing functions operate on ranges of elements                // all includes for program

using namespace std;	//declarative region for providing scope to identifiers
						//below, declaration of global variables:
string file1, file2, file3, file4, file5;	//declaring variables of string type (variables for file names)
float finalsamewords(0), finalsamephrases(0), totalwords(0), totalphrases(0);            // global variables to store updated values //declaring variables of float type
string array_one[10000][5]; //array to store similar clauses. 2-D array because to store similar clauses separately for each file
int same_count[5]; // keeps track of number same phrases in each file 
int samew_count[5]; // keeps track of number same words in in each file
float similarity_count[5]; // keeps track of similarity index in each file
int tracker(0); // keeps track of file currently being processed. It is simply a tracker



void remove_spaces(string& phrase)                                            // function code to remove spaces from word
{
	string str;
	str = phrase;

	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	phrase = str;
}




void ask(string name, string& file)                                                    // file handeling tool to get and verify file name
{
	while(true)	//while loop for checking file
	{
	cout << "Enter the name of " << name << "." << endl;
	getline(cin, file);	//file name is entered
	system("CLS");	//function to clear the screen
	
	ifstream check(file);
	if(check.fail())	//if condition for checking if the file opening is successful
	{
		std::cout << "Could not open file.";	//error message output
		system("Pause");	//pause function
		check.close();	//close the file
		system("CLS");	//clear screen fucntion
		continue;
		
	}
	
	else	//if file is successfully opened
	{
		check.close();	
		break;
	}
	
    }
}




void get_word(ifstream& file, string& word)                                           //function that gets a single word from file
{
	char cursor;	// declaring the variable "cursor" of character type
	word = "";
	int control(0);
	
	cursor = file.get();	//take a word
	if(cursor == ' ' || cursor == '\n')	// if condition for cursor
	{
		while(cursor == ' ' || cursor == '\n') cursor = file.get(); 		//it means that a space or an enter line is not counted as a word and are ignored

	}

	while(true)	// while loop for cursor getting single word
	{
		if(cursor == '\n' || cursor == ' ' || cursor == ',' || cursor == '!' || cursor == '?' || cursor == ':' || cursor == '.' || cursor == ';') break;	//checking for punctuation marks, which are ignored since they are not words
		if(file.eof()) break;	//if end of the file reached, then  break the loop
		word += cursor;	//word variable is given the word contained in cursor variable
		cursor = file.get();	//take the next word
    }
}



void word_check(ifstream& file, int& words)                              // function to check number of words in a file
{
	words = 0;
	string cursor;
	
	while(!file.eof())	// while loop for checking total number of words in a file
	{
		get_word(file, cursor);
		if(!file.eof())	words ++;	//total words are increased by one
	}


	 file.clear();	//clear the file
     file.seekg(0);	//move back to the start of the file
}



int seek_word(ifstream& file, string word)                                     // function that checks if a word is present in file
{
	string cursor;	//a string variable 'cursor' is declared
	
	while(true)	// while loop for checking words
	{
		
		
		get_word(file, cursor);	//get the word stored in the 'file' object
		
			if (file.eof())	//if end of the file is reached, it means that file has been completely read, or it had no words
		{
	
			file.clear();	//clear the 'file' obejct which will now have no data
            file.seekg(0);	//moves back to the arbitrary position
			break;
		} 
		
		
		
		if (cursor == word) 	//checking if the fucntions match
		{
			file.clear();	//clear the 'file' obejct which will now have no data
            file.seekg(0);	//moves back to the arbitrary position
			return (1);	//return value of 1 so that we know that a matching word has been found
		}
		
		
		
	}

	return (0);	//return value of 0 to the function
}

void get_phrase(ifstream& file, string& sentence)                                         // gets a phrase from file
{
	char cursor;	//declaring 'cursor' character
	sentence = "";

	cursor = file.get();	//getting a word and assigning it to cursor
	if(cursor == ' ' || cursor == '\n')
	{
		while(cursor == ' ' || cursor == '\n') cursor = file.get();	//again, to ignore space or 'enter' line. Moreover, if many spaces or lines are there, then this loop will ensure that the next word is reached and then taken into consideration

	}
	
    sentence += cursor;	//storing the word stored in cursor into the 'sentence' variable. This is taken as the beginning of the phrase/clause
	
	while(true)	//this loop will run due to the condition being true always
	{
		cursor = file.get();	//take the next word
		if (cursor == '\n' || cursor == ' ') 
		{
			sentence += " "; //means that the space after the first word in the phrase is added to the phrase, since there is always a space between two words
			continue;	//loop is run again
		}
		if(file.eof()) break;	//when the end of the file has been reached, break the loop
		if (cursor == '.' || cursor == '!' || cursor == ';' || cursor == ':' || cursor == '?'|| cursor == ',') break;
		sentence += cursor;	//sentence variable stores in itself the value of cursor
    }
}


void get_phrase_n(ifstream& file, string& sentence)                                         // gets a phrase from file without blank spaces
{
	char cursor;	//declaring 'cursor' character
	sentence = "";

	cursor = file.get();	//getting a word and assigning it to cursor
	if(cursor == ' ' || cursor == '\n')
	{
		while(cursor == ' ' || cursor == '\n') cursor = file.get();	//again, to ignore space or 'enter' line. Moreover, if many spaces or lines are there, then this loop will ensure that the next word is reached and then taken into consideration

	}
	
    sentence += cursor;	//storing the word stored in cursor into the 'sentence' variable. This is taken as the beginning of the phrase/clause
	
	while(true)	//this loop will run due to the condition being true always
	{
		cursor = file.get();	//take the next word
		if (cursor == '\n' || cursor == ' ') 
		{
			continue;	//loop is run again (the spaces and 'enter' line is ignored)
		}
		if(file.eof()) break;	//when the end of the file has been reached, break the loop
		if (cursor == '.' || cursor == '!' || cursor == ';' || cursor == ':' || cursor == '?'|| cursor == ',') break;
		sentence += cursor;//sentence variable further stores in itself the value of cursor
    }
}





void phrase_check(ifstream& file, int& phrases)                              // function to check the number of phrases in a file
{
	phrases = 0;
	string cursor;	//cursor having string data type
	
	while(!file.eof())	//loop that runs until the whole of the file has been checked
	{
		get_phrase(file, cursor);
		if(!file.eof())	phrases ++;	//increase the phrase number by 1 each time
	}


	 file.clear();	//Accessing toward clear
     file.seekg(0);	//Accessing toward seekg
}


int seek_phrase(ifstream& file, string sentence)                                   // checks if a sentence is present in file
{
	string cursor;	//cursor having string data type
	string str = sentence;
    remove_spaces(str);                   // removes blankspaces from phrase for better checking


	while(true)	//when while loop gets value true
	{
		get_phrase_n(file, cursor);
		if (file.eof())	//if end of file reached
		{
	
			file.clear();	//clear the file object
            file.seekg(0);	//return to arbitrary starting position
          
			return (0);	//return value of 0
		} 
	
	
		if (cursor == str) 
		{
	
			file.clear();	// clears flag state end of file 
            file.seekg(0);	//return to arbitrary starting position
        
			return (1);	//return value of 1
		}
		
	
		

		
	}						// end of while loop
}								//end of user defined function seek_phrase



 
void check_similarity(string a, string b)                           //defining the function that checks similarity and generates reports
{
	

	float samewords(0), samephrases(0);	//float variables with appropriate names
	
	int words1, words2, sen1, phrases1, phrases2;	//int variables with appropriate names
	string cursor1;	//string variable 'cursor1'
	
	ifstream test(a);								// initializing input stream object to string a ( test file ) 
	ifstream reference(b);                          // initializing input stream object to string b ( reference file )
	

	
	word_check(test, words1);						// calling user defined parametrized function which finds word count of file
	word_check(reference, words2);                   // finds size of file
	totalwords += words2;						// adding words2 ( word count of reference file) to global varaible 'totalwords'

	phrase_check(test, phrases1);			// call function ( counts number of phrases in test file )
	phrase_check(reference, phrases2);  			// call function ( counts number of phrases in reference file )
	totalphrases += phrases2;						// adding phrase2 ( phrase count of reference file ) to global varaible total phrases

	
	const int size(words1);						// initailizing constant integer varaible to word count of test file.
	std::string swords[size];					// initializing string array same words to size of word count of test file.
	std::string sphrases[size];                 // initailizing array to store similar words and sentences
	

    int count = 0;										// initialising counter to 0
    while(true)
    {
	get_word(test, cursor1);                              // calling function that finds and stores common words
	
    if (seek_word(reference, cursor1)) 						// calling function to return 1 if similar word is found
	{
	swords[count] = cursor1;							// same word from array is stored to cursor
	count++; 									// increment 1 for counter
	samewords++;							// increment 1 for same word 
    }
     
    if(test.eof())				// checking for end of file flag 
    {
    	test.clear();			// clearing end of file flag
    	test.seekg(0);					// setting pointer to start of file
    	break;						// breaking from infinite loop	
	}
     
    }
    
    samew_count[tracker] = samewords; 	// updates samewords value
    
    sen1 = 0;				// setting sen1 to zero
    samephrases = 0;			// setting local varaible to zero
    int count2 = 0;				// initialing counter for reference file 2
    
    
    while(true)
    {
    
	get_phrase(test, cursor1);		// calling function ( to extract a phrase from test file )
    	
     if(test.eof())					// checking for end of flie flag
    {
    	test.clear();                                   // sets end of file flag to 0
    	test.seekg(0);
    	break;
	}	
    	
    sen1++;	
	
	
    if (seek_phrase(reference, cursor1)) 	// if a phrase is found to be similar, the return value will be 1. This will activate the if-statement
	{
	sphrases[count2] = cursor1;				// adds similar phrase to array 
	array_one[count2][tracker] = cursor1;   // stores similar phrase in global array
	count2++; 									// increment counter for reference file 2 loop 
	samephrases++;									// increment counter same phrases found
    }
	
	
    }
    
	
    
    same_count[tracker] = samephrases; // updates samecount value
    
    
    
    cout << "Number of same words: " << setw(5) << "              Number of same phrases: " << endl;	//setting of headings on the console output
    cout << "*********************************************************************" << std::endl;
    cout << "      " << samewords << setw(45) << samephrases << endl << endl;

	finalsamephrases += samephrases;					// adds amount of same words from file to global varaible final same words
	finalsamewords += samewords;                           // adds same phrases to global same phrase count

    
 
    cout << "Number of words in " << a << ": " << words1 << endl;								// prints total amount of words in test file
    cout << "Number of words in " << b << ": " << words2 << endl << endl;                  // prints total amount of words in reference file           // output formatter

    
   float index = (((samewords)/(words1 + words2))*100);										// initailizing and assigning to variable representing similarity index 
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
			cout << setw(3) << swords[count] << endl;	//a complete list of similar words is output from the array
			count--;
		}
		
		
		
		cout << endl << "Same phrases:" << endl << endl;;	//a complete list of similar phrases is output from the array
		
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



void counter(int count, char& out)           // returns alphabet corresponding to number
{
    count += 96;  // returns ascii code 
	if(count < 123 ) out = count;
	else out = '.';
}





void final_report(string& file)           // generates final report based on global variables
{
	ifstream test(file);
	int ttl(0); // makeshift variable to pass through word check and phrase check

	word_check(test, ttl);
	totalwords += ttl;

	ttl = 0;
	phrase_check(test, ttl);
	totalphrases += ttl;

	int index;

	index = ((finalsamewords/totalwords)*100);
	
	
	ofstream report("Report.txt");
	
	report << setw(7) << "   Total number of similar words found = " << finalsamewords << endl << endl; // for file
	report << setw(17) <<  samew_count[0] <<"  from file 1" << endl;
	report << setw(17) <<  samew_count[1] <<"  from file 2" << endl;
	report << setw(17) <<  samew_count[2] << "  from file 3" << endl;
	report << setw(17) <<  samew_count[3] <<"  from file 4" << endl;
	report << setw(17) <<  samew_count[4] <<"  from file 5" << endl << endl << endl << endl;
	
	

	cout << setw(7) << "   Total number of similar words found = " << finalsamewords << endl << endl; // for console
	cout << setw(17) <<  samew_count[0] <<"  from file 1" << endl; 
	cout << setw(17) <<  samew_count[1] <<"  from file 2" << endl;
	cout << setw(17) <<  samew_count[2] << "  from file 3" << endl;
	cout << setw(17) <<  samew_count[3] <<"  from file 4" << endl;
	cout << setw(17) <<  samew_count[4] <<"  from file 5" << endl << endl << endl << endl;
	
	
	
	cout << setw(14) << "            Similarity index = " << index << "%" << endl << endl;   // for console
	cout << setw(25) << "Source 1 = " << similarity_count[0] << "%" << endl;
	cout << setw(25) << "Source 2 = " <<similarity_count[1] << "%" << endl;
	cout << setw(25) << "Source 3 = " <<similarity_count[2] <<  "%" <<endl;
	cout << setw(25) << "Source 4 = " <<similarity_count[3] << "%" << endl;
	cout << setw(25) << "Source 5 = " << similarity_count[4] << "%" <<endl << endl << endl << endl;
	
	
	report << setw(14) << "            Similarity index = " << index << "%" << endl << endl;  //for file
	report << setw(25) << "Source 1 = " << similarity_count[0] << "%" << endl;
	report << setw(25) << "Source 2 = " <<similarity_count[1] << "%" << endl;
	report << setw(25) << "Source 3 = " <<similarity_count[2] <<  "%" <<endl;
	report << setw(25) << "Source 4 = " <<similarity_count[3] << "%" << endl;
	report << setw(25) << "Source 5 = " << similarity_count[4] << "%" <<endl << endl << endl << endl;
	

	cout << "Total number of similar phrases = " << finalsamephrases << endl;  // for console
	cout <<"Similar Phrases/Clauses" << " \t\t\t\t Source File" << endl;
	cout <<",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << endl;
	
	
	report << "Total number of similar phrases = " << finalsamephrases << endl;  // for file
	report <<"Similar Phrases/Clauses" << " \t\t\t\t Source File" << endl;
	report <<",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,," << endl;

	char output; // for a,b,c, etc
   int char_count = 1; // for keeping track of character prefixes


	int count = 0;
	if( same_count[0] != 0)
	{
		do
		{
			counter(char_count, output);
			cout << "    " << output << ")" << setw(55) << left <<array_one[count][0];                       // prints similar phrases from first file
			cout <<"1" << endl;
			
			report << "    " << output << ")" << setw(55) << left <<array_one[count][0];                       // prints similar phrases from first file to report file
			report <<"1" << endl;
			
			count ++;
			char_count++;
		} while (count != (same_count[0] + 1));
		 

	}


	count = 0;
	if( same_count[1] != 0)
	{
		do
		{
			counter(char_count, output);
			cout << "    " << output  << ")" << setw(55) << left << array_one[count][1];                       // prints similar phrases from second file
			cout  << "2" << endl;
			
			
			report << "    " << output  << ")" << setw(55) << left << array_one[count][1];                       // prints similar phrases from second file to report file
			report  << "2" << endl;
			
			count ++;
			char_count++;
		} while (count != (same_count[1]));
		 

	}
	

	
	count = 0;
	if( same_count[2] != 0)
	{
		do
		{
			counter(char_count, output);
			
			
			cout << "    " << output << ")" << setw(55) << left <<array_one[count][2];                       // prints similar phrases from third file
			cout   << "3" << endl;
			
			report << "    " << output << ")" << setw(55) << left <<array_one[count][2];                       // prints similar phrases from third file to report file
			report   << "3" << endl;
			
			count ++;
			char_count++;

		} while (count != (same_count[2]));
		 

	}
	
	


	count = 0;
	if( same_count[3] != 0)
	{
		do
		{
			counter(char_count, output);
			
			
			cout << "    " << output << ")" << setw(55) << left << array_one[count][3];                       // prints similar phrases from fourth file
			cout << "4" << endl;
			
			report << "    " << output << ")" << setw(55) << left << array_one[count][3];                       // prints similar phrases from fourth file to report file
			report << "4" << endl;
			
			
			count ++;
			char_count++;
		} while (count != (same_count[3]));
		 

	}




	count = 0;
	if( same_count[4] != 0)
	{
		do
		{
			counter(char_count, output);
			
			
			cout << "    " << output << ")" << setw(55) << left << array_one[count][4];                       // prints similar phrases from fifth file
			cout <<  "5" << endl;
			
			report << "    " << output << ")" << setw(55) << left << array_one[count][4];                       // prints similar phrases from fifth file to report file
			report <<  "5" << endl;
			
			
			count ++;
			char_count++;

		} while (count != (same_count[4]));

		 

	}

	cout << endl << endl;
	

	
	
	
	
	
	
	
	
	
	
	
	



	finalsamephrases = 0; finalsamewords = 0; totalwords = 0; totalphrases = 0; tracker = 0; // resets important global variables
	


	system("pause");	//pause function
	system("CLS");		//clear screeen function
	exit(1);
}




void exp_rep()                                    // calls similarity check for each file. Below, automatic order. first the 'ask' function is called, then the 'check_similarity' function, and so on...
{
	string inputfile;
	ask("input file" , inputfile);				//call the 'ask' function that has been created above
												//below, the function 'check_similarity' is called each time for the 5 different files
	check_similarity(inputfile, file1);
	check_similarity(inputfile, file2);
	check_similarity(inputfile, file3);
	check_similarity(inputfile, file4);
	check_similarity(inputfile, file5);               
	final_report(inputfile); 					//the function 'final_report' is called
	
}




int main()	//the main function starts here
{



	while(true)	//while loop that will always run since its condition is always true. Even if out of range option selected, it will ensure that the correct option is selected
	{
	
	int choice;

	Menu main("Add document library", "Check document", "Exit");                                       // calls menu object

	choice = main.call();							//calling the menu, which we initialized in last line
    switch(choice)									//switch statement associated with the variable 'choice'
    { 
    												//different cases discussed when 1, 2, or 3 entered on the console
	case 1: add_entry(); break;
	case 2: exp_rep(); break;                                                                   // main menu switch
	case 3: return(0);								//exit the program
    }
    
    }

return 0;

};

