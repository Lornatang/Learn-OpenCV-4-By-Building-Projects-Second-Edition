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

// OpenGL includes
#ifdef __APPLE__

#include <OpenGL/gl.h>

#else
#include <GL/gl.h>
#endif

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

Mat frame;
GLfloat angle = 0.0;
GLuint texture;
VideoCapture camera;

int loadTexture() {

  if (frame.data == nullptr) return -1;

  glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
  return 0;

}

void on_opengl(void *param) {
  glLoadIdentity();
  // Load Texture
  glBindTexture(GL_TEXTURE_2D, texture);
  // Rotate plane
  glRotatef(angle, 1.0f, 1.0f, 1.0f);
  // Create the plate
  glBegin(GL_QUADS);
  glTexCoord2d(0.0, 0.0);
  glVertex2d(-1.0, -1.0);
  glTexCoord2d(1.0, 0.0);
  glVertex2d(+1.0, -1.0);
  glTexCoord2d(1.0, 1.0);
  glVertex2d(+1.0, +1.0);
  glTexCoord2d(0.0, 1.0);
  glVertex2d(-1.0, +1.0);
  glEnd();

}

int main(int argc, const char **argv) {
  // Open WebCam
  camera.open(0);
  if (!camera.isOpened()) {
    camera.open("Recording3.webm");
    if (!camera.isOpened())
      return -1;
  }

  // Create new windows
  namedWindow("OpenGL Camera", WINDOW_OPENGL);

  // Enable texture
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &texture);

  setOpenGlDrawCallback("OpenGL Camera", on_opengl);

  while (waitKey(30) != 'q') {
    camera >> frame;
    // Create first texture
    loadTexture();
    updateWindow("OpenGL Camera");
    angle = angle + 4;
  }

  // Destroy the windows
  destroyWindow("OpenGL Camera");

  return 0;
}