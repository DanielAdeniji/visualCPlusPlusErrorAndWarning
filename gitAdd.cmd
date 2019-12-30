setlocal

	set _folder=warning\compiler\C4172\aDiAdam

	git add %_folder%\C4172.aDiAdam.h	
	git add %_folder%\C4172.aDiAdam.c
	git add %_folder%\C4172.aDiAdam.exe
	git add %_folder%\compile.cmd
	
	git add git*.cmd
	
endlocal
