
## True Enum
## About
True enum is a fast header only library that aims to make enumerating easy to do! But do not think it is stuck in it's ways, almost every aspect of it can be customized to your needs, an example of which is limiting it's memory usage!

This library was made for my personal game engine project, Techstorm. It all started when I had an idea "What if Enums could be made during runtime?", and then I decided to try to add that to Techstorm and that is how I ended up making this.

## Key Features

 - Type Enumeration
	 - Provide an alias for variables
		 - Setting and Getting
- Reading/Writing to a file
- Allocating memory to True-Enum
	- Memory capping 
- Modularity
	- Certain features can be turned on and off via a simple preproccessing define.

## Getting started
Since this is header-only, you dont need to do a thing at all. Here are two ways you can start using True-Enum. 

    #include "TrueEnum.h"
    
    void YourFunction() {
	    ...
	    
	    TrueEnum::TrueEnumStr enumerator;
	    ...
    }

Yup, thats all! a single line of code is all you need to get started. If you want to use something other than a string as the alias, use the example below,

    #include "TrueEnum.h"
    
    void YourFunction() {
	    ...
	    
	    TrueEnum::ITrueEnum<int> enumerator;
	    ...
    }

Replace the int with what ever type you need!

## How to help
If you feel we are missing something, please feel free to go and make a change! The only way this gets better is if you help, so be my guest!
