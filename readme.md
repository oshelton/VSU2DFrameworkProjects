# VSU 2D Frameowrk Projects - Archived

**WARNING**: This code almost certainly does not compile; even if you took the time to update everything to a more recent version of Visual Studio. It is here for illustrative and historical purposes. Dependencies are provided in a .7z if you're feeling particularly brave and want to give it a go though.

The projects within this repo were created for a handful of honors classes I took at Valdosta State University (2006-2010).

The framework I created builds on top of [Haaf's Game Engine](https://github.com/sungiant/HGE) (which sadly now only seems to exist as a snapshot in a github repo), [CEGUI](http://cegui.org.uk/), and [Anglescript](https://www.angelcode.com/angelscript/).

The framework provides entity and scene management, as well as timer support, and a number of other support functions that are nice to have in a game engine.

There are 4 projects in this repo:

- **Framework:** The source and dependencies of the framework itself.
- **Test:** A simple application that excercises the various features of the framework.
- **Polygon Triangulator:** A simple app that allows the user to draw a polygon with the mouse and then triangulate it.
- **Predator Prey Simulator:** Application that allows for the loading and observation of various predator and prey scenarious defined in Angelscript script files. Only the placement and kind of creature can really be scripted though (so nothing too exciting).

The `Source\Predator Prey Simulator\bin\Release` directory does contain a working binary for the predator prey simulator, but sadly none of the other applications have functioning binaries.
