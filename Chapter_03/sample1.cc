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

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

int main(int argc, const char *argv[]) {
  Mat lena = imread("../lena.jpg");
  Mat photo = imread("../photo.png");

  namedWindow("lena", WINDOW_NORMAL);
  // Check if Lena image has been loaded.
  if (!lena.data) {
    cout << "lena image missing!" << endl;
    return -1;
  }

  namedWindow("Photo", WINDOW_NORMAL);
  // Check if photo image has been loaded.
  if (!photo.data) {
    cout << "photo image missing!" << endl;
    return -1;
  }

  // Move window
  moveWindow("Lena", 10, 10);
  moveWindow("Photo", 520, 10);

  // show images
  imshow("Lena", lena);
  imshow("Photo", photo);

  // Resize window.
  resizeWindow("Lena", 512, 512);

  waitKey(0);

  // destroy the windows
  destroyWindow("Lena");
  destroyWindow("Photo");

  // Create 10 windows
  for (int i = 0; i < 10; i++) {
    ostringstream ss;
    ss << "Photo " << i;
    namedWindow(ss.str());
    moveWindow(ss.str(), 20 * i, 20 * i);
    imshow(ss.str(), photo);
  }

  waitKey(0);
  // Destroy all windows
  destroyAllWindows();
  return 0;
}