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


#include <string>

using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat img;
bool applyGray = false;
bool applyBlur = false;
bool applySobel = false;

void applyFilters() {
  Mat result;
  img.copyTo(result);
  if (applyGray) {
    cvtColor(result, result, COLOR_BGR2GRAY);
  }
  if (applyBlur) {
    blur(result, result, Size(5, 5));
  }
  if (applySobel) {
    Sobel(result, result, CV_8U, 1, 1);
  }
  imshow("Lena", result);
}

void grayCallback(int state, void *userData) {
  applyGray = true;
  applyFilters();
}

void bgrCallback(int state, void *userData) {
  applyGray = false;
  applyFilters();
}

void blurCallback(int state, void *userData) {
  applyBlur = (bool) state;
  applyFilters();
}

void sobelCallback(int state, void *userData) {
  applySobel = !applySobel;
  applyFilters();
}

int main(int argc, const char **argv) {
  // Read images
  img = imread("../lena.jpg");

  // Create windows
  namedWindow("Lena");

  // create Buttons
  createButton("Blur", blurCallback, nullptr, QT_CHECKBOX, 0);

  createButton("Gray", grayCallback, nullptr, QT_RADIOBOX, 0);
  createButton("RGB", bgrCallback, nullptr, QT_RADIOBOX, 1);

  createButton("Sobel", sobelCallback, nullptr, QT_PUSH_BUTTON, 0);

  // wait app for a key to exit
  waitKey(0);

  // Destroy the windows
  destroyWindow("Lena");

  return 0;
}
