// *****************************************************************************
// *****************************************************************************
// File.cpp
//
// Author: Jason Tost
// Date:   12.22.2015
//
// *****************************************************************************
// *****************************************************************************

#include "File.h"
#include "Flash.h"

int File::fileSystemPtr = 0;

int File::fileSystemSize = 0;

int File::numFiles = 0;

File File::files[MAX_FILES];

const File::FileSystemHeader File::HEADER = "TOAST FLASH FILE SYSTEM v1.0";

// In the ESP8266, the user-defined flash storage region starts at 0x3C000;
const int FLASH_STORAGE_ADDRESS = 0x3c000;


// **************************************************************************
//                                  Public
// **************************************************************************

// **************************************************************************
//                          File system management

void File::begin(
   const int& size)
{
   fileSystemPtr = FLASH_STORAGE_ADDRESS;

   if (isFormatted())
   {
      loadFileSystem();
   }
   else
   {
      format();
   }
}

File File::newFile(
   const String& filename,
   const int& maxSize)
{
   File file;

   if (numFiles >= MAX_FILES)
   {
      file.beginPtr = allocate(maxSize);
      if (file.beginPtr != 0)
      {
         file.filename = filename;
         file.maxSize = maxSize;
         file.size = 0;
         file.readPtr = file.beginPtr;

         numFiles++;
         files[numFiles - 1] = file;
      }
   }

   return (file);
}

void File::format()
{
   numFiles = 0;

   for (int i = 0; i < MAX_FILES; i++)
   {
      files[i] = File();
   }
}

void File::defrag()
{
   // TODO.
}

bool File::exists(
   const String& filename)
{
   return (find(filename) != -1);
}

void File::deleteFile(
   const String& filename,
   const bool& defragFileSystem)
{
   int fileIndex = find(filename);

   if (fileIndex != -1)
   {
      files[fileIndex] = File();
   }

   if (defragFileSystem)
   {
      defrag();
   }
}

void File::rename(
   const String& filename,
   const String& newFilename)
{
   int fileIndex = find(filename);

   if (fileIndex != -1)
   {
      files[fileIndex].filename = newFilename;
   }
}

// **************************************************************************
//                            File manipulation

File::File()
{
   filename = "";
   maxSize = 0;
   size = 0;
   beginPtr = 0;
   readPtr = 0;
}

File::~File()
{
   // Nothing to do here.
}

// **************************************************************************
//                                  Public


// **************************************************************************
//                                  Private
// **************************************************************************

bool File::isFormatted()
{
   String header;
   Flash::read(fileSystemPtr, header);

   return (header == String(HEADER));
}

void File::loadFileSystem()
{

}

int File::allocate(
   const int& maxSize)
{
   // TODO: Implement a more sophisticated algorithm that reclaims space from deleted files.

   int filePtr = 0;

   // Search backwards, looking for the last allocated file.
   int i = (MAX_FILES - 1);
   while ((files[i].filename == "") &&
          (i >= 0))
   {
      i--;
   }

   // If we found one, allocate space at the end of it.
   if (i != -1)
   {
      filePtr = files[i].beginPtr + files[i].maxSize;
   }
   // Otherwise, allocate space at the beginning of the file system.
   else
   {
      filePtr = fileSystemPtr;
   }

   // Verify that we have enough space to create the new file.
   if ((filePtr + maxSize) > (fileSystemPtr + fileSystemSize))
   {
      filePtr = 0;
   }

   return (filePtr);
}

int File::find(
   const String& filename)
{
   int fileIndex = -1;

   for (int i = 0; i < MAX_FILES; i++)
   {
      if (files[i].filename == filename)
      {
         fileIndex = i;
         break;
      }
   }

   return (fileIndex);
}
