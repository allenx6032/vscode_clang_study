#ifndef DIM_DIMENSION3D_HPP
#define DIM_DIMENSION3D_HPP

#include "dimension3d/libraries.hpp"
#include "dimension3d/Mesh.hpp"
#include "dimension3d/Light.hpp"
#include "dimension3d/AmbientLight.hpp"
#include "dimension3d/DirectionalLight.hpp"
#include "dimension3d/PointLight.hpp"
#include "dimension3d/Material.hpp"
#include "dimension3d/Object.hpp"
#include "dimension3d/Shader.hpp"
#include "dimension3d/Texture.hpp"
#include "dimension3d/Vector2.hpp"
#include "dimension3d/Vector3.hpp"
#include "dimension3d/Vector4.hpp"
#include "dimension3d/Vector2int.hpp"
#include "dimension3d/Vector3int.hpp"
#include "dimension3d/Vector4int.hpp"
#include "dimension3d/vectors.hpp"
#include "dimension3d/VertexBuffer.hpp"
#include "dimension3d/Window.hpp"
#include "dimension3d/Camera.hpp"
#include "dimension3d/utils.hpp"
#include "dimension3d/FrameBuffer.hpp"
#include "dimension3d/Scene.hpp"
#include "dimension3d/Color.hpp"
#include "dimension3d/Controller.hpp"
#include "dimension3d/OrbitController.hpp"
#include "dimension3d/FlyController.hpp"
#include "dimension3d/DragController.hpp"
#include "dimension3d/Camera2D.hpp"
#include "dimension3d/OrthographicCamera.hpp"
#include "dimension3d/PerspectiveCamera.hpp"

namespace dim
{
	/**
	 * @brief Initialize the OpenGL library.
	 */
	void init_opengl();

	/**
	 * @brief Initialize the ImGui library.
	 */
	void init_imgui();

	/**
	 * @brief Initialize the Dimension3D library.
	 */
	void init();

	/**
	 * @brief Shut down the Dimension3D library.
	 */
	void shut_down();
}

#endif
