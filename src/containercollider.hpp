#ifndef CONTAINER_COLLIDER_H
#define CONTAINER_COLLIDER_H

#include "math.hpp"

namespace Phys {

	class ContainerCollider {
		public:
			ContainerCollider(double width, double height, double depth) noexcept :
				size_(width, height, depth) {}

			Math::Vec4d const size() const noexcept { return size_; }
			Math::Vec4d& size() noexcept { return size_; }

		private:
			Math::Vec4d size_;
	};

}

#endif
