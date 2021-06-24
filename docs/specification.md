Markdown Components
===================

Thematic Breaks:
----------------

~~~ markdown
    ***
    ---
    ___
~~~~

No se valen los siguientes:

~~~ markdown
    +++
    ===
~~~

Estos pueden partir parafos

Se permiten:

1. Espacios entre los caracteres
2. Que se metan mas de 3 caracteres
3. Colocar como miembro de lista

ATX Headings
------------

Son los headers con los caracteres `#`

~~~ markdown
    # foo
    ## foo
    ### foo
    #### foo
    ##### foo
    ###### foo
~~~

Nesitan un espacio, y no pueden ser mas de 6

Permiten emphasis, trailing white spaces y indentacion de hasta 3 espacios

Setext Headings
---------------

Son los headers subrayados, con 3 o mas caracteres subrayando

~~~ markdown
    Foo *bar*
    =========
    
    Foo *baz
    bar*
    ---------
~~~

Permite indentar hasta 3 espacios cada cosa, y no pueden estar vacios

Indented Code Blocks
--------------------

Empiezan con 4 espacios o un tab. El texto se coloca literal Estos no pueden
interrumpir parrafos.

Fenced Code Blocks
------------------

La cerca esta formada por `` ` `` o con `~`. La primera barrera puede contener
un indicador del lenguaje.

Si no se cierran duran hasta el final del documento

Paragraphs
----------

Secuencia de caracteres que puede expandirce por multiples lineas, pero sin
lineas en blanco. Las lineas se pueden indentar por cualquier cantidad.

Containers
----------

### Block Quotes

1 a 3 caracteres de indentacion inicial, que puede contener otros componentes
de markdown. Posiblemente el penultimo en implementar. Link al
[spec](https://spec.commonmark.org/0.29/#block-quotes)

### List item

Para que sean bulleted tienen que empezar con -, +, \*. Y para que sea ordenada
requiere empezar con numeros del 0-9 seguidos de un '.'.

Si la continuacion lleva minimo 2 espacios lo que este ahi puede ser otro
compoenente.

### List

Es una secuencia de list items del mismo tipo

Inlines
-------

### Backslash escapes

Los caracteres de puntuacion pueden ser escapados

~~~ markdown
\!
\"
\#
\$
\%
\&
\'
\(
\)
\*
\+
\,
\-
\.
\/
\:
\;
\<
\=
\>
\?
\@
\[
\\
\]
\^
\_
\`
\{
\|
\}
\~
~~~

Con los demas caracteres se trata como un \ normal. Y puede escapar componentes
de markdown.

### Code spans

Son los el backskick string es una serie de `` ` ``.

Un code span empieza con un backskick string y termina con un backskick string.
Los `\n` son convertidos a espacios. Se le puede hacer trim a un espacio si
empieza y temina con un espacio.

### Emphasis y Stong empasis

#### Italicas (em)

~~~ markdown
*Italicas*
~~~

#### Negritas (strong)

~~~ markdown
**Negritas**
~~~~

### Links

~~~ markdown
[text](url title)
[text](url multi word title)
[text](url)
~~~~

### Images

~~~ markdown
![title](url)
![title](url title)
![title](url multi word title)
~~~
