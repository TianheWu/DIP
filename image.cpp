//
// Created by Tianhe Wu on 2021/4/8.
//

#include <iostream>
#include <stdio.h>
#include "image.h"
#include "__imageParameter.h"


Image::Image() {
    this->fig_rows = ROWS;
    this->fig_cols = COLUMNS;
    this->file_head = new char[DIP_COUNT];
    this->pixel_256 = new Pixel_256[COLOR_NUM];
}


int Image::get_rows() {
    return this->fig_rows;
}


int Image::get_cols() {
    return this->fig_cols;
}


void Image::load_fig(std::string __FILE_NAME_1, std::string __FILE_NAME_2, int _exp) {
    std::cout << "Start to load figure" << std::endl;
    this->file_in = fopen(__FILE_NAME_1.c_str(), "rb");
    if (_exp == 1)
        this->file_out = fopen(__FILE_NAME_2.c_str(), "w");
    else if (_exp == 2 || _exp == 3 || _exp == 4)
        this->file_out = fopen(__FILE_NAME_2.c_str(), "wb");
    std::cout << "Open " << __FILE_NAME_1 << " and " << __FILE_NAME_2 << " successfully!" << std::endl;
    if (_exp == EXP1 || _exp == EXP2 || _exp == EXP4)
        fread(this->file_head, DIP_ONE_BYTE, DIP_COUNT, this->file_in);
    else if (_exp == EXP3) {
        fread(this->file_head, DIP_ONE_BYTE, DIP_COUNT, this->file_in);
        fread(this->pixel_256, PALETTE * COLOR_NUM, PALETTE_COUNT, this->file_in);
    }
    fread(this->pixel, RGB_BYTE, this->fig_rows * this->fig_cols, this->file_in);
    std::cout << "Read file_head and pixel successfully!" << std::endl;
}


void Image::save_color_val(int _border_x, int _border_y, std::string _FILE_NAME) {
    std::cout << "Start to save color" << std::endl;
    for (int i = 0; i < _border_x; i++) {
        for (int j = 0; j < _border_y; j++)
            fprintf(this->file_out, "(%d, %d, %d)", this->pixel[i][j].R, this->pixel[i][j].G, this->pixel[i][j].B);
        fprintf(this->file_out, "\n");
    }
    fclose(this->file_in);
    fclose(this->file_out);
    std::cout << "Save color into txt " << _FILE_NAME << " successfully!" << std::endl;
}


void Image::modify_color_val(int _border_x, int _border_y, std::string _FILE_NAME, int _R, int _G, int _B) {
    std::cout << "Start to modify color" << std::endl;
    for (int i = 0; i < _border_x; i++) {
        for (int j = 0; j < _border_y; j++) {
            pixel[i][j].R = _R;
            pixel[i][j].G = _G;
            pixel[i][j].B = _B;
        }
    }
    fclose(this->file_in);
    fwrite(this->file_head, DIP_ONE_BYTE, DIP_COUNT, this->file_out);
    fwrite(this->pixel, RGB_BYTE, this->fig_rows * this->fig_cols, this->file_out);
    fclose(this->file_out);
    std::cout << "Modify color into" << _FILE_NAME << " successfully!" << std::endl;
}


void Image::modify_palette() {
    std::cout << "Start to modify palette" << std::endl;
    for (int i = 0; i < COLOR_NUM; i++) {
        this->pixel_256[i].G = i;
        this->pixel_256[i].R = 0;
        this->pixel_256[i].B = 0;
        this->pixel_256[i].reserved = 0;
    }
    fwrite(this->file_head, DIP_ONE_BYTE, DIP_COUNT, this->file_out);
    fwrite(this->pixel_256, PALETTE * COLOR_NUM, PALETTE_COUNT, this->file_out);
    fwrite(this->pixel, RGB_BYTE, this->fig_rows * this->fig_cols, this->file_out);
    fclose(this->file_in);
    fclose(this->file_out);
    std::cout << "Modify palette successfully!" << std::endl;
}


void Image::add_edges() {
    std::cout << "Start to add edges" << std::endl;
    int width = this->get_rows(), height = this->get_cols();
    Pixel add_edge_pixel[height + ADD_HEIGHT][width + ADD_WIDTH];
    this->file_head[BMP_WIDTH_POS] += ADD_WIDTH;
    this->file_head[BMP_HEIGHT_POS] += ADD_HEIGHT;
    for (int i = 0; i < height + ADD_HEIGHT; i++) {
        for (int j = 0; j < width + ADD_WIDTH; j++) {
            if (i >= width || j >= height) {
                add_edge_pixel[i][j].R = EXP2_R;
                add_edge_pixel[i][j].G = EXP2_G;
                add_edge_pixel[i][j].B = EXP2_B;
            } else {
                add_edge_pixel[i][j].R = this->pixel[i][j].R;
                add_edge_pixel[i][j].G = this->pixel[i][j].G;
                add_edge_pixel[i][j].B = this->pixel[i][j].B;
            }
        }
    }
    fclose(this->file_in);
    fwrite(this->file_head, DIP_ONE_BYTE, DIP_COUNT, this->file_out);
    fwrite(add_edge_pixel, RGB_BYTE, (width + ADD_WIDTH) * (height + ADD_HEIGHT), this->file_out);
    fclose(this->file_out);
    std::cout << "Add edges successfully!" << std::endl;
}

