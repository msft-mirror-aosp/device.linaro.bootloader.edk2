/** @file

  Private definitions of the VirtioRng RNG driver

  Copyright (C) 2016, Linaro Ltd.

  This program and the accompanying materials are licensed and made available
  under the terms and conditions of the BSD License which accompanies this
  distribution. The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS, WITHOUT
  WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _VIRTIO_RNG_DXE_H_
#define _VIRTIO_RNG_DXE_H_

#include <Protocol/ComponentName.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/Rng.h>

#include <IndustryStandard/Virtio.h>

#define VIRTIO_RNG_SIG SIGNATURE_32 ('V', 'R', 'N', 'G')

typedef struct {
  //
  // Parts of this structure are initialized / torn down in various functions
  // at various call depths. The table to the right should make it easier to
  // track them.
  //
  //                        field              init function       init depth
  //                        ----------------   ------------------  ----------
  UINT32                    Signature;      // DriverBindingStart   0
  VIRTIO_DEVICE_PROTOCOL    *VirtIo;        // DriverBindingStart   0
  EFI_EVENT                 ExitBoot;       // DriverBindingStart   0
  VRING                     Ring;           // VirtioRingInit       2
  EFI_RNG_PROTOCOL          Rng;            // VirtioRngInit        1
} VIRTIO_RNG_DEV;

#define VIRTIO_ENTROPY_SOURCE_FROM_RNG(RngPointer) \
          CR (RngPointer, VIRTIO_RNG_DEV, Rng, VIRTIO_RNG_SIG)

#endif
