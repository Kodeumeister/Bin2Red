/*
	Name: Bin2Red (Binary To Readable)
	Author: William Kimberley (Kodeumeister)
	Date Modified: 2019-12-05
	Date Created: 2019-12-03
*/

// C++ Libs
#include <iostream>
#include <fstream>
#include <string>
// C Libs
#include <cstdlib>
#include <cstdint>
// Author's Libs
// NONE!!!

// I usually don't use the "using namespace" statement but
// I thought I should since there'll be no namespace
// clashes and it makes the code easier to read.
using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "\nUsage: bin2red <file>\n";
	} else if (argc > 2) {
		cout << "\nToo many arguments.\n";
	} else {
		// Initialising objects;
		fstream in, out;
		
		// Initialising really small buffer.
		char* buffer = new char;
		
		// Setting exceptions.
		in.exceptions(fstream::failbit);
		out.exceptions(fstream::failbit);
		
		// Converting filename to string.
		string filename(argv[1]);
#ifdef DEBUG
		clog << "\nDEBUG (showing filename): " << filename << "\n";
#endif
		try {
#ifdef DEBUG
			clog << "DEBUG: Now in TRY BLOCK.\n";
#endif
			// Checking if pointer is initialised.
			if (buffer) {
#ifdef DEBUG
				clog << "DEBUG: Buffer is not null.\n";
#endif
				// Opening files.
				in.open(filename, ios::binary | ios::in);
				
				// Getting file size.
				in.seekg(0, in.end);
				unsigned long filesize = in.tellg();
				in.seekg(0, in.beg);
#ifdef DEBUG
				if (in.is_open()) {
					clog << "DEBUG: IN file is open.\n";
				}
#endif			
				// Creating "readable" file.
				out.open(filename + ".red", ios::out);		
#ifdef DEBUG
				if (out.is_open()) {
					clog << "DEBUG: OUT file is open.\n";
				}
#endif
				char strbuffer[5];
				string* strptr;
				// Converting binary to text.
				for (unsigned long i = 0; i < filesize; ++i) {
					in.read(buffer, sizeof(char));
					// Formatting buffer
#ifdef LITTLEENDIAN
					snprintf(strbuffer, sizeof(strbuffer), "0x%x%x", (*buffer & 0x0f), (*buffer & 0xf0)); // Write low (if CPU little endian)
#endif
#ifdef BIGENDIAN
					snprintf(strbuffer, sizeof(strbuffer), "0x%x%x", ((*buffer & 0xf0) >> 4), (*buffer & 0x0f)); // Write high (if CPU little endian)
#endif
					// Making string.
					strptr = new string(strbuffer);
					
					// Making string pointer.
					if (strptr) {
						// Appending character at the end.
						if (i < filesize - 1) {
							*strptr += ", ";
						} else {
							*strptr += ";";
						}
						
						// Writing to file.
						out << *strptr;
						// Clearing pointer.
						delete strptr;
					}
				}
				
				cout << "\nSuccessfully ASCII-ed binary file.\n";
			}
			
		} catch (const fstream::failure& e) {
			// Clearing pointer.
			if (buffer) {
				delete buffer;
#ifdef DEBUG
				clog << "DEBUG: Cleared buffer.\n";
#endif
			}
#ifdef DEBUG
			clog << "DEBUG (Exception 'WHAT'): " << e.what() << "\n";
			clog << "DEBUG (Exception 'CODE'): " << e.code() << "\n";
#endif	
			// Showing error.
			cerr << "\nFailed to read and write to files.\n";
			
			// Making sure files get closed.
			if (in.is_open()) {
				in.close();
#ifdef DEBUG
				clog << "DEBUG: Closed IN file.\n";
#endif
			}
			if (out.is_open()) {
				out.close();
#ifdef DEBUG
				clog << "DEBUG: Closed OUT file.\n";
#endif
			}
			
			// Returning that the program has failed.
			return EXIT_FAILURE;
		}
		
		// Clearing pointer.
		if (buffer) {
			delete buffer;
#ifdef DEBUG
			clog << "DEBUG: Cleared buffer.\n";
#endif
		}
		
		// Closing files.
		in.close();
		out.close();
	}
	
	return EXIT_SUCCESS;
}