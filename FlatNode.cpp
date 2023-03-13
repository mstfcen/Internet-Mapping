#include "FlatNode.h"
#pragma once
FlatNode::FlatNode(){
    
}
FlatNode::FlatNode(int ID,int initial_bandwith)
{
    this -> ID = ID;
    this->inital_bandwith = initial_bandwith;
    next = NULL;
    prev = NULL;
    is_empty = false;
}

FlatNode::~FlatNode()
{
}
