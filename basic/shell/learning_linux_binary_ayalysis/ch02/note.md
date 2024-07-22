## Chapter 02 ELF binary format
### 2.1 ELF file type
* ET_NONE: unknown
* ET_REL: relocatable (position independent code)
* ET_EXEC: executable
* ET_DYN: shared library
* ET_CORE: core dump
* readelf -h
* ELF header struct
  * ElfN_Ehdr
### 2.2 ELF program header
* Description of the segment in the binary file
* e_phoff: program header offset
* ELF program header struct
  * Elf32_Phdr
#### 2.2.1 PT_LOAD
* An executable file has at least one PT_LOAD segment
* This type of segment will be loaded or mapped into memory
* An ELF that needs to be dynamically linked
  * The text segment that stores program code
  * The data segment for storing global variables and dynamic link information
  * p_align: Memory alignment
* The program header mainly describes the layout of the program in memory when it is executed.
#### 2.2.2 PT_DYNAMIC
* Some information required by the dynamic linker
  * List of shared libraries that need to be linked at runtime
  * Address of the global offset table (GOT)
  * Information about relocation entries
* DT_HASH: The address of the symbol hash table
* DT_STRTAB: The address of the string table
* DT_SYMTAB: The address of the symbol table
* DT_RELA: The address of the relative address relocation table
* DT_RELASZ: Rela table size in bytes
* DT_RELAENT: Rela table entry size in bytes
* DT_STRSZ: string table size in bytes
* DT_SYMENT: Symbol table entry size in bytes
* DT_INIT: The address of the initialization function
* DT_FINT: The address of the termination function
* DT_SONAME: String table offset of the shared object file name
* DT_RPATH: String table offset for library search path
* DT_SYMBOLIC: Modify the linker to search for symbols in shared object files before the executable
* DT_REL: Address of the Rel relocs table
* DT_RELSZ: Rel table size in bytes
* DT_RELENT: Rel table entry size in bytes
* DT_PLTREL: reloc type (Rela or Rel) referenced by PLT
* DT_DEBUG: Not yet defined, reserved for debugging
* DT_TEXTREL: The absence of this entry indicates that the relocation can only be applied to writable segments
* DT_JMPREL: Address of relocation entry for PLT only
* DT_BIND_NOW: Instructs the dynamic linker to process all relocations before handing control to the executable
* DT_RUNPATH: String table offset for library search path
* Related structures
  * Elf32_Dyn
#### 2.2.3 PT_NOTE
* Stores additional information related to a specific vendor or system
#### 2.2.4 PT_INTERP
* Description of the program parser location (C-style string)
#### 2.2.5 PT_PHDR
* Saves the location and size of the program header table itself
* readelf -l \<filename\>
### 2.3 ELF section header
* Segment and section
  * Segments are an essential part of program execution
  * In each segment, there will be code or data divided into different sections.
* The section header table describes the location and size of the section and is mainly used for linking and debugging.
* readelf -l
* Section headers are not required for executing programs, but are required by debuggers and disassemblers.
* section header struct
  * Elf32_Shdr
#### 2.3.1 .text section
* Stores program code instructions is in the text segment and is of type SHT_PROGBITS
#### 2.3.2 .rodata section
* Stores program's readonly data is in the text segment and is of type SHT_PROGBITS
#### 2.3.3 .plt section
* PLT (Procedure Linkage Table), stores dynamically import relevant information is in the text segment and is of type SHT_PROGBITS
#### 2.3.4 .data section
* Stores initialized data is in the data segment and is of type SHT_PROGBITS
#### 2.3.5 .bss section
* Stores uninitialized data is in the data segment and is of type SHT_NOBITS
#### 2.3.6 .got.plt
* .got stores global offset table
* is of type SHT_PROGBITS
#### 2.3.7 .dynsym section
* Stores dynamic symbols imported from dynamic libraries is in the text segment and is of type SHT_DYNSYM
#### 2.3.8 .synstr section
* Dynamic symbol string table
#### 2.3.9 .rel.* section
* Save relocation related information
* is in type SHT_REL
#### 2.3.10 .hash section
* .gnu.hash
* A hash table is stored for symbol lookup
#### 2.3.11 .symtab section
* Stores the symbol information of ElfN_Sym type
* is in type SHT_SYMTAB
#### 2.3.12 .strtab section
* Stores symstr table
* is in type SHT_STRTAB
#### 2.3.13 .shstrtab section
* Stores section header string table
* is in type SHT_STRTAB
#### 2.3.14 .ctors .dtors section
* Address of constructor and destructor
* readelf -S # check ET_REL
### 2.4 ELF symbol
* .dynsym: just stores symbols from external files (dynamic symbol)
* symtab: Stores all symbol
* related struct
  * Elf64_sym
#### 2.4.1 st_name
#### 2.4.2 st_value
#### 2.4.3 st_size
#### 2.4.4 st_other
#### 2.4.5 st_shndx
#### 2.4.6 st_info
* symbol type
  * STT_NOTYPE
  * STT_FUNC
  * STT_OBJECT
* symbol bind
  * STB_LOCAL (C's static)
  * STB_GLOBAL
  * STB_WEAK
  * ELF32_ST_BIND(info) or ELF64_ST_BIND(info)
    * extract binding info from st_info
  * ELF32_ST_TYPE(info) or ELF64_ST_TYPE(info)
    * extract type info from st_info
  * ELF32_ST_INFO(bind,type) or ELF64_ST_INFO(bind,type)
    * make st_info from bind + type
* readelf -s test | egrep 'foochu|func1'
* ftrace -s test
* gcc -nostdlib
* ftrace ./test2
* objdump -d test2
* procedure proligue (check new funcions entry)
  * It is not easy to identify the entry point when gcc-fomit-frame-pointer is specified
### 2.5 ELF relocation
