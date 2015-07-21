#include "CinderCookbookApp.h"

void CinderCookbookApp::setup()
{
    mCamWidth = 640;
    mCamHeight = 480;
    mCapture = Capture(mCamWidth, mCamHeight);
    
    
    mConfig = ConfigManager::create();

    mConfig->newNode("Scene");
    mColor = Color::white();
    mConfig->addParam( "Color", &mColor, false); // ColorA
    mConfig->addParam( "Light Direction", &mLightDirection, false); // Vec3f
    mConfig->addParam( "String ", &mString, false); // string
    
    mConfig->newNode("Cube");
    mConfig->addParam( "Cube Size", &mObjSize, false).min(0.1f).max(20.5f).step(0.1f);
    mConfig->addParam( "Cube Rotation", &mObjOrientation );

    
    mConfig->newNode("Circle");
    mPosition.x = (float)getWindowWidth() / 2.0f;
    mPosition.y = (float)getWindowHeight() / 2.0f;
    mConfig->addParam( "pos", &mPosition, false);
    
    mDragOffset = Vec2f::zero();
    mConfig->addParam( "drag offset", &mDragOffset, false);
    
    mRadius = 100.0f;
    mConfig->addParam( "radius", &mRadius, false);
    
    mScale = 1.0f;
    mConfig->addParam( "mScale", &mScale, false).min(0.0f).step(0.1f);
 
    mEnumNames.push_back( "Orange" );
    mEnumNames.push_back( "Apple" );
    mEnumNames.push_back( "Banana" );
    mEnumValue = 0;
    mConfig->addParam("Enum type parameter", mEnumNames, &mEnumValue);
    
    mConfig->newNode("Stuff");
    mConfig->addParam("A bool", &mShowThings);
    mConfig->addParam("a double", &mAmount);

}

void CinderCookbookApp::update()
{
    //    console() << getElapsedFrames() << std::endl;
}

void CinderCookbookApp::resize()
{
    mRect.x1 = 20.0f;
    mRect.y1 = 20.0f;
    mRect.x2 = getWindowWidth() - 20.0f;
    mRect.y2 = getWindowHeight() - 20.0f;
}

void CinderCookbookApp::draw()
{
    // clear out the window with black
    gl::enableAlphaBlending();
    
    gl::clear( Color( 0, 0, 0 ) );
    
    gl::color( ColorA(1.0f,0.0f, 1.0f, 0.2f));
    gl::drawSolidRect( mRect );
    
    gl::color( mColor );
    gl::drawSolidCircle( mPosition, mRadius );
    
    
    transform();
    // apply transform
    gl::pushModelView();
    
    // usual way to update modelview matrix
    gl::multModelView( mTransform );
    
    
    if( mTextures.size() ){
        int gridRes = (int)ceil( sqrtf( (float)mTextures.size() ) );
        float w = (float)getWindowWidth() / gridRes;
        float h = (float)getWindowHeight() / gridRes;
        Vec2f pos = Vec2f::zero();
        
        for( vector<gl::Texture>::iterator it = mTextures.begin(); it != mTextures.end(); ++it ) {
            gl::draw( *it, Rectf( pos.x, pos.y, pos.x + w, pos.y + h ) );
            if( pos.x + w > getWindowWidth() - w ) {
                pos.x = 0.0f;
                pos.y += h;
            }
            else {
                pos.x += w;
            }
        }
    }
    
    // restore transform
    gl::popModelView();
    gl::disableAlphaBlending();

    mConfig->draw();
}


void CinderCookbookApp::prepareSettings( CinderCookbookApp::Settings *settings)
{
    settings->setTitle("CockyBooky");
    settings->setFrameRate( 60.0f );
    settings->setWindowSize(1024, 768);
}

void CinderCookbookApp::shutdown() {
    XmlTree doc = XmlTree::createDoc();
    XmlTree settings = XmlTree("setting", "");
    doc.push_back(settings);
    doc.write(writeFile("cettings.xml"));
}

void CinderCookbookApp::mouseDown( MouseEvent event )
{
    float distance = mPosition.distance( event.getPos() );
    if( distance < mRadius ){
        mDragged = true;
        mDragOffset = mPosition - event.getPos();
        mColor = Color( 0.0f, 1.0f, 0.0f );
    } else {
        mDragged = false;
    }
}

void CinderCookbookApp::mouseUp( MouseEvent event )
{
    if( mDragged ){
        mColor = Color( 1.0f, 1.0f, 0.0f );
    }
    mDragged = false;
}

void CinderCookbookApp::mouseWheel( MouseEvent event )
{
    mRadius += event.getWheelIncrement();
    if( mRadius < 0.0f ){
        mRadius = 0.0f;
    }
    mScale = lmap(mRadius, -50.0f, 300.0f, 0.0f, 1.0f);
    console() << mScale << endl;
    
}

void CinderCookbookApp::mouseMove( MouseEvent event )
{
    float distance = mPosition.distance( event.getPos() );
    if( distance < mRadius ){
        mColor = Color( 1.0f, 1.0f, 0.0f );
    } else {
        mColor = Color( 1.0f, 1.0f, 1.0f );
    }
}

void CinderCookbookApp::mouseDrag( MouseEvent event )
{
    if( mDragged ){
        mPosition = event.getPos() + mDragOffset;
    }
}

void CinderCookbookApp::fileDrop( FileDropEvent event ){
    const vector< fs::path >& files = event.getFiles();
    mTextures.clear();
    for( vector<fs::path>::const_iterator it = files.begin(); it != files.end(); ++it ){
        console() << it->extension() << endl;
        if( it->extension().string().compare( ".png" ) == 0 ){
            console() << *it << endl;
            gl::Texture texture = gl::Texture( loadImage( *it ));
            mTextures.push_back( texture );
        }
        
    }
}

void CinderCookbookApp::transform()  {
    // construct transformation matrix
    mTransform.setToIdentity();
    mTransform.translate( ci::Vec3f( mPosition, 0.0f ) );
    //    mTransform *= mRotation.toMatrix44();
    mTransform.scale(  ci::Vec2f( mScale, mScale ) );
    
    //    if( mAnchorIsPercentage )
    //        mTransform.translate( ci::Vec3f( ci::Vec3f(0, 0, 0)) * getSize(), 0.0f ) );
    //    else
    //        mTransform.translate( ci::Vec3f( -mAnchor, 0.0f ) );
    
}

CINDER_APP_NATIVE( CinderCookbookApp, RendererGl )
