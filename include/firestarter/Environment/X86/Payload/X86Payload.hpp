/******************************************************************************
 * FIRESTARTER - A Processor Stress Test Utility
 * Copyright (C) 2020 TU Dresden, Center for Information Services and High
 * Performance Computing
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/\>.
 *
 * Contact: daniel.hackenberg@tu-dresden.de
 *****************************************************************************/

#ifndef INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PAYLOAD_PAYLOAD_H
#define INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PAYLOAD_PAYLOAD_H

#include <firestarter/Environment/Payload/Payload.hpp>
#include <firestarter/Logging/Log.hpp>
#include <firestarter/ThreadData.hpp>

#include <asmjit/x86.h>

#define INIT_BLOCKSIZE 1024

namespace firestarter::environment::x86::payload {

class X86Payload : public environment::payload::Payload {
private:
  // we can use this to check, if our platform support this payload
  asmjit::x86::Features const *const _supportedFeatures;
  std::list<asmjit::x86::Features::Id> featureRequests;

protected:
  //  asmjit::CodeHolder code;
  asmjit::JitRuntime rt;
  // typedef int (*LoadFunction)(firestarter::ThreadData *);
  typedef unsigned long long (*LoadFunction)(unsigned long long *,
                                             volatile unsigned long long *,
                                             unsigned long long);
  LoadFunction loadFunction = nullptr;

  asmjit::x86::Features const *const &supportedFeatures = _supportedFeatures;

public:
  X86Payload(asmjit::x86::Features const *const supportedFeatures,
             std::initializer_list<asmjit::x86::Features::Id> featureRequests,
             std::string name)
      : Payload(name), _supportedFeatures(supportedFeatures),
        featureRequests(featureRequests){};
  ~X86Payload(){};

  bool isAvailable(void) override {
    bool available = true;

    for (auto const &feature : featureRequests) {
      available &= supportedFeatures->has(feature);
    }

    return available;
  };

    // A generic implemenation for all x86 payloads
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverloaded-virtual"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverloaded-virtual"
  void init(unsigned long long *memoryAddr, unsigned long long bufferSize,
            double firstValue, double lastValue);
#pragma GCC diagnostic pop
#pragma clang diagnostic pop
  // use cpuid and usleep as low load
  void lowLoadFunction(volatile unsigned long long *addrHigh,
                       unsigned long long period) override;

  unsigned long long highLoadFunction(unsigned long long *addrMem,
                                      volatile unsigned long long *addrHigh,
                                      unsigned long long iterations) override;
};

} // namespace firestarter::environment::x86::payload

#endif
