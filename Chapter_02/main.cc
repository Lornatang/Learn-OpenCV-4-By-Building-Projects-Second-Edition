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
#include <string>
#include <sstream>

using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, const char *argv[]) {
  Mat color = imread("../lena.jpg");
  Mat gray = imread("../lena.jpg", 0);

  if (!color.data) {
    cout << "Can't open image!\n" << endl;
    return -1;
  }

  imwrite("lenaGray.jpg", gray);

  int myRow = color.rows - 1;
  int myCol = color.cols - 1;

  Vec3b pixel = color.at<Vec3b>(myRow, myCol);
  cout << "Pixel value (B,G,R): ("
       << (int) pixel[0] << ","
       << (int) pixel[1] << ","
       << (int) pixel[2] << ")"
       << endl;

  imshow("lena BGR", color);
  imshow("lena Gray", gray);

  waitKey(0);
  return 0;
}
