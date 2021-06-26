/*
 * Example usage for the markdown components.
 */

constexpr const char *const raw_source_atx_headings = R"(
# Single h1 heading

## Single h2 heading

### Single h3 heading

#### Single h4 heading

##### Single h5 heading

###### Single h6 heading

# One
## Two
### Three
#### And four together headings

# Did you know *you* can **use** `inlines` in headings?

# Links and images will be werid, so dont do it. (But you can if you want)

   # Indented up to 3 spaces are still atx headings
)";


constexpr const char *const raw_source_setext_heading = R"(

Single h1
=========

Single h2
---------

No more levels, just 1 and 2
============================

You can *use* **inlines** here `too`
====================================

Seems like they can span over multiple
lines, IDK why will you have a title this
big, you can if you want
=========================================

Note that you dont need to underline it completely
===

You just need 3 of them, but it looks better if it is full
---

   This ones can be indented too
   =============================

   To 3 spaces like everything else
   --------------------------------
)";


constexpr const char* const raw_source_indented_codeblock = R"(

    This ones are easy

    Just lines indented 4 spaces

    They will look exactly the same in your source as in the final document.
    Maybe in the final document they will be highlighted, but for now they are
    just  there

    Now, if they are one after another, they will all be joined together, so the
    end result should be a big code block from here

    Now the obligatory:

    #include <iostream>

    int main(int /*argc*/, char * /*argv*/[]) {
        std::cout << "Hello world\n";
        return 0;
    }
)";


constexpr const char* const raw_source_fenced_code_block = R"(

```
They can be plain as the indented ones

Or they can have a language like the next one:
```

```cpp
#include <iostream>

int main(int /*argc*/, char * /*argv*/[]) {
    std::cout << "Hello world\n";
    return 0;
}
```

~~~
You can use '`' or '~' to create them. I find that for Spanish keyboards its
better to use '~', but I have recently bought an English keyboard and got to
like using '`'.
~~~

~~~python
print("Hello world")
~~~

)";

constexpr const char* const raw_source_block_quote = R"(

> They look like this

> They can span over
multiple lines using
a single '>' at the
start

> Or they can
> put one '>'
> at the start
> of every line

   > They too can be indented up to 3 spaces

)";

constexpr const char* const raw_source_ordered_list = R"(

1. One

1. One
2. Two
3. Three

1. One
  2. Sub List (2 spaces)
    3. Really deep

1. And the elements
   can span over mulitiple
   lines
2. You can indent them to look like above, or
you can just leave them as they are.

1. List can

2. Span over

3. Multiple blocks

4. So if the elements are
   too long you can leave a
   blank line in between them

)";

constexpr const char* const raw_source_unordered_list = R"(

* So you can use

- Any of this characters

+ To make a list. (Why would you use '+'?)

* You can
  * Nest them too
    * Using 2 spaces
    *
* And the elements
   can span over mulitiple
   lines
* You can indent them to look like above, or
you can just leave them as they are.

* List can

* Span over

* Multiple blocks

* So if the elements are
  too long you can leave a
  blank line in between them
)";

/**
 * Any of '-', '*', '_'.
 *
 * * There needs to be at lest 3 of them.
 * * They can have spaces in between them
 */
constexpr const char* const raw_source_thematic_break = R"(

---

***

___


----------------

********************

_____________________

* * * *

- - - - - 

_      _  _ _   _    _

)";

constexpr const char* const raw_source_paragraph = R"(

Just some normal undecorated text.

The most common and most usefull.

Lorem, ipsum dolor sit amet consectetur adipisicing elit. At, suscipit
reiciendis. Non modi eum velit laboriosam aperiam vel, beatae neque officiis
repudiandae expedita quisquam quis nesciunt eligendi atque reprehenderit
adipisci!

)";


//
// The following are here just for testing in block_identifier.cpp
//

constexpr const char* const raw_source_fenced_code_block_opening = R"(

```
Some code

```lang
Some code

~~~
Some code

~~~lang
Some code

)";

constexpr const char* const raw_source_fenced_code_block_closing = R"(

Some more code
```

```

Some more code
~~~

~~~
)";
