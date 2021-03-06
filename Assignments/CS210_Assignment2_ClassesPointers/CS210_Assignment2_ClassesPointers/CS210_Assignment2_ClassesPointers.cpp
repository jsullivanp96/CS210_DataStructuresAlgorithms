/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 Goal: Write a program that will record information about employees
 and will compute their paychecks
 */
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "DynamicStringArray.h"

const string DynamicStringArray::BAD_INPUT = "NULL";

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
  DynamicStringArray names;
  // List of names
  names.addEntry("Frank");
  names.addEntry("Wiggum");
  names.addEntry("Nahasapeemapetilon");
  names.addEntry("Quimby");
  names.addEntry("Flanders");
  
  // Output list
  cout << "List of names:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  // Add and remove some names
  names.addEntry("Spuckler");
  cout << "After adding a name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.deleteEntry("Nahasapeemapetilon");
  cout << "After removing a name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.deleteEntry("Skinner");
  cout << "After removing a name that isn't on the list:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.addEntry("Muntz");
  cout << "After adding another name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  // Remove all of the names by repeatedly deleting the last one
  while (names.getSize() > 0) {
    names.deleteEntry(names.getEntry(names.getSize() - 1));
  }
  
  cout << "After removing all of the names:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  names.addEntry("Olivia");
  cout << "After adding a name:" << endl;
  for (int i = 0; i < names.getSize(); i++)
    cout << names.getEntry(i) << endl;
  cout << endl;
  
  cout << "Testing copy constructor" << endl;
  DynamicStringArray names2(names);
  // Remove Olivia from names
  names.deleteEntry("Olivia");
  cout << "Copied names:" << endl;
  for (int i = 0; i < names2.getSize(); i++)
    cout << names2.getEntry(i) << endl;
  cout << endl;
  
  cout << "Testing assignment" << endl;
  // we can't set names3 = names2 here, since some compilers optimize
  // that into a copy constructor and we want to test operator=()
  //DynamicStringArray names3 = names2;
  // Break it up into default constructor and operator=(), separately:
  DynamicStringArray names3;
  names3 = names2;
  // Remove Olivia from names2
  names2.deleteEntry("Olivia");
  cout << "Copied names:" << endl;
  for (int i = 0; i < names3.getSize(); i++)
    cout << names3.getEntry(i) << endl;
  cout << endl;
  
  cout << "Testing delete multiple entries" << endl;
  DynamicStringArray names4;
  names4.addEntry("Jack");
  names4.addEntry("Jill");
  names4.addEntry("Jack");
  names4.deleteEntry("Jack");
  for (int i = 0; i < names4.getSize(); i++)
    cout << names4.getEntry(i) << endl;
  cout << endl;
  
  cout << "Test get out of bounds entry." << endl;
  cout << "Large index: " << names4.getEntry(1000) << endl;
  cout << "Size index: " << names4.getEntry(names4.getSize()) << endl;
  cout << "Negative index: " << names4.getEntry(-1) << endl;
  cout << endl;
  
  cout << "Test copy constructor of an empty array" << endl;
  DynamicStringArray names5;
  DynamicStringArray names6(names5);
  for (int i = 0; i < names6.getSize(); i++)
    cout << names6.getEntry(i) << endl;
  cout << endl;
  
  cout << "Test assignment of an empty array" << endl;
  DynamicStringArray names7;
  names7 = names5;
  for (int i = 0; i < names7.getSize(); i++)
    cout << names7.getEntry(i) << endl;
  cout << endl;
  

  cout << "Enter a character to exit." << endl;
  char wait;
  cin >> wait;
  return 0;
}
