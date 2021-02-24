# homework_1

## task_1

```shell
cd task_1
chmod +x commands.sh
./commands.sh
```

## task_2

- part1

  ```shell
  cd task_2
  chmod +x build.sh
  ./build.sh
  
  ./results/yujie_example 
  #The sum of 1+2 = 3
  #The sub of 1-2 = -1
  ```

- part2

  ```shell
  cd task_2
  chmod +x install.sh
  ./install.sh
  
  tree
  ```

  The results can be shown as follows

  ```
  ├── ...
  ├── build.sh
  ├── CMakeLists.txt
  ├── include
  │   ├── ipb_arithmetic
  │   │   ├── subtract.hpp
  │   │   └── sum.hpp
  │   └── ipb_arithmetic.hpp
  ├── install
  │   ├── include
  │   │   ├── ipb_arithmetic
  │   │   │   ├── subtract.hpp
  │   │   │   └── sum.hpp
  │   │   └── ipb_arithmetic.hpp
  │   └── lib
  │       └── libipb_arithmetic.a
  ├── install.sh
  ├── results
  │   ├── bin
  │   │   └── example_output
  │   ├── lib
  │   │   └── libipb_arithmetic.a
  │   └── yujie_example
  └── src
      ├── main.cpp
      ├── subtract.cpp
      └── sum.cpp
  ```

  