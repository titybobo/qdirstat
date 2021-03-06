# QDirStat

Qt-based directory statistics: KDirStat without any KDE -- from the author of
the original KDirStat.

(c) 2015 Stefan Hundhammer <Stefan.Hundhammer@gmx.de>

Target Platforms: Linux, BSD, Unix-like systems

License: GPL V2

Updated: 2016-11-02


## Overview

QDirStat is a graphical application to show where your disk space has gone and
to help you to clean it up.

This is a Qt-only port of the old Qt3/KDE3-based KDirStat, now based on the
latest Qt 5. It does not need any KDE libs or infrastructure. It runs on every
X11-based desktop on Linux, BSD and other Unix-like systems.

QDirStat has a number of new features compared to KDirStat. To name a few:

- Multi-selection in both the tree and the treemap.
- Unlimited number of user-defined cleanup actions.
- Properly show errors of cleanup actions (and their output, if desired).
- File categories (MIME types) and their treemap color are now configurable.
- Exclude rules for directories are easily configurable.
- Desktop-agnostic; no longer relies on KDE or any other specific desktop.

See section _New Features_ for more details.



## Screenshots

![Main Window Screenshot]
(https://github.com/shundhammer/qdirstat/blob/master/screenshots/QDirStat-main-win.png)

_Main window screenshot - notice the multi-selection in the tree and the treemap_


![Cleanup Action Output Screenshot]
(https://github.com/shundhammer/qdirstat/blob/master/screenshots/QDirStat-cleanup-output.png)

_Screenshot of output during cleanup actions. Of course this window is purely optional._


![Cleanup Action Configuration Screenshot]
(https://github.com/shundhammer/qdirstat/blob/master/screenshots/QDirStat-cleanup-config.png)

_Screenshot of cleanup configuration._

![MIME Categories Configuration Screenshot]
(https://github.com/shundhammer/qdirstat/blob/master/screenshots/QDirStat-mime-config.png)

_Screenshot of MIME category configuration where you can set the treemap colors
for different file types (MIME types), complete with a real treemap widget as
preview._

![Exclude Rules Configuration Screenshot]
(https://github.com/shundhammer/qdirstat/blob/master/screenshots/QDirStat-exclude-rules-config.png)

_Screenshot of the exclude rules configuration where you can define rules which
directories to exclude when reading directory trees._

-----------------------

![Tree Column Configuration Screenshot]
(https://github.com/shundhammer/qdirstat/blob/master/screenshots/QDirStat-column-config.png)

_Context menu of the tree header where you can configure the columns._


## Current Development Status

**Latest stable release: V1.1**

- 2016-10-31 (Halloween) **New stable release: V1.1-Pumpkin**

  It's about time for another official release to get the accumulated fixes and
  small changes out into the world. Since today is Halloween, this release
  shall be named _Pumpkin_ (as in the unforgettable Charlie Brown's _Great
  Pumpkin_).

  The last stable release, V1.0, was in mid-May (2016-05-16). Since then, there
  were 5 bug fixes and one small feature (the config file split up into
  independent parts so admins can provide presets to their users without
  overwriting the complete configuration), all described in greater detail
  below.

- 2016-10-23

  - Fixed [GitHub issue #32](https://github.com/shundhammer/qdirstat/issues/32):
    %p does not escape single quotes properly

    If you have a file name like `Don't do this.txt` (with a quote character in
    the name), the shell used when executing a cleanup action with this would
    complain about unmatched single quotes.

    QDirStat had always escaped such single quotes, but not the way common
    shells (Bash, Zsh) expect it: They don't want a backslash in front of that
    embedded single quote. Rather, you need to terminate the string with a
    single quote, escape the embedded quote with a backslash (or put it into
    double quotes), and then re-open the old string with another single quote.

    Thus, `'Don't do this'` becomes `'Don'\''t do this'`.

    This is certainly not what most people expect. I just wonder how much other
    software is out there that does it the intuitive (yet wrong) way: Just
    escape the single quote with a backslash (`'Don\'t do this'`).

    Of course, such file names should be avoided entirely, but you can't help
    some slightly broken MP3 ripper program doing it, so it needs to be handled
    correctly.

  - Fixed [GitHub issue #31](https://github.com/shundhammer/qdirstat/issues/31):
    Segfault with cleanup action while reading directories

    Now disabling cleanups that have a refresh policy other than "No Refresh"
    while directory reading is in progress; otherwise the re-read when the
    cleanup action has finished clashes with the directory read already in
    progress.

    This is not an optimal solution, but a very pragmatic one; the optimal
    solution might queue updates and execute them after the main read is done.

  - Fixed [GitHub issue #33](https://github.com/shundhammer/qdirstat/issues/33):
    Added command line option `--slow-update` (or `-s`) for slow remote X connections.


- 2016-08-12

  - Fixed [GitHub issue #23](https://github.com/shundhammer/qdirstat/issues/23):

    The internal cache writer would sometimes generate incorrect cache files
    because of buggy URL escaping resulting in an empty file name and thus
    invalid cache file syntax. This affected file names with colons (which is
    weird, but legal).

    One of these days I'm going to throw out all that QUrl stuff and replace the
    few things that I need with something that actually works consistently and
    not just under optimum conditions.


- 2016-08-10

  - Fixed [GitHub issue #22](https://github.com/shundhammer/qdirstat/issues/22):

    Cache files containing the root file system would not display correctly or
    segfault under certain conditions. This is now fixed.

  - Added "Refresh All" action to the main window tool bar. I had consciously
    avoided that because it's just too tempting to re-read the complete
    directory tree rather than think about what actually might have changed and
    then refresh just that, but it has become so common to use that action in
    web browsers that I found myself missing that more and more. And re-reading
    is not that expensive on today's mainstream PCs.


- 2016-07-02

  - Fixed [GitHub issue #21](https://github.com/shundhammer/qdirstat/issues/21):

    When started from a desktop menu, i.e. without any command line parameters,
    QDirStat would not prompt for a directory to read, but read the current
    directory (typically the user's home directory) right away.

  - More graceful handling for nonexisting paths specified on the commmand
    line: It now no longer just throws an exception right after starting the
    program (which looks like a crash to the unwary user), but posts an error
    popup instead and then asks for a directory to read.


- 2016-06-29

  - V1.01 (Development version)

  - Split up config file into four separate ones below ~/.config/QDirStat:

    - QDirStat.conf
    - QDirStat-cleanup.conf
    - QDirStat-exclude.conf
    - QDirStat-mime.conf

    This should make it much easier for site administrators to provide their
    own site-wide cleanup actions, exclude rules, or MIME categories. I did
    this with this in mind:

      http://moo.nac.uci.edu/~hjm/kdirstat/kdirstat-for-clusters.html

    Here, they describe how users should overwrite their KDirStat config file
    with one provided by the site admin so all users have those carefully
    crafted cleanup actions. But that also means that all other settings get
    lost each time there is a change in any of those commands, and users have
    to update that config file again.

    With the latest change, it is now possible to only replace the cleanup
    action config (QDirStat-cleanup.conf) and leave everything else untouched.

    Notice that this is far from a perfect solution; all cleanup actions the
    user added himself still get lost. But doing this perfectly might pretty
    quickly become an overengineered solution that would be hard to understand
    for everybody.

    As for migration from previous single-file configurations, QDirStat does
    that automatically: It reads the single file and moves the respective parts
    where they belong. No need to bother with any migration scrips or anything
    like that.


- 2016-05-16 **First stable release: V1.0**

  After 3 months of Beta phase and 3 Beta releases, here is finally the
  official first stable release of QDirStat: Version 1.0.

  In terms of source code, there were very little changes from the last Beta
  (0.98-Beta3 from 2016-04-08) and no real code change (only the version number
  increased) from the last check-in from 2016-04-11. This version can really be
  considered stable in the truest sense of the word. It was not rushed out the
  door, and there were no hectic last minute changes. It is well tested, and
  the community had ample opportunity to report any problems.


_See file DevHistory.md for older entries:_

https://github.com/shundhammer/qdirstat/blob/master/DevHistory.md



## Motivation / Rant

After having used KDE since its early days (since about 1998), I don't like the
direction any more that KDE is taking.  I loved KDE 1, KDE 2, KDE 3. When KDE 4
came along, it took me a long time to try to adopt it, and when I did, I moved
back to KDE 3 after a short while, then tried again with the next release,
moved back again -- several times.

I really tried to like it, but whenever I thought I tamed it to meet my
requirements, a new version came along that introduced yet another annoyance.

To name a few:

- I don't like the fact that I can't simply put icons on my desktop any more --
   no, I have to create a plasmoid first as a container, and those things keep
   doing weird stuff that drives every user crazy. With one false move of your
   mouse, it might be gone, change shape, move to another place or whatever.

- I also don't like the desktop search that eats resources like there is no
  tomorrow (disk space, disk I/O, CPU usage) and that for all practical
  purposes you can't get rid of.

- I don't like the fact that the mail client relies on that MySQL based
  framework called _Akonadi_ that is not only resource-hungry, but also so
  fragile that I had to use the _akonadiconsole_ lots of times just to bring it
  back to life. Seriously, if I as a Linux system developer have a hard time
  doing that, what is a normal user expected to do?

- Activities vs. multiple desktops. I tried to use both, but they don't
  integrate well. The desktops previewer is far inferior to the old one from
  KDE3: Only monochrome rectangles, no real preview. The activities plasmoid
  keeps rearranging my carefully placed and named activities at random. WTF?!

Now the next generation KDE is arriving, _Plasma 5_. When I was force-migrated
to it at work with the _SUSE Tumbleweed_ rolling release, the experience was so
bad that I moved to the _Xfce_ Desktop.

Now every time I start my own KDirStat, it starts about a dozen KDE processes
along with it -- processes that it needs only for minor things like loading
icons or translations. I really don't need or want that.

Time to make KDirStat self-sufficient; it never used that much of all the KDE
infrastructure anyway. Time to make a pure Qt-based and self-sufficient
QDirStat.

And while I was at it, time to add some features that I had wanted for a long
time, yet I could never get myself to start working on:

- Multi-selection in the directory tree so you can delete several files at
  once.

- Remove limitations like having only a fixed number of user-defined cleanup
  actions.

- Properly show the output of cleanup actions, in particular when they reported
  errors.

- Make treemap colors configurable: Use custom colors and match them to
  user-defined filename extensions.

- Move away from the arcane KDE build system: Back with KDE 1/2/3 it was the
  _Autotools_ with custom KDE extensions that only a handful people in the
  world understood (I was not among them), later _CMake_ which is little
  better, just differently confusing.

Yes, there is a Qt4 / Qt5 port of KDirStat called K4DirStat. K4DirStat is an
independent project that started when I had not worked on the old KDirStat for
a long time (my last KDirStat release had been in mid-2006).

QDirStat is based on that same code from the 2006 KDirStat. It's an 80% rewrite
using a lot of newer Qt technologies. And there was a lot of cleaning up that
old code base that had been long overdue.



## New Features

- Multi-selection:

  - Both views (the tree and the treemap) now support _extended_ selection,
    i.e. you can select more than one item. This was the most requested feature
    for the last KDirStat. Now you can select more than one item at the same
    time to move it to the trash can, to directly delete it or whatever.

  - Tree view:
    - Shift-click: Select a range of items.
    - Ctrl-Click:  Select an additional item or deselect a selected one.

  - Treemap:
    - Ctrl-Click:  Select an additional item or deselect a selected one.

    - The current item is highlighted with a red rectangle, all other selected
      ones with a yellow rectangle. If the current item is not also selected,
      it has a dotted red outline.

- Proper output of cleanup actions with different colors for the commands that
  are executed, for their output and for error messages (see screenshot
  above). That output window can be configured to always open, to open after a
  certain (configurable) timeout, or only if there are error mesages -- or not
  at all, of course. If things go wrong, you can kill the external command
  started by the cleanup action from there. You can zoom in and out (increase
  or decrease the font size) as you like.

- New macros to use in cleanup actions:

  - %d : Directory name with full path. For directories, this is the same as
    %p. For files, this is their parent directory's %p.

  - %terminal : Terminal window application of the current desktop; one of
    "konsole", "gnome-terminal", "xfce4-terminal", "lxterminal", "eterm".
    The fallback is "xterm".

  - %filemanager : File manager application of the current desktop; one of
    "konqueror", "nautilus", "thunar", "pcmanfm". The fallback is "xdg-open".

- Which desktop is used is determined by the _$XDG_CURRENT_DESKTOP_ environment
  variable. Users can override this with the _$QDIRSTAT_DESKTOP_ environment
  variable, so you can get, say, the Xfce terminal or file manager despite
  currently running KDE if you set

      export QDIRSTAT_DESKTOP="Xfce"

- Of course, you can still simply use your favourite file manager if you simply
  change %filemanager in the default "Open File Manager Here" cleanup action to
  the command to start it.

- You can now select the shell to use for the cleanup commands:

  - $SHELL (the user's login shell) - using the same environment, syntax and
    wildcard etc. behaviour of the shell the user is used to.
  - /bin/bash for well-defined behaviour for wildcards etc.
  - /bin/sh as a last resort (which might be a simplistic _dash_ on Ubuntu).

- Mouse actions in the treemap window:

    - Left click:           Select item and make it the current item.
    - Right click:          Open the context menu with cleanup actions and more.
    - Ctrl+Left click:      Add item to selection or toggle selection.
    - Middle click:         Select the current item's parent. Cycle back at toplevel.
    - Double click left:    Zoom treemap in.
    - Double click middle:  Zoom treemap out.
    - Mouse wheel:          Zoom treemap in or out.

- You can configure what columns to display in the tree view and in which
  order. The only thing that is fixed is the "Name" column which is always
  there and always the first (leftmost). Use the context menu in the tree
  header to unlock column widths. Drag columns to the left or right to change
  their order.

- Exclude rules are now greatly simplified. They no longer always get the
  entire path to match which requires quite complex regexps; by default, they
  only get the last path component -- i.e., no longer
  "/work/home/sh/src/qdirstat/src/.git", but only ".git". You can now even tell
  the exclude rule to use a simplified syntax: "FixedString" or "Wildcard" in
  addition to the normal "RegExp". The old behaviour (matching against the full
  path) is still available, though.

- Configuration dialog for exclude rules -- see screenshots.

- Actions to go one directory level higher or to the toplevel: Context menu and
  menu "Go To" -> "Up One Level" or "Toplevel". This is useful if you clicked
  on a file in the treemap that is deep down in some subdirectory, and you want
  to know what subdirectory that is: Simply click "Go Up" twice (the first
  click will get you to the <Files> pseudo subdirectory, the second one to the
  real one).

- Open all tree branches up to a certain level and close all other ones: Menu
  "View" -> "Expand Tree To Level" -> "Level 0" ... "Level 9".

- The total sum of the selected items (subtrees) is displayed in the status
  line if more than one item is selected.

- Icons are now compiled into the source thanks to Qt's resource system; now
  it's just one binary file, and nothing will go missing. No more dozens of
  little files to handle.

- The build system is now Qt's _QMake_. I got rid of that _AutoTools_
  (Automake, Autoconf, Libtool) stuff that most developers find intimidating
  with its crude M4 macro processor syntax. QMake .pro files are so much
  simpler, and they do the job just as well. And no, it will definitely never
  be _CMake_: I don't like that thing at all. It's just as much as a PITA as
  the AutoTools, just not as portable, no usable documentation, it's changing
  all the time, and those out-of-source builds are a royal PITA all on their
  own with constantly having to change back and forth between source and build
  directories.

- QDirStat now has its own log file. It now logs to /tmp/qdirstat-$UID.log,
  which for most Linux home users (with only one user account on the machine)
  is typically /tmp/qdirstat-1000.log . No more messages on stdout that either
  clobber the shell you started the program from or that simply go missing.

- No longer depending on dozens of KDE libs and a lot of KDE infrastructure; it
  now only requires Qt which is typically installed anyway on a Linux / BSD /
  Unix machine with any X11 (graphical) desktop.

- It should still compile and work with Qt4. We now have a contributor who is
  very interested in that (Michael Matz), so it should be possible to maintain
  this compatibility.

- Slow down display update from 333 millisec (default) to 3 sec (default) with
  `qdirstat --slow-update` or `qdirstat -s`. The slow update interval can be
  customized in `~/.config/QDirStat/QDirStat.conf`:

    ```
    [DirectoryTree]
    SlowUpdateMillisec = 3000
    ```



## Old Features

Features ported from the old KDirStat:

- Fast and efficient directory reading.

- Not crossing file system boundaries by default so you can see what eats up
  all the disk space on your root file system without getting distorted numbers
  due to all the other file systems that are mounted there. If you absolutely
  wish, you can use "Continue reading at mount point" from the context menu or
  from the "File" menu -- or configure QDirStat to always read across file
  systems.

- Efficent memory usage. A modern Linux root file system has well over 500,000
  objects (files, directories, symlinks, ...) and well over 40,000
  directories. This calls for minimalistic C++ objects to represent each one of
  them. QDirStat / KDirStat do their best to minimize that memory footprint.

- Hierarchical tree view that displays accumulated sums in each branch,
  together with a percent bar so you can see at a glimpse how the
  subdirectories compare with each other.

- All numbers displayed human readable -- e.g., 34.4 MB instead of 36116381
  Bytes.

- Each tree level uses another color for that percent bar so you can easily
  compare subdirectories even if some of them are opened in the tree.

- If a directory has files and subdirectories, all files in that subdirectory
  are grouped into a <Files> pseudo directory (called _dot entry_ in the
  QDirStat sources) so you can compare the disk usage of files on that
  directory level with the subdirectories.

- Displaying the latest modification time of any object in each branch. You can
  instantly see in what subdirectory where any changes lately. You can sort by
  this column, of course.

- Treemap display. Treemaps are a way to visualize hierarchical data
  structures, invented by Ben Shneiderman. Basically, the hierarchy is
  flattened and each level grouped in a rectangle, inside which it is again
  subdivided in rectangles. The area of each rectangle corresponds to the size
  of each item or subdirectory. For the purposes of QDirStat, it is enough to
  know that a large blob corresponds to a large file; you can instantly see
  where large ISOs or movies are.

- You can zoom the treemap in and out (Ctrl + / Ctrl - / mouse wheel / menu /
  tool bar) to see more details of directories that are otherwise dominated by
  larger ones.

- You can move the boundary between treemap and tree view up and down as you
  like. You can also get rid of the treemap completely (menu "Treemap" -> "Show
  Treemap" or F9 key)

- Treemap and tree list view communicate. Select an item in one view, and it is
  also selected in the other. If you click on that large blob in the treemap,
  it is located in the tree view, all branches up to its directory are opened,
  and the tree view scrolls to that item.

- Cleanup actions. Once you know what is consuming the disk space, you can
  start cleanup actions from within QDirStat to reclaim disk space - or to
  investigate further if you can safely delete a file. You can create your own
  cleanup actions (as many as you like), and there are some predefined ones:

  - Open file manager here. This will start a file manager in the directory of
    the current item. QDirStat tries its best to guess the name of the relevant
    file manager application for the current desktop, based on the
    $XDG_CURRENT_DESKTOP environment variable. You can override this with the
    $QDIRSTAT_DESKTOP environment variable.

  - Open terminal window here. In most cases, this is much easier than to
    navigate to that directory with 'cd' in an already open terminal window and
    using tab-completion numerous times. As with the file manager application,
    QDirStat tries its best to guess the name of the relevant terminal window
    application for the current desktop.

  - Move to trash bin. QDirStat has its own implementation of the XDG trash
    specification.

  - Delete immediately.

  - Compress: Create a compressed tar archive from a directory and then delete
    the directory.

  - Delete junk files: Backup files left behind by editors, core dumps.

  - All predefined cleanup actions are fully configurable, of course. You can
    change any of them, disable them, or delete them.

- You can copy the complete path of the selected file or directory to the
  system clipboard and paste it to another application.

- Reading and writing cache files:

  - This is mostly meant for remote servers in some server room somewhere:
    Rather than installing the Qt and X11 runtime environment and running
    QDirStat over remote X (ssh with X forwarding), you can run the supplied
    _qdirstat-cache-writer_ Perl script on the server, copy the resulting cache
    file to your desktop machine and view the content there with QDirStat.

  - For large directories (archives etc.) that don't change that much, you can
    also generate a QDirStat cache file (either with the Perl script or with
    QDirStat itself) and save it to that corresponding directory. If QDirStat
    finds a file .qdirstat.cache.gz in a directory, it checks if the toplevel
    directory in that cache file is the same as the current directory, and if
    it is, it uses the cache file for that directory rather than reading all
    subdirectories from disk. If you or the users that machine use QDirStat
    often, this might take a lot of I/O load from the server.

  - If you use the '-l' option of the qdirstat-cache-writer script, it uses the
    long file format with a complete path for each entry, so you can use the
    _zgrep_ command with it as a replacement for the _locate_ command.

  - The KDirStat / QDirStat file format is well documented and very simple. It
    seems to be used by a number of admins and some backup software.
    See also the specification in the doc/ directory:
    https://github.com/shundhammer/qdirstat/blob/master/doc/cache-file-format.txt

  - You can specify a cache file to read directly at the command line:

        ```
        qdirstat --cache cache-file
        ```

- Other command line options: See
    ```
    qdirstat --help
    ```


## Features that are Gone

(Compared with the old KDirStat)


- KPacman: That was that PacMan animation wile reading directory reading. This
  is gone now. KPacMan looked out of place pretty soon after it got to KDirStat
  due to Qt styles doing fancy rendering of widget backgrounds with gradients
  etc.  I know that it does have its fans, but it's unrealistic to get this
  back without breaking the menu bar rendering.

- KioDirReadJob: Network-transparent directory reading for network protocols
  like FTP, HTTP, Fish (ssh-based). This depended on KDE's KIO slaves, so this
  functionality is gone now without KDE. That's a pity, but this is a little
  price to be paid to avoid the rest of the hassle with using the KDE libs.

- KFeedback: That was that form where users could tell their opinion about
  KDirstat. But that was not used that often anyway - not nearly enough to
  justify the effort that has gone into that part. And the KDE usability
  people, like usability people generally tend to do, first discussed that to
  death and then decided they didn't want anything like that in general in KDE
  applications. So be it.

- KActivityTracker: That was a supporting class for KFeedback that kept track
  of how much a user was using the program and after a while (when it was
  determined that it made sense) asked if the user wouldn't like to give his
  feedback about the program.
  Don't you all just hate those dumbass web designers who tell you to do a
  survey how much you like their grand web page before you even had a chance to
  look at it? Shove a pop-up up your face covering the stuff you are
  interesting in with their self-loving marketing bullshit? -- KActivityTracker
  was made to avoid exactly this: Ask the user only once you know that he
  actually used the program for a while.



## MacOS X Compatibility

I was amazed to find that it doesn't take more than the normal "qmake" and then
"make" to build QDirStat for MacOS X. We (Sonja Krause-Harder and I) did some
basic testing, and it seems to work.

The cleanups may need some adaptation, but this is something that might even be
configured by the user.

If anybody wants to give it a try, download Qt for MacOS X, install it, open a
shell window, search the _qmake_ command:

    find . -name qmake

Add this to your $PATH, then do the normal

    qmake
    make

Not sure how well "make install" works, though.

**_Be advised that QDirStat on MacOS X is purely experimental at this stage._**

There is no support. If you try this, you are on your own. Even more so than
with the other platforms, you will have to make sure that your Qt build
environment is set up correctly.

_There be dragons._ ;-)


### Architecture maintainer wanted for QDirStat for MacOS X

If you are a developer with some prior C++ and Qt knowledge on the MacOS X
platform and you'd like to see QDirStat working there, please consider joining
the team.


## Windows Compatibility

None for the forseeable future.

Directory reading might be quite easy to replace for Windows; we don't have
that problem with devices and crossing filesystems on that platform.

But the cleanups might be a challenge, "move to trash" works completely
differently, and we'd need an installer for a Windows version.

So, for the time being, use [WinDirStat](https://windirstat.info/) instead.
WinDirStat is a close relative to the KDirStat family anyway; the author had
liked KDirStat on Linux so much that he decided to write a Windows clone and
called it WinDirStat.


## Ready-made Packages

### openSUSE / SUSE Linux Enterprise

QDirStat packages for:

- openSUSE Tumbleweed
- openSUSE Leap 42.1
- openSUSE 13.2
- SUSE Linux Enterprise (SLE) 12 SP1
- SUSE Linux Enterprise (SLE) 12

Download page for the [**latest stable release**: QDirStat 1.0]
(https://software.opensuse.org/download/package?project=home:shundhammer:qdirstat-stable&package=qdirstat)

Download page for the [**current development version** (git master)]
(https://software.opensuse.org/download/package?project=home:shundhammer:qdirstat-git&package=qdirstat)

Since this version is in development, it may be not quite as stable and
reliable as the latest official stable release, although the QDirStat
developers try their best to keep it as stable as possible.


### Ubuntu

See Nathan Rennie-Waldock's
[**QDirStat PPA**]
(https://launchpad.net/~nathan-renniewaldock/+archive/ubuntu/qdirstat)


## Building

### Build Environment

Make sure you have a working Qt 5 build environment installed. This includes:

- C++ compiler (gcc recommended)
- Qt 5 runtime environment
- Qt 5 header files
- libz (compression lib) runtime and header file

If anything doesn't work, first of all **make sure you can build any of the
simple examples supplied with Qt**, e.g. the
[calculator example]
(http://doc.qt.io/qt-5/qtwidgets-widgets-calculator-example.html).


#### Ubuntu

Install the required packages for building:

    sudo apt-get install build-essential qtbase5-dev zlib1g-dev

Dependent packages will be added automatically.

Recommended packages for developers:

    sudo apt-get install qttools5-dev-tools qtbase5-doc qtbase5-doc-html qtbase5-examples

See also

http://askubuntu.com/questions/508503/whats-the-development-package-for-qt5-in-14-04

If you also have a Qt4 development environment installed, select the desired
one via _qtchooser_:

    sudo apt-get install qtchooser
    export QT_SELECT="qt5"


#### SUSE

Install the required packages for building:

    sudo zypper install -t pattern devel_C_C++
    sudo zypper install libQt5Widgets-devel libqt5-qttools zlib-devel

If you also have a Qt4 development environment installed, make sure that the
Qt5 version of 'qmake' is the first in your $PATH:

    export PATH=/usr/lib64/qt5/bin:$PATH


### Compiling

Open a shell window, go to the QDirStat source directory, then enter these
commands:

    qmake
    make


### Installing

    sudo make install

or

    su -c make install


## Contributing

See file Contributing.md :

https://github.com/shundhammer/qdirstat/blob/master/Contributing.md


## To Do

See file TODO.md :

https://github.com/shundhammer/qdirstat/blob/master/TODO.md


## Troubleshooting

### Can't Move a Directory to Trash

QDirStat does not copy entire directory trees to the trash directory in your
home directory. It tries its best to copy single files there, but for anything
larger, it strictly sticks to the XDG trash specification. So, if you have a
separate /home partition (which is strongly recommended for a lot of reasons),
you cannot move a directory from /tmp to trash because that would mean to move
a directory across file systems -- from /tmp/somewhere to your
~/.local/share/Trash .

But there is an easy workaround. It's described in the XDG trash spec, but here
is a simple recipe what you can do:

Create a dedicated trash directory on the toplevel (mount point) of that file
system. If it is mounted at /data, do this:

    cd /data
    sudo mkdir .Trash
    sudo chmod 01777 .Trash

Permissions '01777' means "rwx for all plus sticky bit". The sticky bit for a
directory means that only the owner of a file can remove it. The sticky bit is
required for security reasons and by the XDG trash spec (it's also required by
the spec that applications like QDirStat refuse to use that trash directory it
if it is not set).

Now you can move directory trees from /data/somewhere to the trash with
QDirStat. It will end up in /data/.Trash/1000/files/somewhere (if 1000 is your
numerical user ID which is common in Linux for the first created user). Your
desktop's native trash application (your trash icon on the desktop and the file
manager window you get when you click on it) should show it, and you can empty
the trash from there.

In Xfce, this works out of the box. KDE might need a forced refresh (press F5)
in that window.

For USB sticks, this explicit toplevel .Trash directory is usually not
necessary: If you have write permission on its toplevel directory, QDirStat
will (again in compliance to the XDG trash specification) create a trash
directory .Trash-1000 in its toplevel directory which is the fallback if there
is no .Trash directory there. This would also happen automatically on /data and
/ if you had write permission there -- which is, however, very uncommon.

What the major desktops (KDE, GNOME, Xfce) usually do with their native file
managers is to recursively copy the entire directory tree to your home trash
directory and then remove the original. Not only is this time-consuming and
wasteful (copy stuff before deleting?!), it might also be error-prone if that
directory tree contains symlinks, sockets or even just sparse files; and
permissions and timestamps (mtime, ctime, not to mention atime) might or might
not be the same as before. This might become a problem if you decide to restore
that directory tree from the trash.

I thought about emulating this behaviour, but this basically means to
reimplement large parts of what the _rsync_ command does (calling _rsync_ from
within QDirStat might not be such a good idea - what if it's not available or
anything goes wrong?), and frankly, I don't want to do that - in particular not
for something that typically gets deleted shortly afterwards anyway upon "empty
trash".

So, if you have this problem, please use the .Trash directory workaround
described above.


## Reference

### Original KDirStat

Home page: http://kdirstat.sourceforge.net/

Sources: https://github.com/shundhammer/kdirstat


### K4Dirstat

Home page: https://bitbucket.org/jeromerobert/k4dirstat/wiki/Home

Sources: https://bitbucket.org/jeromerobert/k4dirstat/src


### WinDirStat (for Windows)

Home page: https://windirstat.info/


### XDG Trash Spec

http://standards.freedesktop.org/trash-spec/trashspec-1.0.html


## Reviews

### YouTube

[Spatry: _Quick Look: QDirStat_]
(https://www.youtube.com/watch?v=ysm4-x_5ftI)


## Misc

http://moo.nac.uci.edu/~hjm/kdirstat/kdirstat-for-clusters.html