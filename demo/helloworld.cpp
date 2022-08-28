#include <iostream>
#include "Engine.h"

using namespace std;

void function1() {
    cout << "initialize callback" << '\n';
}

void function2() {
    cout << "update callback" << '\n';
}

int main( int argc, const char* argv[] ) {

    using namespace engine;

    Engine e;
    int GameParameters = 0;
    e.Start(GameParameters, function1, function2);
    e.name = "Engine started!";
    cout << e.name << '\n';


    return 0;
}