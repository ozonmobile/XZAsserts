#import "Kiwi.h"
#import "XZAsserts.h"

@interface XZAssertHandler ()
@property (nonatomic) BOOL shouldRaiseWhenConditionFail;
@end

SPEC_BEGIN(XZAssertsSpec)

describe(@"XZAsserts", ^{
    context(@"XZAssert", ^{
        it(@"raises XZAssertException when the condition is false", ^{
            NSString *expectedDescription = @"Assertion '1 == 2' failed. Obvious false condition indeed";
            [[theBlock(^{
                XZAssert(1 == 2, @"Obvious false condition %@", @"indeed");
            }) should] raiseWithName:XZAssertExceptionName reason:expectedDescription];
        });

        it(@"does not raise when the condition is true", ^{
            [[theBlock(^{
                XZAssert(1 == 1, @"Obvious true");
            }) shouldNot] raise];
        });
    });

    context(@"NS_BLOCK_ASSERTIONS is defined", ^{
        beforeAll(^{
            [XZAssertHandler handler].shouldRaiseWhenConditionFail = NO;
        });

        describe(@"XZAssertOrReturn", ^{
            it(@"never raises", ^{
                [[theBlock(^{
                    XZAssertOrReturn(2 == 1, @"Not even in this case");
                    [@"Should not get here. XZAssertOrReturn must return before" shouldBeNil];
                }) shouldNot] raise];
            });
        });

        describe(@"XZAssertOrReturnBlock", ^{
            it(@"never raises and calls the block", ^{
                [[theBlock(^{
                    XZAssertOrReturnBlock(3 == 8, @"Yep again", ^(NSError *error){
                        [[error should] beKindOfClass:[NSError class]];
                    });
                    [@"Should not get here. XZAssertOrReturn must return before" shouldBeNil];
                }) shouldNot] raise];
            });
        });
    });

    context(@"NS_BLOCK_ASSERTIONS is undefined", ^{
        beforeAll(^{
            [XZAssertHandler handler].shouldRaiseWhenConditionFail = YES;
        });

        describe(@"XZAssertOrReturn", ^{
            it(@"raises when condition is false", ^{
                [[theBlock(^{
                    XZAssertOrReturn(2 == 1, @"Obivous false");
                    [@"Should not get here. XZAssertOrReturn must return before" shouldBeNil];
                }) should] raiseWithName:XZAssertExceptionName];
            });
        });

        describe(@"XZAssertOrReturnBlock", ^{
            it(@"raises when condition is false and calls the block", ^{
                [[theBlock(^{
                    XZAssertOrReturnBlock(3 == 8, @"Yep again", ^(NSError *error){});
                    [@"Should not get here. XZAssertOrReturn must return before" shouldBeNil];
                }) should] raiseWithName:XZAssertExceptionName];
            });
        });
    });
});

SPEC_END
