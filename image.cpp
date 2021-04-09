//
// Created by Tianhe Wu on 2021/4/8.
//

#include <iostream>
#include <stdio.h>
#include "image.h"
#include "__imageParameter.h"


Image::Image(int _rows, int _cols, int _dip_byte) {
    this->fig_rows = _rows;
    this->fig_cols = _cols;
    std::vector<std::vector<Pixel>> pixel(_rows, std::vector<Pixel>(_cols));
    this->pixel = pixel;
    this->file_head.resize(_dip_byte);
}


void Image::load_fig(std::string __FILE_NAME_1, std::string __FILE_NAME_2) {
    std::cout << "YYYYYYYYYYYY" << std::endl;
    this->file_in = fopen(__FILE_NAME_1.c_str(), "rb");
    this->file_out = fopen(__FILE_NAME_2.c_str(), "w");
    std::cout << "YYYYYYYYYYYY22222222222" << std::endl;
    fread(this->file_head, DIP_ONE_BYTE, DIP_BYTE, this->file_in);
    fread(this->pixel, RGB_BYTE, this->fig_rows * this->fig_cols, this->file_in);
    std::cout << "YYYYYYYYYYYY333333333333333333" << std::endl;
    for (int i = 0; i < pixel.size(); i++) {
        for (int j = 0; j < pixel[i].size(); j++) {
            std::cout << pixel[i][j].R << std::endl;
        }
    }

}


void Image::save_fig(std::string __FILE_NAME) {

}


int Image::get_rows() {
    return this->fig_rows;
}


int Image::get_cols() {
    return this->fig_cols;
}


void Image::save_color_val(int _border_x, int _border_y, std::string _FILE_NAME) {
    for (int i = 0; i < _border_x; i++) {
        for (int j = 0; j < _border_y; j++)
            fprintf(this->file_out, "(%d, %d, %d)", this->pixel[i][j].R, this->pixel[i][j].G, this->pixel[i][j].B);
        fprintf(this->file_out, "\n");
    }
    fclose(this->file_in);
    fclose(this->file_out);
    std::cout << "Save color into txt " << _FILE_NAME << " successfully!" << std::endl;
}


