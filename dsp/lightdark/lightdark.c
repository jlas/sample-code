#include <stdio.h>
#include <stdlib.h>

#define NCOLOR 3

typedef struct Img {
  unsigned short width;
  unsigned short height;
  unsigned short max;
  unsigned char ** data;
} Img;

Img * read_data(const char * filename) {
  int i;
  int j[NCOLOR];
  int chan;
  int npixel;
  FILE * f = fopen(filename, "r");

  /**
   * .ppm meta data
   *   1 string is magic number / file type
   *   2 width
   *   3 height
   *   4 max color value (e.g. 255)
   */
  char meta[4][6];
  for(i = 0; i < 4; i++) {
    fscanf(f, "%s", meta[i]);
  }

  /* eat the final whitespace char */
  fseek(f, 1, SEEK_CUR);

  Img * img = malloc(sizeof(Img));
  img->width = atoi(meta[1]);
  img->height = atoi(meta[2]);
  img->max = atoi(meta[3]);
  npixel = img->width*img->height;

  /* allocate memory for pixel buffers */
  img->data = malloc(NCOLOR*sizeof(char *));
  for (i = 0; i < NCOLOR; i++) {
    j[i] = 0;  /* initialize indexing var for later */
    img->data[i] = malloc(npixel*sizeof(char));
  }

  /* read in pixel data, cycling through color channels */
  for (i = 0; i < NCOLOR*npixel; i++) {
    chan = (i)%NCOLOR;
    fscanf(f, "%c", &img->data[chan][j[chan]++]);
  }

  return img;
}

void write_data(const char * filename, Img * img) {
  int i;
  int j;
  FILE * f = fopen(filename, "w");

  /* write header, hardcode P6 format */
  fprintf(f, "P6 %hu %hu %hu ", img->width, img->height, img->max);

  for (i = 0; i < img->width*img->height; i++) {
    for (j = 0; j < NCOLOR; j++) {
      fprintf(f, "%c", img->data[j][i]);
    }
  }
}

void cleanup(Img * img) {
  int i;
  for (i = 0; i < NCOLOR; i++) {
    free(img->data[i]);
  }
  free(img);
}

/**
 * Combine two images so that the lighter pixels from one image is replaced with
 * pixels from the second image. The lightness is tested according to a
 * threshold value (0-1) where 1 means only a completely white pixel will be
 * replaced. This function modifies and places the result in img1's pixel
 * buffer.
 */
void combine(Img * img1, Img * img2, float threshold) {
  if (img1->height != img2->height ||
      img1->width != img2->width ||
      img1->max != img2->max) {
    printf("ERROR: Images must have identical height, width, & max color vals\n");
    return;
  }

  int i;
  int j;
  int intensity;
  int npixel = img1->width*img1->height;

  for (i = 0; i < npixel; i++) {
    intensity = 0;
    for (j = 0; j < NCOLOR; j++) {
      intensity += img1->data[j][i];
    }
    if ((intensity / 3.0) > threshold*img1->max) {
      for (j = 0; j < NCOLOR; j++) {
        img1->data[j][i] = img2->data[j][i];
      }
    }
  }
}

void usage(char * execname) {
  printf( "usage: %s file1 file2 [threshold]\n", execname);
}

int main(int argc, char * argv[]) {
  float threshold = 0.8;

  if (argc < 3) {
    usage(argv[0]);
    return 1;
  }

  if (argc == 4) {
    threshold = atof(argv[3]);
  }

  Img * img1 = read_data(argv[1]);
  Img * img2 = read_data(argv[2]);

  combine(img1, img2, threshold);
  write_data("out.ppm", img1);

  cleanup(img1);
  cleanup(img2);

  return 0;
}
