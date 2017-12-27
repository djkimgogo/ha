/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#include "ha_visualizer.h"

#include <opencv2/highgui.hpp>

void ha::HaViz::imgshow(const std::string &name, cv::Mat &src, cv::Mat &dst, const double time, const uint8_t scale) {
  namedWindow( name, 1 );
  cv::Mat img;
  scaleTo(dst, dst, scale);
  if (src.channels() == dst.channels()) {
  } else {
    if (src.channels() == 3) {
        cvtToColor(dst, dst);
    } else if (dst.channels() ==3) {
        cvtToColor(src, src);
    } else {
      spd::get("console")->error("src.depth == dst.depth?");
      return;
    }
  }

  if (time > 0.0) {
    char scaleStr[256];
    snprintf(scaleStr, 256, "%.4f FPS", 1.0/time);
    rectangle(dst, Point(10, 5), Point(130, 25), Scalar(0,255,0), CV_FILLED);
    putText(dst, scaleStr, Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
  }

  // printf("ch: %d === %d\n", src.channels(), dst.channels());
  // img = cv::Mat(src.rows, src.cols * 2, 3);
  // src.copyTo(img(cv::Rect(0, 0, src.cols, src.rows)));
  // dst.copyTo(img(cv::Rect(src.cols, 0, src.cols, src.rows)));
  imshow( name, dst );
  moveWindow(name, 0, 0);
}

void ha::HaViz::drawOutput(Mat &dst, const Scalar scalar, const uint8_t scale) {
    // TBD
}
