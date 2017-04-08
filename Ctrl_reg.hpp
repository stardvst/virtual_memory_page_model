#ifndef CTRL_REG_HPP
#define CTRL_REG_HPP

#include <vector>
#include "PD_entry.hpp"


struct Ctrl_reg {
  std::vector<PD_entry>* page_dir_base_addr;
  Ctrl_reg(std::vector<PD_entry>* pdba) : page_dir_base_addr(pdba) {}
};

#endif // !CTRL_REG_HPP
