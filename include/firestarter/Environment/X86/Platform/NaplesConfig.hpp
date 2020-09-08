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

#ifndef INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PLATFORM_NAPLESCONFIG_H
#define INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PLATFORM_NAPLESCONFIG_H

#include <firestarter/Environment/X86/Payload/ZENFMAPayload.hpp>
#include <firestarter/Environment/X86/Platform/X86PlatformConfig.hpp>

namespace firestarter::environment::x86::platform {
class NaplesConfig : public X86PlatformConfig {

public:
  NaplesConfig(const asmjit::x86::Features *supportedFeatures, unsigned family,
               unsigned model, unsigned threads)
      : X86PlatformConfig("ZEN_EPYC", 23, {1, 8, 17, 24}, {1, 2},
                          {65536, 524288, 2097152}, 104857600, family, model,
                          threads,
                          new payload::ZENFMAPayload(supportedFeatures)){};
  ~NaplesConfig(){};

  std::vector<std::pair<std::string, unsigned>>
  getDefaultPayloadSettings(void) override {
    return std::vector<std::pair<std::string, unsigned>>({{"RAM_L", 8},
                                                          {"L3_L", 33},
                                                          {"L2_L", 81},
                                                          {"L1_LS", 79},
                                                          {"REG", 100}});
  }
};
} // namespace firestarter::environment::x86::platform

#endif
