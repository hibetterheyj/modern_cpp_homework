#include "tools.hpp"
int get_first(int num) {
  while (num >= 10) {
    num /= 10;
  }
  return num;
}

int get_last(int num) { return (num % 10); }