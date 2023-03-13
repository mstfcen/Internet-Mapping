#pragma once
class FlatNode
{
public:
    int ID;
    int inital_bandwith;
    bool is_empty;
    FlatNode * next;
    FlatNode * prev;

    FlatNode();
    FlatNode(int ID,int initial_bandwith);
    ~FlatNode();
};
