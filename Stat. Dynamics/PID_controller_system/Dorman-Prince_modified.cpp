#include "Dorman-Prince_modified.h"

CDormanPrince_modified::CDormanPrince_modified()
{
	correlation_interval = 0;
}

CDormanPrince_modified::CDormanPrince_modified(const TYPE correlation_interval)
{
	Step = correlation_interval; // ��������� ��� ������ ������ ��������� ����������
	this->correlation_interval = correlation_interval;
}

void CDormanPrince_modified::set_correlation_interval(const TYPE correlation_interval)
{
	Step = correlation_interval;
	this->correlation_interval = correlation_interval;
}

void CDormanPrince_modified::StepCorrection()
{
	CDormanPrince::StepCorrection();

	TYPE
		currentInterval, nextInterval_of_t;

	// �������� �������� �������� ��������� ����������
	modf(t / correlation_interval, &currentInterval);
		
	/* 
		�������� �������� ���������, � ������� �� ��������, ���� ��������
		� �������� ������� �������������� ���������� ���.
	*/
	modf( (t + Step) / correlation_interval, &nextInterval_of_t );

	/* 
		���� �� � ���� ����� �������� � ��������� ��������� ����������,
		�� �������� ��� �� ������ ��������, ����� �� ��������� �� ������� 
		�������� ��������� ���������� */
	if (nextInterval_of_t != currentInterval)
		Step = nextInterval_of_t * correlation_interval - t;
}
