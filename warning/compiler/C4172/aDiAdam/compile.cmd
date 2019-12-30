setlocal

set "_compilerFolder=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.16.27023\bin\Hostx86\x86\"

set "_compilerBinary=cl.exe"

set "_sourceCodeFolder=."

set "_base=C4172.aDiAdam"

set "_sourceCodeFile_01=%_base%.c"

set "_outputFile=%_base%.exe"

set "_DEBUG=/Z7"

set "_compilerFlag=%_DEBUG%"

"%_compilerFolder%\%_compilerBinary%" ^
%_sourceCodeFolder%\%_sourceCodeFile_01% ^
/Fe:%_outputFile% %_compilerFlag%


endlocal
