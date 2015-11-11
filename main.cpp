#include <iostream>
#include <list>
#include <string>
#include "vendingMachine.h"

using namespace std;


int main(int argc, char **argv){

  //ingest the setup files

  //check the correct number of files are provided
  if(argc != 3){
    cout<< "incorrect number of command line arguments provided \n"
	<<"Please run the program in the form '[exe] [Change Breakdown] [stock]'\n";
    return 0;
  }

  //instantiate the machine class
  VendingMachine machine(argv[1],argv[2]);

  //main menu
  int choice;
  cout<< "Welcome, what would you like to do: \n"
      <<"1: Make Purchase\n"
      <<"2: List Products\n"
      <<"3: Admin Functions\n"
      <<"0:Exit\n";
  cin>>choice;
  while(choice!=0){

    string additionName;
    int additionInt;
    Product newProd = Product("",0);

    switch(choice){
    case 0: break;
    case 1: machine.purchase();break;
    case 2: machine.listProducts();break;
    case 3: 
      cout<<"ADMIN MENU\n"
	  <<"1: Add Stock of Existing Product\n"
	  <<"2: Add New Product\n"
	  <<"3: Remove Product\n"
	  <<"4: Add Change\n"
	  <<"5: Check Change Reserves \n"
	  <<"0:Go Back\n";
      cin>>choice;
      while(choice!=0){
	switch(choice){
	case 0: break;
	case 1:

	  cout<<"Enter the product name and quantity you're adding separated by a space and hit return\n";
	  cin>>additionName>>additionInt;
	  if(!machine.addStock(additionName, additionInt)){
	    cout<<"error adding stock, check this product is listed by the machine or add the product";}
	  break;
    
	case 2:
      
	  cout<<"Enter the product name and price(in pence) you're adding separated by a space and hit return\n";
	  cin>>additionName>>additionInt;
	  newProd = Product(additionName, additionInt);
	  if(!machine.addProduct(newProd)){
	    cout<<"error adding item, check your input\n";
}
	  break;
	case 3:
	  cout<<"Enter the product you wish to remove, warning this will remove all it's stock\n";
	  cin>>additionName;
	  machine.removeProduct(additionName);
	  break;

	case 4:

	  cout<<"Enter the coin type and quantity you're adding separated by a space and hit return\n";
	  cin>>additionName>>additionInt;
	  if(!machine.addChange(additionName, additionInt)){
	    cout<<"error adding coins, check your input\n";
	  }
	  break;
	  
	case 5: 
	  
	  machine.listChange();break;

	default:cout<<"invalid option, please enter 0-5 and return\n";
	  
	}
	cout<<"ADMIN MENU\n"
	    <<"1: Add Stock of Existing Product\n"
	    <<"2: Add New Product\n"
	    <<"3: Remove Product\n"
	    <<"4: Add Change\n"
	    <<"5: Check Change Reserves \n"
	    <<"0:Go Back\n";
	cin>>choice;
      }
    default: if(choice!=0){cout<<"invalid option, please enter 0-3 and return\n";}
    }
    
    cout<< "Welcome back, what would you like to do: \n"
      <<"1: Make Purchase\n"
      <<"2: List Products\n"
      <<"3: Admin Functions\n"
      <<"0:Exit\n";
    cin>>choice;
    
  }

  //write the current state of the machine to the output files
  machine.saveMachineState(argv[1],argv[2]);
  return 0;
}
