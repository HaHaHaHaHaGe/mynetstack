#include "test_main.h"

u8 ______write_buffer_data____get_unread_ptr_____(u32 loop)
{
	u32 i,j,k;
	u8* s1, *s2;
	u32 l,m = 0,n = 0;
	u8* str = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	u8 check;
#ifdef ____SHOW__DEBUG____
	printf("%d", strlen(str));
#endif // ____SHOW__DEBUG____
	initial_buffer(NULL_PTR, strlen(str));
	while (loop--)
	{
#ifdef ____SHOW__DEBUG____
		printf("�����ܴ�С��%d \r\n", strlen(str));
		printf("д�����ݣ�");
#endif // ____SHOW__DEBUG____
		l = rand() % (strlen(str) + 1);
#ifdef ____SHOW__DEBUG____
		for (k = 0; k < l; k++)
			printf("%c", str[k]);
		printf("\r\n");
#endif // ____SHOW__DEBUG____
		write_buffer_data(str, l);
		get_unread_ptr(&s1,&s2,&i,&j,NO);
#ifdef ____SHOW__DEBUG____
		printf("�������ݣ�");
#endif // ____SHOW__DEBUG____
		check = YES;
		for (k = 0; k < i; k++) {
#ifdef ____SHOW__DEBUG____
			printf("%c", s1[k]);
#endif // ____SHOW__DEBUG____
			if (str[k] != s1[k])
				check = NO;
		}
		for (k = 0; k < j; k++) {
#ifdef ____SHOW__DEBUG____
			printf("%c", s2[k]);
#endif // ____SHOW__DEBUG____
			if (str[i+k] != s2[k])
				check = NO;
		}
		if (check == NO)
			m++;
		n++;
#ifdef ____SHOW__DEBUG____
		printf("\r\n");
		printf("��д��ͬ���ִ�����%d",m);
		printf("�����ܴ�����%d", n);
		system("cls");
#endif // ____SHOW__DEBUG____
	}
	if (m == 0)
		return YES;
	return NO;
}