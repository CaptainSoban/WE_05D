//�������������㷨


//�����η�
//���룺��һ�������������ڶ�����������������
//������η�����
//�ر��壺0��0�η�����1��

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


//һ����������2����
//���룺��һ���������������������ڶ���������������������
//������η�����
//		��������Ϊ��ʱ���г���2���ݵ����㣩��

int MutipPowOfTDoub(int x,int pow)
{
	(pow>0)?(x<<pow):(x>>(-pow));
	return x;
}


//�����η�������
//���룺����ƽ������
//����������ĵ�����
//���ò���д����ѧ��Chris Lomont����FAST INVERSE SQUARE ROOT��
//�ο����ף�http://www.matrix67.com/data/InvSqrt.pdf��

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