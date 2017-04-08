#ifndef PAGE_HPP
#define PAGE_HPP

#include <string>


struct Page {
  std::string page;
  Page(int page_size = 4096) {
    page.resize(page_size);
  }
};

#endif // !PAGE_HPP
