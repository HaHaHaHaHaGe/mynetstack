#include "test_main.h"

int main(void)
{
	u8 s = ______write_buffer_data____get_unread_ptr_____(100000);
	if (s == YES)
		printf("YES\r\n");
	while (1);
}