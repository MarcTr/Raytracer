#ifndef CAMERA_H
#define CAMERA_H

#include "../Maths/Vector3.h"

namespace Model
{
	using namespace Maths;

	class Camera
	{
		private:
			Vector3 position;
			Vector3 centerOfInterest;
			Vector3 userUpVector;
			Vector3 viewVector;
			Vector3 sideVector;
			Vector3 upVector;

		public:
			Camera();
			Camera(Vector3 _position, Vector3 _centerOfInterest, Vector3 _userUpVector);

			void initialize();
			Vector3 GetPosition();
			Vector3 GetCenterOfInterest();
			Vector3 GetUserUpVector();
			Vector3 GetViewVector();
			Vector3 GetSideVector();
			Vector3 GetUpVector();
	};
}
#endif

