#include <iostream>
#include "image.h"
#include "__imageParameter.h"
#include <vector>

int main() {
    Image image;
//    image.load_fig(IMG1_24_NAME, EXP1_OUT, 1);
//    image.print_pixel();
//    // EXP_1
//    image.load_fig(PE, EXP1_OUT, 1);
//    image.save_color_val(10, 10, EXP1_OUT);
//      // EXP_2
//    image.load_fig(PE, EXP2_OUT, 2);
//    image.modify_color_val(720, 720, EXP2_OUT, 50, 100, 20);
    // EXP_3
    image.load_fig("wsy_8.bmp", EXP3_OUT, 3);
    image.modify_palette();
   // EXP_4
//    image.load_fig(PE, EXP4_OUT, 4);
//    image.add_edges(20, 20, 10);
    // EXTEND_EXP_1
//    image.load_fig(IMG_EXT_256, EXP_EXT1_OUT, 5);
//    image.verify_biClrUsed_biClrImportant();
//    // EXTEND_EXP_2
//    image.load_fig(WSY, "wsy_8.bmp", 6);
//    image.transform_24_Kmeans(8);
    return 0;
}
