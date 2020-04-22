/* This is a simplefied ELF reader.
 * You can contact me if you find any bugs.
 *
 * Luming Wang<wlm199558@126.com>
 */

#include "kerelf.h"
#include <stdio.h>
/* Overview:
 *   Check whether it is a ELF file.
 *
 * Pre-Condition:
 *   binary must longer than 4 byte.
 *
 * Post-Condition:
 *   Return 0 if `binary` isn't an elf. Otherwise
 * return 1.
 */
int is_elf_format(u_char *binary)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;
        if (ehdr->e_ident[EI_MAG0] == ELFMAG0 &&
                ehdr->e_ident[EI_MAG1] == ELFMAG1 &&
                ehdr->e_ident[EI_MAG2] == ELFMAG2 &&
                ehdr->e_ident[EI_MAG3] == ELFMAG3) {
                return 1;
        }

        return 0;
}

/* Overview:
 *   read an elf format binary file. get ELF's information
 *
 * Pre-Condition:
 *   `binary` can't be NULL and `size` is the size of binary.
 *
 * Post-Condition:
 *   Return 0 if success. Otherwise return < 0.
 *   If success, output address of every section in ELF.
 */

/*
    Exercise 1.2. Please complete func "readelf". 
*/

// reverse the number if needed

#define rev32(x) ((((x)&0xff)<<24)|(((x)&0xff00)<<8)|(((x)&0xff0000)>>8)|(((x)&0xff000000)>>24))
#define rev16(x) ((((x)&0xff)<<8)|((x)&0xff00)>>8)

int readelf(u_char *binary, int size)
{
        Elf32_Ehdr *ehdr = (Elf32_Ehdr *)binary;

        /*int Nr;

        Elf32_Shdr *shdr = NULL;:

        u_char *ptr_sh_table = NULL;
        Elf32_Half sh_entry_count;
        Elf32_Half sh_entry_size;*/


        // check whether `binary` is a ELF file.
        if (size < 4 || !is_elf_format(binary)) {
                printf("not a standard elf format\n");
                return 0;
        }
		
		//check endian type, ph Address, ph number

	    Elf32_Phdr *phdr=NULL;
		u_char *phdr_table=NULL;
		Elf32_Half ph_entry_count =NULL;

		if(ehdr->e_ident[5]==2){
		    ph_entry_count = rev16(ehdr->e_phnum);
			phdr_table = rev32(ehdr->e_phoff) + binary;
		//	printf("0x%x,0x%x\n",ph_entry_count,phdr_table);
		}else{
			ph_entry_count=ehdr->e_phnum;
			phdr_table=ehdr->e_phoff + binary;
		}
		phdr=(Elf32_Phdr*)phdr_table;
		//

		int id;
		for(id=0;id<ph_entry_count;id++){
			Elf32_Word filesize=phdr->p_filesz;
			Elf32_Word memsize=phdr->p_memsz;
			if(ehdr->e_ident[5]==1){
				printf("%d:0x%x,0x%x\n",id,filesize,memsize);
			}else{
				printf("%d:0x%x,0x%x\n",id,rev32(filesize),rev32(memsize));
			}
			phdr=phdr+1;
		}

		/*
        // get section table addr, section header number and section header size.
		sh_entry_count = ehdr->e_shnum;
		sh_entry_size = ehdr->e_shentsize;
		ptr_sh_table = ehdr->e_shoff+(u_char *)ehdr;
		shdr = (Elf32_Shdr *)ptr_sh_table;

        // for each section header, output section number and section addr. 
        // hint: section number starts at 0.
		for(Nr=0;Nr<sh_entry_count;Nr++){
		
		printf("%d:0x%x\n",Nr, shdr->sh_addr);
			shdr=shdr+1;
		}*/
        return 0;
}



