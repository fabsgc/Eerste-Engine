#include "../Math/Vector4.h"
#include "../Math/Math.h"

namespace ee
{
	const Vector4 Vector4::ZERO(0, 0, 0, 0);

	bool Vector4::IsNaN() const
	{
		return Math::IsNaN(x) || Math::IsNaN(y) || Math::IsNaN(z) || Math::IsNaN(w);
	}
}