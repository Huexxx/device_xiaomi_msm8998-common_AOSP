/*
 * Copyright (c) 2011-2018, The Linux Foundation. All rights reserved.
 * Not a Contribution
 *
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __GRALLOC_PRIV_H__
#define __GRALLOC_PRIV_H__

#include <unistd.h>
#include "gr_priv_handle.h"

#define GRALLOC_PROP_PREFIX  "vendor.gralloc."
#define GRALLOC_PROP(prop_name) GRALLOC_PROP_PREFIX prop_name

#define DISABLE_UBWC_PROP                    GRALLOC_PROP("disable_ubwc")
#define ENABLE_FB_UBWC_PROP                  GRALLOC_PROP("enable_fb_ubwc")
#define MAP_FB_MEMORY_PROP                   GRALLOC_PROP("map_fb_memory")

#define ROUND_UP_PAGESIZE(x) roundUpToPageSize(x)
inline size_t roundUpToPageSize(size_t x) {
    return (x + (getpagesize()-1)) & ~(getpagesize()-1);
}

/* Gralloc usage bits indicating the type of allocation that should be used */
/* Refer gralloc1_producer_usage_t & gralloc1_consumer_usage-t in gralloc1.h */

/* Producer flags */
/* Non linear, Universal Bandwidth Compression */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_ALLOC_UBWC  GRALLOC1_PRODUCER_USAGE_PRIVATE_0

/* Set this for allocating uncached memory (using O_DSYNC),
 * cannot be used with noncontiguous heaps */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_UNCACHED    GRALLOC1_PRODUCER_USAGE_PRIVATE_1

/* CAMERA heap is a carveout heap for camera, is not secured */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_CAMERA_HEAP GRALLOC1_PRODUCER_USAGE_PRIVATE_2

/* ADSP heap is a carveout heap, is not secured */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_ADSP_HEAP   GRALLOC1_PRODUCER_USAGE_PRIVATE_3

/* IOMMU heap comes from manually allocated pages, can be cached/uncached, is not secured */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_IOMMU_HEAP  GRALLOC1_PRODUCER_USAGE_PRIVATE_4

/* MM heap is a carveout heap for video, can be secured */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_MM_HEAP     GRALLOC1_PRODUCER_USAGE_PRIVATE_5

/* Use legacy ZSL definition until we know the correct usage on gralloc1 */
#define GRALLOC1_PRODUCER_USAGE_PRIVATE_CAMERA_ZSL  GRALLOC_USAGE_HW_CAMERA_ZSL


/* Consumer flags */
/* TODO(user): Fix when producer and consumer flags are actually separated */
/* This flag is set for WFD usecase */
#define GRALLOC1_CONSUMER_USAGE_PRIVATE_WFD            (UINT32_C(1) << 21)

/* This flag is used for SECURE display usecase */
#define GRALLOC1_CONSUMER_USAGE_PRIVATE_SECURE_DISPLAY (UINT32_C(1) << 31)

/* Buffer content should be displayed on a primary display only */
#define GRALLOC1_CONSUMER_USAGE_PRIVATE_INTERNAL_ONLY  0x04000000

/* Buffer content should be displayed on an external display only */
#define GRALLOC1_CONSUMER_USAGE_PRIVATE_EXTERNAL_ONLY  0x08000000


/* Legacy gralloc0.x definitions */
/* Some clients may still be using the old flags */
#define GRALLOC_USAGE_PRIVATE_ALLOC_UBWC GRALLOC1_PRODUCER_USAGE_PRIVATE_ALLOC_UBWC
#define GRALLOC_USAGE_PRIVATE_UNCACHED GRALLOC1_PRODUCER_USAGE_PRIVATE_UNCACHED
#define GRALLOC_USAGE_PRIVATE_IOMMU_HEAP GRALLOC1_PRODUCER_USAGE_PRIVATE_IOMMU_HEAP
#define GRALLOC_USAGE_PRIVATE_WFD GRALLOC1_CONSUMER_USAGE_PRIVATE_WFD
#define GRALLOC_USAGE_PRIVATE_CAMERA_HEAP GRALLOC1_PRODUCER_USAGE_PRIVATE_CAMERA_HEAP
#define GRALLOC_USAGE_PRIVATE_SECURE_DISPLAY GRALLOC1_CONSUMER_USAGE_PRIVATE_SECURE_DISPLAY
#define GRALLOC_USAGE_PRIVATE_MM_HEAP 0x0

