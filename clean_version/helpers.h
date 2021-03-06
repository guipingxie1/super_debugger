/**
 * 	@file: helpers.h
 * 	@author: Guiping Xie 
 *
 * 	@description: C++ helper functions
 *	@date: Spring 2016
 *
 */
 
 
#ifndef HELPERS_H 
#define HELPERS_H  
 
#include <string> 

 
// Got these online: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

/**
 *	Trim from start / left (in place)
 *
 * 	@param s: String we want to trim
 */
void ltrim(std::string &s);


/**
 *	Trim from end / right (in place)
 *
 * 	@param s: String we want to trim
 */
void rtrim(std::string &s);

/**
 *	Trim both left and right (in place)
 *
 * 	@param s: String we want to trim
 */
void trim(std::string &s);


/**
 *	Trim from start / left (copying)
 *
 * 	@param s: Copy of string we want to trim
 * 	@return The trimmed string
 */
std::string ltrimmed(std::string s);


/**
 *	Trim from end / right (copying)
 *
 * 	@param s: Copy of string we want to trim
 * 	@return The trimmed string
 */
std::string rtrimmed(std::string s);

/**
 *	Trim both left and right (copying)
 *
 * 	@param s: Copy of string we want to trim
 * 	@return The trimmed string
 */
std::string trimmed(std::string s);


/**
 *	Converts paramter string to lowercase 
 *
 * 	@param str: The command we want to lowercase
 */
void str_to_lower( std::string &str );


/**
 *	Converts paramter string to lowercase 
 *
 * 	@param str: The command we want to lowercase
 */
std::string str_to_lowercp( std::string str );


#endif
 
