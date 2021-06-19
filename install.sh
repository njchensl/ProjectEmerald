if [[ -d build ]]
then
    rm -rf build
fi

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -G"Xcode" .. -DVCPKG_TARGET_TRIPLET=x64-osx -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
