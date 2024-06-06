#pragma once

#include <Windows.h>

#define PANIC(do_a_panic, message)                \
  if (do_a_panic) {                               \
    MessageBox(nullptr, message, "Error", MB_OK); \
    exit(1);                                      \
  }