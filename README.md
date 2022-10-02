# chess2d

*note: in order to run this application, you will need VS code. This project was done in VScode 2022*

makes use of the SDL, SDL-TTF, SDL-mixer and SDL-image library

# preview image
![showcase](preview-img/showcase.gif "showcase gif")

# class diagram
![class diagram](preview-img/chess%20class%20diagrams.png "class diagram")

# steps to run this program:

1. on your desktop, open the search bar and type ```"environment variables"```, you should see a system property named ```"edit the system environment variables"```. Click on that to open it

2. At the botttom under the advanced tab, you should see a button that says ```"Environment Variables..."```, click on that

3. At the top you should see a section named ```"User variables for User"```. In that box, click on the Variable labeled as ```"Path"``` so that it is highlighted in blue.

4. Click on the ```"Edit.."``` button just under the box and a new window should open

5. To the left there will be mulpiple buttons. Click on ```"New"``` then click on ```"Browse.."``` or you can manually type out a path or fetch a path from the place the libraries in library paths sections are located in from the file explorer.

6. Now browse to wherever it is you stored the folder for the application. So if you stored the chessgame folder like so: ```C:\Users\User\chessgame```, then browse there

7. continue browsing there and add this path which is in chessgame: ```"C:\<Your own paths>\chessgame\chessgame\dependencies\SDL2_image-2.6.0\lib\x64"```. *if you do not get these paths correct, you will get an error when you try to run the application*

8. repeat steps 5 to 7 for all the other paths you haven't done these steps for in the library paths section

9. after this is complete, click ok and exit the environment variables program

10. Launch VS code with admin rights.

11. Open an existing project with VS code and select to open the chessgame.sln file. It is located here: ```"C:\<Your own paths>\chessgame"``` as chessgame.sln

12. Once that opens, you may now run the solution by pressing CTRL+Shift+B or CTRL+F5. This should build the solution and launch the exe.

13. All the source code can be viewed by clicking on view which is on the top most bar, then clicking on solution explorer. When that opens, if you expand chessgame, you will see a folder named Soure Files where all the souce code the chess game is located.

# Library paths section:

1. SDL-image: ```"C:\<Your own paths>\chessgame\chessgame\dependencies\SDL2_image-2.6.0\lib\x64"```

2. SDL: ```"C:\<Your own paths>\chessgame\chessgame\dependencies\SDL2-2.0.22\lib\x64"```

3. SDL-TTF(for fonts and text): ```"C:\<Your own paths>\chessgame\chessgame\dependencies\SDL2_ttf-2.20.0\lib\x64"```

4. SDL-mixer(for sound effects): ```"C:\<Your own paths>\chessgame\chessgame\dependencies\SDL2_mixer-2.6.1\lib\x64"```
