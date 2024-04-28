## True Enum
## about
True enum is a header only library that aims to make enumerating easy to do! But do not think it is stuck in it's ways, almost every aspect of it can be customized to your needs, an example of which is limiting it's memory usage! 

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
