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

#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char **argv) {
  // create our writter
  FileStorage fs("test.yml", FileStorage::WRITE);
  // Save an int
  int fps = 5;
  fs << "fps" << fps;
  // Create some mat sample
  Mat m1 = Mat::eye(2, 3, CV_32F);
  Mat m2 = Mat::ones(3, 2, CV_32F);
  Mat result = (m1 + 1).mul(m1 + 3);
  // write the result
  fs << "Result" << result;
  // release the file
  fs.release();

  FileStorage fs2("test.yml", FileStorage::READ);

  Mat r;
  fs2["Result"] >> r;
  std::cout << r << std::endl;

  fs2.release();

  return 0;
}