#!/usr/bin/bash

TARGET="Debug"
#TARGET="Release"

BINARY="db_test"

cd build

echo "compile ${TARGET} mode"
cmake -B . -S ../src -DCMAKE_BUILD_TYPE=${TARGET}

if [[ $TARGET == "Release" ]]; then
    
    #echo "create AppImage"
    #mkdir -p ./Packaging/AppDir/usr/bin/
    #cp ${BINARY} ./Packaging/AppDir/usr/bin/.
    #./linuxdeploy-plugin-appimage-x86_64.appimage --appdir ./Packaging/AppDir
    #sha256sum ${BINARY}-x86_64.AppImage > ${BINARY}-x86_64.AppImage.sha256sum
    
    echo "create SBoM"
    cd .. 
    nvm use --lts
    /home/zb_bamboo/Downloads/bin/atom -J-Xmx16g usages -o app.atom --slice-outfile ./build/Packaging/atom_usages_v0.0.0.json -l cpp ./src
    cdxgen -o ./build/Packaging/sbom_v0.0.0.json -t cpp --usages-slices-file ./build/Packaging/atom_usages_v0.0.0.json --author "ZHENG Robert" --deep -r ./src

    cd build
else
    echo "compile Debug mode"
fi

cmake --build . --parallel 6

echo "Done $TARGET"

#./crow_web static/crow_web.ini


#clear
