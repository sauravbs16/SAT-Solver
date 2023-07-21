#include "treeNode.h"

TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return this->content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return this->leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return this->rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  this->leftChild = lChild;
  this->rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

// bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
//   // your code starts here
//     if(this->getContent()=="+"){
//         return this->getLeftChild()->evaluate(assignment) |  this->getRightChild()->evaluate(assignment);
//     }
//     else if(this->getContent()=="*"){
//         return this->getLeftChild()->evaluate(assignment) & this->getRightChild()->evaluate(assignment);
//     }
//     else{
//         return !this->getLeftChild()->evaluate(assignment);
//     }
// }

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

// bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
//   // your code starts here
//     if(this->getContent()=="1"){
//         return true;
//     }
//   return false;
// }

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

// bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
//   // your code starts here
//   if(assignment.find(this->getContent()) != assignment.end())
//   {
//     return assignment.at(this->getContent());
//   } 
//   //return false;
//   else
//   {
//     throw "Error: incomplete assignment";
//   }
// }

// TreeNode::~TreeNode() {
//   delete treeNode;
// }


