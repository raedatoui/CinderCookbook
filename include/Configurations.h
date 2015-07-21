//
//  Configurations.h
//  CinderCookbook
//
//  Created by Raed Atoui on 7/15/15.
//
//

#ifndef __CinderCookbook__Configurations__
#define __CinderCookbook__Configurations__

#include "cinder/Cinder.h"
#include "cinder/Color.h"
#include "cinder/Quaternion.h"
#include "cinder/Function.h"
#include "cinder/params/Params.h"
#include "cinder/Xml.h"
#include "cinder/Json.h"

#include "Utils.h"

#include <string>
#include <vector>
#include <iterator>

#include <boost/algorithm/string.hpp>

using namespace ci;
using namespace ci::app;
using namespace std;


//-----------------------------------------------------------------------------

enum ConfigParamTypes
{
    _NODE,
    _BOOL,
    _FLOAT,
    _DOUBLE,
    _INT,
    _VEC2F,
    _VEC3F,
    _QUATF,
    _COLOR,
    _COLORA,
    _STRING
};

//-----------------------------------------------------------------------------


class ConfigParam
{
    
public:
    ConfigParam(const std::string &aName, void* aParam, ConfigParamTypes aType)
    {
        name = aName;
        
        // === Convert name to alphanum and replace spaces
        // trim spaces
        boost::trim(name);
        // remove multiple spaces
        std::function<bool(char,char)> isConsecutiveWhiteSpace = []( char a, char b ) { return isspace(a) && isspace(b); };
        name.erase( std::unique(name.begin(), name.end(), isConsecutiveWhiteSpace), name.end() );
        // replace spaces with _
        std::replace(name.begin(), name.end(), ' ', '_');
        // remove all not valid chars
        std::function<int(int)> isNameChar = [](char c){ return ( isalnum(c) || c == '_' ); };
        name.erase( std::remove_if(name.begin(), name.end(), not1( isNameChar ) ), name.end() );
        // convert name to lowercase
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        
        param = aParam;
        type = aType;
    }
    ~ConfigParam()
    {
        param = NULL;
    }
    
    std::string name;
    void* param;
    ConfigParamTypes type;
};
//-----------------------------------------------------------------------------

class ConfigManager;
typedef std::shared_ptr<ConfigManager> ConfigManagerRef;


class ConfigManager
{
    
public:
  
    static ConfigManagerRef create() { return std::make_shared<ConfigManager>(); }

    ConfigManager();
  
    //-----------------------------------------------------------------------------
    void save();
    void load(fs::path filePath);
    void draw();
    void addButton( const std::string &name, const std::function<void()> &callback, const std::string &optionsStr = "" );
    
    //-----------------------------------------------------------------------------
    
    template <typename T>
    params::InterfaceGl::Options<T> addParam( const std::string &name, T *target, bool readOnly = false, const std::string &keyName = "" );

    void addParam( const std::string &name, Vec2f *vectorParam, bool readOnly = false, const std::string &keyName = "" );
    void addParam( const std::string &name, const std::vector<std::string> &enumNames, int *param, const std::string &optionsStr = "", bool readOnly = false, const std::string &keyName = "" );

    void newNode( const std::string &name, const std::string &optionsStr = "" );
    //-----------------------------------------------------------------------------
    
    
protected:
    
    template <typename T>
    params::InterfaceGl::Options<T>    addParamImpl( const std::string &name, T *target, ConfigParamTypes aType, bool readOnly, const std::string &keyName = "" );
    
    void addConfigParam( const std::string &name, const std::string &keyName, void* param, ConfigParamTypes type);
    //-----------------------------------------------------------------------------
    
    
    std::vector<ConfigParam> mConfigParameters;
    params::InterfaceGlRef   mVisualParams;
    bool                     mDrawParams;
};




#endif /* defined(__CinderCookbook__Configurations__) */
