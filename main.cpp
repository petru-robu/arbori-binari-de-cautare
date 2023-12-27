#include <fstream>
#include "RB.h"


int main()
{
    RBTree a;
    a.Insert(4);
    a.Insert(5);
    a.Insert(3);

    a.Preorder();
    a.Erase(5);

    a.Preorder();
    std::cout<< a.Search(4);  
    return 0;
}