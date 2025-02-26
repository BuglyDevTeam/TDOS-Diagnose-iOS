//
//  CThreadStack.h
//  Raft-Monitor
//
//  Created by 张鹏 on 4/23/15.
//  Copyright (c) 2015 eYe. All rights reserved.
//
#ifndef _RFKTC_THREAD_STACH_H_
#define _RFKTC_THREAD_STACH_H_

#ifdef __cplusplus

#import <Foundation/Foundation.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <mach/mach_types.h>
#include <mach/task.h>
#include <sys/_types/_sigaltstack.h>
#include <sys/_types/_ucontext.h>

namespace RaftKit {

#define MAX_STACK_DEEP  (512)

class CStackItem {
public:
    explicit CStackItem(vm_address_t addr);
    ~CStackItem();
    
    inline vm_address_t getAddr() const {return addr_;}
    inline void setAddr(vm_address_t addr) {
        addr_ = addr;
#ifdef __arm64__
#define MACH_VM_ADDRESS_MASK (0x0000000FFFFFFFF0)
#else
#define MACH_VM_ADDRESS_MASK (0x00007FFFFFFFFFF0)
#endif
#if __is_target_arch(x86_64) || __is_target_arch(arm64)
        addr_ &= MACH_VM_ADDRESS_MASK;
#endif
    }
    bool isAppCode() const;
    
private:
    vm_address_t addr_;
};

class CThreadStackFrame {
public:
    explicit CThreadStackFrame(std::vector<CStackItem> stackVec, std::string threadName);
    ~CThreadStackFrame();

    std::vector<CStackItem> stackVec;
    std::string threadName;
};

struct frame_data {
    uintptr_t frame_addr_next;
    uintptr_t ret_addr;
};

struct CThreadCursor {
    struct frame_data frame;
    _STRUCT_MCONTEXT _mcontext;
};

class CThreadStack {
public:
    CThreadStack();
    ~CThreadStack();
    
    CThreadStackFrame getThreadStack(thread_t thread);
    CThreadStackFrame getCurrentThreadStack();
    
private:
    bool initCursor(thread_t thread);
    void initCursor_internal_x86();
    void recordPC_x86();
    void recordPCLR_arm();
    bool nextCursor();
    void recordFrame();
    kern_return_t readFramePointer();
    
private:
    CThreadCursor m_cursor;
    CStackItem* m_pStack;
    unsigned int m_nStackCount;
};

class CThreadMonitor {
public:
    CThreadMonitor();
    ~CThreadMonitor();
    
    std::vector<CThreadStackFrame> getAllThreadStack();
    static CThreadStackFrame getThreadStack(thread_t thread);
    CThreadStackFrame getCurrentFrame(thread_t thread);
    
    static CThreadStackFrame getCurrentThreadStack();
    
private:
    CThreadStack m_stack;
};

} /* namespace RaftKit */

#endif /* __cplusplus */
#endif /*_RFKTC_THREAD_STACH_H_*/

