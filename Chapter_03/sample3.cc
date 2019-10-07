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
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

// Create a variable to save the position value in track
int blurAmount = 15;

// Trackbar call back function
static void onChange(int pos, void *userInput);

//Mouse callback
static void onMouse(int event, int x, int y, int, void *userInput);

int main(int argc, const char **argv) {
  // Read images
  Mat lena = imread("../lena.jpg");

  // Create windows
  namedWindow("Lena");

  // create a trackbark
  createTrackbar("Lena", "Lena", &blurAmount, 30, onChange, &lena);

  setMouseCallback("Lena", onMouse, &lena);

  // Call to onChange to init
  onChange(blurAmount, &lena);

  // wait app for a key to exit
  waitKey(0);

  // Destroy the windows
  destroyWindow("Lena");

  return 0;
}

// Trackbar call back function
static void onChange(int pos, void *userInput) {
  if (pos <= 0)
    return;
  // Aux variable for result
  Mat imgBlur;

  // Get the pointer input image
  Mat *img = (Mat *) userInput;

  // Apply a blur filter
  blur(*img, imgBlur, Size(pos, pos));

  // Show the result
  imshow("Lena", imgBlur);
}

//Mouse callback
static void onMouse(int event, int x, int y, int, void *userInput) {
  if (event != EVENT_LBUTTONDOWN)
    return;

  // Get the pointer input image
  Mat *img = (Mat *) userInput;

  // Draw circle
  circle(*img, Point(x, y), 10, Scalar(0, 255, 0), 3);

  // Call on change to get blurred image
  onChange(blurAmount, img);
}