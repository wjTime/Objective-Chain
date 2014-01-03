//
//  OCAStructureAccessor.h
//  Objective-Chain
//
//  Created by Martin Kiss on 3.1.14.
//  Copyright (c) 2014 Martin Kiss. All rights reserved.
//

#import "OCAObject.h"
#import "NSValue+Boxing.h"





@interface OCAStructureAccessor : OCAObject



- (instancetype)initWithStructType:(const char *)structType
                        memberType:(const char *)memberType
                          getBlock:(NSValue *(^)(NSValue *structValue))getBlock
                          setBlock:(NSValue *(^)(NSValue *structValue, NSValue *memberValue))setBlock;

@property (OCA_atomic, readonly, assign) const char *structType;
@property (OCA_atomic, readonly, assign) const char *memberType;

@property (OCA_atomic, readonly, assign) BOOL isNumeric;

@property (OCA_atomic, readonly, assign) NSString *structureDescription;
@property (OCA_atomic, readonly, assign) NSString *memberDescription;
- (instancetype)describeStructure:(NSString *)structure member:(NSString *)member;


- (NSValue *)memberFromStructure:(NSValue *)structValue;
- (NSValue *)setMember:(NSValue *)memberValue toStructure:(NSValue *)structValue;



@end





#define OCAStruct(STRUCT, MEMBER) \
\
(OCAStructureAccessor *)({ \
    STRUCT s; \
    const char *structType = @encode(STRUCT); \
    const char *memberType = @encode(typeof(s.MEMBER)); \
    [[[OCAStructureAccessor alloc] initWithStructType:structType memberType:memberType getBlock:^NSValue *(NSValue *structValue) { \
        typeof(s) structure; \
        BOOL unboxed = [structValue unboxValue:&structure objCType:structType]; \
        if ( ! unboxed) return nil; \
        typeof(s.MEMBER) member = structure.MEMBER; \
        return [NSValue boxValue:&member objCType:memberType]; \
    } setBlock:^NSValue *(NSValue *structValue, NSValue *memberValue) { \
        typeof(s) structure; \
        BOOL structUnboxed = [structValue unboxValue:&structure objCType:structType]; \
        if ( ! structUnboxed) return nil; \
        typeof(s.MEMBER) member; \
        BOOL memberUnboxed = [memberValue unboxValue:&member objCType:memberType]; \
        if ( ! memberUnboxed) return nil; \
        structure.MEMBER = member; \
        return [NSValue valueWithBytes:&structure objCType:structType]; \
    }] describeStructure:@#STRUCT member:@#MEMBER]; \
}) \


inline NSValue *_OCAStructureAccessorGetBlockExample(NSValue *structValue) {
    CGRect s;
    const char *structType = @encode(typeof(s));
    const char *memberType = @encode(typeof(s.origin.x));
    
    
    typeof(s) structure;
    BOOL unboxed = [structValue unboxValue:&structure objCType:structType];
    if ( ! unboxed) return nil;
    
    typeof(s.origin.x) member = structure.origin.x;
    return [NSValue boxValue:&member objCType:memberType];
}


inline NSValue *_OCAStructureAccessorSetBlockExample(NSValue *structValue, NSValue *memberValue) {
    CGRect s;
    const char *structType = @encode(typeof(s));
    const char *memberType = @encode(typeof(s.origin.x));
    
    
    typeof(s) structure;
    BOOL structUnboxed = [structValue unboxValue:&structure objCType:structType];
    if ( ! structUnboxed) return nil;
    
    typeof(s.origin.x) member;
    BOOL memberUnboxed = [memberValue unboxValue:&member objCType:memberType];
    if ( ! memberUnboxed) return nil;
    structure.origin.x = member;
    return [NSValue valueWithBytes:&structure objCType:structType];
}

