#pragma once

#include "Types.h"
#include "LinearAlgebra.h"


class Model
{
protected:
	Eigen::VectorXd m_start_values;

	size_t
		s_size; // длина вектора m_start_values

	TYPE 
		m_interval, // должен ли быть интервал между знач. задан тут?
		t0, 
		t1;

	Eigen::MatrixXd m_result;	// двунаправленный список
	size_t result_size;
	size_t result_line_length;

	// Остановка интегрирования при малых изменениях приращения координаты
	TYPE stop_condition;
	unsigned short stop_count, stop_count_max;
	bool stop_flag;

public:
	Model();
	Model(const Model& other);
	virtual ~Model();

	Model& operator=(const Model& right);

public:
	virtual void Init(int argc = 0, void** argv = nullptr);	// инициализация модели

	virtual Eigen::VectorXd GetRight(const Eigen::VectorXd &X, TYPE t) const = 0;

	virtual bool StopCalculation(
		TYPE t, TYPE step, const Eigen::VectorXd &prev_step, const Eigen::VectorXd &cur_step);

public:
	virtual void AddResult(const Eigen::VectorXd &X, TYPE t);
	Eigen::MatrixXd GetResult() const;
	Eigen::VectorXd GetLastResult() const;
	void ClearResult();

	Eigen::VectorXd GetStart() const;
	void SetStart(const Eigen::VectorXd &arg);

	TYPE GetInterval() const;
	void SetInterval(TYPE arg);

	TYPE Get_t0() const;
	void Set_t0(TYPE arg);

	TYPE Get_t1() const;
	void Set_t1(TYPE arg);	

protected:
	virtual void SetStartValuesSize(size_t new_size, size_t result_line_expansion_by = 1);
	virtual void SetStartValuesSize(const Eigen::VectorXd& new_start_values, size_t result_line_expansion_by = 1);
	void SetResultSize();
};