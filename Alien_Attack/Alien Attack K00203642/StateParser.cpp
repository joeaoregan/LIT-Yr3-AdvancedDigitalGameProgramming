/*
//  StateParser.cpp
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 24/02/2013.
//  Copyright (c) 2013 shaun mitchell. All rights reserved.
*/

#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

using namespace std;

bool StateParser::parseState(const char *stateFile, string stateID, vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs) {    
    TiXmlDocument xmlDoc;	// create the XML document
    
    // load the state file
    if(!xmlDoc.LoadFile(stateFile)) {
        cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }
        
    TiXmlElement* pRoot = xmlDoc.RootElement();	// get the root element
        
    TiXmlElement* pStateRoot = 0;				// pre declare the states root node
    // get this states root node and assing it to pStateRoot
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == stateID) {
            pStateRoot = e;
			break;
        }
    }    
    
    TiXmlElement* pTextureRoot = 0;	// pre declare the texture root
    
    // get the root of the texture elements
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        if(e->Value() == string("TEXTURES")) {
            pTextureRoot = e;
			break;
        }
    }    
    
    parseTextures(pTextureRoot, pTextureIDs);	// now parse the textures
        
    TiXmlElement* pObjectRoot = 0;				// pre declare the object root node
    
    // get the root node and assign it to pObjectRoot
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()){
        if(e->Value() == string("OBJECTS")){
            pObjectRoot = e;
			break;
        }
    }

    // now parse the objects
    parseObjects(pObjectRoot, pObjects);
    
    return true;
}

void StateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string> *pTextureIDs){
    // for each texture we get the filename and the desired ID and add them to the texture manager
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
        string filenameAttribute = e->Attribute("filename");
        string idAttribute = e->Attribute("ID");
        
        pTextureIDs->push_back(idAttribute); // push the id into the list
        
        TheTextureManager::Instance()->load(filenameAttribute, idAttribute, TheGame::Instance()->getRenderer());
    }
}

void StateParser::parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjects) {
    for(TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())     {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        string textureID;
        
        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width",&width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callbackID", &callbackID);
        e->Attribute("animSpeed", &animSpeed);
        
        textureID = e->Attribute("textureID");
        //int x, int y, int width, int height, std::string textureID, int numFrames, void()
         GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed)));
        pObjects->push_back(pGameObject);
    }
}