/* HARDWAREBUFFER flags used by GPU to check secure  secure context support */
#define GRALLOC1_PRODUCER_USAGE_GPU_SAMPLED_IMAGE                   1UL << 8
/* The buffer will be used as a shader storage or uniform buffer object. */
#define GRALLOC1_PRODUCER_USAGE_GPU_DATA_BUFFER                     1UL << 24
/* The buffer will be used as a cube map texture. */
#define GRALLOC1_PRODUCER_USAGE_GPU_CUBE_MAP                        1UL << 25
/* The buffer contains a complete mipmap hierarchy. */
#define GRALLOC1_PRODUCER_USAGE_GPU_MIPMAP_COMPLETE                 1UL << 26

// for PERFORM API :
#define GRALLOC_MODULE_PERFORM_CREATE_HANDLE_FROM_BUFFER 1
#define GRALLOC_MODULE_PERFORM_GET_STRIDE 2
#define GRALLOC_MODULE_PERFORM_GET_CUSTOM_STRIDE_FROM_HANDLE 3
#define GRALLOC_MODULE_PERFORM_GET_CUSTOM_STRIDE_AND_HEIGHT_FROM_HANDLE 4
#define GRALLOC_MODULE_PERFORM_GET_ATTRIBUTES 5
#define GRALLOC_MODULE_PERFORM_GET_COLOR_SPACE_FROM_HANDLE 6
#define GRALLOC_MODULE_PERFORM_GET_YUV_PLANE_INFO 7
#define GRALLOC_MODULE_PERFORM_GET_MAP_SECURE_BUFFER_INFO 8
#define GRALLOC_MODULE_PERFORM_GET_UBWC_FLAG 9
#define GRALLOC_MODULE_PERFORM_GET_RGB_DATA_ADDRESS 10
#define GRALLOC_MODULE_PERFORM_GET_IGC 11
#define GRALLOC_MODULE_PERFORM_SET_IGC 12
#define GRALLOC_MODULE_PERFORM_SET_SINGLE_BUFFER_MODE 13
#define GRALLOC1_MODULE_PERFORM_GET_BUFFER_SIZE_AND_DIMENSIONS 14
#define GRALLOC1_MODULE_PERFORM_ALLOCATE_BUFFER 15
#define GRALLOC1_MODULE_PERFORM_GET_INTERLACE_FLAG 16

// OEM specific HAL formats
#define HAL_PIXEL_FORMAT_RGBA_5551 6
#define HAL_PIXEL_FORMAT_RGBA_4444 7
#define HAL_PIXEL_FORMAT_NV12_ENCODEABLE 0x102
#define HAL_PIXEL_FORMAT_YCbCr_420_SP_VENUS 0x7FA30C04
#define HAL_PIXEL_FORMAT_YCbCr_420_SP_TILED 0x7FA30C03
#define HAL_PIXEL_FORMAT_YCbCr_420_SP 0x109
#define HAL_PIXEL_FORMAT_YCrCb_420_SP_ADRENO 0x7FA30C01
#define HAL_PIXEL_FORMAT_YCrCb_422_SP 0x10B
#define HAL_PIXEL_FORMAT_R_8 0x10D
#define HAL_PIXEL_FORMAT_RG_88 0x10E
#define HAL_PIXEL_FORMAT_YCbCr_444_SP 0x10F
#define HAL_PIXEL_FORMAT_YCrCb_444_SP 0x110
#define HAL_PIXEL_FORMAT_YCrCb_422_I 0x111
#define HAL_PIXEL_FORMAT_BGRX_8888 0x112
#define HAL_PIXEL_FORMAT_NV21_ZSL 0x113
#define HAL_PIXEL_FORMAT_YCrCb_420_SP_VENUS 0x114
#define HAL_PIXEL_FORMAT_BGR_565 0x115
#define HAL_PIXEL_FORMAT_RAW8 0x123

