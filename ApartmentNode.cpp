#include <string>
#include "ApartmentNode.h"
#pragma once
    ApartmentNode::ApartmentNode()
    {
        
    }
    ApartmentNode::ApartmentNode(std::string c_name,int c_max_bandwith)
    {
        name = c_name;
        max_bandwith=c_max_bandwith;
        next=NULL;
        flatHead=NULL;
        used_bandwith=0;

    }

    ApartmentNode::~ApartmentNode()
    // ApartmentNode destructor 
    {   
        if(flatHead!=NULL)  //If there is an flat connected to apartment
        {
            FlatNode * temp1 = flatHead;
            while (temp1->next !=NULL)  //Free each flat's prev flat 
            {   
                temp1=temp1->next;
                delete temp1->prev;
            }//end of while
            delete temp1;   //free last node 
        }//end of if
    }//end of function

    void ApartmentNode::ConnectFlat(int index,FlatNode * newFlatNode)
    //Connect flatNode to stated index 
    {
        this->used_bandwith += newFlatNode->inital_bandwith;    //Update used bandwith
        if(index == 0){ //If adding to the head
            if(this->flatHead == NULL)  //If head is null
            {
                this->flatHead = newFlatNode;   //Make newFlatNode the head node
            }//end of if

            else    
            {
                (this -> flatHead) -> prev = newFlatNode;
                newFlatNode -> next = this -> flatHead;
                this -> flatHead = newFlatNode;
            }//end of else
        }//end of if

        else    //If not adding to the head 
        {
            FlatNode * temp = this->flatHead;
            for (int i = 0; i < index; i++)     //Iterate until we reach the index'th flat
            {   
                if(temp->next ==NULL){  //Stops iteration when we are in the last item so that it won't lose track of last element
                    temp ->next = newFlatNode;
                    newFlatNode->prev= temp;
                    return;
                }//end of if 

                temp = temp->next;
            }//end of for
            
            newFlatNode->prev = temp->prev;             //Arranging flat connections
            (temp->prev) -> next = newFlatNode;         //
            newFlatNode -> next = temp;                 //
            temp -> prev = newFlatNode;                 //
        }//end of else 
    }//end of function

    void ApartmentNode::EmptyFlat(int flat_id)
    //function updates flats is_empty flag to true
    {
        FlatNode * temp = this->flatHead;
        while (temp->ID!=flat_id)   //Iterate through flats until reaching flat with stated id
        {
            temp = temp->next;
        }//end of while
        this->used_bandwith -= temp->inital_bandwith;   //Update bandwith values
        temp->is_empty=true;                            //Update is empty flag
        temp->inital_bandwith=0;                        //Set flats bandwith to 0
    }//end of function