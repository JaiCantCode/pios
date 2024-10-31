#include "sd.h" // See this file for function prototype of ata_lba_read()
#include "fat.h"
#include "serial.h"
#include "rprintf.h"

struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector;
char rde_region[2048];
struct root_directory_entry* rde;


int sd_init();
int sd_readblock();
int strncmp();
int strcmp();

int fatInit() {
   sd_init();
   sd_readblock(0, (unsigned char*)bootSector, 1); // Read sector 0 from disk drive into bootSector array
   bs = (struct boot_sector*)bootSector; // Point boot_sector struct to the boot sector so we can read fields
   
   // Print out some of the elements of the BIOS information block using rprintf...
   
   // TODO: Validate the boot signature = 0xaa55
   if(bs->boot_signature != 0xaa55) {
      esp_printf(putc, "INVALID BOOT SIGNATURE: Expected boot_signature '0xaa55' : Given boot_signature '%#x'\n", bs->boot_signature);
      return -1;
   }

   // TODO: Validate fs_type = "FAT12" using strcmp
   if(!strncmp(bs->fs_type, "FAT12", 5)) {
      esp_printf(putc, "INVALID FAT SYSTEM TYPE: Expected fs_type 'FAT12' : Given fs_type '%#s'\n", bs->fs_type);
      return -1;
   }
   
   // TODO: Read FAT table from the SD card into array fat_table
   sd_init();
   sd_readblock((unsigned int)bs->num_reserved_sectors, (unsigned char*)fat_table , (unsigned int)(bs->num_fat_tables * bs->num_sectors_per_fat));


   // TODO: Compute root_sector as:
   //       num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
   root_sector = (unsigned int)(bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat));

   sd_init();
   sd_readblock(root_sector, (unsigned char*)rde_region, (unsigned int)(bs->num_root_dir_entries * 32) / 512);

   return 0;
}

int fatOpen(char* fname) {
   int i = 0;
   rde = (struct root_directory_entry)rde_region[i];   
   while(!strcmp(rde->file_name, fname)) {
      i++;
      if(i >= 2048) {
         esp_printf(putc, "ERROR: could not find file in rde_region\n");
         return -1;
      }
      rde = (struct root_directory_entry)rde_region[i];   
   } 
   return 0;
}

int fatRead(char* buf, int n) {
   
   int clstr = ((int)rde->cluster)-2;
   sd_init();
   sd_readblock(root_sector + (unsigned int)(((bs->num_root_dir_entries * 32) / 512) + (clstr * bs->num_sectors_per_cluster)), (unsigned char*)buf, (unsigned int)n);
   return 0;
}




int strncmp(char* a, char* b, int num){
   for(int i = 0; i < num; i++){
      if(a[i] != b[i]) {
         return a[i] < b[i] ? -1 : 1;
      }
   }
   return 0;
}

int strcmp(char* a, char* b){
   for(int i = 0; a[i] != ' '; i++) {
      if(a[i] != b[i]) {
         return a[i] < b[i] ? -1 : 1;
      }
   }
   return 0;
}
