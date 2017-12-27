/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */

 #pragma once
#ifndef _HA_GPS_H_
#define _HA_GPS_H_

#include <iostream>
#include <unistd.h>

#include "ha_common.h"
#include "ha_config.h"

#include "libgpsmm.h"
// #include "ha_db_class.h"
#include "ha_db_gps.hxx"
#include "ha_db_gps-odb.hxx"

using namespace std;

#define WAITING_TIME 5000000
#define RETRY_TIME 5
#define ONE_SECOND 1000000

namespace ha {
    class HaGps {
    private:
    public:
        HaGps();
        bool init_gps();
        bool read_gps(std::string &buffer);
        bool parse_gps(std::string &s, HaDbGps &gps_data);
    };
}

#endif // _HA_GPS_H_
