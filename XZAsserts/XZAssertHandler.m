//
//  Created by Felipe Cypriano on 10/05/13.
//  Copyright (c) 2013 Felipe Cypriano. All rights reserved.
//


#import "XZAssertHandler.h"

#ifndef XZAssertLog
#define XZAssertLog NSLog
#endif

#ifdef NS_BLOCK_ASSERTIONS
#define __FCYShouldAbort NO
#else
#define __FCYShouldAbort YES
#endif

NSString *const XZAssertErrorDomain = @"XZAssert";
NSString *const XZAssertExceptionName = @"XZAssertException";
	
@interface XZAssertHandler ()
@property (nonatomic) BOOL shouldRaiseWhenConditionFail;
@end

@implementation XZAssertHandler {

}

+ (XZAssertHandler *)handler {
    static XZAssertHandler *sharedHandler;
    static dispatch_once_t token;
    dispatch_once(&token, ^{
        sharedHandler = [[XZAssertHandler alloc] init];
    });
    return sharedHandler;
}

- (id)init {
    self = [super init];
    if (self) {
        self.shouldRaiseWhenConditionFail = __FCYShouldAbort;
    }
    return self;
}

- (void)assertFailureWithExpression:(NSString *)expression function:(NSString *)function file:(NSString *)file line:(NSInteger)line description:(NSString *)format, ... {
	if (format) {
		va_list args;
		va_start(args, format);
		NSString *trueFormat = va_arg(args, NSString*);
		[self _assertFailureShouldAbort:YES withExpression:expression function:function file:file line:line description:trueFormat arguments:args];
		va_end(args);
	}
	else{
		[self _assertFailureShouldAbort:YES withExpression:expression function:function file:file line:line description:nil arguments:nil];
	}
}

- (void)assertFailureOrReturnWithExpression:(NSString *)expression function:(NSString *)function file:(NSString *)file line:(NSInteger)line description:(NSString *)format, ... {
	if (format) {
		va_list args;
		va_start(args, format);
		NSString *trueFormat = va_arg(args, NSString*);
		[self _assertFailureShouldAbort:self.shouldRaiseWhenConditionFail withExpression:expression function:function file:file line:line description:trueFormat arguments:args];
		va_end(args);
	}
	else{
		[self _assertFailureShouldAbort:self.shouldRaiseWhenConditionFail withExpression:expression function:function file:file line:line description:nil arguments:nil];
	}
}

- (void)assertFailureOrReturnBlock:(XZAssertReturnBlock)returnBlock withExpression:(NSString *)expression function:(NSString *)function file:(NSString *)file line:(NSInteger)line description:(NSString *)description {
    [self _assertFailureShouldAbort:self.shouldRaiseWhenConditionFail withExpression:expression function:function file:file line:line description:description arguments:NULL];

    NSError *error = [NSError errorWithDomain:XZAssertErrorDomain
                                         code:0
                                     userInfo:@{ NSLocalizedDescriptionKey : description }];
    returnBlock(error);
}


#pragma mark - Private Methods

- (NSString *)_assertFailureShouldAbort:(BOOL)shouldAbort withExpression:(NSString *)expression function:(NSString *)function file:(NSString *)file line:(NSInteger)line description:(NSString *)format arguments:(va_list)args {
    NSString *description = @"";
    if (format && args) {
        description = [[NSString alloc] initWithFormat:format arguments:args];
    }
	if (expression.length) {
		XZAssertLog(@"%@: Assertion '%@' failed on line %@:%ld. %@", function, expression, file, (long) line, description);
	}
	else{
		XZAssertLog(@"%@: Always assert triggered on line %@:%ld. %@", function, file, (long) line, description);
	}
    
    if (shouldAbort) {
        NSString *reason = expression.length ? [NSString stringWithFormat:@"Assertion '%@' failed. %@", expression, description] : [NSString stringWithFormat:@"Always assert triggered. %@", description];
        [[NSException exceptionWithName:XZAssertExceptionName reason:reason userInfo:nil] raise];
    }
    return expression.length ? [NSString stringWithFormat:@"%@: Assertion '%@' failed on line %@:%ld. %@", function, expression, file, (long) line, description] :  [NSString stringWithFormat:@"%@: Always asserter triggered on line %@:%ld. %@", function, file, (long) line, description];
}

@end