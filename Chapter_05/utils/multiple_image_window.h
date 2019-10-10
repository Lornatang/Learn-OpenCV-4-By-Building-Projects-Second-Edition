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

#ifndef PHOTO_TOOL_MULTIPLEIMAGEWINDOW_H
#define PHOTO_TOOL_MULTIPLEIMAGEWINDOW_H

#include <string>
#include <iostream>

using namespace std;

// OpenCV includes
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class multiple_image_window {
public:
  /**
   * Constructor
   * Create new window with a max of cols*row images
   *
   * @param string window_title
   * @param int cols number of cols
   * @param int rows number of rows
   * @param int flags see highgui window documentation
   */
  multiple_image_window(const string& window_title, const int& cols, const int& rows, const int& flags);

  /**
   * Add new image to stack of window
   * @param Mat image
   * @param string title caption of image to show
   * @return int position of image in stack
   */
  int add_image(const string& title, const Mat& image, const bool& render = false);

  /**
   * Remove a image from position n
   */
  // void removeImage(const int& pos);

  /**
   * Render/redraw/update window
   */
  void render();

private:
  int cols;
  int rows;
  int canvas_width;
  int canvas_height;
  string window_title;
  vector<string> titles;
  vector<Mat> images;
  Mat canvas;
};

#endif // PHOTO_TOOL_MULTIPLEIMAGEWINDOW_H
