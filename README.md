## Recursive-Descent-Parser

This is the basic version of the recursive descent parser for turtle graphics, the simple drawing language.

The parser forms the first part of the recursive descent parser. It receives instructions such as 'go forward, go left' etc,
and checks that the instructions comply with the turtle grammar. The grammar is provided below:

<div align="center">

![alt text](./images/grammar.png)

</div>

The parser then passes those instructions to the interpreter which draws on the screen using SDL.

The drawings can be really cool. For instance:


<div align="center">

![alt text](./images/example.png)

</div>

And even cooler designs such as this one:

<div align="center">

![alt text](./images/turtle1.png)

</div>

And this one:

<div align="center">

![alt text](./images/turtle2.png)

</div>

And finally:

<div align="center">

![alt text](./images/turtle3.png)

</div>

All code is ANSI C90 compliant, as per Neill Campbell's guidance.
