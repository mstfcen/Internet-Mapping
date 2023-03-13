#include <string>
#pragma once
class ApartmentNode
{
public:
    std::string name;
    FlatNode * flatHead;

    int max_bandwith;
    int used_bandwith;

    ApartmentNode * next;

    ApartmentNode();
    ApartmentNode(std::string c_name,int c_max_bandwith);
    ~ApartmentNode();
    void ConnectFlat(int index,FlatNode * someFlat);
    void EmptyFlat(int flatid);
};