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

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
  string face_cascade_name = argv[1];
  CascadeClassifier face_cascade;

  if (!face_cascade.load(face_cascade_name)) {
    cerr << "Error loading cascade file. Exiting!" << endl;
    return -1;
  }

  Mat face_mask = imread(argv[2]);

  if (!face_mask.data) {
    cerr << "Error loading mask image. Exiting!" << endl;
    return -1;
  }

  // Current frame
  Mat frame, frame_gray;
  Mat frameROI, face_mask_small;
  Mat gray_mask_small, gray_mask_small_thresh, gray_mask_small_thresh_inv;
  Mat masked_face, masked_frame;

  // Create the capture object
  // 0 -> input arg that specifies it should take the input from the webcam
  VideoCapture cap(0);

  // If you cannot open the webcam, stop the execution!
  if (!cap.isOpened())
    return -1;

  //create GUI windows
  namedWindow("Frame");

  // Scaling factor to resize the input frames from the webcam
  float scaling_factor = 0.75;

  vector<Rect> faces;

  // Iterate until the user presses the Esc key
  while (true) {
    // Capture the current frame
    cap >> frame;

    // Resize the frame
    resize(frame, frame, Size(), scaling_factor, scaling_factor, INTER_AREA);

    // Convert to grayscale
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);

    // Equalize the histogram
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | 2, Size(30, 30));

    // Draw green rectangle around the face
    for (auto &face: faces) {

      // Custom parameters to make the mask fit your face. You may have to play around with them to make sure it works.
      int x = face.x - int(0.1 * face.width);
      int y = face.y - int(0.0 * face.height);
      int w = int(1.1 * face.width);
      int h = int(1.3 * face.height);

      // Extract region of interest (ROI) covering your face
      frameROI = frame(Rect(x, y, w, h));

      // Resize the face mask image based on the dimensions of the above ROI
      resize(face_mask, face_mask_small, Size(w, h));

      // Convert the above image to grayscale
      cvtColor(face_mask_small, gray_mask_small, COLOR_BGR2GRAY);

      // Threshold the above image to isolate the pixels associated only with the face mask
      threshold(gray_mask_small, gray_mask_small_thresh, 230, 255, THRESH_BINARY_INV);

      // Create mask by inverting the above image (because we don't want the background to affect the overlay)
      bitwise_not(gray_mask_small_thresh, gray_mask_small_thresh_inv);

      // Use bitwise "AND" operator to extract precise boundary of face mask
      bitwise_and(face_mask_small, face_mask_small, masked_face, gray_mask_small_thresh);

      // Use bitwise "AND" operator to overlay face mask
      bitwise_and(frameROI, frameROI, masked_frame, gray_mask_small_thresh_inv);

      // Add the above masked images and place it in the original frame ROI to create the final image
      if (x > 0 && y > 0 && x + w < frame.cols && y + h < frame.rows)
        add(masked_face, masked_frame, frame(Rect(x, y, w, h)));
    }

    // Show the current frame
    imshow("Frame", frame);

    // Get the keyboard input and check if it's 'Esc'
    // 27 -> ASCII value of 'Esc' key
    auto ch = waitKey(30);
    if (ch == 27) {
      break;
    }
  }

  // Release the video capture object
  cap.release();

  // Close all windows
  destroyAllWindows();

  return 0;
}