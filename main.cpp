

#include "search.h"
using namespace std;

void testCleanToken() {
            
        string ans = "hel,lo 1";
        string ans2 = "";
        int pass = 0, fail = 0;

        if(ans == cleanToken(".hel,lo 1") && ans2 == cleanToken("****")){

                cout << "testCleanToken good"<< endl;

        } 
        else{

                cout << "testCleanToken bad"<< endl;

        }
        if(ans == cleanToken("......hel,lo 1....") && ans2 == cleanToken("****")){

                cout << "testCleanToken good" << endl;

        }
        else{

                cout << "testCleanToken bad"<< endl;

        }

}

void testGatherToken() {
            
        set<string> tokens = gatherTokens("to be or n,ot ,,,, to be");
        set<string> answers = {"to", "be", "or", "n,ot"};
        
        if(tokens.size() == answers.size()){

                cout << "testGatherToken good" << endl;

        }
        else{

                cout << "testGatherToken bad"<< endl;

        }
        if(tokens == answers){ 

                cout << "testGatherToken good"<< endl;

        }
        else{

                cout << "testGatherToken bad"<< endl;

        }

}
void testBuildIndex() {
    int count;
    int checkCount = 4;


    /*
    File test1.txt contains:


    www.shoppinglist.com
    yo
    www.rainbow.org
    yo red
    www.dr.seuss.net
    yo red green
    www.bigbadwolf.com
    blue


    */


    map<string, set<string>> checkIndex = {
        {"yo", {"www.dr.seuss.net", "www.rainbow.org", "www.shoppinglist.com"}},
        {"red", {"www.dr.seuss.net", "www.rainbow.org"}},
        {"green", {"www.dr.seuss.net"}},
        {"blue", {"www.bigbadwolf.com"}}
    };


    map<string, set<string>> index;
    count = buildIndex("test1.txt", index);


    if (count == checkCount && checkIndex == index) {
        cout << "testBuildIndex good" << endl;
    } else {
        cout << "testBuildIndex bad" << endl;
    }
}


void testFindQueryMatches(){


    map<string, set<string>> checkIndex = {
        {"yo", {"www.dr.seuss.net", "www.rainbow.org", "www.shoppinglist.com"}},
        {"red", {"www.dr.seuss.net", "www.rainbow.org"}},
        {"green", {"www.dr.seuss.net"}},
        {"blue", {"www.bigbadwolf.com"}}
    };


    map<string, set<string>> index;
    buildIndex("test1.txt", index);
    set<string> set1 = findQueryMatches(index, "yo -red blue");


    set<string> checkSet1 = {
        "www.shoppinglist.com",
        "www.bigbadwolf.com",
    };


    set<string> set2 = findQueryMatches(index, "yo +green");
    set<string> checkSet2 = {
        "www.dr.seuss.net"
    };


    if(checkSet1 == set1 && checkSet2 == set2){


        cout << "testFindQueryMatches good" << endl;


    }
    else{


        cout << "testFindQueryMatches bad" << endl;


    }
}


int main() {
    
    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.

    testCleanToken();
    testGatherToken();
    testBuildIndex();
    testFindQueryMatches();
    
    string filename;
    getline(cin, filename);
    searchEngine(filename);

    

    
    



    return 0;
}
