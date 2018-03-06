/*main.cpp*/

//
// Banking program in modern C++.
//
// Jhon Nunez
// jnunez34
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//
//------------------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "customer.h"

using namespace std;
//------------------------------------------------------------------------------------
void sortCustomersAndPrint(vector<Customer>& customers)
{
   
  cout << std::fixed;
  cout << std::setprecision(2);
  
   //sort by name
   sort(customers.begin(), 
       customers.end(),  
      
      []( Customer &s1, Customer &s2) 
      
      {
        
        if ( s1.getName() < s2.getName() )
          return true;
          
        //else if ( s1.getName() > s2.getName() )
          //return false;

        else
          return false;
        
      }
 );
   
  //Print the vector  
 for (Customer& C: customers)//print the output
 {
   cout<<C.getName()<< " (" << C.getID() << "): $" << C.getBalance() <<endl;
 }
  
}
//------------------------------------------------------------------------------------
void sortBalanceAndPrint(vector<Customer>& customers)
{
   
  cout << std::fixed;
  cout << std::setprecision(2);
  
   //sort by Balance
   sort(customers.begin(), 
       customers.end(),  
      
      []( Customer &s1, Customer &s2) 
      
      {
        
        if ( s1.getBalance() > s2.getBalance() )
          return true;
          
        else if ( s1.getBalance() < s2.getBalance() )
          return false;

        else
          return false;
        
      }
 );
   
  //Print the vector  
 for (Customer& C: customers)//print the output
 {
   cout<<C.getName()<< " (" << C.getID() << "): $" << C.getBalance() <<endl;
 }
  
}
//------------------------------------------------------------------------------------
bool validTransaction(vector<Customer> &customers, int id, double trans)
{
      for (Customer &C: customers){
        
        if (C.getID() == id)
        {
          if  ( (C.getBalance() + trans) < 0 ){
            return false;
          }
        
          else {
            return true;
          }
        }
      }
    
}
//------------------------------------------------------------------------------------
bool isCustomer(vector<Customer> &customers, int id)
{
  
   for (Customer& C: customers){
    
      if ( C.getID() == id){
        return true;
      }
   
   }
  return false;
}
//------------------------------------------------------------------------------------
void updateCustomers(vector<Customer> &customers, int id, double trans)
{

    for (Customer& C: customers)
    {
      if ( validTransaction(customers, id, trans) == true ) 
      {
      
        if (C.getID() == id)
        {
          C.transactionMod(trans);
        
         }
         //break;
      
      }
    }
  
}
//------------------------------------------------------------------------------------
int main()
{
  
  string sign, utrans, line, name, id, balance;

  string  customerFilename, transactionsFilename;

  cin >> customerFilename;
  cout << customerFilename << endl;
  
  cin >> transactionsFilename;
  cout << transactionsFilename << endl;

  ifstream  custFile(customerFilename);
  ifstream  txFile(transactionsFilename);

  cout << std::fixed;
  cout << std::setprecision(2);

  if (!custFile.good())
  {
    cout << "**ERROR: cannot open customers file: '" << customerFilename << "'" << endl;
    return -1;
  }
  if (!txFile.good())
  {
    cout << "**ERROR: cannot open transactions file: '" << transactionsFilename << "'" << endl;
    return -1;
  }
  
  vector<Customer> customers; //create customers vector
  
  //getline(custFile,line);  
  
  while (getline(custFile,line) )
  {
  
    stringstream ss(line);
  
    getline(ss,name,',');
    getline(ss,id,',');
    getline(ss,balance);
    
    Customer C(name,stoi(id),stod(balance));
    //cout << name << endl;
    customers.push_back(C);
 
    //getline(custFile,line);
  
  }//end of while loop
//------------------------------------------------------------------------------------  
 
  cout << ">> Customers before:" << endl;
  sortCustomersAndPrint(customers);

  cout << ">> Processing..." << endl;
  //make transaction vector
  
  vector<Transaction> transactions;

  //getline(txFile,line);  
 
  while (getline(txFile,line))
  {
  
    stringstream ss(line);
  
    getline(ss,id,',');
    
    getline(ss,utrans);
   
    //Transaction D( stoi(id), stod(utrans) );
      //check if the transaction will go through

    if (isCustomer(customers, stoi(id) ) == false)
    {
      cout << "**Invalid Tx: " << stoi(id) << "," << stod(utrans) << endl;
    } 
    else {
      
      if (validTransaction(customers, stoi(id), stod(utrans) ) == false )
      {
        cout << "**Rejected Tx: " << stoi(id) << "," << stod(utrans) << endl;
      }
      else
      {
        updateCustomers(customers, stoi(id), stod(utrans) );
      }
    
    }



  }//end of while loop
  
  //display final output of customers 
  cout << ">> Customers After:" << endl;
  
  sortBalanceAndPrint(customers);
  
  
  
   return 0;
}

