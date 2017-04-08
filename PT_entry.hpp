#ifndef PT_ENTRY_HPP
#define PT_ENTRY_HPP


struct PT_entry {
  int page_base_addr  : 20;

  unsigned            : 8; // other flags

  unsigned dirty      : 1;
  unsigned accessed   : 1;
  unsigned read_write : 1;
  unsigned present    : 1;

  PT_entry(int pba, unsigned d = 0, unsigned a = 0, unsigned rw = 1, unsigned p = 1)
    : page_base_addr(pba), dirty(d), accessed(a), read_write(rw), present(p) {}
};

#endif // !PT_ENTRY_HPP
