//
//  Created by Felipe Cypriano on 05/10/13.
//  Copyright (c) 2013 Felipe Cypriano. All rights reserved.
//

#import "XZAssertHandler.h"

/// ---------------
/// @name XZAssert
/// ---------------

#define XZAssert(_condition, ...) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
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
    } while(0) \
PRAGMA_POP_DIAGNOSTIC

#define XZAlwaysAssert(...) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
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
	} while(0) \
PRAGMA_POP_DIAGNOSTIC

#define XZAssertParameterNotNil(_paramName) XZAssert((_paramName), @"Invalid parameter '%s'. Must not be nil.", #_paramName)
#define XZAssertNotNil(_varName) XZAssert((_varName), @"Variable '%s' must not be nil.", #_varName)

#define XZAssertIsInMainThread XZAssert(([NSThread isMainThread]), @"This should be running on the main thread.")
#define XZAssertIsNotInMainThread XZAssert((![NSThread isMainThread]), @"This should not be running on the main thread.")
#define XZAssertMethodIsNotImplemented FCYAlwaysAssert( @"%@ method is not implemented in %@", NSStringFromSelector(_cmd), NSStringFromClass([self class]));

/// -----------------------
/// @name XZAssertOrReturn
/// -----------------------

#define XZAssertOrReturn(_condition, ...) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
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
    } } while(0) \
PRAGMA_POP_DIAGNOSTIC

#define FCYAssertOrContinue(_condition, ...) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
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
PRAGMA_POP_DIAGNOSTIC

#define XZAssertOrReturnNil(_condition, ...) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
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
    } } while(0) \
PRAGMA_POP_DIAGNOSTIC

#define XZAssertOrReturnZero(_condition, ...) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
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
	} } while(0) \
PRAGMA_POP_DIAGNOSTIC

#define XZAssertOrReturnBlock(_condition, _desc, _block) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
    do { if (!(_condition)) { \
        [[XZAssertHandler handler] assertFailureOrReturnBlock:(_block) \
                withExpression:[NSString stringWithUTF8String:#_condition] \
                      function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                          file:[NSString stringWithUTF8String:__FILE__] \
                          line:__LINE__ \
                   description:(_desc)]; \
        return; \
    } } while(0) \
PRAGMA_POP_DIAGNOSTIC

#define XZAssertOrReturnNilBlock(_condition, _desc, _block) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
    do { if (!(_condition)) { \
        [[XZAssertHandler handler] assertFailureOrReturnBlock:(_block) \
                withExpression:[NSString stringWithUTF8String:#_condition] \
                      function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
                          file:[NSString stringWithUTF8String:__FILE__] \
                          line:__LINE__ \
                   description:(_desc)]; \
        return nil; \
    } } while(0) \
PRAGMA_POP_DIAGNOSTIC

#define XZAssertOrReturnZeroBlock(_condition, _desc, _block) \
PRAGMA_PUSH_DIAGNOSTIC_AND_IGNORE_ALL_WARNINGS \
	do { if (!(_condition)) { \
			[[XZAssertHandler handler] assertFailureOrReturnBlock:(_block) \
													withExpression:[NSString stringWithUTF8String:#_condition] \
														  function:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] \
															  file:[NSString stringWithUTF8String:__FILE__] \
															  line:__LINE__ \
													   description:(_desc)]; \
		return 0; \
	} } while(0) \
PRAGMA_POP_DIAGNOSTIC
