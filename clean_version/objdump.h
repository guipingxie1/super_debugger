/**
 * 	@file: objDump.h
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 
 
#ifndef OBJDUMP_H 
#define OBJDUMP_H 

#include <string>
#include <vector>
#include <map>


class SourceFile;				// forward declaration
//class Functdata;
//class AllFunct;
 
 
class ObjDump {
	protected:
		struct symbol_data {
			long addr;					// makes it easier to add a long to a void*
			int type;
		};

		struct individ_x86 {
			void* addr;
			std::string instr_code;
			std::string read_instr_code;
		};

		struct x86 {
			int line;					// line number
			std::vector< individ_x86 > assembly;
		};
		
		// list of accepted types
		std::vector< std::string > accept_types[14];

	
	private:
		bool executed = false;					// flag to indicate if we executed the objdump commands
/*
		struct funct_data {
			int start_line;
			int end_line;
			bool symbol_filled;					// bool to check if we filled the symbol table already
			void* base_ptr_addr;				// store the base pointer so we can subtract it at the end --- deleting symbol table?
			void* get_base_addr;				// uses this to break
			std::vector< x86 > x86_code;
			std::map< std::string, symbol_data > symbol_table;		// symbol, symbol data
		};
*/
		// mappers from line to addr and addr to line
		std::map< int, void* > line_to_addr;
		std::map< void*, int > addr_to_line;


		// map of functions to data
		//std::map< std::string, FunctData > all_functs;			// name of function, function data
	
	
		
		// the file name
		std::string filename;
		
		
		/**
		 *	Get the complete object dump of the program
		 *
		 * 	@param program: The program we want to run
		 * 	@return The complete objdump as a vector
		 */
		std::vector< std::string > get_complete_objdump( char* program );
	
	
		/**
		 *	Get the complete list of symbols from the program
		 *
		 * 	@param program: The program we want to run
		 * 	@return A list of all the valid functions in the program
		 */
		std::vector< std::string > get_symbol_dump( char* program );
		
		
		/**
		 *	Run objdump with the decoded line flag
		 *
		 * 	@param program: The program we want to run
		 */
		void get_decoded_line( char* program );


		/**
		 *	Demangles the all the function names --- only really needed for C++
		 *
		 * 	@param funct_names: The function names
		 * 	@return The list of demangled function names
		 */
		std::vector< std::string > get_demangled( std::vector< std::string > &funct_names );


		/**
		 *	Helper for the child process
		 *
		 * 	@param ptr: A file pointer we will redirect stdout to
		 * 	@param exec_arr: The array containing the program we want to execute
		 */
		void child_helper( FILE* ptr, const char** exec_arr );
	
		
		/**
		 *	Helper to redirect stdout and close the file descriptor
		 *
		 * 	@param ptr: A file pointer we will redirect stdout to
		 */
		void redirect_close_fd( FILE* ptr );
	
		
		/**
		 *	Helper to wait for the child process
		 *
		 * 	@param pid: Process ID of the child (debuggee) 
		 */
		void wait_helper( pid_t pid );
	
		
		/**
		 *	Helper to fill the destination vector with the file contents
		 *
		 * 	@param ptr: A file pointer containing the content we want to copy
		 * 	@param dest: The vector we want to store the contents with
		 */
		void fill_vector_temp( FILE* ptr, std::vector< std::string > &dest );
		
		
		/**
		 *	Gets all the valid function names in the program
		 *
		 * 	@param symbol_lines: The symbol file
		 * 	@return A list of all the valid functions in the program
		 */
		std::vector< std::string > parse_symbols( std::vector< std::string > &symbol_lines );


		/**
		 *	Fills the 'all_functs' map with functions to function data
		 *
		 * 	@param objdump: The objdump file
		 * 	@param functions: The list of valid functions
		 * 	@param demangled: The demangled list of valid functions 
		 */
		void fill_funct_map( std::vector< std::string > &objdump, std::vector< std::string > &functions,
																										 std::vector< std::string > &demangled );
																																							

		/**
		 *	Fill the mappers from address to lines and lines to addresses
		 *
		 * 	@param decoded: The vector we get from running decoded lines objdump
		 */
		void fill_line_addr( std::vector< std::string > &decoded );
	
		
		/**
		 *	Fills the acceptable type array 
		 *
		 */
		void fillTypeArr();
		

	public:
		SourceFile* srcfile; 
	
	
		/**
		 *	The beginning of our program
		 *
		 * 	@param argc: Arguments passed straight from original main function
		 * 	@param argv: Arguments passed straight from original main function
		 * 	@return Used for exit status checking
		 */
		void execObjDump( int argc, char* argv[] );
		
		
		/**
		 *	Checks whether the input is a valid function  
		 *
		 * 	@param input: A string of characters to check whether it is a valid function
		 * 	@return True if the input is a valid function
		 */
		bool is_valid_func( std::string &input );
	
		
		/**
		 *	Check if the line number is the start of a function
		 *
		 * 	@param line_num: The line number
		 * 	@return True if the line number is a start of a function
		 */
		bool is_funct_start( int line_num );
	
			
		/**
		 *	Checks if we are at the end of a function
		 *
		 * 	@param line_num: The line number
		 * 	@return True if we are at the end of a function
		 */
		bool end_of_function( int line_num );
	
		
		/**
		 *	Get the function which this line number is corresponding to
		 *
		 * 	@param line_num: The line number
		 * 	@return The function the line number is in
		 */
		std::string get_function( int line_num );
	
		
		/**
		 *	Get the line number corresponding to the address passed in
		 *	Only get lines that correctly correspond to an address
		 *
		 * 	@param addr: The address we want the line number of
		 * 	@return The line number 
		 */
		int get_line_num( void* addr );
	
		
		/**
		 *	Get the address corresponding to the line number passed in
		 *	Only get addresses that correctly correspond to a line number
		 *
		 * 	@param line_num: The line number we want the address of
		 * 	@return The address
		 */
		void* get_addr( int line_num );
	
		
		/**
		 *	Prints the parsed objdump file (assembly code)
		 *	Should only call after executing the object dump command (execObjDump above)
		 *
		 */
		void printData( std::vector< x86 > &x86_code );
	
		
		/**
		 *	Prints the mappers from address to lines and lines to addresses
		 *	Should only call after executing the object dump command (execObjDump above)
		 *
		 */
		void printMaps();
	
		
		/**
		 *	Prints the symbols
		 *	Should only call after executing the object dump command (execObjDump above)
		 *
		 */
		void printSymbols( std::map< std::string, symbol_data > &symbol_table );

};		

#endif
