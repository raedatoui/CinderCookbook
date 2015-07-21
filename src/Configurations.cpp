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
    fs::path filePath = outputPath / fs::path(timeStamp + ".json");
    
//    std::string myXmlStr( "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" );
//    XmlTree doc(myXmlStr);
//    XmlTree node;
//    node.setTag("general");
    
    
    JsonTree doc;
    JsonTree node;
    
    for(std::vector<ConfigParam>::iterator it = mConfigParameters.begin(); it!=mConfigParameters.end(); ++it)
    {
        
        JsonTree pn;
        
        console() << node.getKey() << " " << it->name <<  endl;
        
        switch(it->type)
        {
            case _NODE:
                // cant check if node is initialized
                //
                if(doc.getNumChildren() > 0) {
                    doc.addChild(node);
                }
                node = JsonTree::makeObject(it->name);

                if(doc.getNumChildren() == 0) {
                    doc.addChild(node);
                }
                
                break;
            case _BOOL:
                if( *((bool*)it->param) ) {
                    pn = JsonTree( it->name, 1 );

                } else {
                    pn = JsonTree( it->name, 0 );
                }
                node.addChild( pn );
                break;
            case _FLOAT:
                pn = JsonTree( it->name, *((float*)it->param)  );
                node.addChild( pn );
                break;
            case _DOUBLE:
                pn = JsonTree( it->name,*((double*)it->param)  );
                node.addChild( pn );
                break;
            case _INT:
                pn = JsonTree( it->name, *((int*)it->param)  );
                node.addChild( pn );
                break;
            case _VEC3F:
                pn = JsonTree::makeObject( it->name )
                .addChild(JsonTree("x", (*((Vec3f*)it->param)).x))
                .addChild(JsonTree("y", (*((Vec3f*)it->param)).y))
                .addChild(JsonTree("z", (*((Vec3f*)it->param)).z));
                node.addChild( pn );
                break;
            case _VEC2F:
                pn = JsonTree::makeObject( it->name )
                .addChild(JsonTree("x", (*((Vec2f*)it->param)).x))
                .addChild(JsonTree("y", (*((Vec2f*)it->param)).y));
                node.addChild( pn );
                break;
            case _QUATF:
                pn = JsonTree::makeObject( it->name )
                .addChild(JsonTree("w", (*((Quatf*)it->param)).w))
                .addChild(JsonTree("x", (*((Quatf*)it->param)).v.x))
                .addChild(JsonTree("y", (*((Quatf*)it->param)).v.y))
                .addChild(JsonTree("z", (*((Quatf*)it->param)).v.z));
                node.addChild( pn );
                break;
            case _COLOR:
                pn = JsonTree::makeObject( it->name )
                .addChild(JsonTree("r", (*((Color*)it->param)).r))
                .addChild(JsonTree("g", (*((Color*)it->param)).g))
                .addChild(JsonTree("b", (*((Color*)it->param)).b));
                node.addChild( pn );
                break;
            case _COLORA:
                pn = JsonTree::makeObject( it->name )
                .addChild(JsonTree("r", (*((ColorA*)it->param)).r))
                .addChild(JsonTree("g", (*((ColorA*)it->param)).g))
                .addChild(JsonTree("b", (*((ColorA*)it->param)).b))
                .addChild(JsonTree("a", (*((ColorA*)it->param)).a));
                node.addChild( pn );
                break;
            case _STRING:
                pn = JsonTree( it->name, *((std::string*)it->param)  );
                node.addChild( pn );
                break;
        }
    }
    
    doc.addChild(node);
    doc.write(filePath);
}

// New Params API -------------------------------------------------------------------

// some types might not work well right now (char, uint...)
// using the types specified in AntTweakBar.h (TW_TYPE_FLOAT, instead of _FLOAT)
// might be more a more accurate match to what's Params.h supports

template <> params::InterfaceGl::Options<bool>      ConfigManager::addParam( const std::string &name, bool *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _BOOL, readOnly, keyName ); }

template <> params::InterfaceGl::Options<char>      ConfigManager::addParam( const std::string &name, char *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _STRING, readOnly, keyName ); }

template <> params::InterfaceGl::Options<int8_t>    ConfigManager::addParam( const std::string &name, int8_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<uint8_t>   ConfigManager::addParam( const std::string &name, uint8_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<int16_t>   ConfigManager::addParam( const std::string &name, int16_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<uint16_t>  ConfigManager::addParam( const std::string &name, uint16_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<int32_t>   ConfigManager::addParam( const std::string &name, int32_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<uint32_t>  ConfigManager::addParam( const std::string &name, uint32_t *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _INT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<float>     ConfigManager::addParam( const std::string &name, float *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _FLOAT, readOnly, keyName ); }

template <> params::InterfaceGl::Options<double>    ConfigManager::addParam( const std::string &name, double *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _DOUBLE, readOnly, keyName ); }

template <> params::InterfaceGl::Options<string>    ConfigManager::addParam( const std::string &name, string *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _STRING, readOnly, keyName ); }

template <> params::InterfaceGl::Options<Color>     ConfigManager::addParam( const std::string &name, Color *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _COLOR, readOnly, keyName ); }

template <> params::InterfaceGl::Options<ColorA>    ConfigManager::addParam( const std::string &name, ColorA *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _COLORA, readOnly, keyName ); }

template <> params::InterfaceGl::Options<Quatf>     ConfigManager::addParam( const std::string &name, Quatf *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _QUATF, readOnly, keyName ); }

template <> params::InterfaceGl::Options<Quatd>     ConfigManager::addParam( const std::string &name, Quatd *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _QUATF, readOnly, keyName ); }

template <> params::InterfaceGl::Options<Vec3f>     ConfigManager::addParam( const std::string &name, Vec3f *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _VEC3F, readOnly, keyName ); }

template <> params::InterfaceGl::Options<Vec3d>     ConfigManager::addParam( const std::string &name, Vec3d *param, bool readOnly, const std::string &keyName ) { return addParamImpl( name, param, _VEC3F, readOnly, keyName ); }

template <typename T> params::InterfaceGl::Options<T> ConfigManager::addParamImpl( const std::string &name, T *target, ConfigParamTypes aType, bool readOnly, const std::string &keyName ) {
    addConfigParam(name, keyName, target, aType);
    return mVisualParams->addParam(name, target, readOnly);
}

void ConfigManager::newNode( const std::string &name, const std::string &optionsStr ) {
    mVisualParams->addSeparator();
    mVisualParams->addText(name, optionsStr);
    mConfigParameters.push_back( ConfigParam(name, 0, _NODE) );
}


// Depreacted Params API -------------------------------------------------------------------

void ConfigManager::addParam( const std::string &name, Vec2f *param, bool readOnly, const std::string &keyName) {
    addConfigParam(name, keyName, param, _VEC2F);
    mVisualParams->addParam( name + " X", &param->x, readOnly );
    mVisualParams->addParam( name + " Y", &param->y, readOnly );
}

void ConfigManager::addParam( const std::string &name, const std::vector<std::string> &enumNames, int *param, const std::string &optionsStr, bool readOnly, const std::string &keyName ) {
    mVisualParams->addParam(name, enumNames, param, optionsStr, readOnly);
    addConfigParam(name, keyName, param, _INT);
}

//-----------------------------------------------------------------------------------------

void ConfigManager::addConfigParam( const std::string &name, const std::string &keyName, void* param, ConfigParamTypes type) {
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
