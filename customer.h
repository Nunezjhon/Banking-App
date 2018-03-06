/*customer.h*/

//
// Customer class for banking program in modern C++.
//
// Jhon Nunez
// jnunez34
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#pragma once

#include <iostream>
#include <string>

using namespace std;


class Customer
{

 private:
    string Name;
    int ID;
    double Balance;
  
  public:
  
  Customer(string name, int id, double balance)
    : Name(name), ID(id), Balance(balance)
    {}
    
    string getName() {
      return Name;
    }
    
    int getID() {
      return ID;
    }
  
    double getBalance() {
      return Balance;
    }

    double transactionMod(double x) {
      return Balance += x;
    }
  
};

class Transaction
{
  
  private:
    int ID;
    double userTransaction;
    
  public:
  
  Transaction(int id, double utrans)
  : ID(id), userTransaction(utrans)
  {}
  
  int getID(){
    return ID;
  }
  
  double getUserTransaction(){
    return userTransaction;
  }

  
};
