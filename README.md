# Deserializer for Qt
## Description
Tool for transforming QDataStream serialized data from file "A" to text file "B". 

## How to use
There here are three avaible commands:
```
read <path>
write <path>
quit
```
Each of them is quite self-explanatory.
- read = searches for user-defined file. If found, binary data are stored into array and passed into main scope.
- write = uses previously fetched data and stores them into readable .txt file
- quit = exit application

Paths to files could be written as either absolute or relative (to program build folder). 

## ** NOTE: **
I've made this for float array datatype. Further customization of source code is advised.
