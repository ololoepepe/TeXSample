==============================================================================
 TeXSample
==============================================================================

Homepage: https://github.com/TeXSample-Team/TeXSample

Author: TeXSample Team (ololoepepe@gmail.com)

License: GNU LGPL (see COPYING.txt)

TeXSample is a library developed as a client-server bridge between
TeXSample Server and TeX Creator.

For details, see: https://github.com/TeXSample-Team/TeXSample-Server
and https://github.com/TeXSample-Team/TeX-Creator

==============================================================================
 Dependencies
==============================================================================

In order to build and use TeXSample you will need the same libraries and tools
as for every other project using Qt.

See: http://qt-project.org/resources/getting_started for details.

TeXSample is intended for use with Qt 5, or with Qt 4.8. Classes interface may
slightly vary depending on the version of Qt used. In case of using Qt 4.8,
some features may be missing.
Support of Qt libraries' versions lower than 4.8.0 is not guaranteed.

You will also need BeQt libraries version 3.0.0 or higher.

See: https://github.com/the-dark-angel/BeQt for details.

==============================================================================
 Building and installing (briefly)
==============================================================================

In order to build TeXSample, just cd into the sources directory and execute
the following commands:

 * "qmake [BEQT_PATH=<path>]"
   Here, the path to BeQt may be specified

 * "make"
   or other similar command ("nmake", "mingw32-make", etc.)

 * "make install"
   You may need the superuser privileges in UNIX-like systems 

Note: When building from the command line, you have to configure
the environment (path to Qt libraries, etc.).

You may also use Qt Creator. After building the project, cd to
the output directory and execute the "make install" command, or
configure automatic execution of that command in Qt Creator.

See: http://qt-project.org/doc/qtcreator-2.6 for details.

==============================================================================
 Building and installing (in detail)
==============================================================================

When building TeXSample, you may pass some parameters to qmake:

 * "TSMP_CONFIG+=builtin_resources"
   Embed resources (including translations) into library files
   See: http://qt-project.org/doc/qt-5.0/resources.html for details

 * "TSMP_CONFIG+=no_install"
   Don't install any files (building only)

 * "TSMP_CONFIG+=no_headers"
   Don't install headers

 * "TSMP_CONFIG+=private_headers"
   Install private headers along with the public ones

 * "BEQT_PREFIX=<path>"
   Set path to BeQt libraries. Must be used if BeQt libraries were installed
   to a custom location

 * "TSMP_PREFIX=<path>"
   Set install path. See the note below

 * "TSMP_HEADERS_INSTALLS_PATH=<path>"
   Set install path for headers. See the note below

 * "TSMP_LIBS_INSTALLS_PATH=<path>"
   Set install path for library files. See the note below

 * "TSMP_RESOURCES_INSTALLS_PATH=<path>"
   Set install path for resources. See the note below

 * "TSMP_SUBDIR_NAME=<name>"
   Set name of the TeXSample subdirectory when TeXSample is used as a
   submodule

Note: In Windows systems TeXSample is installed to the
"C:\Program files\TeXSample" directory (or other similar directory, depending
on your system) by default.
Headers, libraries and resources are installed
to the corresponding subdirectories (include, lib, etc.).

In UNIX-like systems the directory structure during installation
looks like this:

 * "/usr/include/texsample"
   Path to headers

 * "/usr/lib"
   Path to libraries

 * "/usr/share/texsample"
   Path to resources

You may set another installation path. To do so,
pass the corresponding parameter to qmake (see above).

Warning: Don't use paths containing spaces. In Windows systems you may replace
directory names, containing spaces, with the corresponding short names:

See: http://support.microsoft.com/kb/142982 for details.

==============================================================================
 Using
==============================================================================

TeXSample may be used either as a system library, or as a project submodule.

Important: TeXSample may be linked to a project with just two lines of code
in the .pro file, but in that case you need to use qmake.

In case TeXSample is used as a system library (or is built and placed to a
separate directory), you need to add the following line to your .pro file:

 "include(<path_to_texsample>/depend.pri)"

"<path_to_texsample>" is a path to TeXSample resources (in UNIX-like systems
it is usually "/usr/share/texsample", and in Windows it is
"C:\Program files\TeXSample").

In case TeXSample is used as a submodule, you will have to make your
project structure slightly more compilcated, creating a common .pro file,
in which both TeXSample and your project will be included as subprojects.

For details, see:
http://qt-project.org/doc/qt-5.0/qmake-project-files.html#project-templates

Common .pro file example:

 "...
 CONFIG+=ordered
 TEMPLATE=subdirs
 SUBDIRS=texsample yourproject
 ..."

Important: Note, that the TeXSample submodule must be included before any
other submodule that uses it, and the "ordered" parameter must be passed to
the "CONFIG" variable. It's done to guarantee that TeXSample is built
before any other submodule uses it.

Note: Due to qmake features you may have to execute "qmake" and "make"
commands again after building the project (it's required for proper library
linking). The repeated command execution will take at most few seconds.

When building, TeXSample generates translation files (.qm), containing
translations of UI elements. These files are located in the "translations"
subdirectory (for example, "translations/texsample_ru.qm").

If you wish to use TeXSample whith different versions of Qt, the following
link may be useful for you:
http://qt-project.org/doc/qt-5.0/qtcore/qtglobal.html#QT_VERSION_CHECK

==============================================================================
 FAQ
==============================================================================

Q: Ho do I start using TeXSample?
A: See "Building and installing" and "Using".

Q: What are TeXSample license restrictions?
A: There are almost no restrictions. You may use TeXSample as you wish,
but don't forget that this statement doesn't apply to the Qt libraries.
See: COPYING.txt, http://qt-project.org/products/licensing for details.

Q: I'm having troubles using TeXSample, where can I get help?
A: Sorry, no user support for this library.

Q: I've detected a bug/I have an idea, where can I report/post it?
A: See the answer above.

Q: Why there is no documentation?
A: Unfoturnately, I just don't have enough time to write documentation.

==============================================================================
 Deploying
==============================================================================

When deploying an application that uses TeXSample, don't forget to include
the resource files (libraries, translations, etc. - see above).

It's recommended to build applications statically, because that helps avoid
dependency issues. You may use the "builtin_resources" parameter
in case of building your project statically.

For details, see:
http://qt-project.org/doc/qt-5.0/deployment.html#static-vs-shared-libraries
