#include "FlatNode.h"
#include "ApartmentNode.h"
#include <iostream>

#include <string>

class Street
{
public:
    ApartmentNode * apartment_head;
    ApartmentNode * apartment_tail;

    Street();
    ~Street();
    void addApartment(std::string apartmentName,int addOperator, std::string addBeforeOrAfterThisApartment,int maxBandwith);
    void addFlatToApartment(std::string apartmentName,int,int,int);
    ApartmentNode * removeApartment(std::string apartmentName);
    void makeFlatEmpty(std::string apartmentName,int flatId);
    FlatNode * getFlatById(int id);
    ApartmentNode * getApartmentByName(std::string apartmentName);
    void relocateFlatsToSomeApartment(std::string apartmentName,int index ,int flatIdToReposition);
    void mergeTwoApartments(std::string apartment1,std::string apartment2);
    int findSumOfBandwiths();
    std::string listApartments();
    ApartmentNode * getApartmentByFlatsId(int id);
    
};//end of class

Street::Street()
{
    apartment_head = NULL;
    apartment_tail = NULL;
}//end of constructor

Street::~Street()
{
    if (apartment_head!=NULL)   //We freed the memory of each apartment in the street if there is any apartment
 {
    ApartmentNode * temp1;
    ApartmentNode * temp2 = apartment_head;
    while(temp2 != apartment_tail)
    {
        temp1 = temp2;
        temp2 = temp2->next;
        delete temp1;
    }
    delete temp2;
 }   
}//end of destructor

void Street::addApartment(std::string apartmentName,int addOperator,std::string addBeforeOrAfterThisApartment,int maxBandwith)
//This function adds apartment to the street at the specified location
//Makes the connections between ApartmentNodes
{
    ApartmentNode * newApartment =new ApartmentNode(apartmentName,maxBandwith);
    ApartmentNode * temp1;
    ApartmentNode * temp2;

    switch (addOperator)
    {
    case 0:     //Means add to head
        if( apartment_head == NULL )    //If there is no apartment
        {
            apartment_head =  apartment_tail = newApartment;    //Head and tail points to new apartment
            apartment_tail->next = apartment_head;      //Make the circular connection
        }//end of if

        else    //If there is an apartment
        {
            newApartment -> next =  apartment_head;     //Insert the node before head
            apartment_tail -> next = newApartment;      //Make the circular connection
            apartment_head = newApartment;              //Connect the new head node
        }//end of else

        break;//end of case

    case 1:     //Means add after addBeforeOrAfterThisApartment
        temp1 = getApartmentByName(addBeforeOrAfterThisApartment);  //Get apartments pointer

        if(temp1 ==  apartment_tail)    //If we are adding after the tail
        {
             apartment_tail = newApartment;     //Connect the new tail node
        }//end of if

        newApartment -> next = temp1->next;     //Insert new apartment between
        temp1 -> next = newApartment;           //temp1 and temp1->next
        
        break;//end of case

    case -1:    //Means add before addBeforeOrAfterThisApartment

        std::string name = apartment_head->name;    //Start iterating from apartment_head
        temp1 =  apartment_tail;
        temp2 =  apartment_head;
       
        while (name != addBeforeOrAfterThisApartment)
        {      
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;
            name = temp2 -> name;
        }//When this iteration ends we should insert newApartment between temp1 and temp2

        if(temp2->name ==  apartment_head->name)    //If we are inserting before the head
        {
             apartment_head = newApartment;         //Update the head
        }

        temp1 -> next = newApartment;               //Insert the new apartment
        newApartment -> next = temp2;               //between temp1 and temp2
        break;//end of case
    }//end of switch
}//end of function

void Street::addFlatToApartment(std::string apartmentName,int index,int initial_bandwith,int flat_id)
{
    ApartmentNode * temp = getApartmentByName(apartmentName);
    int available_bandwith = temp->max_bandwith-temp->used_bandwith;    

    if(available_bandwith>initial_bandwith) //If available bandwith allows 
    {}
    else if (available_bandwith==0) //If there is no available bandwith
    {
        initial_bandwith=0;         //Set 0 bandwith
    }//end of else if
    else 
    {
        initial_bandwith = available_bandwith;   //Set maximum available bandwith if requested bandwith>available bandwith
    }//end of else

    FlatNode * newFlatNode= new FlatNode(flat_id,initial_bandwith);     //Create flats Node
    temp->ConnectFlat(index,newFlatNode);           //Connect flat to the apartment

    if (initial_bandwith==0)
    {
        makeFlatEmpty(apartmentName,flat_id);//If there is no bandwith left then set flat as empty
    }//end of if
}//end of function

