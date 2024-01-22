BITS 64

section .text
global _start

_start:
    ; 초기화 및 부트스트랩 코드 작성

    ; treeOS.bin을 로드할 주소 설정
    mov rsi, 0x100000  ; 로드할 메모리 주소 (64x100000)
    mov rdi, 0          ; 로드할 메모리 위치 (offset 0)

    ; 디스크에서 treeOS.bin을 읽어 메모리로 복사
    mov rax, 0x42       ; 읽기 서비스 호출
    mov rdx, 1          ; 읽을 섹터 수 (1 섹터)
    mov rcx, 2          ; LBA (Logical Block Address), 2번 섹터부터 읽기
    mov rbx, 0x80       ; 부트 디스크 번호 (예: 0x80는 첫 번째 하드 디스크)
    int 0x13            ; BIOS 호출

    ; treeOS.bin을 로드하고 실행
    jmp 0x100000        ; treeOS.bin 실행
