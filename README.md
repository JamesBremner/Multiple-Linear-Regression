# Multiple-Linear-Regression
A tool for multiple linear regression analysis. 

Background:
Multiple linear regression is a statistical technique for analysing the linear relationships between a 'dependent' variable and several 'explanatory' variables. For instance, in the field of economics MLR models may be used to help understand relationships between economic growth, interest rates and unemployment.

How does this tool work?:
The program takes a .txt file of sample data and reads the data into mathematical matrices (implemented as a C struct). Using the Ordinary Least Squares (OLS) method, an equation is generated which describes the relationship between the first variable in the data file, and the remaining variables. Model statistics are then calculated to determine the significance and accuracy of this relationship. 
