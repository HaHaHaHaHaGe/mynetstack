#include "test_main.h"


u8 ______classifier____separa__mix_____(void)
{
	unsigned char *str = "1234567890";
	packeg_data data = mix_packeg_data(NORMAL_DATA, strlen(str), str);
	packeg_base base = mix_packeg_base(DATA_PACKEG, sizeof(packeg_data), &data);



	//separa_packeg_base(,);
	//separa_packeg_data();

}