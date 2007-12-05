/** A Class to load and manage loaded Plugins
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    26.11.2007
 * @version 0.1
 */

#ifndef WIN32
    #include <dlfcn>
    #include <dirent>
#else
    #include <Windows.h>
#endif

#include <iostream>
#include <string.h>
#include "PluginLoader.h"
#include "TrinitasPlugin.h"



/** Construcktor for the PluginLoader later maby we should rename
 * this to PluginManaer
 */
PluginLoader::PluginLoader(void) {
    mPlugins = new vector<TrinitasPlugin*>();
}


void PluginLoader::Load(char *path) {

    //check if the String is a existing path
    // run through all files test them if they are plugins
    // maby use a protected tool method...
    TrinitasPlugin  *loadedPlugin = NULL;
    #ifndef WIN32
        DIR             *dp;
        struct dirent   *dirp;
        //test if we could open the path
        if((dp  = opendir(path) != NULL) {
            //run through all files
            while ((dirp = readdir(dp)) != NULL) {
                loadedPlugin = LoadPlugin(dirp->d_name);
                if (loadedPlugin)
                    mPlugins->push_back(loadedPlugin);
            }
            closedir(dp);
        }
    #else // Windwos stuff
        HANDLE          fileHandle;
        WIN32_FIND_DATA fileInfos;
        /*first we need to take convert the normal
         *pathstring into a path wich Windows undestand
         */
        char  *winPath    = new char[4098];
        sprintf(winPath,"%s\\*",path);
        fileHandle=FindFirstFile(winPath,&fileInfos);
        delete winPath;
        // Ergebnis Nummer 2 ist auch uninteressant (ist ".."):
        while (FindNextFile(fileHandle, &fileInfos) != 0) {
            cout << "Loading Plugin: \t" << fileInfos.cFileName << std::endl;
            if ((fileInfos.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)==false) {
                char *filePath      = new char[4098];
                sprintf(filePath,"%s\\%s",path,fileInfos.cFileName);
                loadedPlugin = LoadPlugin(filePath);
                if (loadedPlugin)
                    mPlugins->push_back(loadedPlugin);
                delete filePath;
            }
        }
        FindClose(fileHandle);
    #endif
}

TrinitasPlugin* PluginLoader::GetByID(long pluginId) {
    //need to implement
    return NULL;
}

 TrinitasPlugin* PluginLoader::GetByName(char* pluginName) {
     vector<TrinitasPlugin *>::iterator iter;
     bool                               found       = false;
     TrinitasPlugin                     *tmpPlugin  = NULL;
     //use an iterator wich "runs through the Vector
     iter = mPlugins->begin();
//     while ((iter != mPlugins->end()) && (!found)) {
     while (iter != mPlugins->end()) {
        found = strcmp((*iter)->GetName(),pluginName);
        if (!found)
            iter++;
     }
     if (found)
        return *iter;
    else
        return NULL;
 }

 TrinitasPlugin* PluginLoader::LoadPlugin(char *file) {
    TrinitasPlugin  *loadedPlugin = NULL;
    #ifndef WIN32
        void* libraryHandle = dlopen(file, RTLD_LAZY);
        if (libraryHandle != NULL) {
            //using typedef to define a Functiontemplate for the loaded symbols
            typedef TrinitasPlugin* (*pluginFunction)(long id);
            //using the functionvar the Plugin as referrence
            pluginFunction thePlugin;
            thePlugin = (pluginFunction) dlsym(libraryHandle, "getPlugin");
            //call getPlugin with the actual ID
            loadedPlugin = (TrinitasPlugin *) thePlugin(mPlugins->size());
        }
        dlclose(libraryHandle);
    #else // Windwos stuff
        //using typedef to define a Functiontemplate for the loaded symbols
        typedef TrinitasPlugin* ( *pluginFunction)(long);
        pluginFunction thePlugin;
        //turn off this stupid and anyoing error dialog box
//        SetErrorMode(SEM_FAILCRITICALERRORS);
        HINSTANCE__* libraryHandle = LoadLibraryA(file);
        if (libraryHandle != NULL) {
            //call getPlugin with the actual ID
            thePlugin = (pluginFunction) GetProcAddress(libraryHandle, "getPlugin");
            if (thePlugin!=NULL)
                loadedPlugin = thePlugin(mPlugins->size());
            FreeLibrary(libraryHandle);
        }
    #endif
     return loadedPlugin;
 }
