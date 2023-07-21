#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include<iostream>
#include<map>


FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
    TreeNode *t1 = parseTerm();
    TreeNode *sNode = nullptr;
    if(tknzr->getToken().content=="*")
    {
        sNode = new OperatorNode("*");
        tknzr->advanceToken();
        if(tknzr->getToken().content == "+" || tknzr->getToken().content == "*" || tknzr->getToken().content == ")")
        {
            throw "Error: invalid input";
        }
        TreeNode *t2 = parseConjTerm();
        sNode->updateChildren(t1, t2);
    }
    
    if(sNode!=nullptr){
        return sNode;
    }
    return t1;
}

TreeNode *FormulaParser::parseTerm() {
    // your code starts here
    TreeNode *t = nullptr;
    if(tknzr->getToken().content == "("){
        tknzr->advanceToken();
        if(tknzr->getToken().content == "+" || tknzr->getToken().content == "*" || tknzr->getToken().content == ")")
        {
            throw "Error: invalid input";
        }
        else
        {
            t = parseFormula();
            if (tknzr->getToken().content != ")")
            {
                //cout<<"ERROR: ) not found - Invalid String"<<endl;
            }
            else{
                tknzr->advanceToken();
                if(tknzr->getToken().type == "variable" || tknzr->getToken().type == "constant" || tknzr->getToken().content == "(" || tknzr->getToken().content == "-")
                {
                    throw "Error: invalid input";
                }
            }
        }
    }
    else if(tknzr->getToken().type == "operator"){
        if(tknzr->getToken().content=="-"){
            tknzr->advanceToken();
            if(tknzr->getToken().content == "+" || tknzr->getToken().content == "*" || tknzr->getToken().content == ")")
            {
                throw "Error: invalid input";
            }
            else
            {
                t=parseTerm();
                TreeNode *negation = new OperatorNode("-");
                negation->updateLeftChild(t);
                return negation;
            }
        }
    }
    else if(tknzr->getToken().type == "variable"){
        t = new VariableNode(tknzr->getToken().content);
        tknzr->advanceToken();
        if(tknzr->getToken().type == "variable" || tknzr->getToken().type == "constant" || tknzr->getToken().content == "(" || tknzr->getToken().content == "-")
        {
            throw "Error: invalid input";
        }
        return t;
    }
    else if(tknzr->getToken().type=="constant"){
        t = new ConstantNode(tknzr->getToken().content);
        tknzr->advanceToken();
        if(tknzr->getToken().type == "variable" || tknzr->getToken().type == "constant" || tknzr->getToken().content == "(" || tknzr->getToken().content == "-")
        {
            throw "Error: invalid input";
        }
        return t;
    }
    else
    {
        throw "Error: invalid input";
    }
    return t;
}

TreeNode *FormulaParser::parseFormula() {
    TreeNode *t1 = this->parseConjTerm();
    TreeNode *plusnode = nullptr;
    //    tknzr->advanceToken();
    if(tknzr->getToken().content == "+"){
        plusnode = new OperatorNode("+");
        tknzr->advanceToken();
        if(tknzr->getToken().content == "+" || tknzr->getToken().content == "*" || tknzr->getToken().content == ")")
        {
            throw "Error: invalid input";
        }
        TreeNode *t2 = this->parseFormula();
        plusnode->updateChildren(t1,t2);
    }
    if(plusnode != nullptr)
    {
        return plusnode;
    }
    return t1;
}

TreeNode * FormulaParser::getTreeRoot() {
    // your code starts here
    return this->parseFormula();
}

// FormulaParser::~FormulaParser() {
//     // your code starts here
//     delete tknzr;
// }

AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
    std::map<std::string, bool> results;
    // your code starts here
    std::string key, value;
    bool b;
    while(tknzr->hasToken())
    {
        if(tknzr->getToken().type == "variable")
        {
            key = tknzr->getToken().content;
            tknzr->advanceToken();
            if(tknzr->getToken().type == "operator")
            {
                tknzr->advanceToken();
                value = tknzr->getToken().content;
                if(tknzr->getToken().content== "1")
                {
                    b = true;
                }
                else if(tknzr->getToken().content== "0")
                {
                    b = false;
                }
                else
                {
                    throw "Error: invalid input";
                }
            }   
            else
            {
                throw "Error: invalid input";
            }
        } 
        else
        {
            throw "Error: invalid input";
        }
        if(results.find(key) != results.end())
          {
            if(results.at(key) != b)
            {
                throw "Error: contradicting assignment";
            }
          }
        results.insert({key,b});
        tknzr->advanceToken(); //for comma
        tknzr->advanceToken();
    }
    return results;
}

AssignmentParser::~AssignmentParser() {
    // your code starts here
    delete tknzr;
}