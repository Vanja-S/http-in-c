// Copyright 2024 Vanja S.

#include "lib.h"

unsigned num_of_digits(const unsigned n) {
    if (n < 10) return 1;
    return 1 + num_of_digits(n / 10);
}
