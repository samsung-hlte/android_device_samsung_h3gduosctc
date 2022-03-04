/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2018, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/file.h>
#include <android-base/strings.h>

#include "init_msm8974.h"

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;

#define ISMATCH(a, b) (!strncmp((a), (b), PROP_VALUE_MAX))

#define SERIAL_NUMBER_FILE "/efs/FactoryApp/serial_no"

void property_override_dual(char const system_prop[],
        char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{
    char const *serial_number_file = SERIAL_NUMBER_FILE;
    std::string serial_number;
    std::string platform = GetProperty("ro.board.platform", "");
    std::string bootloader = GetProperty("ro.bootloader", "");

    if (ReadFileToString(serial_number_file, &serial_number)) {
        serial_number = Trim(serial_number);
        property_override("ro.serialno", serial_number.c_str());
    }

    if (bootloader.find("N9002") == 0) {
        /* h3gduoszn */
        property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "samsung/h3gduoszn/hlte:5.0/LRX21V/N9002ZNSGQA1:user/release-keys");
        property_override("ro.build.description", "h3gduoszn-user 5.0 LRX21V N9002ZNSGQA1 release-keys");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "SM-N9002");
        property_override_dual("ro.product.device", "ro.vendor.product.device", "h3gduoszn");
        gsm_properties("9", "02");
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader <<  " setting build properties for "
            << device <<  " device" << std::endl;
}
