cmm++
=====

Markdown parser in C++17

Specification
=============

It follows [this spec](specification.md), and the plan is to go adjusting
towards the CommonMakrk spec.

Compiling
=========

For use (Not ready)
-------------------

In the root folder

~~~
mkdir bin
cd bin
cmake ..
~~~

You will have the `cmm` lib to integrate on your programs, and the `cmm-parser`
as a command line utility.

For development
---------------

You can add the following cmake flags:

* **CMM_DEBUG:** To enable all asserts in the code (Default: OFF).
* **CMM_UNIT_TEST:** To compile the tests (Default: OFF).

In the near future there will be a `introduction.rst` file in the `docs` folder
to serve as a quick guide for new contributors.

For visual studio users
-----------------------

### Plain Visual Studio

If you are just using visual studio normally and just want to get started, the
simplest way is to generate the project as listed in 'For use' (Adding any
flags needed if you will do development).

Open the `cmm++.sln` file.

You will see on the solution explorer the list of projects. If you want to run
any specific one, you can right click it, and set it as the start project.

### Cmake tools for Windows

If you want to use the cmake integration in visual studio, [read this
article](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio).

Checklist
=========

Inlines 
-------

* [X] backslash escapes
* [X] code_spans
* [X] emphasis
* [X] strong_emphasis
* [X] links
* [X] images

Compoment filtering
-------------------

* [X] atx_heading
* [ ] setext_heading
* [ ] indented_code_block
* [ ] fenced_code_block
* [ ] fenced_code_block_opening
* [ ] fenced_code_block_closing
* [ ] block_quote
* [ ] ordered_list
* [ ] unordered_list
* [ ] thematic_break

Html generation
---------------

* [ ] atx_heading
* [ ] setext_heading
* [ ] indented_code_block
* [ ] fenced_code_block
* [ ] block_quote
* [ ] ordered_list
* [ ] unordered_list
* [ ] thematic_break
