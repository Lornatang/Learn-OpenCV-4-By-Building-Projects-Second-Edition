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

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char *keys = {
        "{help h usage? || print this message}"
        "{@video || video file, if not defined try to use webcamera}"
};

int main(int argc, const char *argv[]) {
  CommandLineParser parser(argc, argv, keys);
  parser.about("Chapter 2");

  //If requires help show
  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }

  String videoFile = parser.get<String>(0);

  // Check if params are correctly parsed in his variables
  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  VideoCapture cap; // open the default camera
  if (!videoFile.empty())
    cap.open(videoFile);
  else
    cap.open("test.mp4");
  if (!cap.isOpened())  // check if we succeeded
    return -1;

  namedWindow("Video", 1);
  for (;;) {
    Mat frame;
    cap >> frame; // get a new frame from camera
    if (frame.empty())
      return 0;
    imshow("Video", frame);
    if (waitKey(30) >= 0) break;
  }
  // Release the camera or video cap
  cap.release();

  return 0;
}


