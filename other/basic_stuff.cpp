#include  <string>
#include <iostream>
#include <vector>
#include <typeinfo>


namespace andrejjeborec{

int func(int haha){
    haha++;
    return haha;
}

}

using std::cout;
using std::cin;


int main()
{
    std::vector<std::string> custom_names = {"Foo", "Fighters", "Monkey", "Wrench"};
    for (int i; )
    std::vector<std::string> names = {};
    std::string txt = "";
    for (int i=0; i < names.size(); i++)
    {   
        if (i == 0){
            txt = names[i];
        }
        else {
            txt = txt + " " + names[i] + " " + std::to_string(i);
        }
        
    }
    cout << txt << "\n";

    // std::cout << "Hello World!\n";

    // int a = 5;
    // //int c = 20;
    // int *b = &a;
    // std::cout << "`a` before " << a << "\n";
    // std::cout << "`b` before " << b << "\n";
    // int c = *b + 100;
    // std::cout << "`a` after " << a << "\n";
    // std::cout << "`b` after " << b << "\n";
    // std::cout << "`c` after " << c << "\n";
    // return 0;
}


