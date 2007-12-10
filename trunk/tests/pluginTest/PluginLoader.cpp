/** A Class to load and manage loaded Plugins
 * Copyright 2007 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    26.11.2007
 * @version 0.1
 */

#ifndef WIN32
    #include <dlfcn.h>
    #include <dirent.h>
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
        DIR             *pluginDirectory;
        struct dirent   *entry;
        //test if we could open the path
        cout << "Searching Plugin in: \t" << path << std::endl;
        pluginDirectory  = opendir(path);
        //pluginDirectory  = opendir(".");
        if (pluginDirectory != NULL) {
            //run through all files
            void *pluginHandel;
            cout << "hier!" << std::endl;
            entry = readdir(pluginDirectory);
            while (entry != NULL)  {
                cout << "try to load: \t" << entry->d_name << std::endl;
                char *filePath      = new char[4098];
                sprintf(filePath,"%s/%s",path,entry->d_name);
                loadedPlugin = LoadPlugin(filePath);
                if (loadedPlugin)
                    mPlugins->push_back(loadedPlugin);
                entry = readdir(pluginDirectory);
            }
            closedir(pluginDirectory);
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
                if (loadedPlugin != NULL)
                {
                    mPlugins->push_back(loadedPlugin);
                }
                delete filePath;
            }
        }
        FindClose(fileHandle);
    #endif
}

TrinitasPlugin* PluginLoader::GetByID(long pluginID) {
    //need to implement
    return mPlugins->at(pluginID-1);
}

 TrinitasPlugin* PluginLoader::GetByName(char* pluginName) {
     vector<TrinitasPlugin *>::iterator iter;
     bool                               found       = false;
     TrinitasPlugin                     *tmpPlugin  = NULL;
     //use an iterator wich "runs through the Vector
     iter = mPlugins->begin();
//     while ((iter != mPlugins->end()) && (!found)) {
     while (iter != mPlugins->end()) {
        tmpPlugin = (*iter);
        found = strcmp(tmpPlugin->GetName(),pluginName);
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
        cout << "loading: ... " << file <<std::endl;
        void* libraryHandle = dlopen(file, RTLD_LAZY);
        if (libraryHandle != NULL) {
            cout << "Libhandle found" << std::endl;
            //using typedef to define a Functiontemplate for the loaded symbols
            typedef TrinitasPlugin* (*pluginFunction)(long);
            //using the functionvar the Plugin as referrence
            pluginFunction thePlugin;
            thePlugin = (pluginFunction) dlsym(libraryHandle, "s");
            if (thePlugin != NULL) {
                cout << "symbol loaded" << file <<std::endl;
                //call getPlugin with the actual ID
                loadedPlugin = thePlugin(mPlugins->size()+1);
                cout << loadedPlugin->GetName() << " Calling Do() ";
                loadedPlugin->Do();
                cout << std::endl;
            }

        }
       // dlclose(libraryHandle);
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
            {
                loadedPlugin = thePlugin(mPlugins->size()+1);
                cout << loadedPlugin->GetName() << " Calling Do() ";
                loadedPlugin->Do();
                cout << std::endl;
            }
//            FreeLibrary(libraryHandle);
        }
    #endif
     return loadedPlugin;
 }
