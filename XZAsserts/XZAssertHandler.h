//
//  Created by Felipe Cypriano on 10/05/13.
//  Copyright (c) 2013 Felipe Cypriano. All rights reserved.
//


#import <Foundation/Foundation.h>

typedef void(^XZAssertReturnBlock)(NSError *);

extern NSString *const XZAssertErrorDomain;
extern NSString *const XZAssertExceptionName;

@interface XZAssertHandler : NSObject

+ (XZAssertHandler *)handler;

- (void)assertFailureWithExpression:(NSString *)expression
                           function:(NSString *)function
                               file:(NSString *)file
                               line:(NSInteger)line
                        description:(NSString *)format, ...;

- (void)assertFailureOrReturnWithExpression:(NSString *)expression
                                   function:(NSString *)function
                                       file:(NSString *)file
                                       line:(NSInteger)line
                                description:(NSString *)format, ...;

- (void)assertFailureOrReturnBlock:(XZAssertReturnBlock)returnBlock
                    withExpression:(NSString *)expression
                          function:(NSString *)function
                              file:(NSString *)file
                              line:(NSInteger)line
                       description:(NSString *)description;

@end