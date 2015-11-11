#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <string>
#include <map>
using namespace std;

class Product{

public:

string name;
double price;

Product(string n, double p):name(n), price(p){}

};

class Coin{

public:
Coin(){}
Coin(string n, int i):name(n),value(i){}
string name;
unsigned int value;//held in pence

};

class VendingMachine{

private:

Coin *coinTypesHeld[8];
map<string, int> changeHeld;//a map holding the number of each coin held in the form {name:quantity}
list<Product> *productList;
map<string,int> stock; // a map in the form {name:stock}
list<string> *insertedCoins;//list of the coins inserted during current purchase
unsigned int balance;//the amount of money currently inserted into the machine

bool checkStock(string productName);
//internal function to ensure we have a given product in stock

public:

VendingMachine(char* coinState, char* productState);

//NEEDS DECONSTRUCTOR

void saveMachineState(char* coinState, char* productState);
//overwrites the files provided as input with the current machine state

void purchase();
//enters the purchase loop

bool insertMoney(string coinName);
//adds valid coins to the balance of the machine, returns false if invalid coin

void dispenseChange(unsigned int value);
//outputs coins to the value given from the machine's held change

void listProducts();
//provides a list of all products, stock and value

bool addProduct(Product newProd);
//adds a new product to the machine with 0 stock

void removeProduct(Product product);
//removes a product - for manual additions in case of mistakes

bool addChange(string coinName, int quantity);
//for adding to the held change, takes a coin object

bool addStock(string productName, int quantity);
//adds stock to already listed items

void listChange();
//gives account of the current held change

};

#endif
