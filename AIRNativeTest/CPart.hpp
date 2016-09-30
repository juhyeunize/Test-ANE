//
//  CPart.hpp
//  AIRNativeTest
//
//  Created by HanJuhyeun on 2016. 9. 29..
//  Copyright © 2016년 SK planet. All rights reserved.
//

#ifndef CPart_hpp
#define CPart_hpp

#include <stdio.h>
#include <Adobe AIR/FlashRuntimeExtensions.h>

extern "C" {
    FREObject nativeTest1(FREContext ctx, void* functionData, uint32_t argc, FREObject argv[]);
    FREObject nativeTest2(FREContext ctx, void* functionData, uint32_t argc, FREObject argv[]);
    
    void MyExtensionContextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctionsToSet, const FRENamedFunction** functionsToSet);
    void MyExtensionContextFinalizer(FREContext ctx);
    void MyExtensionInitializer(void** extDataToSet, FREContextInitializer* ctxInitializerToSet, FREContextFinalizer* ctxFinalizerToSet);
    void MyExtensionFinalizer(void* extData);    
}


#endif /* CPart_hpp */
