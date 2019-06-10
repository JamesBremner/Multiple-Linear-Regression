# Multiple-Linear-Regression
A tool for multiple linear regression analysis. 

Background:
Multiple linear regression is a statistical technique for analysing the linear relationships between a 'dependent' variable and several 'explanatory' variables. For instance, in the field of economics MLR models may be used to help understand relationships between economic growth, interest rates and unemployment.

How does this tool work?:
The program takes a .txt file of sample data and reads the data into mathematical matrices (implemented as a C struct). Using the Ordinary Least Squares (OLS) method, an equation is generated which describes the relationship between the first variable in the data file, and the remaining variables. Model statistics are then calculated to determine the significance and accuracy of this relationship. 



Example output:


    ******************************************************************************
    *                                                                            *
    * Title: Multiple Linear Regression                                          *
    * Description:  This program takes an inputted data file and performs        *
    *               multiple linear regression analysis on the data.             *
    * Author:       Oscar Zealley                                                *
    * Instructions: Put your data in a .txt file in the same directory as        *
    *               this program. Data must be formatted like this:              *
    *                                                                            *
    *  Dependent Variable, Independent Variable 1, Indendent Variable 2,...      *
    *                   4,                      5,                    8,...      *
    *                   7,                     12,                    5,...      *
    *                   .                       .                     .          *
    *                   .                       .                     .          *
    *                                                                            *
    * NB: Max number of variables is 10.                                         *
    *                                                                            *
    * Press enter to see a demonstration using sample data.                      *
    *                                                                            *
    ******************************************************************************
    
    
    Regression Equation:
    Weight = -127.82 +0.24 Age +3.09 Height
    
      Source |       SS       df       MS                  Number of obs =     237
    ---------+------------------------------               F(  2,   234) =  199.61
       Model |  56233.2543     2  28116.6271               Prob > F      =  0.0000
    Residual |  32960.7605   234  140.857951               R-squared     =  0.6305
    ---------+------------------------------               Adj R-squared =  0.6273
       Total |  89194.0148   236  377.940741               Root MSE      =  140.07
    
    ------------------------------------------------------------------------------
     Weight  |      Coef.   Std. Err.       t     P>|t|       [95% Conf. Interval]
    ---------+--------------------------------------------------------------------
     Age     |  0.2402749  0.05510303    4.3605   0.000       0.132273   0.3482769
     Height  |   3.090048   0.2573415    12.008   0.000       2.585659    3.594437
     Const   |  -127.8199      12.099   -10.565   0.000      -151.5339   -104.1059
    ------------------------------------------------------------------------------
