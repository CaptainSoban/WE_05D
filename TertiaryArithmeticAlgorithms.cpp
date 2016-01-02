//三级代数运算算法


//基本次方
//输入：第一参数：底数，第二参数：整数幂数；
//输出：次方数。
//特别定义：0的0次方等于1；

float Power(float base,int pow)
{
	if(pow>0)
	{
		for(int count=2;count<=pow;count++)
		{
			base=base*base;
		}
		return base;
	}
	else
	{
		if(pow==0)
		{
			return 1.0f;
		}
		else
		{
			pow=-pow;
			for(int count=2;count<=pow;count++)
			{
				base=base*base;
			}
			return 1.0f/base;
		}
	}
}


//一个整数乘以2的幂
//输入：第一参数：乘数（整数），第二参数：幂数（整数）；
//输出：次方数。
//		（当幂数为负时进行除以2的幂的运算）。

int MutipPowOfTDoub(int x,int pow)
{
	(pow>0)?(x<<pow):(x>>(-pow));
	return x;
}


//开二次方并求倒数
//输入：被开平方数；
//输出：底数的倒数；
//引用并改写自数学家Chris Lomont论文FAST INVERSE SQUARE ROOT；
//参考文献：http://www.matrix67.com/data/InvSqrt.pdf。

float InvSqrt(float x)
{
	float xhalf=0.5f*x;
	int i=*(int*)&x;		// get bits for floating VALUE
	i=0x5f375a86-(i>>1);	// gives initial guess y0
	x=*(float*)&i;			// convert bits BACK to float
	x=x*(1.5f-xhalf*x*x);	// Newton step, repeating increases accuracy
	x=x*(1.5f-xhalf*x*x);
	return x;
}

//