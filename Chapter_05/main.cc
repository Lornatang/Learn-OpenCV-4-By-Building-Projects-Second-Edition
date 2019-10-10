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
#include <memory>

using namespace std;

// OpenCV includes
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "utils/multiple_image_window.h"

using namespace cv;

shared_ptr<multiple_image_window> miw;

// OpenCV command line parser functions
// Keys accecpted by command line parser
const char *keys = {
        "{help h usage ? | | print this message}"
        "{@image || Image to process}"
        "{@lightPattern || Image light pattern to apply to image input}"
        "{lightMethod | 1 | Method to remove backgroun light, 0 differenec, 1 div, 2 no light removal' }"
        "{segMethod | 1 | Method to segment: 1 connected Components, 2 connectec components with stats, 3 find Contours }"
};

static Scalar randomColor(RNG &rng) {
  auto icolor = (unsigned) rng;
  return Scalar(icolor & 255, (icolor >> 8) & 255, (icolor >> 16) & 255);
}

/**
 * Calcualte image pattern from an input image
 * @param img Mat input image to calculate the light pattern
 * @return a Mat pattern image
 */
Mat calculateLightPattern(const Mat &img) {
  Mat pattern;
  // Basic and effective way to calculate the light pattern from one image
  blur(img, pattern, Size(img.cols / 3, img.cols / 3));
  return pattern;
}


void ConnectedComponents(const Mat &img) {
  // Use connected components to divide our possibles parts of images
  Mat labels;
  auto num_objects = connectedComponents(img, labels);
  // Check the number of objects detected
  if (num_objects < 2) {
    cout << "No objects detected" << endl;
    return;
  } else {
    cout << "Number of objects detected: " << num_objects - 1 << endl;
  }
  // Create output image coloring the objects
  Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
  RNG rng(0xFFFFFFFF);
  for (auto i = 1; i < num_objects; i++) {
    Mat mask = labels == i;
    output.setTo(randomColor(rng), mask);
  }
  //imshow("Result", output);
  miw->add_image("Result", output);
}

void ConnectedComponentsStats(const Mat &img) {
  // Use connected components with stats
  Mat labels, stats, centroids;
  auto num_objects = connectedComponentsWithStats(img, labels, stats, centroids);
  // Check the number of objects detected
  if (num_objects < 2) {
    cout << "No objects detected" << endl;
    return;
  } else {
    cout << "Number of objects detected: " << num_objects - 1 << endl;
  }
  // Create output image coloring the objects and show area
  Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
  RNG rng(0xFFFFFFFF);
  for (auto i = 1; i < num_objects; i++) {
    cout << "Object " << i << " with pos: " << centroids.at<Point2d>(i) << " with area "
         << stats.at<int>(i, CC_STAT_AREA) << endl;
    Mat mask = labels == i;
    output.setTo(randomColor(rng), mask);
    // draw text with area
    stringstream ss;
    ss << "area: " << stats.at<int>(i, CC_STAT_AREA);

    putText(output,
            ss.str(),
            centroids.at<Point2d>(i),
            FONT_HERSHEY_SIMPLEX,
            0.4,
            Scalar(255, 255, 255));
  }
  imshow("Result", output);
  miw->add_image("Result", output);
}

void FindContoursBasic(const Mat& img) {
  vector<vector<Point> > contours;
  findContours(img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  Mat output = Mat::zeros(img.rows, img.cols, CV_8UC3);
  // Check the number of objects detected
  if (contours.empty()) {
    cout << "No objects detected" << endl;
    return;
  } else {
    cout << "Number of objects detected: " << contours.size() << endl;
  }
  RNG rng(0xFFFFFFFF);
  for (auto i = 0; i < contours.size(); i++)
    drawContours(output, contours, i, randomColor(rng));
  imshow("Result", output);
  miw->add_image("Result", output);
}

/**
 * Remove th light and return new image without light
 * @param img Mat image to remove the light pattern
 * @param pattern Mat image with light pattern
 * @return a new image Mat without light
 */
Mat removeLight(Mat img, Mat pattern, int method) {
  Mat aux;
  // if method is normalization
  if (method == 1) {
    // Require change our image to 32 float for division
    Mat img32, pattern32;
    img.convertTo(img32, CV_32F);
    pattern.convertTo(pattern32, CV_32F);
    // Divide the imabe by the pattern
    aux = 1 - (img32 / pattern32);
    // Convert 8 bits format
    aux.convertTo(aux, CV_8U, 255);
  } else {
    aux = pattern - img;
  }
  //equalizeHist( aux, aux );
  return aux;
}

int main(int argc, const char **argv) {
  CommandLineParser parser(argc, argv, keys);
  parser.about("Chapter 5. PhotoTool v1.0.0");
  //If requires help show
  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }

  auto img_file = parser.get<String>(0);
  auto light_pattern_file = parser.get<String>(1);
  auto method_light = parser.get<int>("lightMethod");
  auto method_seg = parser.get<int>("segMethod");

  // Check if params are correctly parsed in his variables
  if (!parser.check()) {
    parser.printErrors();
    return 0;
  }

  // Load image to process
  Mat img = imread(img_file, 0);
  if (img.data == nullptr) {
    cout << "Error loading image " << img_file << endl;
    return 0;
  }

  // Create the Multiple Image Window
  miw = make_shared<multiple_image_window>("Main window", 3, 2, WINDOW_AUTOSIZE);

  // Remove noise
  Mat img_noise, img_box_smooth;
  medianBlur(img, img_noise, 3);
  blur(img, img_box_smooth, Size(3, 3));

  // Load image to process
  Mat light_pattern = imread(light_pattern_file, 0);
  if (light_pattern.data == nullptr) {
    // Calculate light pattern
    light_pattern = calculateLightPattern(img_noise);
  }
  medianBlur(light_pattern, light_pattern, 3);

  //Apply the light pattern
  Mat img_no_light;
  img_noise.copyTo(img_no_light);
  if (method_light != 2) {
    img_no_light = removeLight(img_noise, light_pattern, method_light);
  }

  // Binarize image for segment
  Mat img_thr;
  if (method_light != 2) {
    threshold(img_no_light, img_thr, 30, 255, THRESH_BINARY);
  } else {
    threshold(img_no_light, img_thr, 140, 255, THRESH_BINARY_INV);
  }

  // Show images
  miw->add_image("Input", img);
  miw->add_image("Input without noise", img_noise);
  miw->add_image("Light Pattern", light_pattern);
  miw->add_image("No Light", img_no_light);
  miw->add_image("Threshold", img_thr);

  if (method_seg == 1)
    ConnectedComponents(img_thr);
  if (method_seg == 2)
    ConnectedComponentsStats(img_thr);
  if (method_seg == 3)
    FindContoursBasic(img_thr);

  miw->render();
  waitKey(0);
  return 0;

}