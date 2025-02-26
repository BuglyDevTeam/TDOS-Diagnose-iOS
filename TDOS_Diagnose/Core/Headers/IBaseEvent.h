//
//  IBaseEvent.h
//
//  Created by RAFT on 2021/5/10.
//

#ifndef IBaseEvent_h
#define IBaseEvent_h
@protocol IBaseEvent <NSObject>

@property(nonatomic, assign)BOOL isSuccess;
@property(nonatomic, strong)NSString *code;
@property(nonatomic, strong)NSString *key;
@property(nonatomic, strong)NSDictionary *dic;

@end
#endif /* IBaseEvent_h */
