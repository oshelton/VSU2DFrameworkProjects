CS 3520 Project
Jack Owen Shelton

Polygon Triangulator.

This is a simple application that converts a simple polygon (no holes, no intersecting edges) via the ear-clipping algorithm.  The algorithm can be controlled using the control window that by default appears on the left side of the window.

Points can be added to the polygon by clicking on empty space in the main part of the window as long as the edit mode box is checked and the Calculate button has not been clicked.

The polygon can be erased at any time by clicking the Reset button.

The Original and Optomized output checkboxes can be used to turn on/off which version of the algorithm is being displayed.  Both versions can be displayed at the same time.

A file is generated at each run of the application and placed in the same folder as this document called report.txt which summarizes how long each version takes and the percent improvement of the new optomized version as well as the output and input of the algorithms.