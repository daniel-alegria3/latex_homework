# About
Tarea del 4to laboratorio del Curso de 'Algoritmos Parallelos y Distribuidos'.
Cusco - Peru, Unsaac 2024-I.

Provando tipear mis tareas en Latex usando tectonic.

# Compilacion
Se requiere de [tectonic](https://tectonic-typesetting.github.io). Ya que estoy
usando la [Interface V2](https://tectonic-typesetting.github.io/book/latest/ref/v2cli.html)
de este. Asi, solo tengo que correr:

    tectonic -X build

Pero se puede crear un archivo unico 'onefile.tex' junstando el contenido
de src/_preamble.tex, y main.tex, src/_postamble.tex. Para asi usar cualquier
distribucion de Latex (dado se tengan installados los packetes de latex requeridos).

Usando las reglas dentro del [Makefile](./Makefile)
para crear el pdf (que se guarda en el directorio ./build/output ):

    make output

O simplemente

    make


Las tablas y las imagenes tambien se pueden generar con las siguientes reglas
(los datos que estaban ./src/data y ./src/images se sobreescribiran ).
** Se requiere tener installado python-matplotlib y gcc en un sistema de linux **

    make all

