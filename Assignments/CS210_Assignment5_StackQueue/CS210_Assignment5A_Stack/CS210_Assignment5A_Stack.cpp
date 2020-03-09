//
//  main.cpp
//  CS210_Assignment5_StackQueue
//
//  Created by Jessie Sully on 3/7/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Node.h"
#include "Stack.h"

//#define RUN_INPUT_TEST 1

typedef int NTYPE; // Type to use for Stack Nodes.

#ifdef RUN_INPUT_TEST
  static const string TEST_INPUT = "test_input.txt";

  #if defined(WIN32) || defined(_WIN32)
    #define PATH_SEPARATOR "\\"
  #else
    #define PATH_SEPARATOR "/"
  #endif
#endif /* RUN_INPUT_TEST */

enum StatusCode {
  STATUS_OK = 0,
  ERR_MEMORY_LEAK
};

bool testMemoryLeak();
template <typename T>
void display(const Stack<T>& stack);
int runProgram();

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
  
  int status = runProgram();
  if (testMemoryLeak()) {
    return ERR_MEMORY_LEAK;
  }
  
  return status;
}

// runs program
int runProgram() {
  int choice;
  NTYPE data;
  Stack<NTYPE> stack;
  
  while(1)
  {
    /* Menu */
#ifndef RUN_INPUT_TEST // Don't display menu in test mode
    cout <<"------------------------------------\n";
    cout <<" STACK IMPLEMENTATION PROGRAM \n";
    cout <<"------------------------------------\n";
    cout <<"1. Push\n";
    cout <<"2. Pop\n";
    cout <<"3. Size\n";
    cout <<"4. Print Stack\n";
    cout <<"5. Exit\n";
    cout <<"------------------------------------\n";
    cout <<"Enter your choice: ";
#endif /* RUN_INPUT_TEST */
    
    cin >>choice;
    
    switch(choice)
    {
      case 1:
        cout <<"Enter data to push into stack: ";
        cin >> data;
        
        // Push element to stack
        stack.push(data);
        break;
        
      case 2:
        if (stack.isEmpty()) {
          cerr << "Error, stack is empty." << endl;
        }
        else {
          data = stack.pop();
          cout <<"Data => " << data << endl;
        }
        break;
        
      case 3:
        cout <<"Stack size: " << stack.getSize() << endl;
        break;
      
      case 4:
        display(stack);
        break;
        
        
      case 5:
        cout <<"Exiting from app.\n";
        exit(0);
        break;
        
      default:
        cout <<"Invalid choice, please try again.\n";
    }
    
    cout <<"\n\n";
  }
  return STATUS_OK;
}

// returns true if memory leak
bool testMemoryLeak() {
  if (sNumNodeObjects != 0) {
    cerr << "Num leaked nodes: " << sNumNodeObjects << endl;
    return true;
  }
  return false;
}

// Function to display elements in stack
template <typename T>
void display(const Stack<T>& stack) {
  if (!stack.isEmpty()) {
    stack.display(cout);
    cout << endl;
  }
  
  else
    cout << "stack is empty" << endl << endl;
}