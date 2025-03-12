#!/usr/bin/bash

TARGET="Debug"
#TARGET="Release"

BINARY="db_test"

cd build

echo "compile ${TARGET} mode"
cmake -B . -S ../src -DCMAKE_BUILD_TYPE=${TARGET}

if [[ $TARGET == "Release" ]]; then
    
    echo "create AppImage"
    mkdir -p ./AppDir/usr/bin/
    cp ${BINARY} ./AppDir/usr/bin/.
    ./linuxdeploy-plugin-appimage-x86_64.appimage --appdir ./AppDir
    sha256sum ${BINARY}-x86_64.AppImage > ${BINARY}-x86_64.AppImage.sha256sum

    echo "create deb package"
    cp ${BINARY} ./${BINARY}/${BINARY}/usr/bin/.
    dpkg-deb --build ${BINARY}
    mv ${BINARY}.deb ${BINARY}-x86_64.deb
    sha256sum ${BINARY}-x86_64.deb > ${BINARY}-x86_64.deb.sha256sum
    
    echo "create SBoM"
    mkdir ./sbom
    nvm use --lts
    mkdir dist
    /home/zb_bamboo/Downloads/bin/atom -J-Xmx16g usages -o app.atom --slice-outfile ./sbom/atom_usages_v0.1.0.json -l cpp ../src
    cdxgen -o ./sbom/sbom_v0.1.0.json -t cpp --usages-slices-file ./sbom/atom_usages_v0.1.0.json --author "ZHENG Robert" --deep -r ../src
else
    echo "compile Debug mode"
fi

cmake --build . --parallel 6

echo "Done $TARGET"

#./crow_web static/crow_web.ini


#clear
