#include <memory>
#include <iostream>
#include "tseitinTransformer.h"
#include "satSolver.h"
#include "parser.h"

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
void Invalid_Input(std::string &formulaStr);
int main() {
  
  std::string line;
  while (getline(std::cin, line)) // continuously asking for new inputs from standard input
  {
     // store each input line
    // your code starts here
    try{
      std::string formulaStr = line;
      TreeNode *t;
      Invalid_Input(formulaStr);
      FormulaParser *formulaParser = new FormulaParser(formulaStr);
      
      t = formulaParser->getTreeRoot();
      TseitinTransformer *tseitinTransformer = new TseitinTransformer(t);
      std::vector<std::vector<int>> res = tseitinTransformer->transform();
      bool result = satCallingMiniSat(tseitinTransformer->getVarNum(), res);
      if(result)
      {
        std::cout<<"sat"<<std::endl;
      }
      else{
        std::cout<<"unsat"<<std::endl;
      }
    }
    catch (const char *error)
    {
      std::cout<<"Error: invalid input"<<std::endl;
    }
  }
}

void Invalid_Input(std::string &formulaStr) 
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
}
