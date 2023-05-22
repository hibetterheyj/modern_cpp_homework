# Homework 8

## PPM files

The file format known as “plain PPM” , which stands for “Portable Pixel Map”, is
a text-based image format for color images. PPM files normally have the
extension `.ppm`.

### Here is an example of a PPM file

```txt
P3
# A diagonal black line over a 5x5 white image
5 5
255
0 0 0        255 255 255  255 255 255  255 255 255  255 255 255
255 255 255  0 0 0        255 255 255  255 255 255  255 255 255
255 255 255  255 255 255  0 0 0        255 255 255  255 255 255
255 255 255  255 255 255  255 255 255  0 0 0        255 255 255
255 255 255  255 255 255  255 255 255  255 255 255  0 0 0
```

An image is represented by triples of grayscale values for each pixel. The
values range from 0 for black, up to some fixed maximum for white (255 is a
        common choice).

### The file is organized as follows

1. The string “P3” (defines color image) followed by whitespace.
2. The width followed by whitespace.
3. The height followed by whitespace.
4. The maximum (white) grayscale value, followed by whitespace.
5. Lines containing (3 \* width) x (3 \* height) numbers representing the pixel
color values in R G B order, starting with the first row, separated by
whitespace. Note that the pixel values for a given row are not required to be
on a single line, and the spec recommends a maximum of 70 characters per
line. In addition, comments may appear among items 2, 3, or 4, where any line
starting with a pound sign (“#”) is a comment.

### Png images

We use a library to work with png images. To work with it, install `libpng++`:

```sh
sudo apt install libpng++-dev
```
