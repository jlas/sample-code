# lightdark

Replace light pixels in one image with pixels from a second image

![lightdark](https://raw.github.com/jlas/sample-code/master/dsp/lightdark/media/example.png)

## Usage

Convert images to .ppm format (e.g. using ImageMagick):

    convert image1.jpg image1.ppm
    convert image2.jpg image2.ppm

Run images through program:

    lightdark image1.ppm image2.ppm

Output will be written to `out.ppm`
