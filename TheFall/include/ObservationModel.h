#pragma once

#include "Types.h"
#include "LinearAlgebra.h"

#include <random>
#include <vector>

typedef std::normal_distribution<TYPE> MyNormalDistribution;
typedef std::vector<MyNormalDistribution::param_type> DistributionParamVec;



// ������ ��������� ������� ������� �������� ���������
// ������������ ������ ����������
struct ObservationSession
{
	// ������ ������� ������� ���������
	size_t start_moment;

	// ������ ������� ����� ���������� ���������
	size_t end_moment;

	ObservationSession();
	size_t GetDuration() const;
};

typedef std::vector<ObservationSession> ObservationSessionsVector;



class ObservationModel
{
public:
	ObservationModel();
	virtual ~ObservationModel();

	void Init(size_t observations_size);

	virtual Eigen::VectorXd MakeObservation(const Eigen::VectorXd & X, TYPE t) const = 0;
	virtual void SaveObservation(const Eigen::VectorXd & X, TYPE t);

	Eigen::MatrixXd GetObservations(bool with_time = true) const;
	size_t GetNumOfObservations() const;

	ObservationSessionsVector GetObservationSessionsVector() const;

	void SetDoRandom(bool should_we_do_random);

	DistributionParamVec GetRandomErrorParams() const;
	MyNormalDistribution::param_type GetRandomErrorParams(size_t param_num) const;
	void SetRandomErrorParams(const DistributionParamVec & new_random_error_params);

protected:
	Eigen::MatrixXd observations;
	size_t num_of_observations;

	size_t observation_vec_size;

	ObservationSession current_session;

	// ������ ������� ������� - ����� ���������� � ��� ����������������� � 
	// �������� �������
	ObservationSessionsVector observation_sessions_vec;
	bool is_session_initialized;

	void InitObservationSession(size_t start_moment);
	void CloseObservationSession(size_t end_moment);

protected:
	bool do_random;

	// ������, � ������� �������� ��������� ��������� ������
	DistributionParamVec random_error_params;

	std::default_random_engine generator;
	MyNormalDistribution distribution;
};