// 10 bit
#define HAL_PIXEL_FORMAT_ARGB_2101010 0x117
#define HAL_PIXEL_FORMAT_RGBX_1010102 0x118
#define HAL_PIXEL_FORMAT_XRGB_2101010 0x119
#define HAL_PIXEL_FORMAT_BGRA_1010102 0x11A
#define HAL_PIXEL_FORMAT_ABGR_2101010 0x11B
#define HAL_PIXEL_FORMAT_BGRX_1010102 0x11C
#define HAL_PIXEL_FORMAT_XBGR_2101010 0x11D
#define HAL_PIXEL_FORMAT_YCbCr_420_P010 0x11F
#define HAL_PIXEL_FORMAT_YCbCr_420_P010_UBWC 0x124

#define HAL_PIXEL_FORMAT_CbYCrY_422_I            0x120
#define HAL_PIXEL_FORMAT_BGR_888                 0x121

#define HAL_PIXEL_FORMAT_INTERLACE 0x180

// v4l2_fourcc('Y', 'U', 'Y', 'L'). 24 bpp YUYV 4:2:2 10 bit per component
#define HAL_PIXEL_FORMAT_YCbCr_422_I_10BIT 0x4C595559

// v4l2_fourcc('Y', 'B', 'W', 'C'). 10 bit per component. This compressed
// format reduces the memory access bandwidth
#define HAL_PIXEL_FORMAT_YCbCr_422_I_10BIT_COMPRESSED 0x43574259

// UBWC aligned Venus format
#define HAL_PIXEL_FORMAT_YCbCr_420_SP_VENUS_UBWC 0x7FA30C06
#define HAL_PIXEL_FORMAT_YCbCr_420_TP10_UBWC     0x7FA30C09

// Khronos ASTC formats
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_4x4_KHR 0x93B0
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_5x4_KHR 0x93B1
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_5x5_KHR 0x93B2
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_6x5_KHR 0x93B3
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_6x6_KHR 0x93B4
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_8x5_KHR 0x93B5
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_8x6_KHR 0x93B6
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_8x8_KHR 0x93B7
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_10x5_KHR 0x93B8
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_10x6_KHR 0x93B9
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_10x8_KHR 0x93BA
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_10x10_KHR 0x93BB
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_12x10_KHR 0x93BC
#define HAL_PIXEL_FORMAT_COMPRESSED_RGBA_ASTC_12x12_KHR 0x93BD
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR 0x93D0
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR 0x93D1
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR 0x93D2
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR 0x93D3
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR 0x93D4
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR 0x93D5
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR 0x93D6
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR 0x93D7
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR 0x93D8
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR 0x93D9
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR 0x93DA
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
#define HAL_PIXEL_FORMAT_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD

/* possible values for inverse gamma correction */
#define HAL_IGC_NOT_SPECIFIED 0
#define HAL_IGC_s_RGB 1

/* Color Space: Values maps to ColorSpace_t in qdMetadata.h */
#define HAL_CSC_ITU_R_601         0
#define HAL_CSC_ITU_R_601_FR      1
#define HAL_CSC_ITU_R_709         2
#define HAL_CSC_ITU_R_2020        3
#define HAL_CSC_ITU_R_2020_FR     4

/* possible formats for 3D content*/
enum {
  HAL_NO_3D = 0x0,
  HAL_3D_SIDE_BY_SIDE_L_R = 0x1,
  HAL_3D_SIDE_BY_SIDE_R_L = 0x2,
  HAL_3D_TOP_BOTTOM = 0x4,
  HAL_3D_IN_SIDE_BY_SIDE_L_R = 0x10000,  // unused legacy format
};

enum { BUFFER_TYPE_UI = 0, BUFFER_TYPE_VIDEO };

#endif  // __GRALLOC_PRIV_H__
