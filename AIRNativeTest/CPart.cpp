//
//  CPart.cpp
//  AIRNativeTest
//
//  Created by HanJuhyeun on 2016. 9. 29..
//  Copyright © 2016년 SK planet. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "CPart.hpp"

// Symbols tagged with EXPORT are externally visible.
// Must use the -fvisibility=hidden gcc option.
#define EXPORT __attribute__((visibility("default")))

extern "C" {
    FREObject nativeTest1(FREContext ctx, void* functionData, uint32_t argc, FREObject argv[]) {
        FREObject strResult;
        const char* msg = "[Native Code]: Hello World!";
        FRENewObjectFromUTF8( strlen(msg) + 1, (const uint8_t *) msg, &strResult );
        return strResult;
    }
    
    FREObject nativeTest2(FREContext ctx, void* functionData, uint32_t argc, FREObject argv[]) {
        uint32_t length;
        const uint8_t* value;
        FREGetObjectAsUTF8( argv[0], &length, &value );
        
        FREObject strResult;
        FRENewObjectFromUTF8(length, value, &strResult);
        return strResult;
    }
    
    FRENamedFunction nativeMethods[] = {
        { (const uint8_t*) "test1", 0, nativeTest1 },
        { (const uint8_t*) "test2", 0, nativeTest2 }
    };
    
    void MyExtensionContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToSet, const FRENamedFunction** functionsToSet) {
        *numFunctionsToSet = sizeof(nativeMethods) / sizeof(FRENamedFunction);
        *functionsToSet = nativeMethods;
    }
    
    void MyExtensionContextFinalizer(FREContext ctx) {
        
    }
    
    EXPORT void MyExtensionInitializer(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet) {
        *ctxInitializerToSet = &MyExtensionContextInitializer;
        *ctxFinalizerToSet = &MyExtensionContextFinalizer;
    }
    
    EXPORT void MyExtensionFinalizer(void* extData) {
        return;
    }
}
