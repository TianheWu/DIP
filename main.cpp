#include <iostream>
#include "image.h"
#include "__imageParameter.h"

int main() {
    Image image;
    // EXP_1
//    image.load_fig(WSY, EXP1_OUT, 1);
//    image.save_color_val(BORDER_X_1, BORDER_Y_1, EXP1_OUT);
//    // EXP_2
//    image.load_fig(WSY, EXP2_OUT, 2);
//    image.modify_color_val(BORDER_X_2, BORDER_Y_2, EXP2_OUT, EXP2_R, EXP2_G, EXP2_B);
//    // EXP_3
//    image.load_fig(IMG1_8_NAME, EXP3_OUT, 3);
//    image.modify_palette();
//    // EXP_4
//    image.load_fig(WSY, EXP4_OUT, 4);
//    image.add_edges(15, 20);
//    // EXTEND_EXP_1
//    image.load_fig(IMG_EXT_256, EXP_EXT1_OUT, 5);
//    image.verify_biClrUsed_biClrImportant();
    // EXTEND_EXP_2
    image.load_fig(WSY, EXP_EXT2_OUT, 6);
    image.transform_24_Kmeans(8);
    return 0;
}
