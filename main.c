/* lib_ppm.h */
struct pixel_s {
    unsigned char r, g, b;
};

struct image_s {
    int width;
    int height;
    struct pixel_s *pix;
};

int read_ppm(char *file, struct image_s *image);
int write_ppm(char *file, struct image_s *image);
int free_ppm(struct image_s *image);
/* exemplo */

int main(void){
    struct image_s data;
struct image_s *image = &data;
    int i, j, r;

r = read_ppm("lena.ppm", image);

/* modificando o valor do pixel [20, 50] (posic¸˜ao X, Y) */
image->pix[50 * image->width + 20].r = 255;
image->pix[50 * image->width + 20].g = 255;
image->pix[50 * image->width + 20].b = 255;

write_ppm("copy.ppm", image);

}
