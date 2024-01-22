#ifndef EASYOSDIR_H
#define EASYOSDIR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mntent.h>
#include <sys/wait.h>

#define MAX_FILENAME_LENGTH 256

// 파일 유형 정의
#define FILE_TYPE_FILE 0
#define FILE_TYPE_DIRECTORY 1

// 파일 시스템 초기화 함수
void easyosdir_init() {
    printf("Initializing TreeOS File System...\n");
    // 여기에 실제 초기화 로직 추가 (현재는 메시지 출력만)
}

// 디렉토리 생성 함수
int easyosdir_create(const char *path, int file_type) {
    if (file_type == FILE_TYPE_DIRECTORY) {
        if (mkdir(path, 0777) == 0) {
            return 1; // 성공
        } else {
            return 0; // 실패
        }
    } else if (file_type == FILE_TYPE_FILE) {
        FILE *file = fopen(path, "w");
        if (file) {
            fclose(file);
            return 1; // 성공
        } else {
            return 0; // 실패
        }
    } else {
        return 0; // 잘못된 파일 유형
    }
}

// 파일 또는 디렉토리 삭제 함수
int easyosdir_remove(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            if (rmdir(path) == 0) {
                return 1; // 성공 (디렉토리 삭제)
            } else {
                return 0; // 실패
            }
        } else {
            if (remove(path) == 0) {
                return 1; // 성공 (파일 삭제)
            } else {
                return 0; // 실패
            }
        }
    } else {
        return 0; // 경로가 존재하지 않음
    }
}

// 디렉토리 내의 파일 목록 가져오기 함수
void easyosdir_list(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("디렉토리 열기 실패");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

// 데이터를 파일에 기록하는 함수 (예: 0x100 주소의 데이터를 log.txt에 저장)
void easyosdir_save_to_log(void *address) {
    FILE *file = fopen("log.txt", "a"); // 로그 파일 경로 지정
    if (file != NULL) {
        fwrite(address, 1, 1024, file); // 예시로 1024 바이트 기록
        fclose(file);
    } else {
        perror("파일 열기 실패");
    }
}

// 바이너리 파일 실행 함수
int easyosdir_execute_bin(const char *bin_path, char *const argv[]) {
    pid_t pid = fork(); // 자식 프로세스 생성

    if (pid == -1) {
        perror("Error forking process");
        return 0; // 실패
    } else if (pid == 0) { // 자식 프로세스
        if (execv(bin_path, argv) == -1) {
            perror("Error executing binary file");
            exit(EXIT_FAILURE); // 실패 시 자식 프로세스 종료
        }
    } else { // 부모 프로세스
        int status;
        waitpid(pid, &status, 0); // 자식 프로세스가 종료될 때까지 대기
        return 1; // 성공
    }
}

#endif /* EASYOSDIR_H */
