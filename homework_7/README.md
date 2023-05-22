# Build a Codebook using k-means
## Overview 

One of the goals is implementing the $k$-means algorithm for [SIFT](https://medium.com/data-breach/introduction-to-sift-scale-invariant-feature-transform-65d7f3a72d40) features in order to find the $k$ most representative features also called "centroids".


[image_0]: docs/kmeans.png
![alt text][image_0] 

The last goal is implementing a class describing the `Bag of Visual Words Dictionary`. This class must be a singleton. 

## Project Files

The project include the following source files:

* [k-means implementation](src/codebook.cpp)
* [bag of visual words dictionary](src/bow_dictionary.cpp)

The matching header files are:

* [k-means implementation](include/codebook.h)
* [bag of visual words dictionary](include/bow_dictionary.h)

## Running k-means
* Make a dir named `build`
```
cd build

cmake ..

make 
```

```
.\kmeans
```
For testing $k-means$ with new data change $codebook$ source file. There are already a few examples there.


## References
* [Introduction on Bag of Visual Words](https://www.youtube.com/watch?v=a4cFONdc6nc)
* [Homework description: steps to code above implementation](/./homework_7.pdf)