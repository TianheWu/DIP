//
// Created by Tianhe Wu on 2021/4/8.
//
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "__imageParameter.h"


#ifndef DIP_EXP_IMAGE_H
#define DIP_EXP_IMAGE_H


class Pixel {
public:
    unsigned char B;
    unsigned char G;
    unsigned char R;
    Pixel() {}
};


class Pixel_256 {
public:
    unsigned char B;
    unsigned char G;
    unsigned char R;
    unsigned char reserved;
    Pixel_256() {}
};


class Image {
private:
    FILE* file_in;
    FILE* file_out;
    int fig_rows;
    int fig_cols;
    Pixel pixel[ROWS][COLUMNS];
    Pixel_256* pixel_256;
    char* file_head;

public:
    Image();
    void load_fig(std::string __FILE_NAME, std::string __FILE_NAME_2, int _exp);
    void save_color_val(int _border_x, int _border_y, std::string _FILE_NAME);
    void modify_color_val(int _border_x, int _border_y, std::string _FILE_NAME, int _R, int _G, int _B);
    void modify_palette();
    void add_edges();
    int get_rows();
    int get_cols();
};



#endif //DIP_EXP_IMAGE_H
