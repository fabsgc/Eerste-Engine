#include "../Math/Vector4.h"
#include "../Math/Math.h"

namespace ee
{
	const Vector4 Vector4::ZERO(0, 0, 0, 0);

	bool Vector4::isNaN() const
	{
		return Math::isNaN(x) || Math::isNaN(y) || Math::isNaN(z) || Math::isNaN(w);
	}
}