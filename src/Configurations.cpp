//
//  Configurations.cpp
//  CinderCookbook
//
//  Created by Raed Atoui on 7/15/15.
//
//

#include "Configurations.h"

using namespace ci;
using namespace ci::app;
using namespace std;

ConfigManager::ConfigManager() {
    mVisualParams = params::InterfaceGl::create( getWindow(), "Configurations", toPixels( Vec2i( 400, 550 ) ) );
    mVisualParams->addButton("Save Config", std::bind(&ConfigManager::save, this) );
}


void ConfigManager::save() {
    
    fs::path outputPath = Utils::getAssetsDirectoryPath();
    string timeStamp = Utils::getCurrentTimestamp();
    fs::path filePath = outputPath / fs::path(timeStamp + ".xml");
    
    std::string myXmlStr( "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" );
    XmlTree doc(myXmlStr);
    XmlTree node;
    node.setTag("general");
    
    for(std::vector<ConfigParam>::iterator it = mConfigParameters.begin(); it!=mConfigParameters.end(); ++it)
    {
        XmlTree pn;
        pn.setTag(it->name);
        
        switch(it->type)
        {
            case _NODE:
                doc.push_back( node );
                node = XmlTree();
                node.setTag(it->name);
                break;
            case _BOOL:
                if( *((bool*)it->param) ) {
                    pn.setValue<int>( 1 );
                } else {
                    pn.setValue<int>( 0 );
                }
                node.push_back( pn );
                break;
            case _FLOAT:
                pn.setValue<float>( *((float*)it->param) );
                node.push_back( pn );
                break;
            case _DOUBLE:
                pn.setValue<double>( *((double*)it->param) );
                node.push_back( pn );
                break;
            case _INT:
                pn.setValue<int>( *((int*)it->param) );
                node.push_back( pn );
                break;
            case _VEC3F:
                pn.setAttribute<float>("x", (*((Vec3f*)it->param)).x);
                pn.setAttribute<float>("y", (*((Vec3f*)it->param)).y);
                pn.setAttribute<float>("z", (*((Vec3f*)it->param)).z);
                node.push_back( pn );
                break;
            case _QUATF:
                pn.setAttribute<float>("w", (*((Quatf*)it->param)).w);
                pn.setAttribute<float>("x", (*((Quatf*)it->param)).v.x);
                pn.setAttribute<float>("y", (*((Quatf*)it->param)).v.y);
                pn.setAttribute<float>("z", (*((Quatf*)it->param)).v.z);
                node.push_back( pn );
                break;
            case _COLOR:
                pn.setAttribute<float>("r", (*((Color*)it->param)).r);
                pn.setAttribute<float>("g", (*((Color*)it->param)).g);
                pn.setAttribute<float>("b", (*((Color*)it->param)).b);
                node.push_back( pn );
                break;
            case _COLORA:
                pn.setAttribute<float>("r", (*((ColorA*)it->param)).r);
                pn.setAttribute<float>("g", (*((ColorA*)it->param)).g);
                pn.setAttribute<float>("b", (*((ColorA*)it->param)).b);
                pn.setAttribute<float>("a", (*((ColorA*)it->param)).a);
                node.push_back( pn );
                break;
            case _STRING:
                pn.setValue<std::string>( *((std::string*)it->param) );
                node.push_back( pn );
                break;
        }
    }
    
    doc.push_back( node );
    doc.write(writeFile(filePath));
}

// New Params API -------------------------------------------------------------------

// some types might not work well right now (char, uint...)
// using the types specified in AntTweakBar.h (TW_TYPE_FLOAT, instead of _FLOAT)
// might be more a more accurate match to what's Params.h supports

template <> params::InterfaceGl::Options<bool> ConfigManager::addParam( const std::string &name, bool *param, bool readOnly, const std::string &keyName ) {
    return addParamImpl( name, param, _BOOL, readOnly, keyName ); }

template <> params::InterfaceGl::Options<char>  ConfigManager::addParam( const std::string &name, char *param, bool readOnly, const std::string &keyName ) {
    return addParamImpl( name, param, _STRING, readOnly, keyName ); }

template <> params::InterfaceGl::Options<int8_t>    ConfigManager::addParam( const std::string &name, int8_t *param, bool readOnly, const std::string &keyName ) {
    return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<uint8_t>    ConfigManager::addParam( const std::string &name, uint8_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<int16_t>    ConfigManager::addParam( const std::string &name, int16_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<uint16_t>    ConfigManager::addParam( const std::string &name, uint16_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<int32_t>    ConfigManager::addParam( const std::string &name, int32_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<uint32_t>    ConfigManager::addParam( const std::string &name, uint32_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<float>        ConfigManager::addParam( const std::string &name, float *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _FLOAT, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<double>    ConfigManager::addParam( const std::string &name, double *param, bool readOnly, const std::string &keyName ) {
    return addParamImpl( name, param, _DOUBLE, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<string>    ConfigManager::addParam( const std::string &name, string *param, bool readOnly, const std::string &keyName ) {
    return addParamImpl( name, param, _STRING, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<Color>        ConfigManager::addParam( const std::string &name, Color *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _COLOR, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<ColorA>    ConfigManager::addParam( const std::string &name, ColorA *param, bool readOnly, const std::string &keyName ) {
    return addParamImpl( name, param, _COLORA, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<Quatf>        ConfigManager::addParam( const std::string &name, Quatf *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _QUATF, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<Quatd>        ConfigManager::addParam( const std::string &name, Quatd *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _QUATF, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<Vec3f>        ConfigManager::addParam( const std::string &name, Vec3f *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _VEC3F, readOnly, keyName  ); }

template <> params::InterfaceGl::Options<Vec3d>        ConfigManager::addParam( const std::string &name, Vec3d *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _VEC3F, readOnly, keyName  ); }

template <typename T>

params::InterfaceGl::Options<T>    ConfigManager::addParamImpl( const std::string &name, T *target, ConfigParamTypes aType, bool readOnly, const std::string &keyName )
{
    // should check for params initialized?
    addConfigParam(name, keyName, target, aType);
    return mVisualParams->addParam(name, target, readOnly);
}

void ConfigManager::newNode( const std::string &name, const std::string &optionsStr )
{
    mVisualParams->addSeparator();
    mVisualParams->addText(name, optionsStr);
    mConfigParameters.push_back( ConfigParam(name, 0, _NODE) );
}

//-----------------------------------------------------------------------------

void ConfigManager::addConfigParam( const std::string &name, const std::string &keyName, void* param, ConfigParamTypes type)
{
    std::string _keyName;
    (keyName == "") ? _keyName = name : _keyName = keyName;
    mConfigParameters.push_back( ConfigParam(_keyName, param, type) );
}

void ConfigManager::draw() {
    mVisualParams->draw();
}

void ConfigManager::addButton( const std::string &name, const std::function<void ()> &callback, const std::string &optionsStr ) {
    mVisualParams->addButton(name, callback, optionsStr);
}
