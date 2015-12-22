// *****************************************************************************
// *****************************************************************************
// FileManager.h
//
// Author: Jason Tost
// Date:   12.15.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "Arduino.h"

class File
{

public:

   // **************************************************************************
   //                             File system management
   // **************************************************************************

   // Starts the file manager.
   static void begin(
      const int& fileSystemSize);

   // Creates a new file in the file system.
   static File newFile(
      const String& filename,
      const int& maxSize);

   // Formats the file system.
   // Note: All existing files will be destroyed.
   static void format();

   // Defragments the file system.
   static void defrag();

   // Returns true if the specified file exists in the file system.
   static bool exists(
      const String& filename);

   // Deletes the specified file from the filesystem.
   static void deleteFile(
      const String& filename,
      const bool& defragFileSystem = true);

   static void rename(
      const String& filename,
      const String& newFilename);

   // **************************************************************************
   //                             File manipulation
   // **************************************************************************

   // Constructor.
   File();

   // Destructor.
   virtual ~File();

   // Opens a file for reading/writing.
   bool open(
      const String& filename);

   // Closes a file for reading/writing.
   bool close(
      const String& filename);

   // Reads all of the contents of a file into a string.
   String read();

   // Reads one line from the file into a string.
   String readLine();

   // Writes a string to a file.
   bool write(
      const String& string);

   // Appends a string to the end of a file
   bool append(
      const String& string);

   // Returns the size of a file.
   int getSize() const;

   // Returns the maximum size allocated for a file.
   int getMaxSize() const;

private:

   static bool isFormatted();

   static void loadFileSystem();

   static int allocate(
      const int& maxSize);

   static int find(
      const String& filename);

   // **************************************************************************
   //                             Constants

   // The maximum length for a file name.
   static const int MAX_FILENAME_LENGTH = 30;

   // The maximum length for a file system header.
   static const int MAX_FILE_SYSTEM_HEADER_LENGTH = 30;

   // The maximum number of files able to be stored by this file system.
   static const int MAX_FILES = 100;

   // **************************************************************************
   //                              Typedefs

   typedef char Filename[MAX_FILENAME_LENGTH + 1];

   typedef char FileSystemHeader[MAX_FILE_SYSTEM_HEADER_LENGTH + 1];

   // **************************************************************************
   //                           Static variables

   // The header that will be written at the start of the file system.
   // The presence of this header will indicate that the file system has been formatted for use.
   static const FileSystemHeader HEADER;

   // A pointer to the location in flash memory where the file system should reside.
   static int fileSystemPtr;

   // The total bytes allocated for use in the file system.
   static int fileSystemSize;

   // The number of files in the file system.
   static int numFiles;

   // An array containing all the files in the file system.
   static File files[MAX_FILES];

   // **************************************************************************
   //                           Non-static variables

   String filename;

   int size;

   int maxSize;

   int beginPtr;

   int readPtr;
};

#endif  // FILE_H_INCLUDED
