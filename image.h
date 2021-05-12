//
// Created by Tianhe Wu on 2021/4/8.
//
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "__imageParameter.h"


#ifndef DIP_EXP_IMAGE_H
#define DIP_EXP_IMAGE_H

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;


struct Bitmap_file_header {
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};


struct Bitmap_info_header {
    DWORD biSize;//信息头大小
    DWORD biWidth;//图像宽度
    DWORD biHeight;//图像高度
    WORD biPlanes;//位平面数，必须为1
    WORD biBitCount;//每像素位数。常用的值为1(黑白二色图), 4(16色图), 8(256色), 24(真彩色图)或32(新的.bmp格式支持32位色）
    DWORD  biCompression; //压缩类型：有效的值为BI_RGB，BI_RLE8，BI_RLE4，BI_BITFIELDS(都是一些Windows定义好的常量)
    DWORD  biSizeImage;  //压缩图像大小字节数 biSizeImage=biWidth’ × biHeight，biWidth’必须是4的整倍数，(所以不是biWidth，而是biWidth’，表示大于或等于biWidth的，最接近4的整倍数）
    DWORD  biXPelsPerMeter; //水平分辨率，单位是每米的象素个数
    DWORD  biYPelsPerMeter; //垂直分辨率，单位是每米的象素个数
    DWORD  biClrUsed; //位图实际用到的色彩数，如果该值为零，则用到的颜色数为2^biBitCount
    DWORD  biClrImportant; //本位图中重要的色彩数,如果该值为零，则认为所有的颜色都是重要的。
};


class Pixel {
public:
    unsigned char B;
    unsigned char G;
    unsigned char R;
    Pixel() {}
    bool operator==(const Pixel& pixel) {
        if (this->B == pixel.B && this->R == pixel.R && this->G == pixel.G)
            return true;
        else return false;
    }
};


class Pixel_palette {
public:
    unsigned char B;
    unsigned char G;
    unsigned char R;
    unsigned char reserved;
    Pixel_palette() {}
};


class Image {
private:
    WORD bfType;
    Bitmap_file_header bmp_file_head;
    Bitmap_info_header bmp_info_head;
    FILE* file_in;
    FILE* file_out;
    int fig_width;
    int fig_height;
    Pixel* pixel;
    BYTE* origin_pixel_256;
    BYTE* new_pixel_256;
    Pixel_palette* pixel_palette;
    Pixel_palette* new_form_palette;
    int find_suitable_color_pos(Pixel& in_pixel, int target_color_num);
    int find_rgb_pos(std::vector<Pixel>& rgb_vocab, Pixel& rgb);
    int find_color_type(std::vector<int>& k_means_vec, Pixel& in_pixel, std::vector<Pixel>& point);
    int find_match_average(std::vector<int>& same_type, Pixel& average_pixel, std::vector<Pixel>& point);

public:
    Image();
    void load_fig(std::string __FILE_NAME, std::string __FILE_NAME_2, int _exp);
    void save_color_val(int _height_edge, int _width_edge, std::string _FILE_NAME);
    void modify_color_val(int _height_edge, int _width_edge, std::string _FILE_NAME, int _R, int _G, int _B);
    void modify_palette();
    void add_edges(int _add_height, int _add_width, int _offset);
    void print_pixel();
    void verify_biClrUsed_biClrImportant();
    void transform_24_Kmeans(int target_color_num);
    void transform_24_topK(int target_color_num);
    int get_heights();
    int get_widths();
};


#endif //DIP_EXP_IMAGE_H