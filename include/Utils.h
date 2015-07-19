//
//  Utils.h
//  CinderCookbook
//
//  Created by Raed Atoui on 7/19/15.
//
//
#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/Utilities.h"

#include <string>
#include <stdio.h>

using namespace std;

class Utils {

public:
    static string getCurrentTimestamp();
    static ci::fs::path getAssetsDirectoryPath();
    
};
