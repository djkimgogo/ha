/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by https://stackoverflow.com/questions/13607163/gpsd-client-data-buffer/13617355#13617355
 * Modified by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#include "ha_gps.h"
#include "ha_db_class.h"

using namespace ha;

int main(void)
{
    HaGps haGps;
    HaDbGps gps_data;

    for(;;){
        if (!haGps.init_gps()) {
            continue;
        }

        std::string buffer;
        for (;;) {
            if (haGps.read_gps(buffer)) {
                haGps.parse_gps(buffer, gps_data);
            }
        }
    }
}
