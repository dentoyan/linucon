/*
**      LinuCon
**      Linux Console Handler
**
**      Copyright (C) 2025
**      Jörg Dentler
**
*/


#ifndef _CONSOLE_BUFFER_H_
#define _CONSOLE_BUFFER_H_

#include <string>
#include <vector>

struct console_buffer
{
  bool getline(std::string &str, const std::string &pmt = ">");

private:
  std::vector<std::string> history;
  int h_idx = -1;

  std::string buffer;
  std::string seqbuf;

  const std::string UP {'\x1b', '\x5b', '\x41'};
  const std::string DN {'\x1b', '\x5b', '\x42'};
  const std::string E {'\n'};

  bool getseq();
  bool kbhit();
  bool ends_with(std::string const & value, std::string const & ending);
};

#endif