ApartmentNode * Street::removeApartment(std::string apartmentName)
{
    if( apartment_head ==  apartment_tail)  //If apartment linked list has one apartment.
    {
        delete apartment_head;              //Then it means remove the only element 
        apartment_head = apartment_tail = NULL;
        return NULL;
    }

    ApartmentNode * prevNode =  apartment_tail; 
    ApartmentNode * currNode;
    
    while (prevNode->next->name != apartmentName)   
    //When this iteration ends I have the apartment named with apartmentName(currNode) and prevNode(prevNode)
    {
        prevNode = prevNode -> next;
    }//end of while

    currNode = prevNode->next;
    
    if(currNode ==  apartment_tail) //If we are removing the tail node
    {
         apartment_tail = prevNode; //New tail is the prev node
    }//end of if

    else if (currNode ==  apartment_head)   //If we are removing the head node
    {
        apartment_head = currNode->next;
    }//end of else if

    prevNode->next = currNode->next;    //Connect prevNode to currNodes next to eliminate currNode

    delete currNode;    //Free the memory allocated to currNode
    return apartment_head;
}//end of function

void Street::makeFlatEmpty(std::string apartmentName,int flatId)    //Convert flats is_empty flag to true
{   
    ApartmentNode * currNode = getApartmentByName(apartmentName);
    currNode->EmptyFlat(flatId); 
}//end of function

int Street::findSumOfBandwiths()
{
    int sum = 0;
    ApartmentNode * temp = apartment_head;

    if (temp == NULL)return 0;  //If there is no apartment return 0

    do
    {
        sum += temp->max_bandwith;  //Iterate through each apartmentNode to add up their bandwiths
        temp = temp->next;
    } while (temp!=apartment_head);
    
    return sum;
}//end of function

void Street::mergeTwoApartments(std::string apartment1,std::string apartment2)
{;

    ApartmentNode * firstAptNode = getApartmentByName(apartment1);
    ApartmentNode * secondAptNode = getApartmentByName(apartment2);

    firstAptNode->max_bandwith += secondAptNode->max_bandwith;      //Update max_bandwith values with adding them up
    firstAptNode->used_bandwith += secondAptNode->used_bandwith;    //Update used_bandwith values with adding them up

    if(firstAptNode->flatHead==NULL)//If first apartment has no flats then just firstAptNode->flatHead = secondAptNode->FlatHead
    {
        firstAptNode->flatHead=secondAptNode->flatHead;
        secondAptNode->flatHead ==NULL;
    }

    else if(secondAptNode->flatHead==NULL)//If second apartment has no flats then just relocate the Apt2 and free it.
    {
        
    }

    else    //If both of them has flats then append Apt1 by Apt2's flats.
    {
        FlatNode * temp = firstAptNode->flatHead; //Temp points to first flat in Apt1

        while (temp->next!=NULL)    //Iterate to the last element 
        {
            temp = temp->next;
        }                           //Now temp holds the last flat in Apt1

        temp->next = secondAptNode->flatHead;   //Connect Apt1's last flat to Apt2's first flat 
        secondAptNode->flatHead->prev=temp;     //Make the connection for prev pointer.
    }
    
    secondAptNode->flatHead=NULL;       //Making flathead NULL makes program work fine on destructor
    this->removeApartment(apartment2);  //removing apartment2
}

