#pragma once
#include "SimpleMath.h"
#include "Common.h"

// �����ƕ��ʂ̌���������s��
inline bool IntersectRayPlane(
	const DirectX::SimpleMath::Ray& ray,
	const DirectX::SimpleMath::Plane& plane,
	DirectX::SimpleMath::Vector3* const intersection
)
{
	/*
	�������ʂƌ�_�̎��@t = normal * (position - origin) / (normal * direction)
	��_ origin + direction * t

	����: P = P0 + tV
	����: P �EN + d = 0
	(P0 + tV)�EN + d = 0
	t = -(P0�EN + d) / (V�EN)
	P = P0 + tV
	*/

	// ���ʖ@���x�N�g���ƌ����̓��ς��v�Z����
	float d = plane.Normal().Dot(ray.direction);
	// �����ƕ��ʂ����s�̏ꍇ�͌�_�͑��݂��Ȃ�
	if (d == 0.0f)
		return false;
	// ���ʂ̖@���x�N�g���ƌ����̌��_�̊Ԃ̓��ς��v�Z����
	float t = (plane.D() - plane.Normal().Dot(ray.position)) / d;
	// �����_���v�Z����
	*intersection = ray.position + ray.direction * t;
	// �����ƕ��ʂ��������Ă���
	return true;
}

// �_���~�̓����ɂ��邩�ǂ����𔻒肷��
inline bool InsideCircle(const int& radius, const DirectX::SimpleMath::Vector2& center, const DirectX::SimpleMath::Vector2& point)
{
	// 2�_�Ԃ̋������v�Z����
	float distance = (center.x - point.x) * (center.x - point.x) + (center.y - point.y) * (center.y - point.y);
	// �����Ɣ��a�̓��Ɣ�r����
	if (distance <= radius * radius)
		return true;
	else
		return false;
}

// �~�Ɛ����̌���������s��
inline bool IntersectCircleLine(
	const DirectX::SimpleMath::Vector2& center,					// ���S�_
	const float& radius,																// ���a
	const DirectX::SimpleMath::Vector2& start,						// �����̊J�n
	const DirectX::SimpleMath::Vector2& end							// �����̏I��
)
{
	// �����̊J�n�n�_����~�̒��S�ւ̃x�N�g��
	DirectX::SimpleMath::Vector2 startToCenter = center - start;
	// �����̏I���n�_����~�̒��S�ւ̃x�N�g��
	DirectX::SimpleMath::Vector2 endToCenter = center - end;
	// �����̊J�n�ʒu����I���ʒu�ւ̃x�N�g��
	DirectX::SimpleMath::Vector2 startToEnd = end - start;
	// �����̊J�n�ʒu����I���ʒu�ւ̃x�N�g���𐳋K������
	DirectX::SimpleMath::Vector2 normalStartToEnd = Normalize(startToEnd);
	// �~�̒��S��������܂ł̋������v�Z����
	float length = Cross2D(startToCenter, normalStartToEnd);
	// �~�̒��S��������܂ł̋��������a��菬�����ꍇ
	if (abs(length) <= radius)
	{
		if (Dot2D(startToCenter, startToEnd) * Dot2D(endToCenter, startToEnd) <= 0)
			return true;
		else if (radius > startToCenter.Length() || radius > endToCenter.Length())
			return true;
	}
	return false;
}
