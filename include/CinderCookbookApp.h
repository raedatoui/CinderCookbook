#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "cinder/Xml.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"

#include "Configurations.h"


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

    
    // camera
    int mCamWidth;
    int mCamHeight;
    Capture mCapture;
    
    //drag drop images
    vector< gl::Texture > mTextures;
    
    // configuration / interfacegl manager
    ConfigManagerRef mConfig;
    
    // parameters to manage
    Vec2f           mPosition;
    Vec2f           mDragOffset;
    float           mRadius;
    float           mScale;
    ColorA          mColor;
    Matrix44f       mTransform;
    Rectf           mRect;
    float           mObjSize;
    Quatf           mObjOrientation;
    Vec3f           mLightDirection;
    string          mString;
    vector<string>	enumNames;
    int				enumValue;
    
    bool        mDragged;

};