#include "mappers.h"

int firstPageToLoad(unsigned int mapperId, unsigned int prgPageAmount){
	int page;
	switch(mapperId){
		case 0:
			if(prgPageAmount > 2){
				page = -9;
			}
			else{
				page = 0;
			}
			break;
		default:
			page = -5;
			break;
	}
	return page;
}

int secondPageToLoad(unsigned int mapperId, unsigned int prgPageAmount){
	int page;
	switch(mapperId){
		case 0:
			if(prgPageAmount > 2){
				page = -9;
			}
			else if(prgPageAmount == 2){
				page = 1;
			}
			else{
				page = 0;
			}
			break;
		default:
			page = -5;
			break;
	}
	return page;
}

int chrPageToLoad(unsigned int mapperId, unsigned int chrPageAmount){
    int page;
    switch(mapperId){
        case 0:
            if(chrPageAmount > 1){
                page = -9;
            }
            else{
                page = 0;
            }
            break;
        default:
            page = -5;
            break;
    }
    return page;
}
