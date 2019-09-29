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

#include <iostream>

using namespace std;

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, const char *argv[]) {
  // Read images
  Mat color = imread("../lena.jpg");
  Mat gray = imread("../lena.jpg", 0);

  if (!color.data) {
    cout << "Can't open image!\n" << endl;
    return -1;
  }

  // Write images
  imwrite("lenaGray.jpg", gray);

  // Get same pixel with OpenCV function
  int myRow = color.rows - 1;
  int myCol = color.cols - 1;

  Vec3b pixel = color.at<Vec3b>(myRow, myCol);
  cout << "Pixel value (B,G,R): ("
       << (int) pixel[0] << ","
       << (int) pixel[1] << ","
       << (int) pixel[2] << ")"
       << endl;

  // Show images
  imshow("lena BGR", color);
  imshow("lena Gray", gray);

  // Wait for any key press
  waitKey(0);
  return 0;
}
