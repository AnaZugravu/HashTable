build:
	cl  /W3 -D_CRT_SECURE_NO_DEPRECATE .\tema0.c .\hash.c .\list.c
	
clean:
	del /F /Q /A *.exe *.obj
