#ifndef V_ADDR_HPP
#define V_ADDR_HPP


struct V_addr {
  int dir_index : 10,
    tbl_index : 10,
    offset : 12;

  bool operator<(const V_addr& v_addr) const {
    return
      dir_index < v_addr.dir_index ? true
      : tbl_index < v_addr.tbl_index ? true
      : offset < v_addr.offset ? true
      : false;
  }
};


#endif // !V_ADDR_HPP
