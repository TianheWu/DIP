//
// Created by Tianhe Wu on 2021/4/8.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cmath>
#include <unordered_map>
#include "image.h"
#include "__imageParameter.h"


bool cmp(std::pair<int, int> x1, std::pair<int, int> x2) {
    return x1.second >= x2.second;
}


Image::Image() {
//    this->fig_rows = ROWS;
//    this->fig_cols = COLUMNS;
    this->pixel_palette = new Pixel_palette[COLOR_NUM];
}


int Image::get_widths() {
    return this->fig_rows;
}


int Image::get_heights() {
    return this->fig_cols;
}


void Image::load_fig(std::string __FILE_NAME_1, std::string __FILE_NAME_2, int _exp) {
    std::cout << "Start to load figure" << std::endl;
    this->file_in = fopen(__FILE_NAME_1.c_str(), "rb");
    if (_exp == 1)
        this->file_out = fopen(__FILE_NAME_2.c_str(), "w");
    else if (_exp == 2 || _exp == 3 || _exp == 4 || _exp == 5 || _exp == 6)
        this->file_out = fopen(__FILE_NAME_2.c_str(), "wb");
    std::cout << "Open " << __FILE_NAME_1 << " and " << __FILE_NAME_2 << " successfully!" << std::endl;
    if (_exp == EXP1 || _exp == EXP2 || _exp == EXP4 || _exp == EXTEND_EXP_2) {
        fread(&this->bfType, 2, 1, this->file_in);
        fread(&this->bmp_file_head, 12, 1, this->file_in);
        fread(&this->bmp_info_head, 40, 1, this->file_in);
        this->fig_rows = this->bmp_info_head.biWidth;
        this->fig_cols = this->bmp_info_head.biHeight;
        fread(this->pixel, RGB_BYTE_24, this->fig_rows * this->fig_cols, this->file_in);
    }
    else if (_exp == EXP3 || _exp == EXTEND_EXP_1) {
        fread(&this->bfType, 2, 1, this->file_in);
        fread(&this->bmp_file_head, 12, 1, this->file_in);
        fread(&this->bmp_info_head, 40, 1, this->file_in);
        this->fig_rows = this->bmp_info_head.biWidth;
        this->fig_cols = this->bmp_info_head.biHeight;
        fread(this->pixel_palette, PALETTE * COLOR_NUM, PALETTE_COUNT, this->file_in);
        fread(this->rgb_idx, RGB_BYTE_256, this->fig_rows * this->fig_cols, this->file_in);
    }
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
    fwrite(&this->bfType, 2, 1, this->file_out);
    fwrite(&this->bmp_file_head, 1, 12, this->file_out);
    fwrite(&this->bmp_info_head, 1, 40, this->file_out);
    fwrite(this->pixel, RGB_BYTE_24, this->fig_rows * this->fig_cols, this->file_out);
    fclose(this->file_out);
    std::cout << "Modify color into" << _FILE_NAME << " successfully!" << std::endl;
}


void Image::modify_palette() {
    std::cout << "Start to modify palette" << std::endl;
    for (int i = 0; i < COLOR_NUM; i++) {
        this->pixel_palette[i].G = i;
        this->pixel_palette[i].R = 0;
        this->pixel_palette[i].B = 0;
        this->pixel_palette[i].reserved = 0;
    }
    fwrite(&this->bfType, 2, 1, this->file_out);
    fwrite(&this->bmp_file_head, 1, 12, this->file_out);
    fwrite(&this->bmp_info_head, 1, 40, this->file_out);
    fwrite(this->pixel_palette, PALETTE * COLOR_NUM, PALETTE_COUNT, this->file_out);
    fwrite(this->rgb_idx, RGB_BYTE_256, this->fig_rows * this->fig_cols, this->file_out);
    fclose(this->file_in);
    fclose(this->file_out);
    std::cout << "Modify palette successfully!" << std::endl;
}


