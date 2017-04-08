#ifndef VIRTUAL_MEMORY_HPP
#define VIRTUAL_MEMORY_HPP

#include <utility>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "V_addr.hpp"
#include "PD_entry.hpp"
#include "PT_entry.hpp"
#include "Ctrl_reg.hpp"
#include "Page.hpp"


class Virtual_memory {
public:
  Virtual_memory(int = 81920); // 80K/4K = 20 virtual pages

  V_addr allocate(int);
  void free(V_addr);

  char& operator[](V_addr);
  const char operator[](V_addr) const;

private:
  const int ram_size;
  int v_size;
  int page_size;
  int ram_next_addr;

  std::vector<Page> ram;

  std::vector<PD_entry> page_directory;
  mutable std::vector<PT_entry> page_table;
  Ctrl_reg PDBR;

  std::map<V_addr, int> memory_sizes;
  std::list<std::pair<V_addr, int> > holes;
};

#endif // !VIRTUAL_MEMORY_HPP
