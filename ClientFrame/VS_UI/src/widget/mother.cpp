#include "client_PCH.h"
#include "mother.h"

//-----------------------------------------------------------------------------
// Proportion
//
// (target <= target_max)
// base�� ǥ���Ϸ��� �����̴�.
//
// ex) target = 50, target_max = 100, base = 51
//		 => 100�� ���� 50�� base�� 51���� ���ΰ��� ���Ѵ�.
//
// �̰��� ������� ���ϴ� �İ� ����. ������ 100�� �ƴ� ��� �̰��� ����ϸ� �ȴ�.
//
// ��ȯ�Ǵ� �� x�� (0 <= x <= base)�̴�.
//-----------------------------------------------------------------------------
double Proportion(double target, double target_max, double base)
{
	if (target > target_max)
		target = target_max;
	if (target_max == 0)
		return 0;

	return (((double)target/target_max)*base);
}

//-----------------------------------------------------------------------------
// Percentage
//
// ������� ���Ѵ�.
//-----------------------------------------------------------------------------
double Percentage(double target, double target_max)
{
	return Proportion(target, target_max, PERCENTAGE);
}