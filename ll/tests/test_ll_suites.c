#include <greatest.h>

#include "test_ll.h"

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(ll_suite);
  GREATEST_MAIN_END();
}
