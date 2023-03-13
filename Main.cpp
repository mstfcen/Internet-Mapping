#include "Street.cpp"
#include "FileReader.hpp"
#include "FlatNode.cpp"
#include "ApartmentNode.cpp"
#include "FileWriter.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char const *argv[])
{ 
    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];
    std::string output = "";

    Street * bbm203Street = new Street();

    std::vector<std::string> inputs = FileReader::readFile(inputFileName);//This vector holds each word in txt as an element

    std::string apartmentName,flats,add_operator,singleInput;
    bool writingFirstTime = true;
    int index,initial_bandwith,flat_id,eachFlat;

    for(int i = 0; i<inputs.size();i++)    //Iterate through each word in txt file.
    {
        singleInput = inputs[i];    //This variable holds the input
        if (singleInput == "add_apartment") 
        {
            apartmentName = inputs[++i];   
            add_operator = inputs[++i];     //add_operator->(head,before_**,after_**)
            initial_bandwith = std::stoi(inputs[++i]);  

            if (add_operator[6]=='_')//add_operator = before_(apartmentName)
            {
                std::string addBeforeThisApartment = add_operator.substr(add_operator.find('_')+1);
                bbm203Street->addApartment(apartmentName,-1,addBeforeThisApartment,initial_bandwith);   //-1 in function call means add before
            }//end of if

            else if(add_operator[5]=='_')//add_operator = after_(apartmentName)
            {
                std::string addAfterThisApartment = add_operator.substr(add_operator.find('_')+1);
                bbm203Street->addApartment(apartmentName,1,addAfterThisApartment,initial_bandwith);     //1 in function call means add before
            }//end of else if
            
            else        //add_operator = head
            {
                bbm203Street->addApartment(apartmentName,0,"none",initial_bandwith);    //0 in function call means add to head
            }//end of else
        }//end of if

        else if (singleInput == "add_flat")
        {
            apartmentName = inputs[++i];
            index = std::stoi(inputs[++i]);
            initial_bandwith = std::stoi(inputs[++i]);
            flat_id = std::stoi(inputs[++i]);

            bbm203Street->addFlatToApartment(apartmentName,index,initial_bandwith,flat_id);
        }//end of else if

        else if (singleInput == "remove_apartment")
        {
            apartmentName = inputs[++i];

            bbm203Street->removeApartment(apartmentName);
        }//end of else if

        else if (singleInput ==  "make_flat_empty")
        {
            apartmentName = inputs[++i];
            flat_id = std::stoi(inputs[++i]);

            bbm203Street->makeFlatEmpty(apartmentName,flat_id);
        }//end of else if

        else if (singleInput =="find_sum_of_max_bandwidths")
        {   
            int sum = bbm203Street->findSumOfBandwiths();

            output += ("sum of bandwidth: "+std::to_string(sum)+"\n\n");
            
        }//end of else if

        else if (singleInput =="merge_two_apartments")
        {
            std::string firstApartmentName = inputs[++i];        
            std::string secondApartmentName = inputs[++i];

            bbm203Street->mergeTwoApartments(firstApartmentName,secondApartmentName);
        }//end of else if

        else if (singleInput =="relocate_flats_to_same_apartment")
        {//end of else if
            apartmentName = inputs[++i];
            flat_id = std::stoi(inputs[++i]);
            flats = inputs[++i];
            flats = flats.substr(1,inputs[i].length()-2); //Converts [**,**,*,*] kind of string to **,**,*,*
            std::stringstream ss(flats);    //This string stream extracts integers inside of a string
            int i;
            while (ss >> i)
            {   
                if (ss.peek() == ','||ss.peek()==']'||ss.peek()=='['){
                    ss.ignore();}
                
                bbm203Street->relocateFlatsToSomeApartment(apartmentName,flat_id,i);    //Extracted each integer from string and make function calls for each flat with id i
            }//end of while

        }//end of else if

        else if (singleInput =="list_apartments")
        {
            output+=(bbm203Street->listApartments()+"\n");
        }//end of else if

    }//end of for
    delete bbm203Street;
    writeToFile(outputFileName,output);
    return 0;
}//end of main