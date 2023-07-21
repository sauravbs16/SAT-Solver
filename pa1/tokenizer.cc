#include "tokenizer.h" 
#include <vector>
#include <regex>
#include <cctype>
#include<iostream>


Tokenizer::Tokenizer(std::string ln) {

  std::string meh = ln;
  std::regex var("[A-Za-z][0-9]+");
  std::regex oper("[+,-,*,:,),(]");
  std::regex cons("[0,1]");

  for(int i=0;i<ln.size();i++)
  {
      if(ln[i] == ' ')
      {
        continue;
      }
      Token t;
      std::string x = std::string(1, ln[i]);
      if(std::regex_match(x, oper) || ln[i] == '-')
      {
        t.content = ln[i];
        t.type = "operator";
      }
      else if(regex_match(x, cons))
      {
        t.content = ln[i];
        t.type = "constant";
      }
      else{
          t.type = "variable";
          std::string s;
          while(isalnum(ln[i]))
          {
            s+=ln[i];
            i++;
            if(s.length()>10)
            {
              throw "Error: invalid input";
            }
          }
          int temp = (int)s[0];
          if(isdigit((temp)))
          {
            throw "Error: invalid input";
          }
          i--;
          t.content=s;
      }
      token_vector.push_back(t); // array of structures
  }
}

Token Tokenizer::getToken() {
  // your code starts there
  Token resultToken;
  if(hasToken()){
    resultToken = this->token_vector[token_index];
    return resultToken;
  }
  return resultToken;
}

bool Tokenizer::advanceToken() {
  // your code starts here
  token_index++;
  if(this->token_vector.size()<= this->token_index)
  {
    return false;
  }
  return true;
}

bool Tokenizer::hasToken() const {
  // your code starts here
  if(this->token_vector.size() > this->token_index){
    return true;
  }
  return false;
}

