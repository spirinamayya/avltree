# AVL Tree 
This repository contains step-by-step AVL Tree visualising application written in C++ language. Project itself is Qt based, written in Clion.
It has diverse functionality, which involves not only insertion, deletion and search operations, but also allows to study traversal types.
What is more, to improve user's experience step back option and change of speed possibility are included.For those, who do not want to insert nodes one by one, possibility to download the whole tree from .txt file was included.\
In the following picture interace of the application is shown:\
\
![Screenshot](interface.png)
# Build instructions
To build program user has to change options in CMakeLists.txt, so that they suit configurations of Qt application. Inside program, in file View.cpp inside constructor appropriate link to stylesheet.qss file should be provided (otherwise, colour of the buttons and slider will be lost).
