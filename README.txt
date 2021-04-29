El código que resuelve el problema del enunciado está en el archivo tp1.cpp.
Para compilarlo se debe ejecutar el comando 
	make
en la consola.

Al ejecutarlo se le debe pasar un parámetro que indique cuál algoritmo se desea utilizar entre las siguientes opciones:
	- FB: Fuerza bruta
	- BT: Backtracking con podas por factibilidad y optimalidad.
	- BT-F: Backtracking solamente con poda por factibilidad.
	- BT-O: Backtracking solamente con poda por optimalidad.
	- DP: Programación dinámica.

Además se debe pasar la instancia por entrada estándar. Por ejemplo, para ejecutar backtracking solamente con podas por factibilidad en una instancia INST1.TXT se debe correr el siguiente comando:
	cat INST1.txt | ./jamboT BT-F
La salida del programa es doble. Por la salida estándar se devuelve lo pedido por el enunciado. Por la STDERR se devuelve el tiempo de ejecución del algoritmo.

Experimentación:
La generación de instancias y corrida de experimentos de manera secuencia está programada en Python utilizando Jupyter Lab (https://jupyter.org/). Para ver los notebooks se debe instalar Jupyter Labs siguiendo las instrucciones en su web. Se recomienda seguir los pasos de instalación utilizando pip3.

Una vez instalado Jupyter Lab, abrir una consola en la carpeta python y correr el comando:
	jupyter lab

Allí, existen tres archivos:
	- generar-instancias.ipynb: genera las instancias descriptas en el trabajo y las ubica en la carpeta python/instancias.
	- experimentos.ipynb: corre los experimentos del trabajo y deja el resultado de todas las ejecuciones en un CSV en la carpeta python/resultados
	- analysis.ipynb: toma los resultados de las ejecuciones y genera todos los gráficos correspondientes.
