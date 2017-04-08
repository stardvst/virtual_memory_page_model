#include <algorithm>
#include <exception>
#include <iostream>
#include <cmath>
#include <map>
#include "Virtual_memory.hpp"
#include "PD_entry.hpp"
#include "PT_entry.hpp"
#include "V_addr.hpp"
#include "Page.hpp"


Virtual_memory::Virtual_memory(int virtual_size)
  : ram_size(40960), v_size(virtual_size), page_size(4096),
  ram_next_addr(0),
  PDBR(&page_directory) {

  ram.resize(ram_size / page_size); // 40K/4K = 10 physical pages
}


V_addr Virtual_memory::allocate(int size) {

  int old_addr = ram_next_addr;

  if(page_directory.empty()) {
    page_directory.push_back(PD_entry(&page_table));
  }

  if(!holes.empty()) {
    for(std::list<std::pair<V_addr, int> >::const_iterator it = holes.begin(); it != holes.end(); ++it) {
      if((*it).second >= size) {
        V_addr v_addr = (*it).first;
        memory_sizes.insert(std::pair<V_addr, int>(v_addr, size));
        holes.erase(it);
        return v_addr;
      }
    }
  }


  if(size < v_size && ram_next_addr + size < v_size) {
    int next_page_start_addr = static_cast<int>(page_table.size()) * page_size + page_size;

    if(ram_next_addr + size > next_page_start_addr) {

      const int num_of_pages_to_alloc = (v_size + page_size) / page_size;
      const int pt_size = static_cast<int>(page_table.size());

      for(int i = pt_size; i < pt_size + num_of_pages_to_alloc; ++i) {
        page_table.push_back(PT_entry(i));
      }
      next_page_start_addr += page_size * num_of_pages_to_alloc;
    } else if(page_table.empty()) {
      page_table.push_back(PT_entry(0));
    }

    ram_next_addr += size;
  } else {
    // move some memory to hard disk
  }

  V_addr v_addr;
  v_addr.dir_index = static_cast<int>(page_directory.size()) - 1;
  v_addr.tbl_index = static_cast<int>(page_table.size()) - 1;
  v_addr.offset = old_addr;

  memory_sizes.insert(std::pair<V_addr, int>(v_addr, size));

  return v_addr;
}


void Virtual_memory::free(V_addr v_addr) {
  std::map<V_addr, int>::const_iterator it = memory_sizes.find(v_addr);

  if(it == memory_sizes.end()) {
    throw std::exception("invalid memory deallocation\n");
  }

  holes.push_back(std::pair<V_addr, int>((*it).first, (*it).second));
  memory_sizes.erase(it);
}


char& Virtual_memory::operator[](V_addr v_addr) {

  if(memory_sizes.find(v_addr) == memory_sizes.end()) {
    throw std::exception("can't write to invalid memory\n");
  }

  // if offset is in range and page is in memory
  if(v_addr.dir_index < page_directory.size() &&
     v_addr.tbl_index < page_table.size() &&
     v_addr.offset < page_size) {

    // page_table[v_addr.tbl_index].present
    if(((*((*(PDBR.page_dir_base_addr))[v_addr.dir_index].page_table_base_addr))[v_addr.tbl_index]).present) {
      page_table[v_addr.tbl_index].accessed = 1;
      page_table[v_addr.tbl_index].dirty = 1;
    } else {
      // bring to ram from hard disk
    }
    return ram[page_table[v_addr.tbl_index].page_base_addr].page[v_addr.offset];
  }

  throw std::exception("can't write to invalid memory\n");
}


const char Virtual_memory::operator[](V_addr v_addr) const {

  if(memory_sizes.find(v_addr) == memory_sizes.end()) {
    throw std::exception("can't read from invalid memory\n");
  }

  // if offset is in range and page is in memory
  if(v_addr.dir_index < page_directory.size() &&
     v_addr.tbl_index < page_table.size() &&
     v_addr.offset < page_size) {

    // page_table[v_addr.tbl_index].present
    if(((*((*(PDBR.page_dir_base_addr))[v_addr.dir_index].page_table_base_addr))[v_addr.tbl_index]).present) {
      page_table[v_addr.tbl_index].accessed = 1;
    } else {
      // bring to ram from hard disk
    }
    return ram[page_table[v_addr.tbl_index].page_base_addr].page[v_addr.offset];
  }

  throw std::exception("can't read from invalid memory\n");
}
