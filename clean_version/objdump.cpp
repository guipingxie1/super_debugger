/**
 * 	@file: objDump.cpp
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
#include <sstream> 

#include "objdump.h"
#include "helpers.h"
#include "functdata.h"


using std::string;
using std::vector;
using std::map;
using std::cerr;
using std::stringstream;


static int sizeof_types[] = { sizeof(unsigned int), sizeof(unsigned long long), 
sizeof(unsigned long), sizeof(long long), sizeof(int), sizeof(long), sizeof(long double), 
sizeof(double), sizeof(float), sizeof(unsigned short), sizeof(short), sizeof(char) };



/**
 *	Fills the acceptable type array 
 *
 */
void ObjDump::fillTypeArr() {
	vector< string > u_int_arr = {"unsigned int "};
	vector< string > u_ll_arr = {"unsigned long long int ", "unsigned long long "};
	vector< string > u_l_arr = {"unsigned long int ", "unsigned long "};
	vector< string > ll_arr = {"signed long long int ", "long long int ", "signed long long ", "long long "};
	vector< string > int_arr = {"signed int ", "int "};
	vector< string > l_arr = {"signed long int ", "signed long ", "long int ", "long "};
	vector< string > ld_arr = {"long double "};
	vector< string > d_arr = {"double "};
	vector< string > f_arr = {"float "};
	vector< string > u_s_arr = {"unsigned short int ", "unsigned short "};
	vector< string > s_arr = {"signed short int ", "signed short ", "short int ", "short "};
	vector< string > c_arr = {"char "};
	vector< string > cp_arr = {"char* "};
	vector< string > str_arr = {"string "};
	
	accept_types[0] = u_int_arr; 
	accept_types[1] = u_ll_arr;
	accept_types[2] = u_l_arr;
	accept_types[3] = ll_arr;
	accept_types[4] = int_arr;
	accept_types[5] = l_arr;
	accept_types[6] = ld_arr;
	accept_types[7] = d_arr;
	accept_types[8] = f_arr;
	accept_types[9] = u_s_arr;
	accept_types[10] = s_arr;
	accept_types[11] = c_arr;
	accept_types[12] = cp_arr;
	accept_types[13] = str_arr;
}


/**
 *	Prints the parsed objdump file (assembly code)
 *	Should only call after executing the object dump command (execObjDump above)
 *	Used for cout debugging purposes
 *
 */
void ObjDump::printData( vector< x86 > &x86_code ) {
	if ( !executed ) {
		cerr << "You did not execute the object dump yet\n";
		return;
	}

	for ( int i = 0; i < x86_code.size(); ++i ) {
		cerr << "--------------------------------------------------------------------------------\n\n";
		cerr << "Line number in " << filename << " is: " << x86_code[i].line << "\n";
		cerr << "Line is: \"" << sourceFile[ x86_code[i].line ] << "\"\n";
		
		cerr << "Assembly code is:\n";
		vector< individ_x86 > temp = x86_code[i].assembly;
		for ( int j = 0; j < temp.size(); ++j ) {
			cerr << "  Parsed Output:\n";
			cerr << "    Memory address is: " << temp[j].addr << "\n";
			cerr << "    Instruction code is: " << temp[j].instr_code << "\n";
			cerr << "    Instr in x86 readable format is: " << temp[j].read_instr_code << "\n";
		}
		
		cerr << "\n";
	}
}


/**
 *	Prints the symbols
 *	Should only call after executing the object dump command (execObjDump above)
 *	Used for cout debugging purposes
 *
 */
void ObjDump::printSymbols( map< string, symbol_data > &symbol_table ) {
	if ( !executed ) {
		cerr << "You did not execute the object dump yet\n";
		return;
	}
	
	for ( auto it = symbol_table.begin(); it != symbol_table.end(); ++it ) {
		symbol_data temp = it -> second;
		cerr << it -> first << "  " << temp.addr << "  " << accept_types[temp.type][0] << "\n";
	}
}


/**
 *	Prints the mappers from address to lines and lines to addresses
 *	Should only call after executing the object dump command (execObjDump above)
 *	Used for cout debugging purposes
 *
 */
void ObjDump::printMaps() {
	if ( !executed ) {
		cerr << "You did not execute the object dump yet\n";
		return;
	}
	
	cerr << "Lines to memory addresses\n";
	for ( auto it = line_to_addr.begin(); it != line_to_addr.end(); ++it ) 
		cerr << it -> first << "\t" << it -> second << "\n";
	cerr << "\n";
	
	cerr << "Memory addresses to lines\n";
	for ( auto it = addr_to_line.begin(); it != addr_to_line.end(); ++it ) 
		cerr << it -> first << "\t" << it -> second << "\n";
	cerr << "\n";
}


/**
 *	Get the line number corresponding to the address passed in
 *
 */
int ObjDump::get_line_num( void* addr ) {
	assert( (addr_to_line.find(addr) != addr_to_line.end()) && "Address does not correspond to a line number" );
	
	return addr_to_line[ addr ];
}


