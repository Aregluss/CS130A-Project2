#include <math.h>
#include <string>
#include <iostream>
#include "SplayTree.h"
#include "SNode.h"

using namespace std;


int main()
{
    SplayTree test;

    int n;
    cin >> n;

 

    for(int i = 0; i < n; i++)
    {
        string command = "";
        int value = -1;
        cin >> command;
        
        if(!(command.compare("insert")))
        {
            cin >> value;
            test.insertVal(value);
        }
        else if(!(command.compare("delete")))
        {
            cin >> value;
            test.deleteVal(value);
        }
        else if(!(command.compare("find")))
        {
            cin >> value;
            test.findVal(value);    
        }
        else if(!(command.compare("print")))
            test.print();
    }
   
}
