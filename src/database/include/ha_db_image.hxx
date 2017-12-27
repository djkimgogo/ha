/* Copyright (C) HiAi, Inc - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by DJ Kim <djkimgo@gmail.com>, September 2017
 */
#pragma once
#ifndef _HA_IMAGE_HXX_
#define _HA_IMAGE_HXX_

#include <string>

#include <odb/core.hxx>

using namespace std;

#pragma db object
class HaDbImage {
public:
    HaDbImage (
        const std::string& frame,
        unsigned long imageGps
    )
    : frame_ (frame), imageGps_ (imageGps)
    {
    }

    const std::string&
    frame () const {
        return frame_;
    }

    unsigned long
    imageGps () {
        return imageGps_;
    }

    void
    imageGps (unsigned long imageGps) {
        imageGps_ = imageGps;
    }

private:
    friend class odb::access;
    HaDbImage() {}

    #pragma db id auto
    unsigned long id_;

    std::string frame_;
    unsigned long imageGps_;
};

#endif // _HA_IMAGE_HXX_
