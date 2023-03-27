#pragma once
#include <raylib.h>
#include <vector>

namespace Game{
	
	class App{
		private:
			Model model;
			Camera camera;
			BoundingBox model_size;
			std::size_t chunk_size;
			std::vector<Vector3> chunk_position;
			Shader shader;	

		public:
			App();
			~App();
			void run();	
	};
}
