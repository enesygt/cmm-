Markdown Components
===================

Thematic Breaks:
----------------

They are done using:

~~~ markdown
    ***
    ---
    ___
~~~~

Not the following:

~~~ markdown
    +++
    ===
~~~

They allow any amount of spaces between characters. There has to be at least
3 characters.

ATX Headings
------------

They start with up to 6 `#` characters.

~~~ markdown
    # foo
    ## foo
    ### foo
    #### foo
    ##### foo
    ###### foo
~~~

There needs to be a space between the `#` and the title.

They allow inlines, and can be indented up to 3 spaces.

Setext Headings
---------------

These are underlined, using `=` for a `h1`, and `-` for a `h2`.

~~~ markdown
    Foo *bar*
    =========
    
    Foo *baz
    bar*
    ---------
~~~

They can be indented up to 3 spaces, and cant be empty. They can span for more
than one line.

Indented Code Blocks
--------------------

They start with 4 spaces or one tab. These cant interrupt paragraphs.

Fenced Code Blocks
------------------

The fence is formed using `` ` `` or `~`. The first fence can indicate the language.

If they are not closed they span until the end of the document.

Paragraphs
----------

The sequence of characters can span over multiple lines, without blank lines in
the middle. Lines can be indented up to 3 spaces.

Containers
----------

### Block Quotes

Can have up to 3 characters of indentation, and can contain other components
inside of it. [CommonMark Spec](https://spec.commonmark.org/0.29/#block-quotes)

### List item

For a bulleted list, they have to start with `-`, `+` and `*`. And for it to be
ordered it need to start with numbers from `1-9` followed by a `.`.

If the continuation starts with 2 spaces, the next element can be another list.

### List

A sequence of list item of the same type.

Inlines
-------

### Backslash escapes

The punctuation characters that can be escaped.

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

In the rest of cases, the `` \ `` will be treated as a normal character.

### Code spans

A back-stick string is a series of `` ` ``.

A code span starts with a back-stick string, and ends in another one of the
same length. The `\n` will be turned into spaces. If it starts and ends with
a space, the space can be trimmed.

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
