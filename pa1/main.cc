#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <regex>
#include <cctype>
#include "parser.h"
#include "treeNode.h"

void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr);
void Invalid_Input(std::string &formulaStr, std::string &assignmentStr);

int main() 
{
  std::string line;
  while (getline(std::cin,line)) 
  {
    try
    {
      std::string formulaStr;
      std::string assignmentStr; 
      parseLine (line, formulaStr, assignmentStr);
      Invalid_Input(formulaStr, assignmentStr);
      FormulaParser fp(formulaStr);
      AssignmentParser ap(assignmentStr);
      TreeNode *root;
      std::map<std::string,bool> ass = ap.parseAssignment();
      std::vector<std::string>x;
      std::vector<std::string>y;
      for (auto& it: ass)
      {
        x.push_back(it.first);
      }
      root = fp.getTreeRoot();
      std::cout<<root->evaluate(ass)<<std::endl;
    }
    catch(const char* t)
      {
        std::cout<<t<<std::endl;
      }
  }
}

void parseLine(const std::string &line, std::string &formulaStr, std::string &assignmentStr) 
{
  if(line[0] == ';')
  {
      throw "Error: invalid input";
  }
  
  int cnt=0;
  for (long i=0;i<line.length();i++)
  {
    if(line[i]==';')
    {
      cnt++;
    }
  }
  if(cnt>1 || cnt ==0)
  {
    throw "Error: invalid input";
  }
  
  int pos = line.find(";");
  formulaStr = line.substr(0, pos);
  assignmentStr = line.substr(pos+1, line.length()-1);
}

void Invalid_Input(std::string &formulaStr, std::string &assignmentStr) 
{ 
  int c1 = 0;
  int c2 = 0;
  for (int i =0;i<formulaStr.length();i++)
  {
    if(formulaStr[i] == ')')
    {
      c1++;
    }
    if(formulaStr[i] == '(')
    {
      c2++;
    }
    if(c1>c2)
    {
      throw "Error: invalid input";
    }
  }
  if(c1 != c2)
    {
      throw "Error: invalid input";
    }
  
  for (int i =0;i<formulaStr.length();i++)
  {
    if(isalnum(formulaStr[i]) || formulaStr[i] == '(' || formulaStr[i] == ')' || formulaStr[i] == '+' || formulaStr[i] == '-' || formulaStr[i] == '*' || formulaStr[i] == ' ')
    {
    }
    else
    {
      throw "Error: invalid input";
    }
  }

  for (int i =0;i<assignmentStr.length();i++)
  {
    if(isalnum(assignmentStr[i]) || assignmentStr[i] == ':' || assignmentStr[i] == ',' || assignmentStr[i] == ' ')
    {
    }
    else
    {
      throw "Error: invalid input";
    }
  }
}