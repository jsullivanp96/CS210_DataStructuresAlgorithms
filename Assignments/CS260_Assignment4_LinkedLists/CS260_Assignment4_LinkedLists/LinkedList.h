/*
 Programmer: Jessica Sullivan
 Programmer's ID: 1282151
 Class: COMSC-210-5067
 */
//  LINKEDLIST.h
//  CS260_Assignment4_LINKEDLISTs
//
//  Created by Jessie Sully on 2/25/20.
//  Copyright © 2020 Jessie Sully. All rights reserved.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <fstream>
using namespace std;

class LinkedList {
public:
  LinkedList() { init(); }
  ~LinkedList();
  
  class Node {
  public:
    Node() { sNumObjects++; }
    Node(unsigned int key) : mKey(key) { sNumObjects++; }
    virtual ~Node() { unlink(); sNumObjects--; }
    
    unsigned int getKey() const { return mKey; }
    Node* getNext() { return mNextNode; }
    Node* getPrev() { return mPrevNode; }
    
    virtual bool merge(Node* other) { return false; }
    void link(Node* next);
    void unlink();
    
    static int sNumObjects;  // Used to detect memory leaks
    
  private:
    unsigned int mKey = 0;
    Node* mNextNode = this;
    Node* mPrevNode = this;
  };

  Node* getHead() const { return mHead; }
  Node* getFirst() const { return mHead->getNext(); }
  Node* getLast() const { return mHead->getPrev(); }

  Node* getNode(unsigned int key); // returns nullptr if unable to find node
  
  Node* addNode(Node* node);
  void removeNode(Node* node);
  
private:
  bool findClosestNode(unsigned int key);
  void init(); // helper function to initialize mHead
  Node* mHead = nullptr;
  Node* mCurrent = nullptr;
};

void LinkedList::init() {
  mHead = new LinkedList::Node();
  mCurrent = mHead;
}

/* static */ int LinkedList::Node::sNumObjects = 0;

LinkedList::~LinkedList() {
  Node* nextNode = mHead->getNext();
  while (nextNode != mHead) {
    nextNode = nextNode->getNext();
    delete nextNode->getPrev();
  }
  delete mHead;
}

void LinkedList::Node::link(Node* next) {
  mPrevNode = next->mPrevNode;
  mNextNode = next;
  mPrevNode->mNextNode = this;
  mNextNode->mPrevNode = this;
}

void LinkedList::Node::unlink() {
  mPrevNode->mNextNode = mNextNode;
  mNextNode->mPrevNode = mPrevNode;
  mPrevNode = this;
  mNextNode = this;
}

bool LinkedList::findClosestNode(unsigned int key) {
  // Move backward while previous entries are larger, or until we hit Head
  while (mCurrent->getPrev() != mHead && mCurrent->getPrev()->getKey() >= key) {
    mCurrent = mCurrent->getPrev();
  }
  // Move forward while current entries are smaller, or until we hit Head
  while (mCurrent != mHead && mCurrent->getKey() < key) {
    mCurrent = mCurrent->getNext();
  }
  return mCurrent != mHead && mCurrent->getKey() == key;
}

LinkedList::Node* LinkedList::addNode(Node* node) {
  if (findClosestNode(node->getKey())) {
    mCurrent->merge(node);
    delete node;
    return mCurrent;
  }
  else {
    node->link(mCurrent);
    return node;
  }
}

void LinkedList::removeNode(Node* node) {
  if (node == mHead) {
    cerr << "Warning: Cannot remove head node!" << endl;
    return;
  }
  if (mCurrent == node) {
    mCurrent = mCurrent->getNext();
  }
  delete node;
}

LinkedList::Node* LinkedList::getNode(unsigned int key) {
  if (!findClosestNode(key)) {
    return nullptr;
  }
  return mCurrent;
}

#endif /* LINKEDLIST_H */
