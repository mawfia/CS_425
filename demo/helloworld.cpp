#include <iostream>
#include "Engine.h"

using namespace std;

void callback1() {
    cout << "initialize callback" << '\n';
}

void callback2(char key) {
    cout << key << ' ';
}

int main( int argc, const char* argv[] ) {

    using namespace engine;

    Engine e;
    int GameParameters = 0;
    e.Start(GameParameters, callback1, callback2);
    e.name = "Engine started!";
    cout << e.name << '\n';


    return 0;
}