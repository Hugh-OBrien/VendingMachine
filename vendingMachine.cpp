#include <iostream>
#include <string>
#include <list>
#include <map>
#include <fstream>
#include <iomanip>
#include "vendingMachine.h"

using namespace std;

VendingMachine::VendingMachine(char* coinState, char* productState){
  ifstream in;
  
  balance = 0;
  productList = new list<Product>();

  //set up the coin reserve based on the input file
  string coinNames[8] = {"1p", "2p", "5p", "10p", "20p", "50p", "£1", "£2"};
  int coinValues[8] = {1,2,5,10,20,50,100,200};
  
  in.open(coinState);

  for(int i=0; i<8; i++){
    coinTypesHeld[i] = new Coin(coinNames[i],coinValues[i]);
    int coinQuantity=0;
    in>>coinQuantity;
    changeHeld[coinNames[i]] = coinQuantity;
  }
  insertedCoins = new list<string>();

  in.close();

  //set up the current product stock based on the file provided
  in.open(productState);

  while(!in.eof()){
    string name;
    int price;
    int quantity;

    in>>name>>price>>quantity;
    if(name.compare("")!=0){
      Product newProd = Product(name, price);
      this->addProduct(newProd);
      this->addStock(name,quantity);
    }
    
  }
  in.close();
}

VendingMachine::~VendingMachine(){

  delete insertedCoins;
  delete productList;
  for(int i=0; i<8; i++)
    delete coinTypesHeld[i];

}

void VendingMachine::saveMachineState(char* coinState, char* productState){

  ofstream out;

  //write the coin counts to the coin file:
  out.open(coinState);
  for(int i=0; i<8; i++){
    out<< changeHeld[coinTypesHeld[i]->name]<< " ";
  }
  out.close();

  //write the products state:

  //remove current file
  remove(productState);
  //write to the new clean file
  out.open(productState);
  for(list<Product>::iterator ite=productList->begin(); ite!= productList->end(); ite++){
    out<<ite->name<< " " << ite->price << " " << stock[ite->name]<< "\n";
  }
  out.close();

}


void VendingMachine::purchase(){
  
  //enter the name of the product
  string p;
  cout<<"Please enter the name of the product you want to buy \n"
      <<"Enter 'LIST' to list the products and 'EXIT' to go back \n";
  cin>>p;

  //continue offering to list the products or exit until a valid product is selected
  while(!this->checkStock(p) || p.compare("LIST")==0 || p.compare("EXIT")==0){
    if(p.compare("LIST")==0){
      cout<<endl;      
      this->listProducts();}
    
    else if(p.compare("EXIT")==0){
      return;} 

    else {cout<< "Invalid Selection \n";}

    cout<<endl<<"Please enter the name of the product you want to buy \n"
	<<"Enter 'LIST' to list the products and 'EXIT' to go back \n";
    cin>>p;
  }

  //get the product object and begin
  for(list<Product>::iterator ite=productList->begin(); ite!= productList->end(); ite++){
    if(ite->name.compare(p)==0){
      if(stock[ite->name] <= 0){
	cout<<"This product is out of stock\n";
	return;
      }  
      while(ite->price > balance){
	//ask for money until we're over the value of the product 
	string nextCoin;
	cout << "Current balance is: " << balance << "p"<<endl
	     <<"Please insert a coin, accepted coins are '1p'"
	     <<", '2p', '5p', '10p', '20p', '50p', '£1', '£2'\n";
	
	cin>> nextCoin;
	if(this->insertMoney(nextCoin));
	else{
	  cout<< "that is not a valid coin\n";
	}
      }
      balance -= ite->price;

      //remove the product from our stock
      stock[ite->name]--;

      //add the change to the internal coin store
      for(list<string>::iterator c=insertedCoins->begin(); c!= insertedCoins->end(); c++){
	if(!this->addChange(c->c_str(),1)){
	  cout<<"Coin input error";}
      }
      
      //dispense change equal to the value of the remaining balance
      this->dispenseChange(balance);

      //      
      cout<<"Enjoy your: " << ite->name<<endl;
    }
  }

}

bool VendingMachine::insertMoney(string coinName){

  for(int i=0; i<8; i++){
    if(coinTypesHeld[i]->name.compare(coinName)==0){
      balance += coinTypesHeld[i]->value;
      insertedCoins->push_back(coinName);
      return true;
    }
  }
  
  return false;
}

void VendingMachine::dispenseChange(unsigned int value){
  cout<< "Thank you, your change is: "<<value<< "p made up of:  \n";

  // give out the largest denominations until we're at the at zero
  for(int i=7; i>=0; i--){
    while(coinTypesHeld[i]->value <= value && changeHeld[coinTypesHeld[i]->name]>0){
      cout<<coinTypesHeld[i]->name<<endl;
      changeHeld[coinTypesHeld[i]->name]--;
      value -= coinTypesHeld[i]->value;
    }
  }
  if(value!=0){
    cout<<"INSUFFICIENT CHANGE AVAILABLE\n";
  }
  
}

void VendingMachine::listProducts(){
  cout << setiosflags ( ios :: left );
  cout.width(20);

  cout<<"Current products are: \n";
  for(list<Product>::iterator ite=productList->begin(); ite!= productList->end(); ite++){
    cout.width(15);
    cout<<ite->name<< "price: " <<ite->price << "p\t"
	<<  "stock: " << stock[ite->name] << endl;
  }
}

bool VendingMachine::addProduct(Product newProd){
  //check if this product is already in the product list by name
  for(list<Product>::iterator ite=productList->begin(); ite!= productList->end(); ite++){
    if(newProd.name.compare(ite->name)==0){
      cout<<"There is already a product with this name!\n";
      return false;
    }
  }
  //otherwise go ahead and add it to the product list and create a stock entry    
  productList->push_back(newProd);
  stock[newProd.name] = 0;
  return true;
  
}

void VendingMachine::removeProduct(string productName){

  //find the product object
  for(list<Product>::iterator ite=productList->begin(); ite!= productList->end(); ite++){
    if(ite->name.compare(productName)==0){
      map<string,int>::iterator mpit;
      mpit=stock.find(ite->name);
      stock.erase(mpit);
      productList->erase(ite);
      cout<<"Product removed successfully\n";
      return;
    }
  }

  cout<< "Product not found to remove!\n";

}

bool VendingMachine::addChange(string coinName, int quantity){

  //ensure this is a coin type we accept
  for(int i=0; i<8; i++ ){
    if(coinTypesHeld[i]->name == coinName){
      changeHeld[coinName]+=quantity;
      return true;
    }
  }
  return false;
}

bool VendingMachine::addStock(string productName, int quantity){
  //check this product exists
  for(list<Product>::iterator ite=productList->begin(); ite!= productList->end(); ite++){
    if(ite->name.compare(productName)==0){
      stock[productName] += quantity;
      return true;
    }
  }
  return false;
}

void VendingMachine::listChange(){

  cout<< "Current coins in the machine are: \n";

  for(int i=0; i<8; i++){
    cout<< coinTypesHeld[i]->name<< "\t" << "Quantity: "
	<<changeHeld[coinTypesHeld[i]->name]<<endl;
  }

}

bool VendingMachine::checkStock(string productName){
  for(list<Product>::iterator ite=productList->begin(); ite!= productList->end(); ite++){
    if(productName.compare(ite->name)==0){
      return true;
    }
  }
  return false;
}
