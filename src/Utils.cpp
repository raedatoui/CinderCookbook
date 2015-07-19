//
//  Utils.cpp
//  CinderCookbook
//
//  Created by Raed Atoui on 7/19/15.
//
//

#include "Utils.h"

using namespace ci;
using namespace ci::app;
using namespace std;

string Utils::getCurrentTimestamp() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    return to_string(now->tm_year + 1900) + '-' + to_string(now->tm_mon + 1) + '-' +  to_string(now->tm_mday) + '-' + to_string(now->tm_hour) + '-' + to_string(now->tm_min) + "-" + to_string(now->tm_sec);
}

fs::path Utils::getAssetsDirectoryPath() {
    
    return fs::path(getPathDirectory(getAssetPath(fs::path(".gitignore")).string()));
}