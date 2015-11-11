# VendingMachine


##Takes 2 input files to determine it's start state:

###1: The change state (i.e. what coins the machine contains to provide change with)

In the form of 8 integers to give the counts for the 8 coins the machine takes in ascending value order:

1p 2p 5p 10p 20p 50p £1 £2


###2: The product state

Each line is a separate product currently offered by the machine in the form:

[Name] [price in pence] [quantity in the machine]

With the first being a contigious string without spaces and the latter two integers


###The main function takes both of these files as command line arguments in the above order in the form:

###[exe] [change state] [product state]

###The state files will get overwritten when the application is quit and so reflect any changes made to stock or change reserves while the machine was running
