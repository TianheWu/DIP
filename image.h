//
// Created by Tianhe Wu on 2021/4/8.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>

#ifndef DIP_EXP_IMAGE_H
#define DIP_EXP_IMAGE_H

class Pixel {
public:
    unsigned char R;
    unsigned char G;
    unsigned char B;
    Pixel() {}
    Pixel(unsigned char _R, unsigned char _G, unsigned char _B) : R(_R), G(_G), B(_B) {}
};


class Image {
private:
    FILE* file_in;
    FILE* file_out;

public:
    int fig_rows;
    int fig_cols;
    std::vector<std::vector<Pixel>> pixel;
    std::vector<char> file_head;
    Image(int _rows, int _cols, int _dip_byte);
    void load_fig(std::string __FILE_NAME, std::string __FILE_NAME_2);
    void save_fig(std::string __FILE_NAME);
    void save_color_val(int _border_x, int _border_y, std::string _FILE_NAME);
    void read_file(int _elem_byte, int _elem_num);
    int get_rows();
    int get_cols();
};



#endif //DIP_EXP_IMAGE_H
