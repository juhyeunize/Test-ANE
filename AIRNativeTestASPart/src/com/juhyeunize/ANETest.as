package com.juhyeunize {
import flash.external.ExtensionContext;

public class ANETest {
    private var _extensionContext:ExtensionContext;

    public function ANETest() {
        _extensionContext = ExtensionContext.createExtensionContext("com.juhyeunize.ANETest", "");
    }

    public function test1():void {
        _extensionContext.call("test1");
    }

    public function test2():String {
        var result:String = _extensionContext.call("test2", "paramValue") as String;
        return result;
    }
}
}
