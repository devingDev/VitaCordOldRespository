rm -rf build
mkdir build
cd build
cmake ..
make -j64
cd ..

#not working >_>
#7z a -tzip build/vita_cord.vpk -r assets/emoji/*

#works :D

#echo "packing assets into vpk"
#7z a build/vita_cord.vpk assets/

#echo ""
echo "Finished vpk! ;-)"


