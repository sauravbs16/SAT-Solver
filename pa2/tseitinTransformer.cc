#include "tseitinTransformer.h"
#include<iostream>
using namespace std;

TseitinTransformer::TseitinTransformer(TreeNode *root): formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode *subRoot)
{
  // your code starts here
  if (subRoot->getContent() == "+" || subRoot->getContent() == "-" || subRoot->getContent() == "*")
  {
    
    int left;
    int right;
    this->varIdCounter++;
    int operatoriD = this->varIdCounter;
    if (subRoot->getContent() == "-")
    {
      left = this->transSubformula(subRoot->getLeftChild());
      addNegEq(operatoriD, left);
      return operatoriD;
    }
    if (subRoot->getContent() == "+")
    {
      if (subRoot->getLeftChild() != nullptr)
      {
        left = this->transSubformula(subRoot->getLeftChild());
      }
      if (subRoot->getRightChild() != nullptr)
      {
        right = this->transSubformula(subRoot->getRightChild());
      }
      addOrEq(operatoriD, left, right);
      return operatoriD;
    }
    if (subRoot->getContent() == "*")
    {
      if (subRoot->getLeftChild() != nullptr)
      {
        left = this->transSubformula(subRoot->getLeftChild());
      }
      if (subRoot->getRightChild() != nullptr)
      {
        right = this->transSubformula(subRoot->getRightChild());
      }
      addAndEq(operatoriD, left, right);
      return operatoriD;
    }
  }
  else
  {
    if (this->varIdTable.find(subRoot->getContent()) != this->varIdTable.end())
    {
      return this->varIdTable[subRoot->getContent()];
    }
    else
    {
      this->varIdCounter++;
      this->varIdTable[subRoot->getContent()] = this->varIdCounter;
      return this->varIdTable[subRoot->getContent()];
    }
  }
}
void TseitinTransformer::addNegEq(int curID, int childID) {
  // your code starts here
  vector<int>Neg;
  Neg.push_back(curID*-1);
  Neg.push_back(childID*-1);
  this->cnf.push_back(Neg);
  while(!Neg.empty())
  {
    Neg.pop_back();
  }
  Neg.push_back(curID);
  Neg.push_back(childID);
  this->cnf.push_back(Neg);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  vector<int>add;
  add.push_back(curID*-1);
  add.push_back(leftID);
  add.push_back(rightID);
  this->cnf.push_back(add);
  while(!add.empty())
  {
    add.pop_back();
  }
  add.push_back(leftID*-1);
  add.push_back(curID);
  this->cnf.push_back(add);
  while(!add.empty())
  {
    add.pop_back();
  }
  add.push_back(rightID*-1);
  add.push_back(curID);
  this->cnf.push_back(add);
}


void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  vector<int>andd;
  andd.push_back(curID*-1);
  andd.push_back(leftID);
  this->cnf.push_back(andd);
  while(!andd.empty())
  {
    andd.pop_back();
  }
  andd.push_back(curID*-1);
  andd.push_back(rightID);
  this->cnf.push_back(andd);
  while(!andd.empty())
  {
    andd.pop_back();
  }
  andd.push_back(leftID*-1);
  andd.push_back(rightID*-1);
  andd.push_back(curID);
  this->cnf.push_back(andd);
}

TreeNode *TseitinTransformer::getTreeRoot() const
{
  return this->formulaRoot;
}

std::vector<std::vector<int>> TseitinTransformer::transform() {
  // your code starts here
  //TreeNode *t = getTreeRoot();
  int root = this->transSubformula(getTreeRoot());
  this->cnf.push_back({1});
  return this->cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return this->varIdCounter;
}
