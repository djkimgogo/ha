/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_VISUALIZER_
#define _HA_VISUALIZER_

#include "ha_common.h"
#include "ha_config.h"

namespace ha {
  class HaViz : public HaCommon {
  public:
    void imgshow(const std::string &name, cv::Mat &src, cv::Mat &dst, const double time, const uint8_t scale = 1);
    void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1);
  };
}

#endif /* end of include guard: _HA_VISUALIZER_ */
