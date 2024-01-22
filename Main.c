#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "easyosdir.h"
#include "Snetwork.h"

int mount_usb_drive(const char *usb_device) {
    char mount_command[256];
    sprintf(mount_command, "mount %s /mnt/usb", usb_device);
    return system(mount_command);
}

int unmount_usb_drive() {
    return system("umount /mnt/usb");
}

int copy_to_usb_drive(const char *source_file, const char *usb_drive_path) {
    char copy_command[256];
    sprintf(copy_command, "cp %s %s", source_file, usb_drive_path);
    return system(copy_command);
}

void read_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("Failed to open the file.\n");
    }
}

int main() {
    easyosdir_init();
    network_init();

    while (1) {
        printf("TreeOS> ");

        char command[256];
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        if (strcmp(command, "list") == 0) {
            easyosdir_list("/");
        } else if (strncmp(command, "create", 6) == 0) {
            char path[MAX_FILENAME_LENGTH];
            int file_type;
            if (sscanf(command, "create %s %d", path, &file_type) == 2) {
                if (easyosdir_create(path, file_type)) {
                    printf("File created successfully.\n");
                } else {
                    printf("Failed to create file.\n");
                }
            } else {
                printf("Invalid command. Usage: create <path> <file_type>\n");
            }
        } else if (strncmp(command, "log", 3) == 0) {
            void *data_address = (void *)0x100;
            easyosdir_save_to_log(data_address);
            printf("Data saved to log.txt.\n");
        } else if (strncmp(command, "execute", 7) == 0) {
            char bin_path[MAX_FILENAME_LENGTH];
            char *argv[10];
            int argc = sscanf(command, "execute %s %s %s %s %s %s %s %s %s %s", bin_path, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
            argv[argc] = NULL;
            if (easyosdir_execute_bin(bin_path, argv)) {
                printf("Binary file executed successfully.\n");
            } else {
                printf("Failed to execute binary file.\n");
            }
        } else if (strncmp(command, "read", 4) == 0) {
            char file_path[MAX_FILENAME_LENGTH];
            if (sscanf(command, "read %s", file_path) == 1) {
                read_file(file_path);
            } else {
                printf("Invalid command. Usage: read <file_path>\n");
            }
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    network_cleanup();

    return 0;
}
