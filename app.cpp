#include "app.hpp"
#include <raylib.h>
#include <iostream>
#include <algorithm>

namespace Game{
	App::App(){
		InitWindow(800,640, "Train!!!");
		SetTargetFPS(60);
		
		//loading the shader first!!
		App::shader = LoadShader("shader.vs", 0);

		//load da model!1
		App::model = LoadModel("models/untitled.obj");
		Texture2D texture = LoadTexture("models/road_tex.png");

		App::model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
		App::model_size = GetMeshBoundingBox(App::model.meshes[0]);
		App::model.materials[0].shader = App::shader;


		App::chunk_size = 20;
		for(size_t i = 0; i< App::chunk_size; i++) chunk_position.push_back((Vector3){0.0,0.0,i*model_size.max.z*2});

		//set the camera
		App::camera.fovy = 50;
		App::camera.position = (Vector3){0.0,0.8,0.0};
		App::camera.up = (Vector3){0.0,1.0,0.0};
		App::camera.target = (Vector3){0.0,0.0, 4.0};
		App::camera.projection = CAMERA_PERSPECTIVE;
	}
	App::~App(){
		CloseWindow();
		UnloadModel(App::model);
		UnloadShader(App::shader);
	}

	void App::run(){
		Model m = App::model;
		float model_length = App::model_size.max.z*2;
		float chunk_count = App::chunk_size;
		int camera_location = GetShaderLocation(App::shader, "camera");
		int offset_location = GetShaderLocation(App::shader, "offset");
		
		float t=0;
		while(!WindowShouldClose()){
			
			std::for_each(std::begin(App::chunk_position), std::end(App::chunk_position),
				[model_length, chunk_count](Vector3& value){
					value.z -= 0.3;
					if(value.z<-model_length){
						value.z += model_length*chunk_count;
					}
				});

			//drawing everything!!!
			BeginDrawing();
				float camera[3] = {App::camera.position.x, App::camera.position.y, App::camera.position.z};
				SetShaderValue(App::shader, camera_location, camera, SHADER_UNIFORM_VEC3);
				SetShaderValue(App::shader, offset_location, &t, SHADER_UNIFORM_FLOAT);
				

				ClearBackground(RAYWHITE);
				BeginMode3D(App::camera);
					std::for_each(std::begin(chunk_position), std::end(chunk_position),
						[m](Vector3& value){
							DrawModel(m, value, 1.0, WHITE);
						});

				EndMode3D();
				DrawFPS(50,50);
			EndDrawing();
			t+=0.3;
		}
	}
}
