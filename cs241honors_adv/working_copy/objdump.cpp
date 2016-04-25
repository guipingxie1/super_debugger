/**
 * 	@file: objDump
 * 	@author: Guiping Xie 
 *	@thanks: Bhuvan Venkatesh, CS241 Honors TAs for their assistance
 *
 * 	@description: UIUC - CS241 (System Programming) Honors Project 
 *	@date: Spring 2016
 *
 */

using namespace std;

struct symbol_data {
	long addr;					// makes it easier to add a long to a void*
	int type;
};

struct individ_x86 {
	void* addr;
	string instr_code;
	string read_instr_code;
};

struct x86 {
  string line;
  int lineNum;
  vector< individ_x86 > assembly;
};

// mappers from line to addr and addr to line
map< int, vector<void*> > line_to_addr;
map< void*, int > addr_to_line;

vector< string > objectDump;
vector< string > mainFunct;							// only debugging main for now
vector< string > sourceFile;

// the file name
string filename;

// important
vector< x86 > x86_code;

// the last address of the 'main' function
void* break_main_addr;

// map of symbols
map< string, symbol_data > symbol_table;				// symbol, symbol data

// list of accepted types
static vector< string > accept_types[14];

static int sizeof_types[] = { sizeof(unsigned int), sizeof(unsigned long long), 
sizeof(unsigned long), sizeof(long long), sizeof(int), sizeof(long), sizeof(long double), 
sizeof(double), sizeof(float), sizeof(unsigned short), sizeof(short), sizeof(char) };

// Got these online - http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

/**
 *	Trim from start / left (in place)
 *
 * 	@param pid: String we want to trim
 */
static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
}


/**
 *	Trim from end / right (in place)
 *
 * 	@param pid: String we want to trim
 */
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
}


/**
 *	Trim both left and right (in place)
 *
 * 	@param pid: String we want to trim
 */
static inline void trim(string &s) {
    ltrim(s);
    rtrim(s);
}


/**
 *	Trim from start / left (copying)
 *
 * 	@param pid: String we want to trim
 * 	@return The trimmed string
 */
static inline string ltrimmed(string s) {
    ltrim(s);
    return s;
}


/**
 *	Trim from end / right (copying)
 *
 * 	@param pid: String we want to trim
 * 	@return The trimmed string
 */
static inline string rtrimmed(string s) {
    rtrim(s);
    return s;
}


/**
 *	Trim both left and right (copying)
 *
 * 	@param pid: String we want to trim
 * 	@return The trimmed string
 */
static inline string trimmed(string s) {
    trim(s);
    return s;
}


// ------ END ------


/**
 *	Fills the acceptable type array 
 *
 */