/**
 *	Get the address corresponding to the line number passed in
 *
 */
void* ObjDump::get_addr( int line_num ) {
	assert( (line_to_addr.find(line_num) != line_to_addr.end()) && "Line number does not correspond to an address" );
	
	return line_to_addr[ line_num ];
}


/**
 *	Check if the line number is the start of a function
 *
 */
bool ObjDump::is_funct_start( int line_num ) {
	for ( auto it = all_functs.begin(); it != all_functs.end(); ++it ) {
		if ( (it -> second).start_line == line_num )	
			return true;
	}
	
	return false;
}


/**
 *	Get the function which this line number is corresponding to
 *
 */
string ObjDump::get_function( int line_num ) {
	for ( auto it = all_functs.begin(); it != all_functs.end(); ++it ) {		
		if ( line_num >= (it -> second).start_line && line_num <= (it -> second).end_line )
			return it -> first;
	}
	
	return "-invalid-";					// should never reach
}


/**
 *	Checks if we are at the end of a function
 *
 */
bool ObjDump::end_of_function( int line_num ) {
	for ( auto it = all_functs.begin(); it != all_functs.end(); ++it ) {		
		if ( line_num == (it -> second).end_line )
			return true;
	}
	
	return false;
}


/**
 *	Checks whether the input is a valid function  
 *
 */
bool ObjDump::is_valid_func( string &input ) {
	for ( auto it = all_functs.begin(); it != all_functs.end(); ++it ) {
		if ( !input.compare(it -> first) )
			return true;
	}
	
	cerr << "Function name: '" << input << "' is undefined\n";
	return false;
}


/**
 *	Fill the mappers from address to lines and lines to addresses
 *
 */
void ObjDump::fill_line_addr( vector< string > &decoded ) {
	for ( int i = 7; i < decoded.size(); ++i ) {
		if ( decoded[i].empty() )
			break;
			
		stringstream ss;
		int line;
		string addr, file;
		ss << decoded[i];
		ss >> file >> line >> addr;
		
		long mem_addr = stol( addr, NULL, 16 );				// convert to void pointer
		
		if ( line_to_addr.find(line) == line_to_addr.end() ) 
			line_to_addr[line] = (void*)mem_addr;

		addr_to_line[(void*)mem_addr] = line; 	
	}
}


/**
 *	Fills the 'all_functs' map with functions to function data
 *
 */
void ObjDump::fill_funct_map( vector<string> &objdump, vector<string> &functions, vector<string> &demangled ) {
	// fill the acceptable types array
	fillTypeArr();

	int len = objdump.size();
	int i = 0;
	int idx;
	map< string, vector<string> > all_funct_asm;
	while ( i < len ) {
		idx = -1;
		for ( int j = 0; j < functions.size(); ++j ) {
			if ( objdump[i].find( "<" + functions[j] + ">:" ) != -1 ) {
				idx = j;
				break;
			}
		}
		
		// if true, this is an individual function
		if ( idx != -1 ) {
			i += 2;
			vector< string > funct_asm;
			while ( !objdump[i].empty() ) {
				funct_asm.push_back( objdump[i] );
				++i;
			}
			
			// assert that this is the first instance of this function
			assert( (all_funct_asm.find(demangled[idx]) == all_funct_asm.end()) && "Duplicate function names" );
			all_funct_asm[ demangled[idx] ] = funct_asm;
		}
		
		++i;
	}
	
	parse_funct_map( all_funct_asm );
}


/**
 *	Gets all the valid function names in the program
 *
 */
vector<string> ObjDump::parse_symbols( vector<string> &symbol_lines ) {
	// used for stringstream
	string addr, type, name;
	vector< string > funct_names;
	for ( int i = 0; i < symbol_lines.size(); ++i ) {
		if ( symbol_lines[i].find(filename) != -1 ) {
			stringstream ss;
			ss << symbol_lines[i];
			ss >> addr >> type >> name;
			
			if ( !type.compare("T") )
				funct_names.push_back( name );
		}
	}
	
	return funct_names;
}


/**
 *	Helper to fill the destination vector with the file contents
 *
 */
void ObjDump::fill_vector_temp( FILE* ptr, vector<string> &dest ) {
	rewind( ptr );
	char* line = NULL;
	size_t n = 0;
	while ( getline(&line, &n, ptr) != -1 ) {
		line[ strlen(line) - 1 ] = 0;				// get rid of newline
		dest.push_back( line );
	}

	free( line );
	fclose( ptr );
}


/**
 *	Helper to wait for the child process
 *
 */
void ObjDump::wait_helper( pid_t pid ) {
	int status;
	int k = waitpid( pid, &status, 0 );			
	
	assert( (k != -1) && "Child process for object dump failed" ); 
}


/**
 *	Helper to redirect stdout and close the file descriptor
 *
 */
void ObjDump::redirect_close_fd( FILE* ptr ) {
	int fd = fileno( ptr );
		
	// make stdout go to file	
	assert( (dup2(fd, 1) != -1) && "Could not redirect stdout to our file for objdump pipe" );
	
	// fd no longer needed - the dup'ed handles are sufficient
	assert( !close(fd) && "Could not close file descriptor for objdump" );
}