void Image::add_edges(int _add_height, int _add_width) {
    std::cout << "Start to add edges" << std::endl;
    int width = this->get_widths(), height = this->get_heights();
    std::cout << "figure width = " << width << " figure height = " << height << std::endl;
    Pixel add_edge_pixel[height + _add_height][width + _add_width];
    this->bmp_info_head.biWidth += _add_width;
    this->bmp_info_head.biHeight += _add_height;
    std::cout << "new width = " << bmp_info_head.biWidth << " new height = " << bmp_info_head.biHeight << std::endl;
    for (int i = 0; i < height + _add_height; i++) {
        for (int j = 0; j < width + _add_width; j++) {
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
    fwrite(&this->bfType, 2, 1, this->file_out);
    fwrite(&this->bmp_file_head, 1, 12, this->file_out);
    fwrite(&this->bmp_info_head, 1, 40, this->file_out);
    fwrite(add_edge_pixel, RGB_BYTE_24, (width + _add_width) * (height + _add_height), this->file_out);
    fclose(this->file_out);
    std::cout << "Add edges successfully!" << std::endl;
}


void Image::verify_biClrUsed_biClrImportant() {
    int width = this->get_widths(), height = this->get_heights();
    DWORD biClrUsed = this->bmp_info_head.biClrUsed;
    std::cout << "Origin biClrUsed is " << biClrUsed << std::endl;
    this->bmp_info_head.biClrUsed = 2;
    std::cout << "New biClrUsed is " << this->bmp_info_head.biClrUsed << std::endl;
    DWORD biClrImportant = this->bmp_info_head.biClrImportant;
    std::cout << "Origin biClrImportant is " << biClrImportant << std::endl;
    this->bmp_info_head.biClrImportant = 1;
    std::cout << "New biClrImportant is " << this->bmp_info_head.biClrImportant << std::endl;
    fwrite(&this->bfType, 2, 1, this->file_out);
    fwrite(&this->bmp_file_head, 1, 12, this->file_out);
    fwrite(&this->bmp_info_head, 1, 40, this->file_out);
    fwrite(this->pixel_palette, PALETTE * COLOR_NUM, PALETTE_COUNT, this->file_out);
    fwrite(this->rgb_idx, RGB_BYTE_256, width * height, this->file_out);
    fclose(this->file_in);
    fclose(this->file_out);
}


int Image::find_rgb_pos(std::vector<Pixel>& rgb_vocab, Pixel& rgb) {
    int n = rgb_vocab.size();
    for (int i = 0; i < n; i++) {
        if (rgb_vocab[i] == rgb)
            return i;
    }
    return -1;
}


int Image::find_suitable_color_pos(Pixel& in_pixel, int target_color_num_all) {
    int sum = 999, pos = 0;
    for (int i = 0; i < target_color_num_all; i++) {
        int temp_G = abs(this->new_form_palette[i].G - in_pixel.G);
        int temp_B = abs(this->new_form_palette[i].B - in_pixel.B);
        int temp_R = abs(this->new_form_palette[i].R - in_pixel.R);
        int temp_sum = temp_B + temp_G + temp_R;
        if (temp_sum < sum) {
            sum = temp_sum;
            pos = i;
        }
    }
    return pos;
}


void Image::transform_24_topK(int target_color_num) {
    this->new_form_palette = new Pixel_palette[(int) pow(2, target_color_num)];
    std::vector<Pixel> rgb_vocab;
    std::vector<std::pair<int, int>> cnt_rgb;
    int width = this->get_widths(), height = this->get_heights();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int pos = find_rgb_pos(rgb_vocab, this->pixel[i][j]);
            if (pos != -1)
                continue;
            else {
                rgb_vocab.push_back(this->pixel[i][j]);
                int pos = find_rgb_pos(rgb_vocab, this->pixel[i][j]);
                std::pair<int, int> idx_cnt = std::make_pair(pos, 0);
                cnt_rgb.push_back(idx_cnt);
            }
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int pos = find_rgb_pos(rgb_vocab, this->pixel[i][j]);
            cnt_rgb[pos].second++;
        }
    }
    std::sort(cnt_rgb.begin(), cnt_rgb.end(), cmp);
    std::cout << "Start to build palette" << std::endl;
    for (int i = 0; i < (int) pow(2, target_color_num); i++) {
        Pixel temp_pixel = rgb_vocab[cnt_rgb[i].first];
        this->new_form_palette[i].G = temp_pixel.G;
        this->new_form_palette[i].B = temp_pixel.B;
        this->new_form_palette[i].R = temp_pixel.R;
        this->new_form_palette[i].reserved = 0;
    }
    std::cout << "Start to form picture information" << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int pos = find_suitable_color_pos(this->pixel[i][j], (int) pow(2, target_color_num));
            this->new_form_pixel[i][j] = (BYTE) pos;
        }
    }
    this->bmp_info_head.biBitCount = target_color_num;
    this->bmp_file_head.bfOffBits = 54 + (int) pow(2, target_color_num) * 4;
    this->bmp_info_head.biSizeImage = width * height;
    this->bmp_file_head.bfSize = this->bmp_file_head.bfOffBits + this->bmp_info_head.biSizeImage;
    fwrite(&this->bfType, 2, 1, this->file_out);
    fwrite(&this->bmp_file_head, 1, 12, this->file_out);
    fwrite(&this->bmp_info_head, 1, 40, this->file_out);
    fwrite(this->new_form_palette, PALETTE * COLOR_NUM, PALETTE_COUNT, this->file_out);
    fwrite(this->new_form_pixel, RGB_BYTE_256, width * height, this->file_out);
    fclose(this->file_in);
    fclose(this->file_out);
}


