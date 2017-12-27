/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_GPS_HXX_
#define _HA_GPS_HXX_

#include <string>

#include <odb/core.hxx>

using namespace std;

#pragma db object
class HaDbGps {
public:
    HaDbGps (double latitude,
            double longitude,
            const std::string& date,
            const std::string& time,
            double speed,
            double angle
        )
        : latitude_ (latitude), longitude_ (longitude), date_ (date), time_ (time), speed_ (speed), angle_ (angle)
    {
    }

    double
    latitude () const
    {
      return latitude_;
    }

    void
    latitude (double latitude)
    {
        latitude_ = latitude;
    }

    double
    longitude () const
    {
      return longitude_;
    }

    void
    longitude (double longitude)
    {
        longitude_ = longitude;
    }

    double
    speed () const
    {
      return speed_;
    }

    void
    speed (double speed)
    {
        speed_ = speed;
    }

    double
    angle () const
    {
      return angle_;
    }

    void
    angle (double angle)
    {
        angle_ = angle;
    }

    const std::string&
    date () const
    {
      return date_;
    }

    void
    date (const std::string& date)
    {
        date_ = date;
    }

    const std::string&
    time () const
    {
      return time_;
    }

    void
    time (const std::string& time)
    {
        time_ = time;
    }

private:
    friend class odb::access;
    HaDbGps() {}

    #pragma db id auto
    unsigned long id_;

    double latitude_;
    double longitude_;
    std::string date_;
    std::string time_;
    double speed_;
    double angle_;
};

#endif // _HA_GPS_HXX_
