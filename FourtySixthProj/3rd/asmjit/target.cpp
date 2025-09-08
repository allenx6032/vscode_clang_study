// This file is part of AsmJit project <https://asmjit.com>
//
// See asmjit.h or LICENSE.md for license and copyright information
// SPDX-License-Identifier: Zlib

#include "asmjit/api-build_p.h"
#include "asmjit/target.h"

ASMJIT_BEGIN_NAMESPACE

Target::Target() noexcept
  : _environment{},
    _cpuFeatures{} {}
Target::~Target() noexcept {}

ASMJIT_END_NAMESPACE
