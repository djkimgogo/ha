/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#include "ha_gps.h"

static gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

ha::HaGps::HaGps() {
    //For version 3.7
}

bool ha::HaGps::init_gps() {
    bool success(true);

    if (gps_rec.stream(WATCH_ENABLE|WATCH_NMEA) == NULL) {
        cout << "No GPSD running. Retry to connect in " << RETRY_TIME << " seconds." << endl;
        usleep(RETRY_TIME * ONE_SECOND);
        success = false;
    }

    return success;
}

bool ha::HaGps::read_gps(std::string &buffer) {
    bool success(true);
    struct gps_data_t* newdata;

    if (!gps_rec.waiting(WAITING_TIME)) {
        success = false;
    } else {
        if ((newdata = gps_rec.read()) == NULL) {
            // cerr << "Read error.\n";
            success = false;
        } else {
            const char* buf = gps_rec.data();
            buffer = std::string(buf);
        }
    }
    return success;
}

bool ha::HaGps::parse_gps(std::string &s, HaDbGps &gps_data) {
    bool success(false);
    try {
        std::string delimiter(",");
        int i=0;

        if (s.find("GPRMC")!=std::string::npos) {
            std::string ss = s.substr(s.find("$GPRMC"));
            if (ss.empty()) {
                return success;
            }
            if (ss.find("{")!=std::string::npos) {
                ss = ss.substr(0, ss.find("{")-1);
            }
            if (ss.empty()) {
                return success;
            }
            size_t pos = 0;
            std::string token;
            while ((pos = ss.find(delimiter)) != std::string::npos) {
                token = ss.substr(0, pos);
                if (i==1 || (i>=3 && i<=9)) {
                    switch (i) {
                        case 1:
                            gps_data.time(token);
                            break;
                        case 3:
                            gps_data.latitude(stod(token.c_str()) / 100.0);
                            break;
                        case 4:
                            gps_data.latitude(gps_data.latitude()*(strcmp(token.c_str(),"N")==0 ? 1.0 : -1.0));
                            break;
                        case 5:
                            gps_data.longitude(stod(token.c_str()) / 100.0);
                            break;
                        case 6:
                            gps_data.longitude(gps_data.longitude()*(strcmp(token.c_str(),"E")==0 ? 1.0 : -1.0));
                            break;
                        case 7:
                            gps_data.speed(stod(token.c_str()));
                            break;
                        case 8:
                            gps_data.angle(stod(token.c_str()));
                            break;
                        case 9:
                            gps_data.date(token);
                            break;
                        default:
                            break;
                    }
                }
                ss.erase(0, pos + delimiter.length());
                i++;
            }
            success = true;
        }
    } catch (std::exception &e) {
        spd::get("console")->error("{}", e.what());
    }
    return success;
}
