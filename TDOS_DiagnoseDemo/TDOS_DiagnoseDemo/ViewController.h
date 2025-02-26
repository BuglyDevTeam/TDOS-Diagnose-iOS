//
//  ViewController.h
//  TDOS_DiagnoseDemo
//
//  Created by Hongbo Cui on 2025/2/25.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

/// 诊断触发事件输入框
@property (weak, nonatomic) IBOutlet UITextField *guidTextField;
/// 染色信息Label
@property (weak, nonatomic) IBOutlet UILabel *colorLabel;

@end

