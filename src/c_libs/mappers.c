#include "mappers.h"

int firstPageToLoad(unsigned int mapperId, unsigned int prgPageAmount){
	int page;
	switch(mapperId){
		case 0:
			if(prgPageAmount > 2){
				page = -1;
			}
			else{
				page = 0;
			}
			break;
		default:
			page = -1;
			break;
	}
	return page;
}

int secondPageToLoad(unsigned int mapperId, unsigned int prgPageAmount){
	int page;
	switch(mapperId){
		case 0:
			if(prgPageAmount > 2){
				page = -1;
			}
			else if(prgPageAmount == 2){
				page = 1;
			}
			else{
				page = 0;
			}
			break;
		default:
			page = -1;
			break;
	}
	return page;
}
