rem
rem Batch file "cleanproject.bat" to clean a PIC project, 
rem created with the PIC Mikroelektronika IDE
rem
rem Filetypes which are created just by calling an IDE
del *.bmk
del *.brk
del *.c.ini
del *.cfg
del *.dct
rem Filetypes created by building a project, and
rem which can be selected by "Clean Project"
del *.asm
del *.asm.ini
del *.brk
del *.c.ini
del *.cfg
del *.cp
del *.dbg
del *.dct
del *.dlt
del *.hex
del *.log
del *.lst
del *.mcl
del *.mcppi_callertable.txt
del *.user.dic
