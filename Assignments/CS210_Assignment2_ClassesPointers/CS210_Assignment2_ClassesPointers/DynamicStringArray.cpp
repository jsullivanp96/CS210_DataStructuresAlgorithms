//
//  DynamicStringArray.cpp
//  CS210_Assignment2_ClassesPointers
/*
Programmer: Jessica Sullivan
Programmer's ID: 1282151
Class: COMSC-210-5067
Goal: Write a program that will record information about employees
and will compute their paychecks
*/
/*
#include <iostream>
using namespace std;
*/
#include "DynamicStringArray.h"

DynamicStringArray::DynamicStringArray(){
  mSize = 0;
  mDynamicArray = nullptr;
}

DynamicStringArray::DynamicStringArray(const DynamicStringArray &srcArray) {
  mSize = srcArray.mSize;
  mDynamicArray = new string[mSize];
  for (int i = 0; i < mSize; i++) {
    mDynamicArray[i] = srcArray.mDynamicArray[i];
  }
}

DynamicStringArray& DynamicStringArray:: operator=(const DynamicStringArray &srcArray) {
  mSize = srcArray.mSize;
  mDynamicArray = new string[mSize];
  for (int i = 0; i < mSize; i++) {
    mDynamicArray[i] = srcArray.mDynamicArray[i];
  }
  return *this;
}

void DynamicStringArray::addEntry(const string &entry) {
  string *tempArray = mDynamicArray;
  mSize++;
  mDynamicArray = new string[mSize];
  
  if (tempArray != nullptr) {
    for (int i = 0; i < mSize - 1; i++) {
      mDynamicArray[i] = tempArray[i];
    }
    delete [] tempArray;
  }
  mDynamicArray[mSize - 1] = entry;
}

int DynamicStringArray::getNumMatchingEntries(const string &entry) const {
  int numEntries = 0;
  if (mSize > 0) {
    for (int i = 0; i < mSize; i++) {
      if (mDynamicArray[i] == entry) {
        numEntries++;
      }
    }
  }
  return numEntries;
}

bool DynamicStringArray::deleteEntry(const string &entry) {
  string *tempArray = mDynamicArray;
  int numEntries = getNumMatchingEntries(entry);
  int newSize = mSize - numEntries;
  
  if (numEntries) {
    mDynamicArray = new string[newSize];
    for (int i = 0, j = 0; j < newSize && i < mSize; i++) {
      if (tempArray[i] != entry) {
        mDynamicArray[j] = tempArray[i];
        j++;
      }
    }
    delete [] tempArray;
    mSize = newSize;
  }
  else {
    return false;
  }
  return true;
}
