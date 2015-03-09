//
//  Created by Felipe Cypriano on 05/10/13.
//  Copyright (c) 2013 Felipe Cypriano. All rights reserved.
//

#import "XZAssertHandler.h"

/// ---------------
/// @name XZAssert
/// ---------------

#define XZAssert(_condition, ...) \
    do { \
        if (!(_condition)) { \
			if(sizeof(#__VA_ARGS__) == sizeof("")){ \
				[[XZAssertHandler handler] assertFailureWithExpression:[NSString stringWithUTF8String:#_condition] \
												   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
													   file:[NSString stringWithUTF8String:__FILE__] \
													   line: __LINE__ \
												description:nil]; \
			} \
			else{ \
				[[XZAssertHandler handler] assertFailureWithExpression:[NSString stringWithUTF8String:#_condition] \
															   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
																   file:[NSString stringWithUTF8String:__FILE__] \
																   line: __LINE__ \
															description:(@""), ##__VA_ARGS__]; \
			} \
        } \
    } while(0)

#define XZAlwaysAssert(...) \
	do { \
		if(sizeof(#__VA_ARGS__) == sizeof("")){ \
			[[XZAssertHandler handler] assertFailureWithExpression:@"" \
														   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
															   file:[NSString stringWithUTF8String:__FILE__] \
															   line: __LINE__ \
														description:nil]; \
		} \
		else{ \
			[[XZAssertHandler handler] assertFailureWithExpression:@"" \
														   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
															   file:[NSString stringWithUTF8String:__FILE__] \
															   line: __LINE__ \
														description:(@""), ##__VA_ARGS__]; \
		} \
	} while(0)

#define XZAssertParameterNotNil(_paramName) XZAssert((_paramName), @"Invalid parameter '%s'. Must not be nil.", #_paramName)
#define XZAssertNotNil(_varName) XZAssert((_varName), @"Variable '%s' must not be nil.", #_varName)

#define XZAssertIsInMainThread XZAssert(([NSThread isMainThread]), @"This should be running on the main thread.")
#define XZAssertIsNotInMainThread XZAssert((![NSThread isMainThread]), @"This should not be running on the main thread.")
#define XZAssertMethodIsNotImplemented FCYAlwaysAssert( @"%@ method is not implemented in %@", NSStringFromSelector(_cmd), NSStringFromClass([self class]));

/// -----------------------
/// @name XZAssertOrReturn
/// -----------------------

#define XZAssertOrReturn(_condition, ...) \
	do { if (!(_condition)) { \
			if(sizeof(#__VA_ARGS__) == sizeof("")){ \
				[[XZAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
												   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
													   file:[NSString stringWithUTF8String:__FILE__] \
													   line: __LINE__ \
												description:nil]; \
			} \
			else { \
				[[XZAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
										function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
											file:[NSString stringWithUTF8String:__FILE__] \
																		   line: __LINE__ \
																	description:(@""), ##__VA_ARGS__]; \
			} \
        return; \
    } } while(0)

#define FCYAssertOrContinue(_condition, ...) \
    if (!(_condition)) { \
        if(sizeof(#__VA_ARGS__) == sizeof("")){ \
            [[FCYAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
                                                                function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                                                                file:[NSString stringWithUTF8String:__FILE__] \
                                                                line: __LINE__ \
                                                                description:nil]; \
            } \
        else { \
            [[FCYAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
                                                                function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                                                                file:[NSString stringWithUTF8String:__FILE__] \
                                                                line: __LINE__ \
                                                                description:(@""), ##__VA_ARGS__]; \
        }; \
    continue; \
} \

#define XZAssertOrReturnNil(_condition, ...) \
    do { if (!(_condition)) { \
			if(sizeof(#__VA_ARGS__) == sizeof("")){ \
				[[XZAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
																	   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
																		   file:[NSString stringWithUTF8String:__FILE__] \
																		   line: __LINE__ \
																	description:nil]; \
			} \
			else { \
				[[XZAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
																	   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
																		   file:[NSString stringWithUTF8String:__FILE__] \
																		   line: __LINE__ \
																	description:(@""), ##__VA_ARGS__]; \
			} \
        return nil; \
    } } while(0)

#define XZAssertOrReturnZero(_condition, ...) \
	do { if (!(_condition)) { \
		if(sizeof(#__VA_ARGS__) == sizeof("")){ \
			[[XZAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
																   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
																	   file:[NSString stringWithUTF8String:__FILE__] \
																	   line: __LINE__ \
																description:nil]; \
		} \
		else { \
			[[XZAssertHandler handler] assertFailureOrReturnWithExpression:[NSString stringWithUTF8String:#_condition] \
																   function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
																	   file:[NSString stringWithUTF8String:__FILE__] \
																	   line: __LINE__ \
																description:(@""), ##__VA_ARGS__]; \
		} \
		return 0; \
	} } while(0)

#define XZAssertOrReturnBlock(_condition, _desc, _block) \
    do { if (!(_condition)) { \
        [[XZAssertHandler handler] assertFailureOrReturnBlock:(_block) \
                withExpression:[NSString stringWithUTF8String:#_condition] \
                      function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                          file:[NSString stringWithUTF8String:__FILE__] \
                          line:__LINE__ \
                   description:(_desc)]; \
        return; \
    } } while(0)

#define XZAssertOrReturnNilBlock(_condition, _desc, _block) \
    do { if (!(_condition)) { \
        [[XZAssertHandler handler] assertFailureOrReturnBlock:(_block) \
                withExpression:[NSString stringWithUTF8String:#_condition] \
                      function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                          file:[NSString stringWithUTF8String:__FILE__] \
                          line:__LINE__ \
                   description:(_desc)]; \
        return nil; \
    } } while(0)

#define XZAssertOrReturnZeroBlock(_condition, _desc, _block) \
	do { if (!(_condition)) { \
			[[XZAssertHandler handler] assertFailureOrReturnBlock:(_block) \
													withExpression:[NSString stringWithUTF8String:#_condition] \
														  function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
															  file:[NSString stringWithUTF8String:__FILE__] \
															  line:__LINE__ \
													   description:(_desc)]; \
		return 0; \
	} } while(0)
