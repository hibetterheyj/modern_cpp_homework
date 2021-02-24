# homework_3

```shell
mkdir build
cd build
cmake ..
make
cd ..
./bin/create_image_browser > test.html
```

## dependance

- ~~fmt: https://fmt.dev/latest/usage.html~~ (deprecated)

```shell
git clone https://github.com/fmtlib/fmt
cd fmt/
mkdir build
cd build
cmake -DBUILD_SHARED_LIBS=TRUE ...
make -j4
make test
sudo make install
```
