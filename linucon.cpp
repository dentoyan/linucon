/*
**      LinuCon
**      Linux Console Handler
**
**      Copyright (C) 2025
**      Jörg Dentler
**
*/

#include <iostream>
#include "console_buffer.h"

int main(int argc, char *argv[])
{
    using namespace std;
    console_buffer cb;
    string cmd;
    while (cb.getline(cmd)) {
        if (cmd == "run")
            cout << "run command issued" << endl;
        else if (cmd == "exit")
            return 1;
        else
            cout << "cmd: " << cmd << endl;
    }
    return 0;
}


