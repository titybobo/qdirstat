# QDirStat To Do List

This is roughly ordered by priority.


## Ready-made Packages for SUSE and Ubuntu

- Write a .control file for Ubuntu .deb packages

- Use the openSUSE build service to create .deb packages


## General

### Translations

- Add translation stuff. Setting up the Qt translator classes is easy
  enough. The translation file(s) will probably also end up in the resource
  file to avoid being dependent on external files (they can always go
  missing). But then, since it's not KDE any more, the number of supported
  languages will be really small: I can supply a German translation, and maybe
  I can talk my Czech, Spanish and maybe Russian colleagues into contributing
  their languages, but there won't be many more than that.

- Once translations are there, definitely add config option to "force English".
  As much as translations are welcomed, I do not agree to translate everything
  to death, in particular when the English term is much more widely used. This
  happens a lot in German translations. I don't want to be at the mercy of the
  German translator; I want to be able to use my original English texts --
  without switching my entire desktop and shell environment to English or the
  POSIX locale.



### Online Help

I know that most users can't be bothered to read that stuff anyway, but I spent
a lot of work for the old help files; porting them should be easy enough. But
that will definitely be only for English and maybe (!)  for German. There is no
way to maintain that much text in any more languages.


## Some Time in the Future

### Reports?

- Format selected items in useful format and export to clipboard / to file?

- Text, CSV, YaML?


### Config Dialog


- General parameters config page - postponed for the time being. There are
  currently not enough worthwhile parameters to be configured.

- Config dialog page for OutputWindow colors

- Find a better way to get objects like CleanupCollection and MimeCategorizer
  to the respective config pages; the main window shouldn't need to know that
  much about the internal structure of those pages.

- Create a subclass for things common to all the config pages:
  - setup()
  - apply()
  - discardChanges()



### Treemap Parameters

Add config page for at least some of them?

Not sure if all those crazy treemap parameters need to be user configurable.
They are pretty much expert-only, and most of them look pretty scary to normal
people. I might leave them in the config file, but most likely anybody who
really wants to change any of them will need to use his favourite editor.



### MacOS X Support

- Find out how to package a MacOS app

- Find a volunteer for a MacOS X platform maintainer


### Windows Support

**Postponed to the very far future**

- Create DirReadJob subclass that strictly uses Qt classes (QFileInfo) and no
  POSIX system calls

- Find out how to package a windows app

- Installer


## Unclassified / Undecided

### Support for non-UTF-8 Locales

See also
[Github Issue #19]
(https://github.com/shundhammer/qdirstat/issues/19)

This might be useful for some users, in particular in Japan (Shift-JIS
encoding). But this has large potential to bring back nasty problems for users
using a UTF-8 locale, but who not really aware of all the implications: If
their environment is not set up correctly, the might have the opposite problem
of that lone user who requested this (unaware that he has been using an
outdated locale environment for a very long time).

It might or might not be worthwhile to introduce a large risk of breaking
things for the great majority of users (who have a modern UTF-8 setup) to maybe
make a small number of users happy (who just never bothered to update to a
modern UTF-8 locale environment).

This might warrant a poll (polldaddy?) how many users are actually interested
in this.
