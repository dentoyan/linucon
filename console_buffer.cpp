/*
**      LinuCon
**      Linux Console Handler
**
**      Copyright (C) 2025
**      Jörg Dentler
**
*/

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>

#include "console_buffer.h"


bool console_buffer::getline(std::string &str, const std::string &pmt)
{
    std::cout << pmt << std::flush;
    buffer.clear();
    str.clear();

    bool rc;
    while ((rc = getseq())) {
        if (ends_with(seqbuf, E)) {
            buffer += seqbuf.substr(0, seqbuf.size() - E.size());
            h_idx = -1;
            rc = true;
            break;

        } else if (ends_with(seqbuf, UP)) {
            buffer += seqbuf.substr(0, seqbuf.size() - UP.size());
            std::cout << "\33[2K\r" << pmt << std::flush;

            if (h_idx < 0) {
                h_idx = history.size() - 1;

            } else {
                if (h_idx > 0)
                    h_idx--;
            }
            if (h_idx >= 0) {
                buffer = history[h_idx];
                std::cout << buffer;
            }

        } else if (ends_with(seqbuf, DN)) {
            buffer += seqbuf.substr(0, seqbuf.size() - DN.size());
            std::cout << "\33[2K\r" << pmt << std::flush;

            if (h_idx >= 0) {
                 if (int(history.size()) > (h_idx + 1))
                     h_idx++;
                 buffer = history[h_idx];
                 std::cout << buffer;
            }

        } else {
            buffer += seqbuf;
        }
    }

    if (rc) {
        if (buffer.empty()) {
            if (rc) {
                // repeat last
                if (history.empty()) {
                    // first input is empty
                    rc = false;
                } else {
                    buffer = history.back();
                }
            }

        } else {
            if (rc) {
                if (history.empty()) {
                    history.push_back(buffer);
                } else {
                    if (history.back() != buffer) {
                        history.push_back(buffer);
                    }
                }
            } else {
                buffer.clear();
            }
        }

        str = buffer;
    } else {
        std::cout << "\b" << std::endl;
    }
    return rc;
}

bool console_buffer::ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size())
        return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool console_buffer::getseq()
{
    while (!kbhit()) {
        usleep(10 * 1000);
    }
    return !seqbuf.empty();
}

bool console_buffer::kbhit()
{
    struct termios oldt, newt;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOKE);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    char ss[256];
    char *ps = fgets(ss , 100 , stdin);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ps) {
        seqbuf = ss;
        return true;

    } else {
        return false;
    }
}

