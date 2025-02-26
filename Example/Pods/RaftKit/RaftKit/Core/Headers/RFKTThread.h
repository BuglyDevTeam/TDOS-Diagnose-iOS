//
//  RFKTThread.h
//  RMonitor
//
//  Created by eYeYuna on 14/12/4.
//

#import <Foundation/Foundation.h>
#include <mach/mach_types.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/// mach_thread_self 和 mach_port_deallocate 成对调用
/// 建议使用pthread_mach_thread_np(pthread_self())
/// https://codereview.chromium.org/276043002/
__attribute__((always_inline)) static inline mach_port_t rm_mach_thread_self(void) {
    return pthread_mach_thread_np(pthread_self());
}

#ifdef __cplusplus
}  // extern "C"
#endif

typedef void (^RFKTThreadTask)(void);

@protocol RFKTThreadProtocol <NSObject>

- (void)doBlock:(RFKTThreadTask)task;

@end

/// NSThread封装类
@interface RFKTThread : NSThread <RFKTThreadProtocol>

+ (RFKTThread *)defaultWorkThread;
- (void)asyncWork:(RFKTThreadTask)task;
- (void)syncWork:(RFKTThreadTask)task;
- (NSRunLoop*)runloop;
- (thread_t)threadPort;
- (void)stop;

@end
