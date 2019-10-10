/**
 * Copyright 2019 Lcy Authors. All Rights Reserved.
 * Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ==============================================================================
 */

#include "multiple_image_window.h"

multiple_image_window::multiple_image_window(const string& window_title, const int& cols, const int& rows, const int& flags) {
  this->window_title = window_title;
  this->cols = cols;
  this->rows = rows;
  namedWindow(window_title, flags);
  this->canvas_width = 1200;
  this->canvas_height = 700;
  this->canvas = Mat(this->canvas_height, this->canvas_width, CV_8UC3);
  imshow(this->window_title, this->canvas);
}

int multiple_image_window::add_image(const string& title, const Mat& image, const bool& render) {
  this->titles.push_back(title);
  this->images.push_back(image);
  if (render)
    this->render();
  return int(this->images.size()) - 1;
}

//void multiple_image_window::removeImage(const int& pos) {
//  this->titles.erase(this->titles.begin() + pos);
//  this->images.erase(this->images.begin() + pos);
//}

void multiple_image_window::render() {
  // Clean our canvas
  this->canvas.setTo(Scalar(20, 20, 20));
  // width and height of cell. add 10 px of padding between images
  int cell_width = (canvas_width / cols);
  int cell_height = (canvas_height / rows);
  int max_images = (this->images.size() > cols * rows) ? cols * rows : int(this->images.size());
  int i = 0;
  auto titles_it = this->titles.begin();
  for (const auto& img : this->images) {
    string title = *titles_it;
    int cell_x = (cell_width) * ((i) % cols);
    int cell_y = (cell_height) * int(floor((float)i / (float) cols));
    Rect mask(cell_x, cell_y, cell_width, cell_height);
    // Draw a rectangle for each cell mat
    rectangle(canvas, Rect(cell_x, cell_y, cell_width, cell_height), Scalar(200, 200, 200), 1);
    //For each cell draw an image if exists
    Mat cell(this->canvas, mask);
    // resize image to cell size
    Mat resized;
    double cell_aspect = (double) cell_width / (double) cell_height;
    double img_aspect = (double) img.cols / (double) img.rows;
    double f = (cell_aspect < img_aspect) ? (double) cell_width / (double) img.cols : (double) cell_height /
                                                                                      (double) img.rows;
    resize(img, resized, Size(0, 0), f, f);
    if (resized.channels() == 1) {
      cvtColor(resized, resized, COLOR_GRAY2BGR);
    }

    // Assign the image
    Mat sub_cell(this->canvas, Rect(cell_x, cell_y, resized.cols, resized.rows));
    resized.copyTo(sub_cell);
    putText(cell, title, Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(200, 0, 0), 1, LINE_AA);
    i++;
    ++titles_it;
    if (i == max_images)
      break;
  }

  // show image
  imshow(this->window_title, this->canvas);
}
