# LinuCon #

A linux console command handler for interactive use.

* basic command handler
* special key functions
* history buffer access via up, down
* repeat last command by pressing return


## Usage ##

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


build via
    g++ -Wall -o linucon linucon.cpp console_buffer.cpp
or
    g++ -Wall -o linucon -I .. -g -O0 -fno-inline linucon.cpp console_buffer.cpp


## License ##

LinuCon is distributed under the [MIT license](http://www.opensource.org/licenses/MIT).


