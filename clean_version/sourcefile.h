/**
 * 	@file: sourcefile.h
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 

#ifndef SOURCEFILE_H 
#define SOURCEFILE_H

#include <vector>
#include <string>


class SourceFile {
	private:
		/* the source file stored as a vector (1 indexed) */
		std::vector< std::string > sourceFile;

		/* the file name */
		std::string filename;
		
		
		/**
		 *	Opens the source file and stores it in a vector (fed from objdump)
		 *	Helper for our constructor
		 *
		 * 	@param file_name: The relative path of the source file
		 */
		void getFileLines( std::string file_name );
		
	
	public:	
		/**
		 *	Constructor: fills the vector above with the contents of the file name provided
		 *
		 *	@param file_line: The unparsed file line
		 */
		SourceFile( std::string file_line );

	
		/**
		 *	Returns the line in the file corresponding to the line number
		 *
		 * 	@param line_num: The line number
		 * 	@return The line (in the form of a string)
		 */
		std::string get_line( int line_num );
	
		
		/**
		 *	Returns the number of lines in the file (1 indexed)
		 *
		 * 	@return The number of lines in the file
		 */
		int get_file_len(); 
};


#endif
