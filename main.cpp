#include <iostream>
#include "image.h"
#include "__imageParameter.h"


int main() {
    Image image(ROWS, COLUMNS, DIP_BYTE);
    image.load_fig(IMG1_24_NAME, EXP1_OUT);
    image.save_color_val(BORDER_X, BORDER_Y, EXP1_OUT);
    return 0;
}
