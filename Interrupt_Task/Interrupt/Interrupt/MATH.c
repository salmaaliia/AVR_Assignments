#include "STD_TYPES.h"
#include "MATH.h"

u32 MATH_u32Power(u32 Copy_u32Num, u32 Copy_u32Exponent)
{
	u32 Local_u32Itr;
	u32 Local_u32Res=1;
	for(Local_u32Itr = 0; Local_u32Itr<Copy_u32Exponent; Local_u32Itr++)
	{
		Local_u32Res*=Copy_u32Num;
	}
	return Local_u32Res;
}