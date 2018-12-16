#include "../inc/sdata_trans.h"


void trans_8to7b(u8 *src, u8 *dst, u32 dst_len)
{
	u32 len = dst_len;
	u32 ss1;
	while (len--)
	{
		ss1 = (8 * len + 1) - (8 * len + 1) / 8 - 1;
		if (ss1 % 8)
		{
			dst[len] = (src[ss1 / 8] << (ss1 % 8 - 1)) & 0x7f;
			dst[len] |= src[(ss1 + 8 - ss1 % 8) / 8] >> (9 - ss1 % 8);
		}
		else
		{
			dst[len] = src[ss1 / 8] >> 1;
		}
	}
}

void trans_7to8b(u8 *src, u8 *dst, u32 src_len)
{
	u32 len = src_len;
	u32 ss1;
	for (len = 0; len < src_len; len++)
	{
		ss1 = (8 * len + 1) - (8 * len + 1) / 8 - 1;
		if (ss1 % 8)
		{
			dst[ss1 / 8] |= src[len] >> (ss1 % 8 - 1);
			dst[(ss1 + 8 - ss1 % 8) / 8] = src[len] << (9 - ss1 % 8);
		}
		else
		{
			dst[ss1 / 8] = src[len] << 1;
		}
	}
}

void trans_8to7b_64bytes(u8 *src, u8 *dst, u32 dst_len)
{
	u32 len = dst_len;
	u32 ss1;
	while (len)
	{
		len -= 8;
		ss1 = len - (((len << 3) + 1) >> 6);

		dst[len] = src[ss1] >> 1;

		dst[len + 1] = ((src[ss1] << 6) & 0x7f) | src[ss1 + 1] >> 2;

		dst[len + 2] = ((src[ss1 + 1] << 5) & 0x7f) | src[ss1 + 2] >> 3;

		dst[len + 3] = ((src[ss1 + 2] << 4) & 0x7f) | src[ss1 + 3] >> 4;

		dst[len + 4] = ((src[ss1 + 3] << 3) & 0x7f) | src[ss1 + 4] >> 5;

		dst[len + 5] = ((src[ss1 + 4] << 2) & 0x7f) | src[ss1 + 5] >> 6;

		dst[len + 6] = ((src[ss1 + 5] << 1) & 0x7f) | src[ss1 + 6] >> 7;

		dst[len + 7] = src[ss1 + 6] & 0x7f;


	}
}

void trans_7to8b_64bytes(u8 *src, u8 *dst, u32 src_len)
{
	u32 len = src_len;
	u32 ss1;
	while (len)
	{
		len -= 8;
		ss1 = len - (((len << 3) + 1) >> 6);

		dst[ss1] = src[len] << 1 | src[len + 1] >> 6;

		dst[ss1 + 1] = src[len + 1] << 2 | src[len + 2] >> 5;

		dst[ss1 + 2] = src[len + 2] << 3 | src[len + 3] >> 4;

		dst[ss1 + 3] = src[len + 3] << 4 | src[len + 4] >> 3;

		dst[ss1 + 4] = src[len + 4] << 5 | src[len + 5] >> 2;

		dst[ss1 + 5] = src[len + 5] << 6 | src[len + 6] >> 1;

		dst[ss1 + 6] = src[len + 6] << 7 | src[len + 7];
	}
}


void trans_8to7b_64bytes_fast(u8 *src, u8 *dst, u32 src_len)
{
	u32 len = src_len;
	u32 len_2 = src_len;
	u32 ss1,ss2;
	while (len)
	{
		len -= 7;
		
		ss1 = *(u32*)&src[len] & 0x80808080;
		ss2 = *(u32*)&src[len+4] & 0x00808080;

		dst[len_2] = (ss1 >> 1) |

					(ss1 >> 10) |

					(ss1 >> 19) |

					(ss1 >> 28) |

					(ss2 >> 5) |

					(ss2 >> 14) |

					(ss2 >> 23);

		len_2++;

		*(u64*)&dst[len] |= *(u64*)&src[len] & 0x007f7f7f7f7f7f7f;

	}
}

void trans_7to8b_64bytes_fast(u8 *src, u8 *dst, u32 src_len)
{
	u32 len = (src_len * 7) / 8;
	u32 len_2 = len;
	u32 ss1;
	while (len)
	{
		len -= 7;

		*(u32*)&dst[len] |= *(u32*)&src[len] | (((src[len_2] << 1) | (src[len_2] << 10) | (src[len_2] << 19) | (src[len_2] << 28)) & 0x80808080);
		*(u32*)&dst[len + 4] |= *(u32*)&src[len + 4] | (((src[len_2] << 5) | (src[len_2] << 14) | (src[len_2] << 23)) & 0x00808080);

		len_2++;
	}
}




