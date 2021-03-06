/** A Class to load and manage loaded Plugins
 * Copyright 2008 by Trinitas. All rights reserved.
 * Distributed under the terms of the BSD License.
 *
 * @autor   Paradoxon
 * @date    02.11.2008
 * @version 0.1
 */

#ifndef WIN32
    #include <dlfcn.h>
    #include <dirent.h>
#else
    #include <Windows.h>
#endif

#include <iostream>
#include <string>
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
            entry = readdir(pluginDirectory);
            while (entry != NULL)  {
                cout << "==========================" << std::endl;
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
            cout << "Loading: \t" << fileInfos.cFileName << std::endl;
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

TrinitasPlugin* PluginLoader::GetAt(long index) {
    //need to implement
    if (index >=0 && index <= mPlugins->size())
        return mPlugins->at(index-1);
    else
        return NULL;
}

 TrinitasPlugin* PluginLoader::GetByName(char* pluginName) {
     vector<TrinitasPlugin *>::iterator iter;
     bool                               found       = false;
     TrinitasPlugin                     *tmpPlugin  = NULL;
     //use an iterator wich "runs through the Vector
     iter = mPlugins->begin();
//     while ((iter != mPlugins->end()) && (!found)) {
     while ( (iter != mPlugins->end()) && (found == false) ) {
        tmpPlugin = (*iter);
        if (strcmp(tmpPlugin->GetName(),pluginName) == 0)
            found = true;
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
        //reseting errors
        dlerror();
        void* libraryHandle = dlopen(file, RTLD_LAZY);
        if (libraryHandle != NULL) {
            //using typedef to define a Functiontemplate for the loaded symbols
            typedef TrinitasPlugin* (*pluginFunction)(long);
            //using the functionvar the Plugin as referrence
            pluginFunction thePlugin;
            //reseting errors
            dlerror();
            thePlugin = (pluginFunction) dlsym(libraryHandle, "getPlugin");
            if (thePlugin != NULL) {
                cout << "!!!!!!!!! SYMBOL LOADED !!!!!!!" << file <<std::endl;
                //call getPlugin with the actual ID
                loadedPlugin = thePlugin(mPlugins->size()+1);
               /* cout << loadedPlugin->GetName() << " Calling Do() ";
                loadedPlugin->Do();*/
                cout << std::endl;
            }
            else
                cout << "Fehler dlsym:\t" << dlerror()  <<std::endl;
       //     dlclose(libraryHandle);
        }
        else
                cout << "Fehler dlopen:\t" << dlerror()  <<std::endl;

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
