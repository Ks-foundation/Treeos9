Set objShell = CreateObject("WScript.Shell")

' genisoimage 명령 실행
strCommand = "genisoimage -o treeOS.iso -b treeOS.bin -no-emul-boot -boot-load-size 4 -boot-info-table path/to/iso_directory"
objShell.Run strCommand, 0, True

WScript.Echo "ISO 파일 생성이 완료되었습니다."
