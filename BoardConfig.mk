# Copyright (C) 2014-2016 The CyanogenMod Project
# Copyright (C) 2017-2018 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

DEVICE_PATH := device/samsung/h3gduosctc

# inherit from common hlte
include device/samsung/hlte-common/BoardConfigCommon.mk

TARGET_OTA_ASSERT_DEVICE := h3g,h3gduosctc,hlte

# Init
TARGET_INIT_VENDOR_LIB := libinit_h3gduosctc

# Kernel
TARGET_KERNEL_CONFIG := lineage_h3gduosctc_defconfig

# NFC
include $(COMMON_PATH)/nfc/bcm2079x/board.mk

# Radio/RIL
include $(COMMON_PATH)/radio/dual/board.mk

# inherit from the proprietary version
-include vendor/samsung/h3gduosctc/BoardConfigVendor.mk
