#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "cinder/Xml.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h"
#include "cinder/Xml.h"

#include <string>
#include <list>


using namespace ci;
using namespace ci::app;
using namespace std;

class CinderCookbookApp : public AppNative {

public:

    void prepareSettings(Settings *settings);
    void setup();
    void update();
    void draw();
    void shutdown();


    void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );
    void mouseWheel( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void resize();

    void transform();
    void fileDrop( FileDropEvent event );
    void loadConfig();
    void saveConfig();
    
    int mCamWidth;
    int mCamHeight;
    Capture mCapture;

    Vec2f   mPosition, mDragOffset;
    float mRadius;
    float mScale;
    ColorA mColor;
    bool mDragged;
    ci::Matrix44f mTransform;
    Rectf mRect;

    vector< gl::Texture > mTextures;
    
    
    float mObjSize;
    Quatf mObjOrientation;
    Vec3f mLightDirection;

    params::InterfaceGl mParams;
    string mString;

    string mHostIP;
    int mHostPort;
};
