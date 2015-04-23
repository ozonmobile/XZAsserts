//
//  Created by Felipe Cypriano on 10/05/13.
//  Copyright (c) 2013 Felipe Cypriano. All rights reserved.
//


#import <Foundation/Foundation.h>

#define PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
_Pragma("clang diagnostic push"); \
_Pragma("clang diagnostic ignored \"-Wall\"");

#define PRAGMA_POP_DIAGNOSTIC \
_Pragma("clang diagnostic pop")

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