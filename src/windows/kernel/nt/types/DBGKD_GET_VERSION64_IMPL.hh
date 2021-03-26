/*
 * Copyright 2021 Assured Information Security, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <introvirt/core/memory/guest_ptr.hh>
#include <introvirt/windows/kernel/nt/types/DBGKD_GET_VERSION64.hh>
#include <introvirt/windows/pe/const/MachineType.hh>

namespace introvirt {
namespace windows {
namespace nt {

namespace structs {
struct _DBGKD_GET_VERSION64 {
    uint16_t MajorVersion;
    uint16_t MinorVersion;
    uint16_t ProtocolVersion;
    uint16_t Flags;
    pe::MachineType MachineType;
    uint8_t MaxPacketType;
    uint8_t MaxStateChange;
    uint8_t MaxManipulate;
    uint8_t Simulation;
    uint16_t Unused[0x1];
    uint64_t KernBase;
    uint64_t PsLoadedModuleList;
    uint64_t DebuggerDataList;
};
} // namespace structs

class DBGKD_GET_VERSION64_IMPL final : public DBGKD_GET_VERSION64 {
  public:
    /**
     * Should be 0xF for a free build, 0xC for a checked build
     *
     * @returns The MajorVersion field
     */
    uint16_t MajorVersion() const override;

    /**
     * @returns The operating system build number
     */
    uint16_t MinorVersion() const override;

    /**
     * @returns The protocol version
     */
    uint16_t ProtocolVersion() const override;

    /**
     * @brief Get the Flags field
     *
     * @returns The wrapper around the Flags field
     */
    DBGKD_VERS_FLAG Flags() const override;

    /**
     * @returns The architecture of the machine
     */
    pe::MachineType MachineType() const override;

    /**
     * @returns one plus the highest number for a debugger packet type recognized by the target
     */
    uint8_t MaxPacketType() const override;

    /**
     * @returns one plus the highest number for a state change generated by the target
     */
    uint8_t MaxStateChange() const override;

    /**
     * @returns one more that the highest number, recognized by the target, for a command to
     * manipulate the target
     */
    uint8_t MaxManipulate() const override;

    /**
     * @returns an indication if the target is in simulated execution
     */
    uint8_t Simulation() const override;

    /**
     * @returns The base address of the kernel
     */
    uint64_t KernelBase() const override;

    /**
     * @returns The value of the kernel's PsLoadedModuleList
     */
    uint64_t PsLoadedModuleList() const override;

    DBGKD_GET_VERSION64_IMPL(const NtKernel& kernel);

  private:
    using _DBGKD_GET_VERSION64 = structs::_DBGKD_GET_VERSION64;
    guest_ptr<_DBGKD_GET_VERSION64> header_;
};

} // namespace nt
} // namespace windows
} // namespace introvirt