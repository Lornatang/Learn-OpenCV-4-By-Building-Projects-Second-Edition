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

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace std;

using namespace cv;


int main(int argc, const char **argv) {
  // Read images
  Mat lena = imread("../lena.jpg");

  // Create windows
  namedWindow("Lena");

  // show images
  imshow("Lena", lena);

  // Display Overlay
  displayOverlay("Lena", "Overlay 5secs", 5000);

  // Display Status Bar
  displayStatusBar("Lena", "Status bar 5secs", 5000);

  // Save window parameters
  saveWindowParameters("Lena");

  // load Window parameters
  loadWindowParameters("Lena");

  // wait for any key press
  waitKey(0);

  // Destroy the windows
  destroyWindow("Lena");

  return 0;
}