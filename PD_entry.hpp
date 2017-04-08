#ifndef PD_ENTRY_HPP
#define PD_ENTRY_HPP

#include "PT_entry.hpp"


struct PD_entry {
  PD_entry(std::vector<PT_entry>* ptba) : page_table_base_addr(ptba) {}

  std::vector<PT_entry>* page_table_base_addr;
};

#endif // !PD_ENTRY_HPP
