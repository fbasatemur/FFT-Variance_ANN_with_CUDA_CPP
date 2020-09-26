Running CUDA Files in CLR Projects

This project has been prepared with CUDA v10.2.
Steps:

1) Proje Configuration ayarlari Debug x64 olarak secilmelidir.
	x64 secenegi yok ise new configuration->x64 secilir ve WIN32'de kullanilan ayarlar dogrudan kopyalanir.
	
2) .cu ve .cuh uzantili cuda ve cuda header dosyalari projenin source ve header dizinleri altina eklenir.

3) Project-> Build Dependencies-> Build Customizations-> CUDA 10.2 secilir

4) Poject-> Properties-> CUDA C/C++-> Common-> Target Machine Platform-> 64-bit (--machine 64) secenegi secilir.

5) Project-> Properties-> Linker-> Input-> Additional Dependencies-> cudart.lib eklenir.

6) .cu uzantili cuda dosyasi icin Properties-> General-> Item Types-> CUDA C/C++ secenegi secilir.

7) .cuh uzantili cuda header dosyasi icin Properties-> General-> Item Types-> C/C++ Compiler secenegi secilir.

CUDA VERSION HATASI COZUMU

CUDA version 10.2'den farkli ortamlarda calistirilacagi zaman yapilmasi gereken duzenleme:

1) .vxcproj dosyasi icerisinde CUDA .probs ve .target adresi bulunan alanlarda version duzenlemesi yapilir.
Yani "CUDA 10.2" olarak belirtilen (58. ve 167. satirlarda) bolge, sahip olunan x versiyonu icin "CUDA x" olarak duzenlenir