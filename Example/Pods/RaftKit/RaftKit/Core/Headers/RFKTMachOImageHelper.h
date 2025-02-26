//
//  RMMachOImageHelper.h
//  Raft-Monitor
//
//  Created by 张鹏 on 4/27/15.
//  Copyright (c) 2015 com.tencent. All rights reserved.
//

#ifndef _RFKT_MACHO_IMAGE_HELPER_H_
#define _RFKT_MACHO_IMAGE_HELPER_H_
#ifdef __cplusplus

#import <Foundation/Foundation.h>
#import <vector>
#import <string>
#import <mach/vm_types.h>

#ifdef __LP64__

typedef struct mach_header_64 mach_header_t;
typedef struct segment_command_64 segment_command_t;
typedef struct section_64 section_t;

#else

typedef struct mach_header mach_header_t;
typedef struct segment_command segment_command_t;
typedef struct section section_t;

#endif

#if __is_target_arch(x86_64)

#define MY_THREAD_STATE_COUTE x86_THREAD_STATE64_COUNT
#define MY_THREAD_STATE x86_THREAD_STATE64
#define MY_EXCEPTION_STATE_COUNT x86_EXCEPTION_STATE64_COUNT
#define MY_EXCEPITON_STATE x86_EXCEPTION_STATE64
#define MY_SEGMENT_CMD_TYPE LC_SEGMENT_64

#elif __is_target_arch(i386)

#define MY_THREAD_STATE_COUTE x86_THREAD_STATE_COUNT
#define MY_THREAD_STATE x86_THREAD_STATE
#define MY_EXCEPTION_STATE_COUNT x86_EXCEPTION_STATE_COUNT
#define MY_EXCEPITON_STATE x86_EXCEPTION_STATE
#define MY_SEGMENT_CMD_TYPE LC_SEGMENT

#elif __is_target_arch(arm64)

#define MY_THREAD_STATE_COUTE ARM_THREAD_STATE64_COUNT
#define MY_THREAD_STATE ARM_THREAD_STATE64
#define MY_EXCEPTION_STATE_COUNT ARM_EXCEPTION_STATE64_COUNT
#define MY_EXCEPITON_STATE ARM_EXCEPTION_STATE64
#define MY_SEGMENT_CMD_TYPE LC_SEGMENT_64

#else

#define MY_THREAD_STATE_COUTE ARM_THREAD_STATE_COUNT
#define MY_THREAD_STATE ARM_THREAD_STATE
#define MY_EXCEPITON_STATE ARM_EXCEPTION_STATE
#define MY_EXCEPTION_STATE_COUNT ARM_EXCEPTION_STATE_COUNT
#define MY_SEGMENT_CMD_TYPE LC_SEGMENT

#endif

namespace RaftKit {

struct MachOImage{
    std::string name;
    std::string path;
    bool isSys;
    
    int cpuType;
    int cpuSubType;

    unsigned char uuid[16];

    vm_address_t loadAddr;
    vm_address_t endAddr;
};

typedef std::vector<MachOImage> MachOImageList;

struct MachOImageHelper {
    static const MachOImage& getAppImage();
    
    /// return true if address not system lib.
    static bool isAppAddress(const vm_address_t addr);
    
    /// if return MachOImage's name is null, mean not found.
    static const MachOImage& imageInfoForAddress(const vm_address_t addr);
    
    static const MachOImageList& getAllImageInfo();
    
    /// save and read images info.
    static bool writeAllImageInfoToFile(const char* filepath);
    static MachOImageList readImageInfoFromFile(const char* filepath);
    static MachOImage imageForAddressFromImageList(vm_address_t addr, const MachOImageList& imageList);
};

/*!
 * Get Arch Name with cputype and cpusubtype.
 */
const char* archName(uint32_t cputype, uint32_t cpusubtype);

/**
 * Get stack frame description.
 */
NSString* stackFrameDescription(vm_address_t addr, int index);
NSString* stackFrameDescriptionFromImageList(vm_address_t addr, int index, const MachOImageList& imageList);

}

#endif /* #ifdef __cplusplus */
#endif /*_RFKT_MACHO_IMAGE_HELPER_H_*/
