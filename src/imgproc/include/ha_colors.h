/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #pragma once
 #ifndef _HA_COLORS_H_
 #define _HA_COLORS_H_

 #include "ha_common.h"
 #include "ha_config.h"

 namespace ha {
   class HaColors : public HaCommon {
     private:
         HaColorTypes m_colorTypes = HaColorTypes::R;
     public:
       void colorExtractionFrame(cv::Mat &input, const uint8_t scale = 1);
       void setColorTypes(const HaColorTypes colorType) { this->m_colorTypes = colorType; }
       void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1);
   };
 }

 #endif /* end of include guard:_HA_COLORS_H_ */
