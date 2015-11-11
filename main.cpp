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
      <<"3: add stock\n"
      <<"4: add new product\n"
      <<"5: add change\n"
      <<"6: check change reserves \n"
      <<"0:Exit\n";
  cin>>choice;
  while(choice!=0){

    string additionName;
    int additionInt;
    Product newProd = Product("",0);

    switch(choice){
    case 1: machine.purchase();break;
    case 2: machine.listProducts();break;
    case 3: 
      cout<<"Enter the product name and quantity you're adding separated by\
 a space and hit return\n";
      cin>>additionName>>additionInt;
      if(!machine.addStock(additionName, additionInt)){
	cout<<"error adding stock, check this product is listed by the machine\
 or add the product";}
      break;
    
    case 4:
      
      cout<<"Enter the product name and price(in pence) you're adding separated by a space and hit return\n";
      cin>>additionName>>additionInt;
      newProd = Product(additionName, additionInt);
      if(!machine.addProduct(newProd)){
	cout<<"error adding item, check your input\n";}
      break;

    case 5:

      cout<<"Enter the coin type and quantity you're adding separated by a space and hit return\n";
      cin>>additionName>>additionInt;
      if(!machine.addChange(additionName, additionInt)){
	cout<<"error adding coins, check your input\n";}
      break;

    case 6: 

      machine.listChange();break;

    default: cout<<"invalid option, please enter 0-5 and return\n";
    }
      
    cout<< "Welcome back, what would you like to do: \n"
	<<"1: Make Purchase\n"
	<<"2: List Products\n"
	<<"3: add stock\n"
	<<"4: add new product\n"
	<<"5: add change\n"
	<<"6: check change reserves \n"
	<<"0:Exit\n";
    cin>>choice;
    
  }

  //write the current state of the machine to the output files
  machine.saveMachineState(argv[1],argv[2]);
  return 0;
}
