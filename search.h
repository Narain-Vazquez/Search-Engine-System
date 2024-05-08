// TODO: remove and replace this file header comment
// This is a .h file you will edit and turn in.

// Remove starter comments and add your own
// comments on each function and on complex code sections.

#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
string cleanToken(string s) {
    
    
    // TODO:  Write this function.
    string newText;                     //using as the return value
    bool containsCharacter = false;     //using to determine whether a token as a char to make sure its valid to be a token
    int startString;                    //using to determine when to start cleaning to token, basically io use this to get rid of puncations
    int endString;                      //used like startString to determine where the end of clean should be

    for(size_t i = 0 ; i < s.size(); ++i ){
        
        //checking whether the token has atleast on character
        if (isalpha(s.at(i))) {

            containsCharacter = true;

        }

    }
    if(!containsCharacter){
        
        //if it doesnt contain atleast one character the function should return empty
        newText = "";
        return newText;

    }

    for(size_t i = 0 ; i < s.size(); ++i ){
        
        //if the string atleast has no character we remove the leading punctions 
        //by finding where the first character appears in the index
        if(!ispunct(s.at(i))){
            startString = i;
            break;
        }

    }

    for(size_t i = s.size() - 1 ; i >= 0 ; --i){

        //finding the last character appears by reversing the searching
        //i didnt want to use a nested for loop bnecause first it's agaisnt the rules 
        //and it makes it more complicated to read
        if(!ispunct(s.at(i))){
            endString = i;
            break;
        }

    }

    //making the new string with no leading or trailing puncations
    newText = s.substr(startString, (endString-startString) + 1 );

    for(size_t i = 0 ; i < newText.size(); ++i ){

        //making all uppercase letters in the new string lowercase
        if(isupper(newText.at(i))){

            newText.at(i) = tolower(newText.at(i));

        }   

    }
    
    return newText;  //return the new clean token
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
set<string> gatherTokens(string text) {
    set<string> tokens;
    
    
    // TODO:  Write this function.
    stringstream strstream;         //opening string stream to make this process easier
    string tempString;              //using this tempString to hold the clean token that come in from the string stream

    //inputing the string provided into a stream
    strstream << text;

    while(strstream >> tempString){
        
        tempString = cleanToken(tempString);

        //have to check whether or not the string is empty as we 
        //dont want to input empty strings to the set of tokens
        if(!tempString.empty()){

            //inseting the clean tokens into the set named tokens
            tokens.insert(tempString);

        }

    }
    
    
    return tokens;  //returning the set
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
int buildIndex(string filename, map<string, set<string>>& index) {
    
    
    // TODO:  Write this function.
    ifstream inFS;                  //input file stream
    string fileInput;               //using to hold output from file stream
    string tempString;              //using to hold temperary strings
    string URL;                     //using to hold URLS in the files
    
    int count = 0;                  //counting how much the URLS as opened

    inFS.open(filename);

    if (!inFS.is_open()) {
        return 0; 
    }
    
    while(getline(inFS, fileInput)){

        URL = fileInput;            //collecting URL
        getline(inFS, fileInput);   
        tempString = fileInput;     //getting the sentence/words associated with the URL

        //making the set of strings that are under the URL
        //or you can say that we're building the keys of the map
        set <string> tokens = gatherTokens(tempString);

        //this is a nest loop, but a TA told me this is fine as it's the only way to make the map of the tokens and URLS. 
        //And bascially what's happening here is that the set of keys/tokens are all being added/connected to the URL it has above it
        for(auto a : tokens){

            //https://www.geeksforgeeks.org/map-of-sets-in-c-stl-with-examples/
            //im only putting this here for future reference
            index[a].insert(URL);
            
        }

        count++;

    }

    inFS.close();
    
    return count;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    
    // TODO:  Write this function.
    stringstream strstream;         //using the same technique to read sentence easier (string stream)
    set<string> tempSet;            //using to store temperary sets
    set<string> diff;               //using to store a temperary set to then allocate it the final set
    string tempString;              //using to store temperary strings
    
    strstream << sentence;

    strstream >> tempString;
    
    //checking whether the key given exist
    if(index.count(tempString) == 1){
        
        //if it does than we allocate the set to the result
        result = index.at(tempString);

    }

    while(strstream >> tempString){
        tempSet.clear();            //clearing the temperary sets because if i dont once it iterates again the result can miss up as 
        diff.clear();               //some of the memory can be maintained and effect the result once the algorthim functions take place
        
        //checking the first part of the word to determine what type of algorhtim function to use
        if(tempString.at(0) == '-'){

            //making a new sub string to properly move forward with the functions
            tempString = tempString.substr(1);

            //seeing if key exist
            if(index.count(tempString) == 1){
                
                //then after we do that we use the algorthim functions to then, in this case, only have the URls of the
                // first set (result) and get rid of the URlS in this set (tempSet), by using set_difference
                tempSet = index.at(tempString);
                set_difference(result.begin(), result.end(),tempSet.begin(),tempSet.end(), inserter(diff, diff.begin()));
                result = diff;

            }

        }
        else if(tempString.at(0) == '+'){

            tempString = tempString.substr(1);

            if(index.count(tempString) == 1){

                //using the same layout as the set_diffrence part of the code, just in this case we only 
                //only find the values the two sets share and ONLY, by using set_intersection
                tempSet = index.at(tempString);
                set_intersection(result.begin(), result.end(),tempSet.begin(),tempSet.end(), inserter(diff, diff.begin()));
                result = diff;

            }

        }
        else{
            
            if(index.count(tempString) == 1){

                //this just adds set (tempSet) URLS with the Results, by using the set_union function
                tempSet = index.at(tempString);
                set_union(result.begin(), result.end(),tempSet.begin(),tempSet.end(), inserter(diff, diff.begin()));
                result = diff;

            }
        }

    }
    
    return result;  // TODO:  update this.
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string filename) {
    
    // TODO:  Write this function.
    map<string, set<string>> index;
    string userInput;
    int pageCount;                      //count to see number of keys
    bool breakLoop = false;             //usiung to break the loop below

    //building the map of terms and their URLS and then seting
    // them equal to a count to then print out 
    pageCount = buildIndex(filename, index);

    //index.size() would return how many URLS is in the map, as basically
    //with every key, there be set that has three terms and so on
    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << pageCount << " pages containing " << index.size() << " unique terms" << endl;
    cout << endl;
     

    while(!breakLoop){

        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, userInput);

        //exit statment for user
        if(userInput == ""){

            cout << "Thank you for searching!" << endl;
            breakLoop = true;
            break;

        }

        //using userInput to not on find mathces to the keys 
        //but also perfomr the proper operations if stated so
        set<string> finds = findQueryMatches(index, userInput);

        //checking whether anything was found
        if(finds.empty()){

            cout << "No matching pages found" << endl;

        }
        //if something was found 
        else{
            
            cout << "Found " << finds.size() << " matching pages" << endl;

            //printing out the URLS that matched the sentence
            //of operations that the user inputed
            for(const auto& a : finds) {

                cout << a << endl;
                
            }

        }
    }
}
