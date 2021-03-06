/**
 * 	@file: functdata.h
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 
 
#ifndef FUNCTDATA_H 
#define FUNCTDATA_H


#include "objdump.h"


class FunctData : public ObjDump {
	private:
		/* the start of our function */
		int start_line;
		
		/* the end of our function */
		int end_line;
		
		/* bool to check if we filled the symbol table already */
		bool symbol_filled;			
		
		/* store the base pointer so we can subtract it at the end */		
		void* base_ptr_addr;				
		
		/* uses this to break --- might not need */
		void* get_base_addr;				
		
		/* assembly code for the function */
		std::vector< x86 > x86_code;
		
		/* the symbol table for this function --- symbol to symbol data */
		std::map< std::string, symbol_data > symbol_table;		

	public:
		
		
		/**
		 * 	@return The line number the function starts at
		 */
		int get_startline();
		
		
		/**
		 * 	@return The line number the function ends at
		 */
		int get_endline();
		
		
		/**
		 * 	@return True if the symbol table is currently correct (added base pointer)
		 */
		bool get_sym();
		
		
		/**
		 * 	@return The base pointer of the function
		 */
		void* get_baseptr();
		
		
		/**
		 * 	@return The last valid address of this function
		 */
		void* get_baseaddr();
		
		/**
		 * 	@return A vector of the assembly code as a reference
		 */
		std::vector< x86 >& get_x86();
		
		
		/**
		 * 	@return The symbol table corresponding to the function as a reference
		 */
		std::map< std::string, symbol_data >& get_symtable();
		
		
		/**
		 * 	@return The size of the x86 vector
		 */
		int get_x86size();
		
		
		/**
		 * 	Sets the line number the function starts at
		 *
		 * 	@param start_line: The start line
		 */
		void set_startline( int start_line );
		
		
		/**
		 * 	Sets the line number the function ends at
		 *
		 * 	@param end_line: The end line
		 */
		void set_endline( int end_line );
		
		
		/**
		 * 	Sets whether the symbol table is currently correct (added base pointer / active)
		 *
		 * 	@param symbol_filled: Whether the symbol table is correct
		 */
		void set_sym( bool symbol_filled );
		
		
		/**
		 * 	Sets the base pointer of the function
		 *
		 * 	@param base_ptr: The base pointer
		 */
		void set_baseptr( void* base_ptr );
		
		
		/**
		 * 	Sets the last valid address of this function
		 *
		 * 	@param last_addr: The last valid address
		 */
		void set_baseaddr( void* last_addr );
		
		/**
		 * 	Inserts into the x86 assembly vector
		 *
		 * 	@param code: The assembly code
		 */
		void set_x86( x86 code );
		
		
		/**
		 * 	Sets the symbol table corresponding to the function as a reference
		 *
		 * 	@param symbol_table: The symbol table we want to set
		 */
		void set_symtable( std::map< std::string, symbol_data > symbol_table );
};


#endif
