#include <iostream>
#include "image.h"
#include "__imageParameter.h"


int main() {
    Image image;
    // EXP_1
//    image.load_fig(IMG1_24_NAME, EXP1_OUT, 1);
//    image.save_color_val(BORDER_X_1, BORDER_Y_1, EXP1_OUT);
//    // EXP_2
//    image.load_fig(IMG1_24_NAME, EXP2_OUT, 2);
//    image.modify_color_val(BORDER_X_2, BORDER_Y_2, EXP2_OUT, EXP2_R, EXP2_G, EXP2_B);
    // EXP_3
//    image.load_fig(IMG1_8_NAME, EXP3_OUT, 3);
//    image.modify_palette();
    // EXP_4
    image.load_fig(IMG1_24_NAME, EXP4_OUT, 4);
    image.add_edges();

    return 0;
}