void fillTypeArr() {
	static vector< string > u_int_arr = {"unsigned int "};
	static vector< string > u_ll_arr = {"unsigned long long int ", "unsigned long long "};
	static vector< string > u_l_arr = {"unsigned long int ", "unsigned long "};
	static vector< string > ll_arr = {"signed long long int ", "long long int ", "signed long long ", "long long "};
	static vector< string > int_arr = {"signed int ", "int "};
	static vector< string > l_arr = {"signed long int ", "signed long ", "long int ", "long "};
	static vector< string > ld_arr = {"long double "};
	static vector< string > d_arr = {"double "};
	static vector< string > f_arr = {"float "};
	static vector< string > u_s_arr = {"unsigned short int ", "unsigned short "};
	static vector< string > s_arr = {"signed short int ", "signed short ", "short int ", "short "};
	static vector< string > c_arr = {"char "};
	static vector< string > cp_arr = {"char* "};
	static vector< string > str_arr = {"string "};
	
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
 *
 */
void printData() {
	for ( int i = 0; i < x86_code.size(); ++i ) {
		cerr << "--------------------------------------------------------------------------------\n\n";
		cerr << "Line number in " << filename << " is: " << x86_code[i].lineNum << "\n";
		cerr << "Line is: \"" << x86_code[i].line << "\"\n";
		
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
 *
 */
void printSymbols() {
	for ( auto it = symbol_table.begin(); it != symbol_table.end(); ++it ) {
		symbol_data temp = it -> second;
		cerr << it -> first << "  " << temp.addr << "  " << accept_types[temp.type][0] << "\n";
	}
}

 
/**
 *	Prints the mappers from address to lines and lines to addresses
 *
 */
void printMaps() {
	cerr << "Lines to memory addresses\n";
	for ( auto it = line_to_addr.begin(); it != line_to_addr.end(); ++it ) {
		for ( int i = 0; i < (it -> second).size(); ++i )
			cerr << it -> first << "\t" << (it -> second)[i] << "\n";
	}
	cerr << "\n";
	
	cerr << "Memory addresses to lines\n";
	for ( auto it = addr_to_line.begin(); it != addr_to_line.end(); ++it ) 
		cerr << it -> first << "\t" << it -> second << "\n";
	cerr << "\n";
}


/**
 *	Fill the mappers from address to lines and lines to addresses
 *
 */
void fillMaps() {
	for ( int i = 0; i < x86_code.size(); ++i ) {
		x86 temp = x86_code[i];
		individ_x86 get_addr = temp.assembly[0];
		line_to_addr[temp.lineNum].push_back( get_addr.addr );
		
		addr_to_line[get_addr.addr] = temp.lineNum; 
	}
}


/**
 *	Creates the symbol and inserts it into the map
 *
 * 	@param line: The source code line
 * 	@param symbol: The symbol_data object we want to fill
 * 	@return True if we can find the type of the symbol (variable)
 */
bool get_type( string line, symbol_data &symbol ) {
	int idx = -1;
	int j_idx = -1;
	bool flag = false;
	
	for ( int i = 0; i < 14 /* manual entry */ ; ++i ) {
		for ( int j = 0; j < accept_types[i].size(); ++j ){ 
			if ( line.find(accept_types[i][j]) != -1 ) {
				idx = i;
				j_idx = j;
				flag = true;
				break;
			}
		}
		
		if ( flag )
			break;
	}

	if ( idx == -1 )
		return false;
		
	symbol.type = idx;	

	string name = line.substr( 0, line.find("=") );
	name.erase( 0, line.find(accept_types[idx][j_idx]) + accept_types[idx][j_idx].length() );
	trim( name );
	
	if ( symbol_table.find(name) == symbol_table.end() ) 
		symbol_table[name] = symbol;
	
	return true;
}


/**
 *	Fill the symbol vector with all declared varaiables
 *
 */
void fillSymbols() {
	for ( int i = 0; i < x86_code.size(); ++i ) {
		x86 temp = x86_code[i];
		vector< individ_x86 > line_asm = temp.assembly;
		
		// look at the individual parts for the assembly code
		for ( int j = 0; j < line_asm.size(); ++j ) {
			string asm_line = line_asm[j].read_instr_code;
			
			if ( asm_line.find("(%rbp)") != -1 && asm_line.find("(%rbp)") != 0 && asm_line.find("(%rbp),") == -1 ) {
				asm_line.erase( 0, asm_line.find(",") + 1 );	
				long offset = stol( asm_line, NULL, 16 );
				string line = temp.line;				// the line in the source file
				
				symbol_data new_symbol;
				new_symbol.addr = offset;

				// assuming only 1 line of code per line
				// can have type declaration before initialization --- need to handle two cases
				// only handling stack and text data for now --- no malloc / heap
				// char* must be char* not char *
				if ( !get_type(line, new_symbol) ) {				// only handling the case where everything is initialized in one line
					// TO DO
					
					// if we cannot find the variable name type
					//cerr << "Cannot find type - view 'help' for a list of accepted types\n";
				}
			} 
		}
	}
}


/**
 *	Opens the object dump file and stores it in a vector
 *
 * 	@param file_name: The name of the objdump file
 * 	@return True if the objdump file cannot be opened
 */
bool getObjDump( string file_name ) {
	ifstream parseMe( file_name );				// got from online - cppreference
	if ( parseMe.is_open() ) {
		string line;

		while ( getline(parseMe, line) ) {
			if ( line.find("<main>:") != -1 ) {
				objectDump.push_back( line );
				break;
			}
		}
		
		while ( getline(parseMe, line) ) {
			if ( !line.empty() )
				objectDump.push_back( line );
			else break;
		}

		parseMe.close();
	}
	else {
		cerr << "\n\t\e[1mObject dump file could not be opened\e[0m\n\n";
		return true;
	}
	
	return false;
}


/**
 *	Opens the source file and stores it in a vector
 *
 * 	@param file_name: The absolute path of the source file
 * 	@return True if the source file cannot be opened
 */
bool getFileLines( string fileloc ) {
	ifstream source( fileloc );	
	if ( source.is_open() ) {
		string line;
		sourceFile.push_back("");

		while ( getline(source, line) ) {
			trim( line );
			sourceFile.push_back( line );
		}

		source.close();
	}
	else {
		cerr << "\n\t\e[1mYour file --- " << filename << " --- could not be opened\e[0m\n\n";
		return true;
	}
	
	return false;
}


/**
 *	Parses the absolute location of the file to get the file name
 *
 * 	@param fileloc: The absolute path of the file location 
 */
void getFileName( string fileloc ) {
	int idx = 0;

	for ( int i = fileloc.length() - 1; i >= 0; --i ) {
		if ( fileloc[i] == '/' ) {
			idx = i;
			break;
		}
	}

	filename = fileloc.substr( idx + 1 );
}


/**
 *	Parse the assembly code lines 
 *
 * 	@param code: The assembly code line (string) we want to parse
 * 	@return An individ_x86 object holding the parsed contents
 */
individ_x86 parseStr( string code ) {
	individ_x86 parsedx86;
	int k = 0;

	string addr = code.substr( 0, (k = code.find(':')) );
	trim( addr );
	long mem_addr = stol( addr, NULL, 16 ); 			// in hex so we get a memory address
	parsedx86.addr = (void*)mem_addr;
	
	string data;
	int i;
	for (	i = k + 1; i < code.length(); ++i ) 
		if ( code[i] != '\t' )
			break;
	
	for ( ; i < code.length(); ++i ) {
		if ( code[i] != '\t' )
			data += code[i];
		else break;
	}

	trim( data );
	parsedx86.instr_code = data;
	
	string instr;
	
	for ( ; i < code.length(); ++i )
		instr += code[i];
	
	trim( instr );
	parsedx86.read_instr_code = instr;
	
	return parsedx86;
}


/**
 *	Parses the whole assembly file
 *
 * 	@param indices: The indices of the assembly file (broken by line numbers)
 * 	@param linenumber: The line number of source file corresponding to the assembly code
 */
void parseAssem( const vector< int >& indices, const vector< int >& linenumber ) {
	int i = 0;
	
	while ( i < indices.size() - 1 ) {
		x86 temp;	
		int k = indices[i];
		int e = indices[i + 1];
		
		temp.line = trimmed( sourceFile[linenumber[i]] );
		temp.lineNum = linenumber[i];
		
		while ( k < e ) {
			temp.assembly.push_back( parseStr(mainFunct[k]) );
			++k;
		}
		
		++i;
		x86_code.push_back( temp );
	}
	
	x86 temp;	
	int k = indices[i];
	
	temp.line = sourceFile[linenumber[i]];
	temp.lineNum = linenumber[i];
	
	while ( k < mainFunct.size() ) {
		temp.assembly.push_back( parseStr(mainFunct[k]) );
		++k;
	}
	
	x86_code.push_back( temp );
}


/**
 *	The beginning of our program
 *
 * 	@param argc: Arguments passed straight from original main function
 * 	@param argv: Arguments passed straight from original main function
 * 	@return Used for exit status checking
 */
int execObjDump( int argc, char* argv[] ) {			// these arguments are the exact same as argc and argv
	string temp = argv[1];
	temp = temp.substr( 2 ); 
	temp += "_copy.asm";		
	const char* file_name = &temp[0];				// convert to char array

	pid_t objdump = fork();
	
	if ( objdump == -1 ) {
    cerr << "\n\t\e[1mForking failed for object dump process\e[0m\n\n";
    return 1;
  }

	if ( !objdump ) {			
		int fd = open( file_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
		
		if ( dup2(fd, 1) == -1 ) {   				// make stdout go to file
			cerr << "\n\t\e[1mCould not redirect stdout to our file for objdump pipe\e[0m\n\n";
			exit( 1 );
		}
		
		if ( close(fd) ) {     					// fd no longer needed - the dup'ed handles are sufficient
			cerr << "\n\t\e[1mCould not close file descriptor for objdump pipe\e[0m\n\n";
			exit( 1 );
		}
		
		// can also use objdump --dwarf=decodedline ./name_of_program to get everything
		const char* objdump_args[5];
		objdump_args[0] = "objdump";
		objdump_args[1]	= "-d";
		objdump_args[2]	= "-l";
		objdump_args[3]	= argv[1];
		objdump_args[4] = NULL; 

		int k = execvp( objdump_args[0], (char* const*)objdump_args );

		if ( k == -1 ) {
			cerr << "\n\t\e[1mExecution for object dump failed\e[0m\n\n";
			exit( 1 );
		}
	}

	int status;
	int k = waitpid( objdump, &status, 0 );			
	
	if ( k == -1 ) {
    cerr << "\n\t\e[1mChild process for object dump failed\e[0m\n\n";
    return 1;
  }
  
  if ( WIFEXITED(status) && WEXITSTATUS(status) == 1 ) 
    return 1;
	
	
	// get the object dump file
	if ( getObjDump(file_name) ) 
		return 1;					// only return if we failed

	// now the vector objectDump has all the lines
	int len = objectDump.size();

	if ( !len ) {
		cerr << "\n\t\e[1mMain was not found in the object dump\e[0m\n\n";
		return 1;
	}
	
	int incre = 2;
	int idx = 0;
	vector< int > indices;
	vector< int > linenumber;
	string fileloc;
		
	while ( incre < len ) {
		if ( objectDump[incre][0] == ' ' ) {
			mainFunct.push_back( objectDump[incre] );
			++idx;
		}
		else {
			// this line corresponds to the next block of x86 instructions				
			string line = objectDump[incre];
			int linelen = line.length();
			int numstart = 0;
			
			for ( int i = linelen - 1; i; --i ) {
				if ( line[i] == ':' ) {
					numstart = i;
					break;
				}
			}

			int linenum = stoi( line.substr(numstart + 1) );
			linenumber.push_back( linenum );
			indices.push_back( idx );
			
			if ( !idx )
				fileloc = line.substr( 0, numstart );
		}
		
		++incre;
	}
	
	// get last instruction of main (addr) --- need better method
	string break_addr = mainFunct[0].substr( 0, mainFunct[0].find(":") );
	if ( indices.size() > 1 )
		break_addr = mainFunct[indices[1] - 1].substr( 0, mainFunct[indices[1] - 1].find(":") );
	trim( break_addr );
	break_main_addr = (void*)stol( break_addr, NULL, 16 );
	
	if ( fileloc.empty() ) {
		cerr << "\n\t\e[1mMake sure you compiled your program with the -g flag\e[0m\n\n";
		return 1;
	}
	
	// gets the file name
	getFileName( fileloc );
	
	// gets the lines of the original program
	if ( getFileLines(fileloc) )
		return 1;
	
	// parse the assembly x86 file
	parseAssem( indices, linenumber );
	
	// ignore main
	x86_code.erase( x86_code.begin() );
	
	fillTypeArr();
	
	fillMaps();
	
	// print the data in the maps
	//printMaps();
	
	// fill the symbol vector
	fillSymbols();
	
	// print all the symbols
	//printSymbols();
	
	if ( remove(file_name) )
		cerr << "\n\t\e[1mCannot remove file\e[0m\n\n";
	
	// print parsed data
	//printData();
	
	return 0;
}

