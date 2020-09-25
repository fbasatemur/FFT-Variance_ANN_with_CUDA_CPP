**********************  KURULUM AYARLARI **********************  

OpenCV icin on ayarlar:

- Kullanilan OpenCV version 4.1.1
- Ilk olarak platform Debug x64 olarak seçilmeli
 
-> Properties
	-> VC++ Directories
		-> Include Directories = C:\opencv\build\include
		-> Library Directories = C:\opencv\build\x64\vc14\lib
	-> Linker
		-> Input
			-> Additional Dependencies = opencv_world411d.lib

Yukaridaki ayarlar yapildiktan sonra her zaman RUN etmeden once Debug platform seçeneğinin x64 olarak secildiginden emin olun.