int Image::find_color_type(std::vector<int>& k_means_vec, Pixel& in_pixel, std::vector<Pixel>& point) {
    int sum = 999, n = k_means_vec.size(), type_idx = -1;
    for (int i = 0; i < n; i++) {
        int temp_R = abs(point[k_means_vec[i]].R - in_pixel.R);
        int temp_G = abs(point[k_means_vec[i]].G - in_pixel.G);
        int temp_B = abs(point[k_means_vec[i]].B - in_pixel.B);
        int temp_sum = temp_R + temp_G + temp_B;
        if (temp_sum < sum) {
            sum = temp_sum;
            type_idx = k_means_vec[i];
        }
    }
    return type_idx;
}


int Image::find_match_average(std::vector<int>& same_type, Pixel& in_pixel, std::vector<Pixel>& point) {
    int sum = 999, point_idx = 0;
    for (int i = 0; i < same_type.size(); i++) {
        int temp_G = abs(point[same_type[i]].G - in_pixel.G);
        int temp_B = abs(point[same_type[i]].B - in_pixel.B);
        int temp_R = abs(point[same_type[i]].R - in_pixel.R);
        int temp_sum = temp_B + temp_G + temp_R;
        if (temp_sum < sum) {
            sum = temp_sum;
            point_idx = same_type[i];
        }
    }
    return point_idx;
}


void Image::transform_24_Kmeans(int target_color_num) {
    // each point has idx
    std::vector<Pixel> point;
    std::vector<int> k_means_vec;
    std::vector<int> point_type;
    int width = this->get_widths(), height = this->get_heights();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            point.push_back(this->pixel[i][j]);
    int pixel_num = point.size();
    point_type.resize(pixel_num, 0);

    srand((unsigned) time(NULL));
    std::unordered_map<int, int> random_num_map;

    // first k-means
    int i = 0;
    while (i < (int) pow(2, target_color_num)) {
        int rand_num = rand() % pixel_num;
        if (random_num_map.find(rand_num) != random_num_map.end())
            continue;
        random_num_map[rand_num]++;
        k_means_vec.push_back(rand_num);
        point_type[rand_num] = i;
        i++;
    }

    for (int z = 0; z < 7; z++) {
        std::cout << "Epoch: " << z << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int type_idx = find_color_type(k_means_vec, this->pixel[i][j], point);
                point_type[i * height + j] = point_type[type_idx];
            }
        }
        std::cout << "Finish update point type" << std::endl;
        k_means_vec.clear();
        std::cout << "Start to calculate each same type average point" << std::endl;
        for (int i = 0; i < (int) pow(2, target_color_num); i++) {
            std::cout << "Epoch: " << z << " | Type: " << i << std::endl;
            std::vector<int> same_type;
            for (int j = 0; j < pixel_num; j++) {
                if (point_type[j] == i)
                    same_type.push_back(j);
            }
            int average_r = 0, average_g = 0, average_b = 0, size_same = same_type.size();
            std::cout << "Calculate average" << std::endl;
            for (int j = 0; j < size_same; j++) {
                average_r += point[same_type[j]].R;
                average_g += point[same_type[j]].G;
                average_b += point[same_type[j]].B;
            }
            average_r /= size_same;
            average_b /= size_same;
            average_g /= size_same;
            Pixel average_pixel;
            average_pixel.R = average_r;
            average_pixel.G = average_g;
            average_pixel.B = average_b;
            std::cout << "Start to find match average point" << std::endl;
            int point_idx = find_match_average(same_type, average_pixel, point);
            k_means_vec.push_back(point_idx);
        }
    }
    std::cout << "Start to form new palette" << std::endl;
    this->new_form_palette = new Pixel_palette[(int) pow(2, target_color_num)];
    for (int i = 0; i < (int) pow(2, target_color_num); i++) {
        this->new_form_palette[i].G = point[k_means_vec[i]].G;
        this->new_form_palette[i].B = point[k_means_vec[i]].B;
        this->new_form_palette[i].R = point[k_means_vec[i]].R;
        this->new_form_palette[i].reserved = 0;
    }
    std::cout << "Start to form new pixel" << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            this->new_form_pixel[i][j] = (BYTE) point_type[i * height + width];
        }
    }
    this->bmp_info_head.biBitCount = target_color_num;
    this->bmp_file_head.bfOffBits = 54 + (int) pow(2, target_color_num) * 4;
    this->bmp_info_head.biSizeImage = width * height;
    this->bmp_file_head.bfSize = this->bmp_file_head.bfOffBits + this->bmp_info_head.biSizeImage;
    fwrite(&this->bfType, 2, 1, this->file_out);
    fwrite(&this->bmp_file_head, 1, 12, this->file_out);
    fwrite(&this->bmp_info_head, 1, 40, this->file_out);
    fwrite(this->new_form_palette, PALETTE * COLOR_NUM, PALETTE_COUNT, this->file_out);
    fwrite(this->new_form_pixel, RGB_BYTE_256, width * height, this->file_out);
    fclose(this->file_in);
    fclose(this->file_out);
}