/**
 *	Helper for the child processes
 *
 */
void ObjDump::child_helper( FILE* ptr, const char** exec_arr ) {
	redirect_close_fd( ptr );

	int k = execvp( exec_arr[0], (char* const*)exec_arr );
	assert( (k != -1) && "Execution for object dump failed" );
}


/**
 *	Demangles the all the function names --- only really needed for C++
 *	Will create a child to exec the objdump command
 *
 */
vector<string> ObjDump::get_demangled( vector<string> &funct_names ) {
	FILE* demangled_name = tmpfile();
	assert( demangled_name && "Temp file provided was NULL" ); 
	
	pid_t filter = fork();
	assert( (filter != -1) && "Forking failed for object dump process" ); 
	
	if ( !filter ) {
		redirect_close_fd( demangled_name );
		
		for ( int i = 0; i < funct_names.size(); ++i ) {
			char exec_cmd[ 16 + funct_names[i].length() ];
			strcpy( exec_cmd, "c++filt -p ");
			strncat( exec_cmd, &funct_names[i][0], funct_names[i].length() );
						
			int k = system( exec_cmd );
			assert( (k != -1) && "Execution for name demangling failed" );
		}
		
		exit( 0 );
	}

	wait_helper( filter );
	
	vector< string > demangled;
	fill_vector_temp( demangled_name, demangled );
	
	return demangled;
}


/**
 *	Run objdump with the decoded line flag
 *	This will get the line numbers and memory addresses of the file
 *	Will create a child to exec the objdump command
 * 
 */
void ObjDump::get_decoded_line( char* program ) {
	FILE* decoded_line = tmpfile();
	assert( decoded_line && "Temp file provided was NULL" ); 
	
	pid_t decode_objdump = fork();
	assert( (decode_objdump != -1) && "Forking failed for object dump process" ); 

	if ( !decode_objdump ) {					// in child
		const char* objdump_args[4];
		objdump_args[0] = "objdump";
		objdump_args[1]	= "--dwarf=decodedline";
		objdump_args[2]	= program;
		objdump_args[3] = NULL;
		
		child_helper( decoded_line, objdump_args );
	}
	
	wait_helper( decode_objdump );
	
	vector< string > obj_decode_lines;
	fill_vector_temp( decoded_line, obj_decode_lines );

	filename = obj_decode_lines[5];
	assert( !getFileLines() );
	
	fill_line_addr( obj_decode_lines );
}


/**
 *	Get the complete list of symbols from the program
 *	Runs 'nm' with the line numbers flag to get the symbols
 *	Will create a child to exec the objdump command
 *
 */
vector<string> ObjDump::get_symbol_dump( char* program ) {
	FILE* symbol_dump = tmpfile();
	assert( symbol_dump && "Temp file provided was NULL" ); 
	
	pid_t symbol = fork();	
	assert( (symbol != -1) && "Forking failed for object dump process" ); 

	if ( !symbol ) {					// in child
		const char* symbol_args[3];
		symbol_args[0] = "nm";
		symbol_args[1] = "-l";
		symbol_args[2] = program;
		symbol_args[3] = NULL;
		
		child_helper( symbol_dump, symbol_args );
	}
	
	wait_helper( symbol ); 
	
	vector< string > symbol_lines;
	fill_vector_temp( symbol_dump, symbol_lines );
	
	return parse_symbols( symbol_lines );
}


/**
 *	Get the complete object dump of the program
 *	Objdump run with disassembler and line number flags
 *	Will create a child to exec the objdump command
 *
 */
vector<string> ObjDump::get_complete_objdump( char* program ) {
	FILE* complete_objdump = tmpfile();
	assert( complete_objdump && "Temp file provided was NULL" ); 
	
	pid_t objdump = fork();	
	assert( (objdump != -1) && "Forking failed for object dump process" ); 

	if ( !objdump ) {						// in child
		const char* objdump_args[5];
		objdump_args[0] = "objdump";
		objdump_args[1]	= "-d";
		objdump_args[2]	= "-l";
		objdump_args[3]	= program;
		objdump_args[4] = NULL; 

		child_helper( complete_objdump, objdump_args );
	}

	wait_helper( objdump );
	
	vector< string > object_dump;
	fill_vector_temp( complete_objdump, object_dump );

	return object_dump;
}


/**
 *	The beginning of our program
 *
 */
void ObjDump::execObjDump( int argc, char* argv[] ) {
	// decoded line object dump
	get_decoded_line( argv[1] );

	// symbol dump --- for a list of symbols
	vector< string > funct_names = get_symbol_dump( argv[1] );	
	
	// object dump with lines
	vector< string > object_dump = get_complete_objdump( argv[1] );
	
	// gets the demangled names of the functions --- in case they do C++
	vector< string > demangled = get_demangled( funct_names );
	
	// this will do most of the parsing, fills up all the data from objdump
	fill_funct_map( object_dump, funct_names, demangled );
	
	executed = true;
}
