/* --------------------------------------------------------------------------------------
   Programer's Name: Farah Afifah binti Zulkefli
   ID: 154725
   Program's Name: Mystic Grill Food Ordering System
   Function of the program: This program has 2 users manager and customer
   						 	1. Manager should be able to edit menu and accept order
   						 	2. Customer should be able to take order
   -------------------------------------------------------------------------------------- */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Function prototype
void managerOrCustomer(char, char);
void menuList(string[], double[], int);
void selectMenu(string[], string, int, double[], double);
void editMenu(float, int);
void acceptorder();

// main function
int main ()
{
	// Declaration of variables
	int lists;
	char managers, customers;
	
	// Function call to decide manager or customer
	managerOrCustomer(managers, customers);
	
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function manager or customer
void managerOrCustomer(char manager, char customer)
{
	// Variable declarations
	int i = 9, lists, orders, codes[i], quantities[i], option;
	double prices[i], totalAll;
	string menu[i], names;
	char managerOrCustomer;
	float price;

	//*******************************************************************************************
	// User input the managerOrCustomer
	//********************************************************************************************
	cout << "----------------------MYSTIC FALL ORDERING SYSTEM---------------------" << endl;
	cout << "  " << endl;
	cout << "Type 'M' (MANAGER) if you are the Restaurant Manager(s)\n";
	cout << "Type 'C' (CUSTOMER) if you are the Customer(s).\n";
	cin >> managerOrCustomer;
	
	//********************************************************************************************
	// Decided whether customer or manager
	//********************************************************************************************
	while(managerOrCustomer)
	{
	if(managerOrCustomer == 'c' || managerOrCustomer == 'C')
		{
			cout << "You are the customer. You can order the food now.\n";
			menuList(menu, prices, i);		// Function call to show the menu lists
			selectMenu(menu, names, i, prices, totalAll);		// Function call to let user take order
			break;
		}
	else if(managerOrCustomer == 'm' || managerOrCustomer == 'M')
		{
			cout << "You are the manager. What do you want to do?\n";
			
			menuList(menu, prices, i);		// Function call to show the menu lists
			
			cout << "Type [1] to Accept Order and [2] to Edit Menu Lists\n";
			cin >> option;
				
			while(option)
			{
				if(option == 1)
				{
					acceptorder();		// Function call to let manager accept order
					break;    
				}
				else if(option == 2)
				{
					editMenu(price, lists);		// Function call to let the manager edit the menus in the same file
					break;
				}
				else
				{
					cout << "INVALID code, try again!\n";
				}
				
				cin >> option;
			}
			
			break;
		}
	else
		{
			cout << "INVALID code, try again!\n";
		}
		
		cin >> managerOrCustomer;	 
	} 
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Funtion menu List
void menuList(string menu[], double price[], int list)
{
	//********************************************************************************************
	// Let the inputfile open to edit the menu
	//********************************************************************************************
	cout << "\n---------------------Welcome to Mystic Grill Restaurant-------------------" << endl;
	cout << " " << endl;
	
	// To open the inout file
	ifstream inFile;
	
	// Open the file
	inFile.open("Menu.txt");
	
	// Declaration
	int count = 0;
	
	// Read the contents of the file into the array
	while(inFile)
	{
		getline(inFile, menu[count], '\t');
		inFile >> price[count];
		inFile.ignore();
		count++;
	}
	
	cout << showpoint << fixed << setprecision(2);

	for(int count = 0; count < 9; count++)
	{
		cout << "[" << (count + 1) << "]" << menu[count] << "\t\t\tRM" << price[count] << endl;
	}
	cout << endl;
	
	// Close the file
	inFile.close();
}


void editMenu(float price, int list)
{
	// Declare the variables
	ifstream inFile;
	ofstream outFile;
	string food;
	
	// Prompt the manager to edit list of menus
	cout << "\n\nHow many lists of food you want to update?";
	cin >> list;	
	
	// Open the outFile
	outFile.open("Menu.txt");
	
	for(int count = 0; count < list; count++)
	{	
		cin.ignore();
		// Let the manager key in the name of the food
		cout << "Update the food or beverages " << (count + 1) << ": ";
		getline(cin, food);
		
		// Let the user key in the price
		cout << "Update the price " << (count + 1) << ": RM";
		cin >> price;
		
		outFile << showpoint << fixed << setprecision(2);
		outFile << food << "\t" << price << endl;
		
	}
	
	// Close the output file
	outFile.close();
	
	// When done updating
	cout << "\nDONE updating the menu, you can now open the Menu.txt file";

}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function selectMenu
void selectMenu(string menuList[], string name, int order, double price[], double subtotal1)
{
	// Variables declarations
	char manager, customer, methods;
	int quantity[order], phone, estimateDelivery;
	const double tax = 0.06, delivery = 3; 
	double total[order], subtotal, amount;
	ofstream outFile;
	string postcode, method;
	
	//*******************************************************
	// Let the user key in their details
	//*******************************************************
	cin.ignore();
	cout << "\nPlease fill in the details below \n";
	cout << "Name: ";
	getline(cin, name);
	cout << "Phone No. : ";
	cin >> phone;
	cout << "Postcode: ";
	cin >> postcode;
	cout << "There 3 payment methods [A]COD, [B]Debit Card, [C]Online Banking \nSelect :";
	cin >> methods;
		
	//*******************************************************
	// To choose the payment methods
	//*******************************************************
	while(methods)
	{
		if(methods == 'A' || methods == 'a')
		{
			method = "Cash On Delivery";
			break;
		}
		else if(methods == 'B' || methods == 'b')
		{
			method = "Debit Card";
			break;
		}
		else if(methods == 'C' || methods == 'c')
		{
			method = "Online Banking";
			break;
		}
		else
		{
			cout << "Invalid code. TRY AGAIN.\n";
		}
		cin >> methods;
	}
		
	//*******************************************************	
	// Let the user decide the quantity of each menu
	//*******************************************************
	cout << "\nType the quantity of each menus you want to order\n";
	cout << "Please put 0 if you don't want to order certain menus\n";
	cout << "DO NOT PUT ANY CHARACTER!\n\n";
	
	for(int count = 0; count < order; count++)
	{
		cout << "Menu [" << (count + 1) << "]: ";
		cin >> quantity[count];
		
		while(quantity[count])
		{
			if(quantity[count] < 0)
			{
				cout << "INVALID! Please enter quantity more than -1: ";
			}
			else if(quantity[count] >= 0)
			{
				break; 
			}
			else
			{
				cout << "INVALID! please enter the numbers: ";
			}
			cin >> quantity[count];
		}
	}
		
	//*******************************************************
	// Display the list of the menus that user has ordered
	//*******************************************************
	cout << "\nList foods and beverages you have ordered\n";
	for(int count = 0; count < order; count++)
	{
		while((count + 1))
		{
			cout << menuList[count];
			total[count] = price[count] * quantity[count];				
			cout << ": " << quantity[count] << "\tRM" << total[count];
			subtotal += total[count];
			break;
		}
		cout << endl;
	}
	
	//*******************************************************
	// Calculation of the subtotal
	//*******************************************************
	subtotal1 = subtotal + (subtotal * tax) + delivery;
	
	
	//*******************************************************
	// To determine the estimated delivery time in minutes
	//*******************************************************
	if(subtotal1 < 20)
	{
		estimateDelivery = 10;
	}
	else if(subtotal1 >=20 && subtotal1 < 50)
	{
		estimateDelivery = 25;
	}
	else if(subtotal1 >=50 && subtotal1 < 100)
	{
		estimateDelivery = 40;
	}
	else
	{
		estimateDelivery = 50;
	}
	
	//*********************************************************
	// To print out the receipt 
	//*********************************************************
	cout << showpoint << fixed << setprecision(2);
	cout << "\n===============================THE RECEIPT===========================\n";
	cout << "\nTotal: RM" << subtotal << endl; 
	cout << "GST tax 6%\n";
	cout << "Delivery charge: RM" << delivery << endl;
	cout << "\n-----------------------------------------------------------------------\n";
	cout << "\nSubtotal: RM" << subtotal1 << endl;
	cout << "CASH: RM";
	cin >> amount;
	cout << "CHANGE: RM" << amount - subtotal1 << endl;
	cout << "\n=============================ORDER DETAILS==================================\n";
	cout << "\nName: " << name << endl;
	cout << "Phone No.: +60" << phone << endl;
	cout << "Postcode: " << postcode << endl;
	cout << "Subtotal: RM" << subtotal1 << endl;
	cout << "Payment Method: " << method << endl;
	cout << "Estimated delivery time: " << estimateDelivery << " minutes" << endl;
	cout << "\n*************************THANK YOU FOR ORDERING OUR FOODS********************\n";
	cout << "\n\t\t    Powered by MysticFalls \t\t\t\n";
	cout << "\t\t  For more visit mysticfalls.restaurant.my\t\t\t\n";
		
	
	
	// Open the outputfile
	outFile.open("CustomerOrder.txt");
	
	// Display the customer details in outputFile
	outFile << name << endl;
	outFile << method << endl;
	outFile << phone << endl;
	outFile << postcode << endl;
	outFile << subtotal1 << endl;
	
	// Close the outFile
	outFile.close();
	
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
// Function acceptOrder
void acceptorder()
{
	// Variable declarations
	char option, manager, customer;
	int count = 0, numbers;
	float subtotal;
	string method, postcode, phone, name;
	ifstream inFile;

	cout << "\nThis is the customer details\n\n";
	
	// Open the file
	inFile.open("CustomerOrder.txt");
	
	//*******************************************************
	// Get the content of the file
	//*******************************************************
	cout << "**************************************************\n";
	getline(inFile, name);
	getline(inFile, method);
	inFile >> phone;
	inFile >> postcode;
	inFile >> subtotal;
	inFile.ignore();
	
	//*******************************************************
	// Display the content of the file on the screen
	//*******************************************************
	cout << fixed << showpoint << setprecision(2);
	cout << "Customer: " << name << "\nPayment Method: " << method << "\nPhone No.: +60" 
		 << phone << "\nPostcode: " << postcode
		 << "\nTotal Payment: RM" << subtotal << endl;
	cout << "**************************************************\n";
	
	// Close the file
	inFile.close();
	
	// User enter the option whether to accept the order or not
	cout << "\nDo you want to accept this order? [A] YES [B] NO\nSelect: ";
	cin >> option;
	cin.ignore();
	
	while(option)
	{
		if(option == 'A' || option == 'a')
		{
			cout << "Congratulations!!\n";
			cout << "You have accepted this order!! \n";
			cout << "Total Sales and Payment for today: RM" << subtotal << endl;		// Display the total
			break;
		
		}
		else if(option == 'B' || option == 'b')
		{
			cout << "The order does not be accepted.\n\n";
			break;
		}
		else
		{
			cout << "INVALID code. Try again!\n";
		}
		
		cin.ignore();
	}

	
}
