#!/bin/sh

AIR_SDK=~/Development/Frameworks/AIRSDK_Compiler/23
XCODEBUILD=/usr/bin/xcodebuild

echo "====== [Step 1] Build SWC ======"
pushd AIRNativeTestASPart
rm -f out/production/ANETest/ANETest.swc
"$AIR_SDK"/bin/acompc -source-path src -include-classes	com.juhyeunize.ANETest -output=out/production/ANETest/ANETest.swc
popd

echo "====== [Step 2] Build Native C ======"
pushd AIRNativeTest
rm -f build/Release/ANETest.framework
"$XCODEBUILD" -project AIRNativeTest.xcodeproj -configuration Release -arch x86_64 clean build
popd

echo "====== [Step 3] Build ANE ======"
rm -f ./ANE/Test.ane
rm -f ./ANE/swc/ANETest.swc
rm -rf ./ANE/swc/swc-assets

cp "./AIRNativeTestASPart/out/production/ANETest/ANETest.swc" ./ANE/swc
mkdir -p ANE/swc/swc-assets
pushd ANE/swc/swc-assets
jar xf ../ANETest.swc 
popd

rm -rf ./ANE/platform/mac
mkdir ./ANE/platform/mac
cp -R "./AIRNativeTest/build/Release/ANETest.framework" ./ANE/platform/mac
cp "./ANE/swc/swc-assets/library.swf" ./ANE/platform/mac

pushd ANE
"$AIR_SDK"/bin/adt -package -target ane Test.ane extension.xml -swc swc/ANETest.swc -platform MacOS-x86-64 -C platform/mac ANETest.framework library.swf
popd

echo "====== [Step 4] Execute Demo ======="
rm -f ./Demo/out/production/Demo/Test.ane
cp ./ANE/Test.ane ./Demo/out/production/Demo/

rm -rf ./Demo/out/production/Demo/ane-assets
mkdir -p ./Demo/out/production/Demo/ane-assets/Test.ane
pushd ./Demo/out/production/Demo/ane-assets/Test.ane
jar xf ../../Test.ane
popd

pushd ./Demo/out/production/Demo
"$AIR_SDK"/bin/adl -profile extendedDesktop -extdir ./ane-assets Main-descriptor.xml .
popd