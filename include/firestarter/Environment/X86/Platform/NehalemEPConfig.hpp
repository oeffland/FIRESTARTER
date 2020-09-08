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

#ifndef INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PLATFORM_NEHALEMEPCONFIG_H
#define INCLUDE_FIRESTARTER_ENVIRONMENT_X86_PLATFORM_NEHALEMEPCONFIG_H

#include <firestarter/Environment/X86/Payload/SSE2Payload.hpp>
#include <firestarter/Environment/X86/Platform/X86PlatformConfig.hpp>

namespace firestarter::environment::x86::platform {
class NehalemEPConfig : public X86PlatformConfig {

public:
  NehalemEPConfig(const asmjit::x86::Features *supportedFeatures,
                  unsigned family, unsigned model, unsigned threads)
      : X86PlatformConfig("NHM_XEONEP", 6, {26, 44}, {1, 2},
                          {32768, 262144, 2097152}, 104857600, family, model,
                          threads,
                          new payload::SSE2Payload(supportedFeatures)){};
  ~NehalemEPConfig(){};

  std::vector<std::pair<std::string, unsigned>>
  getDefaultPayloadSettings(void) override {
    return std::vector<std::pair<std::string, unsigned>>(
        {{"RAM_P", 1}, {"L1_LS", 60}, {"REG", 2}});
  }
};
} // namespace firestarter::environment::x86::platform

#endif
