#pragma once

namespace js::enums
{
	enum class eLayerType
	{
		None,
		Monster,
		Player,
		End = 16,
	};

	enum class eComponentType
	{
		None,
		Transform,
		Camera,
		Mesh,
		Collider,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};
}