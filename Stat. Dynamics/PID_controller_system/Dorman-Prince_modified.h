#pragma once

#include "Integrator.h"

class CDormanPrince_modified : public CDormanPrince
{
private:
	// �������� ����������, � ������� �� ����� ���������� �������� ���������� ���������� ��������
	TYPE correlation_interval;

	/* 
		����������� ��������� ����, ����� ��� ������������� �������� 
		������������ ������ ����
	*/
	void StepCorrection() override;
public:
	CDormanPrince_modified();
	CDormanPrince_modified(const TYPE correlation_interval);

	void set_correlation_interval(const TYPE correlation_interval);
};