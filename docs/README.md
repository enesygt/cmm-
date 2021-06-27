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

* **CMM_DEBUG:** To enable all asserts in the code.
* **CMM_UNIT_TEST:** To compile the tests.

In the near future there will be a `introduction.rst` file in the `docs` folder
to serve as a quick guide for new contributors.

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

* [ ] thematic_breaks
* [ ] atx_headings
* [ ] setext_headings
* [ ] indented_code_blocks
* [ ] fenced_code_blocks
* [ ] link_reference
* [ ] container blocks
* [ ] paragraph

Html generation
---------------

* [ ] paragraph
* [ ] thematic_breaks
* [ ] atx_headings
* [ ] setext_headings
* [ ] indented_code_blocks
* [ ] fenced_code_blocks
* [ ] link_reference
* [ ] container blocks
