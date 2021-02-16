rm -rf install
mkdir install
# install all the neccessary files to ship your library and share it it others
#cp -r ./include/ ./install/include/
rm -rf build
mkdir build
cd build
cmake ..
make -j4
make install
#make install