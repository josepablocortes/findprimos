#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

/*
2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
167, 173, 179, 181, 191, 193, 197, 199
*/

typedef vector<unsigned int> mySet;
typedef map<string, mySet> collection;

bool isPrimo(unsigned int number);
collection makeSet(mySet * set);


int main()
{
    mySet elementos;
    for(unsigned int i = 1; i < 4; ++i){
        elementos.push_back(i);
    }
    collection conj = makeSet( &elementos );
    for (collection::iterator it = conj.begin(); it != conj.end(); ++it){
        cout << "["<< it->first << "] = ";
        mySet m2 = it->second;
        for (mySet::iterator it2 = m2.begin(); it2 != m2.end(); ++it2){
            cout << *it2 << " ";
        }
        cout  << endl;
    }
    return 0;
}



bool isPrimo(unsigned int number){

    if (number <= 2){
        return true;
    }
    if ( !(number % 2) && number > 2 ) {
        return false;
    }
    bool result = true;
    for (unsigned int i = 3 ; i < ((unsigned int)sqrt( number ) + 1); ++i)
    {
        if ( !(number % i) ) {
            result = false;
            i = number;
        }
    }
    return result;
}

bool sumAndCheck(mySet & set){
    unsigned int sum = 0;
    for(mySet::iterator it = set.begin(); it != set.end(); ++it){
        sum += *it;
    }
    return isPrimo( sum );
}

collection makeSet(mySet * set){
    collection conjunto;

    for (mySet::iterator it = set->begin(); it != set->end(); ++it){
        mySet sub;
        stringstream key;
        for (mySet::iterator it2 = set->begin(); it2 != set->end(); ++it2){
            if (it2 != it ){
                key << *it2 << ".";
                sub.push_back(*it2);
            }
        }


        if(sumAndCheck( sub )){
            conjunto[ key.str() ] = sub;
        }

        if( sub.size() > 1 ) {
            collection tmp = makeSet( &sub );
            conjunto.insert( tmp.begin(),tmp.end() );
        }
    }

    return conjunto;
}
