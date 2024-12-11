# CMD_Trading_Platform_using-CPP
Command line based Trading platform (simulation) using C++
Program to simulate transactions on a trading platform.

Build as part of my coursework for "Object Oriented Programming Specialization"
Course URL: https://www.coursera.org/specializations/object-oriented-programming-s12n

Remarks on the various Classes built:
The OrderBookEntry represents a row in the order book data set (i.e. a single order in the order book). It can be a bid or an ask order.

The OrderBook class presents a high level interface on all the orders in the order book data set, 
including query functions to find out which products are in the data set, and to retrieve a subset of the orders using filters.

The MerkleMain class represents the application itself, and it deals with user input and menu printing. 

The Wallet class represents the user's wallet that contains the currency & its amount that he/she can use to place an ask or bid order.
