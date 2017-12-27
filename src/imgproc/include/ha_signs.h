/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
 #pragma once
 #ifndef _HA_SIGNS_H_
 #define _HA_SIGNS_H_

 #include "ha_common.h"
 #include "ha_config.h"

 namespace ha {
   class HaSigns : public HaCommon {
     private:
         HaSignTypes m_signTypes = HaSignTypes::TRAFFIC;
     public:
       void signExtractionFrame(cv::Mat &input, const uint8_t scale = 1);
       void setSignTypes(const HaSignTypes signType) { this->m_signTypes = signType; }
       void drawOutput(Mat &dst, const Scalar scalar = Scalar(0,0,255), const uint8_t scale = 1);
   };
 }

 #endif /* end of include guard:_HA_SIGNS_H_ */
