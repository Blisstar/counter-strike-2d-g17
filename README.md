# Ejemplo de CMAKE para el TP Final

**Importante:** el primer commit de este repositorio tiene el setup
básico para el TP Final que incluye la instalación de la lib de Google
Tests, `SDL2` y `SDL2pp` (el wrapper de C++).

El resto de los commits son a modo de ejemplo de como se pueden
agregar mas código fuente al proyecto.

Este ejemplo **no** incluye instalarse otras libs que son dependencias
tanto de `SDL2` como de `SDL2pp` (pero si estan documentadas en el
`CMakeFile` para Xubuntu 24.04).

Este repo **no** incluye tampoco un instalador.

**Se deben agregar las librerias necesarias y el instalador.**

También el ejemplo usa una estructura de carpetas muy simple:

```
client/
server/
editor/
common/
```

Bien se puede mejorar (cambiando el cmakefile) agregando mas
sub-carpetas.

Tambien, por default solo se compila una version *debug* sin
optimizar. Si se quiere compilar binarios optimizados
(lo que cmake llama *release*) se puede, solo hay modificar
cmake.

Aprender del ejemplo para saber como extenderlo!

**Importante:** este repositorio **no** incluye pre-commits hooks,
ni scripts adicionales (como correr valgrind).

**Eso esta a cargo de los estudiantes,** tal como fue mostrado
en los tps individuales, recaps y hands-on.

**Como buildear: Ejemplo con el server**  
en la carpeta raiz haces:  
mkdir build  
cd build  
Luego elegis que buildear  
cmake .. -DCS2D_SERVER=ON -DCS2D_CLIENT=OFF -DCS2D_EDITOR=OFF -DCS2D_TESTS=OFF  
y luego compilas la parte que queres:  
make cs2d_server