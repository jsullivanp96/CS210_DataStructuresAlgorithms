/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  main.cpp
//  CS260_Assignment7_SortingAlgorithms
//
//  Created by Jessie Sully on 3/31/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//#define RUN_TESTS
//#define RUN_INPUT_TEST

#include "MySortableArray.h"


#ifdef RUN_INPUT_TEST
  static const string TEST_INPUT = "input.txt";

  #if defined(WIN32) || defined(_WIN32)
    #define PATH_SEPARATOR "\\"
  #else
    #define PATH_SEPARATOR "/"
  #endif
#endif /* RUN_INPUT_TEST */


// returns true if memory leak
bool testMemoryLeak();

// prints array in "<index>=><value>" format separated by spaces.
template <typename T>
void printArray(ostream &ostr, const MySortableArray<T> array);

// helper function to parse index and value from input - with index validation. Returns parse fails or if index < 0.
template <typename T>
bool parseIndexValue(const string &input, int &index, T &value);

// helper function to parse an int from input
bool parseIndex(const string &input, int &num);

// runs tests for the project.
void runTests();

// runs the UI for the project.
void runProgram();

int main(int argc, const char * argv[]) {
  // programmer's identification
  cout << "Programmer: Jessica Sullivan" << endl;
  cout << "Programmer's ID: 1282151" << endl;
  cout << "File: " << __FILE__ << endl;
  
#ifdef RUN_INPUT_TEST
  // Override cin with a test input file.
  string testInputFile(__FILE__);
  size_t filePos = testInputFile.rfind(PATH_SEPARATOR);
  testInputFile = testInputFile.erase(filePos + 1, string::npos);
  testInputFile += TEST_INPUT;
  
  ifstream in(testInputFile.c_str());
  cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
#endif /* RUN_INPUT_TEST */
  
#ifdef RUN_TESTS
  runTests();
#else
  runProgram();
#endif /* RUN_TESTS */
  testMemoryLeak();
  
  return 0;
}


// run tests for the project
void runTests() {
  
  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.display(cout);
    assert(array.getSize() == 1);// sometimes fails
    assert(array.getEntry(1) == 2);
    array.addEntry(1, 5);
    assert(array.getSize() == 1);
    assert(array.getEntry(1) == 5);
  }

  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.deleteIndex(1);
    array.addEntry(2, 3);
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.deleteIndex(5);
    array.addEntry(2, 3);
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(1, 2);
    array.addEntry(2, 3);
    array.deleteIndex(5);
    array.addEntry(3, 4);
    array.display(cout);
  } // FIXME: This sometimes crashes on destructor.

  {
    MySortableArray<int> array;
    assert(array.getLoc(0) == 0);
    array.addEntry(0, 5);
    assert(array.getLoc(0) == 0);
    array.addEntry(1, 5);
    array.addEntry(2, 4);
    array.addEntry(4, 6);
    array.display(cout);
    assert(array.getLoc(0) == 0);
    assert(array.getLoc(4) == 3); //sometimes crashes
    assert(array.getLoc(100) == 4);
    assert(array.getEntry(2) == 4);
    assert(array.getEntry(0) == 5);
    bool caught = false;
    try {
      array.getEntry(100);
    } catch (out_of_range) {  // FIXME: getEntry should raise an out_of_range exception
      caught = true;
    }
    assert(caught == true);
  }
  
  {
    MySortableArray<int> source;
    
    MySortableArray<int> dest1(source);
    assert(dest1.isEmpty());
    dest1.addEntry(1, 2);     // FIXME: This crashes.
    assert(dest1.getEntry(1) == 2);
    
    MySortableArray<int> dest2;
    dest2.copyData(source);
    assert(dest2.isEmpty());
    
    source.addEntry(1, 2);
    source.addEntry(2, 3);
    
    MySortableArray<int> dest3(source);
    assert(dest3.getSize() == 2); // FIXME: This sometimes fails
    assert(dest3.getEntry(1) == 2);
    assert(dest3.getEntry(2) == 3); // FIXME: This somtimes fails
    
    MySortableArray<int> dest4;
    dest4.copyData(source);
    assert(dest4.getSize() == 2);  // FIXME: This sometimes fails
    assert(dest4.getEntry(1) == 2);
    assert(dest4.getEntry(2) == 3);  // FIXME: This sometimes fails
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(0, 2);
    array.addEntry(1, 2);
    array.sort(2); 
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(0, 2);
    array.sort(1);
    array.display(cout);
  }
  
  {
    MySortableArray<int> array;
    array.addEntry(4, 0);
    array.addEntry(2, 1);
    array.addEntry(0, 4);
    array.addEntry(1, 2);
    array.display(cout);
    array.sort(0);
    array.display(cout);
    array.sort(1);
    array.display(cout);
    array.sort(2);
    assert(array.getEntry(0) == 2); //sometimes crashes
    assert(array.getEntry(1) == 4);
    assert(array.getEntry(2) == 1);
    assert(array.getEntry(4) == 0);
    array.display(cout);
    array.sort(3);
    assert(array.getEntry(0) == 1);
    assert(array.getEntry(1) == 2);// crash
    assert(array.getEntry(2) == 4);
    assert(array.getEntry(4) == 0);
    array.display(cout);
    array.sort(4);
    assert(array.getEntry(0) == 0);
    assert(array.getEntry(1) == 1);
    assert(array.getEntry(2) == 2);
    assert(array.getEntry(4) == 4);
    array.display(cout);
    array.sort(5);
    array.display(cout);
  }
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

// prints array in "<index>=><value>" format separated by spaces.
template <typename T>
void printArray(ostream &ostr, const MySortableArray<T> array) {
  if (!array.isEmpty()) {
    array.display(cout);
  }
  else {
    ostr << "Array is empty" << endl;
  }
  ostr << endl;
}

// helper function to parse index and value from input - with index validation. Returns parse fails or if index < 0.
template <typename T>
bool parseIndexValue(const string &input, int &index, T &value) {
  stringstream ss;
  ss.str(input);
  ss >> index >> value;
  return !ss.fail() && index >= 0;
}

// helper function to parse an int from input
bool parseIndex(const string &input, int &num) {
  stringstream ss;
  ss.str(input);
  ss >> num;
  return !ss.fail() && num >= 0;
}

// runs the UI for the project.
void runProgram() {
  string input = "";
  int index = 0, value = 0, numEntries = 0;
  MySortableArray<int> dataToSort;
  
  cout << "Please enter data as '<index> <value>' enter -1 to end: " << endl;
  getline(cin, input);
  while (input != "-1") {
    if (parseIndexValue(input, index, value)) {
      dataToSort.addEntry(index, value);
    }
    else {
      cerr << "Error with entry, please try again: " << endl;
    }
    getline(cin, input);
  }
  cout << endl << "Data entered: " << endl;
  printArray(cout, dataToSort);
  
  do {
    cout << "Number of entries to sort: ";
    getline(cin, input);
    if (!parseIndex(input, numEntries)) {
      cerr << "Error, please try again." << endl << endl;
    }
  } while (numEntries < 0);
  
  dataToSort.sort(numEntries);
  printArray(cout, dataToSort);
  
  do {
    cout << endl << "Enter an index to view, enter -1 to exit: ";
    getline(cin, input);
    if (parseIndex(input, index) && dataToSort.validateIndex(index)) {
      cout << endl << dataToSort.getEntry(index) << endl;
    }
    else {
      if (index != -1) {
        cerr << "Invalid index, please try again." << endl;
      }
    }
  } while (index != -1);
}
