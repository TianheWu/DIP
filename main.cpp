#include "image.h"
#include "__imageParameter.h"

int main() {
    Image image;
    // EXP_1
    image.load_fig("exp_24.bmp", EXP1_OUT, 1);
    image.save_color_val(10, 10, EXP1_OUT);
    // EXP_2
    image.load_fig("exp_24.bmp", EXP2_OUT, 2);
    image.modify_color_val(720, 720, EXP2_OUT, 17, 19, 113);
    // EXP_3
    image.load_fig("bingzhang.bmp", EXP3_OUT, 3);
    image.modify_palette();
    // EXP_4
    image.load_fig("exp_24.bmp", EXP4_OUT, 4);
    image.add_edges(40, 40, 20);
    // EXTEND_EXP_1
    image.load_fig("bingzhang.bmp", EXP_EXT1_OUT, 5);
    image.verify_biClrUsed_biClrImportant();
    // EXTEND_EXP_2
    image.load_fig("exp_24.bmp", "topK.bmp", 6);
    image.transform_24_topK(8);
    return 0;
}
