setlocal

	rem set "_url=https://github.com/DanielAdeniji/visualCPlusPlusErrorAndWarning/blob/master/"
	set "_url=https://raw.githubusercontent.com/DanielAdeniji/visualCPlusPlusErrorAndWarning/master"
	
	set "_file=README.md"
	wget %_url%/%_file% -O %_file% -r
	
endlocal