void Street::relocateFlatsToSomeApartment(std::string apartmentName,int flat_id ,int flatIdToReposition)
//remove flatIdToReposition from its apartment and put it in apartmentName after flat (flat_id)
{
    //std::cout << "ananinaminda 5 cayi" << std::endl;
    ApartmentNode * apartmentToRemoveFlatFrom  = getApartmentByFlatsId(flatIdToReposition);
    FlatNode * transferringFlat = getFlatById(flatIdToReposition);

    int bandwith = transferringFlat->inital_bandwith;   //Hold flats initial bandwith
    int index=0;

    FlatNode * referenceFlat = (getApartmentByName(apartmentName))->flatHead;   //We will add flat to this apartment
    ApartmentNode * referenceApartment = getApartmentByName(apartmentName);     //after this flat

    apartmentToRemoveFlatFrom->max_bandwith-=bandwith;          //Update bandwith values  
    apartmentToRemoveFlatFrom->used_bandwith-=bandwith;         //Update bandwith values 
    referenceApartment->max_bandwith+=bandwith;                 //Update bandwith values 
    referenceApartment->used_bandwith+=bandwith;                //Update bandwith values 

    while (referenceFlat->ID!=flat_id)  //Iterate until reference flat reaches where we want to insert our flat afterwards
    {
        index +=1;
        referenceFlat = referenceFlat->next;    
    }//end of while
    
    
    if(transferringFlat->prev==NULL && transferringFlat->next==NULL)//These if else statements operates the reordering of apt2's flats.
    {
        apartmentToRemoveFlatFrom->flatHead=NULL;
    }//end of if

    else if (transferringFlat->prev==NULL)      //These if else statements operates the reordering of apt2's flats.
    {
        apartmentToRemoveFlatFrom->flatHead==transferringFlat->next;
        transferringFlat->next->prev=NULL;
    }//end of else if

    else if(transferringFlat->next==NULL)       //These if else statements operates the reordering of apt2's flats.
    {
        transferringFlat->prev->next=NULL;
    }//end of else if 
    else        //These if else statements operates the reordering of apt2's flats.
    {
        transferringFlat->prev->next=transferringFlat->next;
        transferringFlat->next->prev=transferringFlat->prev;
    }//end of else 

    referenceApartment->ConnectFlat(index,transferringFlat);    //connect the flat to the index at referenceApartment
}//end of function

std::string Street::listApartments()    //Iterate through each apartments each flat and return a string representing the linkedlist map
{
    std::string outputString ="";
    ApartmentNode * temp =  apartment_head;
    FlatNode * tempFlatNode;

    do  //This whole loop appends string with the map of linkedlist
    {
        outputString=outputString + temp->name+"("+std::to_string(temp->max_bandwith)+")\t";
        tempFlatNode = temp->flatHead;
        while(tempFlatNode!=NULL)
        {
            outputString =outputString +"Flat"+std::to_string(tempFlatNode->ID)+"("+std::to_string(tempFlatNode->inital_bandwith)+")\t";
            tempFlatNode = tempFlatNode->next;
        }
    outputString += "\n";
    
    temp = temp->next;

    } while (temp->name != apartment_head->name);

    return outputString;
    
}//end of function

ApartmentNode * Street::getApartmentByName(std::string apartmentName)
//returns apartments pointer whose name is apartmentName by iterating the apartment list
{
    ApartmentNode * temp =  apartment_head;

    while(temp->name!=apartmentName)
    {
        temp = temp->next;
    }//end of while
    return temp;
}//end of function

FlatNode * Street::getFlatById(int id)
//returns flats pointer who has the stated id as id 
{
    ApartmentNode * temp =  apartment_head;
    FlatNode * tempFlat;
//We must iterate through each apartments each flat to find the flat
    do{    //Iterate through each apartment
        tempFlat= temp->flatHead;
        while (tempFlat!=NULL)  //Iterate through each flat
        {
            if(tempFlat->ID==id)    
            {
                return tempFlat;
            }
            tempFlat=tempFlat->next;
        }
        temp = temp->next;
    }while(temp!= apartment_head);
}//end of function

ApartmentNode * Street::getApartmentByFlatsId(int id)
//Get apartment pointer who has the flat with stated id 
{
    ApartmentNode * temp =  apartment_head;
    FlatNode * tempFlat;

    do{    //Iterate through each apartment
        tempFlat= temp->flatHead;
        while (tempFlat!=NULL)  //Iterate through each flat
        {
            if(tempFlat->ID==id)
            {
                return temp;
            }
            tempFlat=tempFlat->next;
        }
        temp = temp->next;
    }while(temp!= apartment_head);
}//end of function 