// Copyright 2020 jeonghun

#include "fps_unlock.h"
#include "code_patcher.h"

namespace fps_unlock {

code_patcher skip_delay;
code_patcher skip_eval;

void apply() {
  DWORD hinst = reinterpret_cast<DWORD>(GetModuleHandle(NULL));
  const unsigned char nop_5[] = { 0x90, 0x90, 0x90, 0x90, 0x90 }; // NOP NOP NOP NOP NOP

  void* skip_delay_addr = reinterpret_cast<void*>(0x001C2239 + hinst);
  skip_delay.apply(skip_delay_addr, nop_5, sizeof(nop_5));

  void* skip_eval_addr = reinterpret_cast<void*>(0x001C2241 + hinst);
  skip_eval.apply(skip_eval_addr, nop_5, sizeof(nop_5));
}

void undo() {
  skip_delay.undo();
  skip_eval.undo();
}

}  // namespace fps_unlock
