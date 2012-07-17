templater
---------

This is a command-line tool for creating project source code, based on a set of templates.

Each template consists of a set of text files which contain markup for strings which should be injected by the templating engine.  The project name itself is a mandatory string; other user-defined strings (e.g. UIDs, license headers) may be optionally added to the template.  The tool takes a specified template, substitutes in user-supplied values for each variable, and outputs a set of source files which is ready to be compiled.

Current templates include:

* Python script
* Qt console application
* Qt QWidget application
* BASH shell script
* Symbian console application
* Symbian Avkon application
* Symbian WSERV application

