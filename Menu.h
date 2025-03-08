#include <iostream>
#include <string>



class Menu
{
	
	private:
		std::string A = "0";
		std::string B = "0";
		std::string C = "0";
		std::string D = "0";
		std::string E = "0";                                                // private variables
	
	int fail()
	{
		std::cout << "Please select a valid option." << std::endl;
		system("pause");
		system("CLS");                                                      // fail screen
		
	}
	
	
	public:
		
		Menu(std::string a, std::string b)
		{
			A = a; B = b;
		}
		
		
		Menu(std::string a, std::string b, std::string c)
		{
			A = a; B = b; C = c;
		}
		
		Menu(std::string a, std::string b, std::string c, std::string d)
		{
			A = a; B = b; C = c; D = d;
		}
		
		Menu(std::string a, std::string b, std::string c, std::string d, std::string e)            // constructors
		{
			A = a; B = b; C = c; D = d; E = e;
		}
		

	
	int call()                                          // function calls menu window 
	{
		
		while(true)
		
		{
		 
		int limit = 2;                               // control for valid input options
		std::string answer;
		int ans;
		
		
		std::cout << "1:" << A << std::endl;
		std::cout << "2:" << B << std::endl;        // displays base options
		
		if(C != "0") 
		{
			std::cout << "3:" << C << std::endl;        // display other options depending on constructor used
			limit++;
		}
		
		if(D != "0") 
		{
			std::cout << "4:" << D << std::endl;
			limit++;
		}
		
		if(E != "0") 
		{
			std::cout << "5:" << E << std::endl;
			limit++;
			
		}
		
		std::cin >> answer;
		system("CLS");
		
		if(answer != "1" && answer != "2" && answer != "3" && answer != "4" && answer != "5")   // input controller
		{
			fail();
			continue;
		}
		
		ans = std::stoi(answer);
		
		if(ans <= limit)
		{
			return ans;
		}
		
		else
		{
			fail();
			continue;
		}
		
		
		
		
		
    	}
		
		
		
		
		
		
		
    }
		
	
	
	
	
	
	
	
	
};