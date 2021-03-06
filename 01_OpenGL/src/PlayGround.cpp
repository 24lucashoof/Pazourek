#include "PlayGround.h"
#include "Enemy.h"

#include <fstream>

void PlayGround::OnAttach()
{
	EventHandler::camera = camera;
	//EventHandler::mouseRay = worldRay;

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos,
		double mouseYPos)
		-> void {EventHandler::cursor_pos_callback(window, mouseXPos, mouseYPos); });
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
		int action, int mods)
		-> void {EventHandler::key_callback(window, key, scancode, action, mods); });

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button,
		int action, int mode)
		-> void {EventHandler::mouse_button_callback(window, button, action, mode); });

	lightPositions[0] = glm::vec3(5, 5, 8);
	lightPositions[1] = glm::vec3(5, 5, -10);

	Light l0;
	l0.color = glm::vec3(1.0f);
	l0.position = glm::vec3(3.5f, 12, 0);
	l0.type = LightType::Point;
	l0.lightDir = glm::vec3(0.0f, 0.0f, -1.0f);
	l0.cutoff = 12.0f;
	lights[0] = l0;

	Light l1;
	l1.color = glm::vec3(0.5f);
	l1.position = glm::vec3(6, -20, 10.5f);
	l1.type = LightType::Point;
	l1.lightDir = glm::vec3(0.0f, 0.0f, 1.0f);
	l1.cutoff = 12.0f;
	lights[1] = l1;
	//in future ure gonna just pass the "ojb. folder" -> that folder WILL have to include
	//texture files in correct form (AO.png, .. )
	
	//model_teren = new Model("C:\\Users\\Ondra-PC\\Desktop\\space_origin.obj", 1);
	model_teren = new Model("C:\\Users\\Ondra-PC\\Desktop\\space_origin2.obj", 1);
	//model_teren = new Model("C:\\Users\\Ondra-PC\\Desktop\\zkouska.obj", 1);
	
	std::ofstream out;
	out.open("C:\\Users\\Ondra-PC\\Desktop\\liber_tmp.txt");
	bool first = true;
	for (Mesh m : model_teren->meshes)
	{
		// save into the file
		{
			std::string vb_data = "";
			std::string ib_data = "";

			glm::vec3 color = glm::vec3(0.8f, 0.0f, 0.0f);
			for (auto v : m.vertices)
			{
				vb_data += std::to_string(v.position.x);
				vb_data += "f, ";
				vb_data += std::to_string(v.position.y);
				vb_data += "f, ";
				vb_data += std::to_string(v.position.z);
				vb_data += "f, ";
				vb_data += std::to_string(v.normal.x);
				vb_data += "f, ";
				vb_data += std::to_string(v.normal.y);
				vb_data += "f, ";
				vb_data += std::to_string(v.normal.z);
				vb_data += "f, ";
				vb_data += std::to_string(v.texCoord.x);
				vb_data += "f, ";
				vb_data += std::to_string(v.texCoord.y);
				vb_data += "f, ";
			}
			for (auto i : m.indices)
			{
				ib_data += std::to_string(i);
				ib_data += ", ";
			}

			
			out << vb_data;
			out << "*";
			out << ib_data;
			out << "~"; // represents new mesh

			first = false;

		}
		
	}
	out.close();
	
	//model = new Model("C:/dev/Pazourek/01_OpenGL/src/res/models/backpack/backpack.obj", 0);
	//model_zidle = new Model("src\\res\\models\\zidle\\zidle__.obj", 1);
	//model_stul = new Model("src\\res\\models\\stul\\stul__.obj", 1);
	//model_kniha = new Model("src\\res\\models\\kniha\\kniha__.obj", 1);
	//model_vaza = new Model("src\\res\\models\\vaza\\vaza__.obj", 1);
	//model_podlaha = new Model("src\\res\\models\\podlaha\\podlaha__.obj", 1);
	//model_sipka = new Model("src\\res\\models\\sipka\\sipka.obj", 1);

	// init map here..
	map->Init();

	// test

	for (int i = 0; i < 5; i++)
	{
		if (Random::Float() > 0.5f)
		{
			glm::vec3 p1 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p2 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p3 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p4 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::mat4x3 bezier = {
				p1.x, p1.y, p1.z,
				p2.x, p2.y, p2.z,
				p3.x, p3.y, p3.z,
				p4.x, p4.y, p4.z
			};
			Object* o = new Enemy(bezier);
			OM->Add(*o);
		}
		else
		{
			glm::vec3 p1 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p2 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p3 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p4 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::mat4x3 bezier = {
				p1.x, p1.y, p1.z,
				p2.x, p2.y, p2.z,
				p3.x, p3.y, p3.z,
				p4.x, p4.y, p4.z
			};
			Object* o = new Ally(bezier);
			OM->Add(*o);
		}
	}
	EventHandler::camera = camera;
	EventHandler::object_manager = OM;

	loader->init();
	
	//model_obj_txt = new Model();
	
	std::string line;
	std::ifstream file("C:\\Users\\Ondra-PC\\Desktop\\liber_tmp.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
			obj_txt += line;
		file.close();
	}



	model_obj_txt = new Model();
	{
		std::vector<std::string> _vertices;
		std::vector<std::string> _indices;

		std::string word = "";

		bool after_ast = false;
		for (char c : obj_txt)
		{
			// new mesh
			if (c == '~')
			{
				std::vector<Vertex> vertices;
				std::vector<unsigned int> indices;

				for (int i = 0; i < _vertices.size() / 8; i++)
				{
					Vertex v{};
					v.position.x = std::stof(_vertices[(i * 8) + 0]);
					v.position.y = std::stof(_vertices[(i * 8) + 1]);
					v.position.z = std::stof(_vertices[(i * 8) + 2]);

					v.normal.x = std::stof(_vertices[(i * 8) + 3]);
					v.normal.y = std::stof(_vertices[(i * 8) + 4]);
					v.normal.z = std::stof(_vertices[(i * 8) + 5]);

					v.texCoord.x = std::stof(_vertices[(i * 8) + 6]);
					v.texCoord.y = std::stof(_vertices[(i * 8) + 7]);

					vertices.push_back(v);
				}

				for (std::string ind : _indices)
				{
					unsigned int number = (unsigned int)std::strtoul(ind.c_str(), NULL, 0);
					indices.push_back(number);
				}

				Mesh m(vertices, indices);
				model_obj_txt->meshes.push_back(m);

				vertices.clear();
				indices.clear();
				_vertices.clear();
				_indices.clear();
				after_ast = 0;
			}



			if (c == '*')
				after_ast = 1;

			if (c == ',' )
			{
				if (after_ast)
					_indices.push_back(word);
				else
					_vertices.push_back(word);

				word = "";
			}
			else if (c != '~')
				word += c;
		}
	}
	
}

void PlayGround::OnDetach()
{
    delete camera;
    delete renderer;
    delete alonso;
    delete tex;
    delete skyBox;
    // delete diffuse;
    // delete specular;
    // delete normal;
    // delete ao;
    // delete roughness;
    //delete anim;
    delete grass;
    //delete animation;
    //delete model;
}

void PlayGround::OnUpdate()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->MoveForward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->MoveLeft();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->MoveBackward();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->MoveRight();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->MoveUp();
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->MoveDown();



	//animation->OnUpdate();
	//rotation += 1;

	t += 0.002f * direction;
	if (t > 1)
		direction = -1;
	if (t < 0)
		direction = 1;


	glm::vec4 matOne = glm::vec4(t * t * t, t * t, t, 1);

	glm::mat4 matTwo = {
		-1,  3, -3, 1,
		 3, -6,  3, 0,
		-3,  3,  0, 0,
		 1,  0,  0, 0
	};

	glm::mat4x3 matThree = {
		0, 5, 2,
		0, 5, 12,
		10, 5, 12,
		10, 5, 2
	};

	glm::vec3 final = (matThree * matTwo) * matOne;


	//lights[0].position = final;

	r += 1;
	OM->GetObjects()[0]->Rotate(r, { 1, 0, 0 });


	// unparse
	


}

void PlayGround::OnRender()
{
	renderer->Clear();
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 0, GL_REPLACE);

	

    renderer->DrawCube(*skyBox, camera->GetPosition(), { 1, 1, 1 }, 0, 0, 0, 1);
	//renderer->DrawMap(*map, { 0, 0, 0 }, lights, drawNormals);
	renderer->DrawLight(lights[0]);
	renderer->DrawLight(lights[1]);
	
	
	//renderer->DrawModel(*diffuse, *specular, *normal, *ao, *roughness, { 5, 8, -5 }, 0, lights, ambientStrength, shininess, *model);
	//renderer->DrawModel(*zidle_diffuse, *blank, *blank, *blank, *blank, { 0, 0, 0 }, 0, lights, ambientStrength, shininess, *model_zidle);
	//renderer->DrawModel(*stul_diffuse, *blank, *stul_normal, *blank, *blank, { 0, 0, 0 }, 0, lights, ambientStrength, shininess, *model_stul);
	//renderer->DrawModel(*kniha_diffuse, *blank, *kniha_normal, *blank, *blank, { 0, 0, 0 }, 0, lights, ambientStrength, shininess, *model_kniha);
	//renderer->DrawModel(*teren_diffuse, *blank, *blank, *blank, *blank, { 0, 0, 0 }, 0, lights, ambientStrength, shininess, *model_teren);
	//renderer->DrawModel(*vaza_diffuse, *blank, *blank, *blank, *blank, { 0, 0, 0 }, 0, lights, ambientStrength, shininess, *model_vaza);
	//renderer->DrawModel(*podlaha_diffuse, *blank, *blank, *blank, *blank, { 0, 0, 0 }, 0, lights, ambientStrength, shininess, *model_podlaha);
	//
	//renderer->DrawModel(*blank, *blank, *blank, *blank, *blank, { 5, 3, -5 }, 0, lights, ambientStrength, shininess, *model_sipka);
	
	//for (Model* m : loader->models)
	//	renderer->DrawModel(*blank, *blank, *blank, *blank, *blank, {0, 0, 0}, 0.0f, lights, ambientStrength, shininess, *m);

	renderer->DrawModel(*blank, *blank, *blank, *blank, *blank, {}, 0.0f, lights, ambientStrength, shininess, *model_obj_txt);


	renderer->DrawLine({ EventHandler::mouseRay->originPoint }, { EventHandler::mouseRay->destPoint });

	renderer->DrawFont(*font, "NENI MUJ MODEL", glm::vec3(2, 11, -5), glm::vec3(0.0f));


	//for (Object* o : OM->GetObjects())
	//{
	//	glStencilFunc(GL_ALWAYS, o->GetID(), GL_REPLACE);
	//	o->Move(0.01f);
	//	renderer->DrawObject(*o);
	//}
	//
    //// rendering font
    //char test_char = 'C';
    //renderer->DrawChar(*font, test_char, glm::vec3(0, 5, 0), glm::vec3(1.0f));
	//
    //std::string test_text = "TOHLE JE TEST_123?!%.";
    //renderer->DrawFont(*font, test_text, glm::vec3(0, 8, 0), glm::vec3(0.0f));


}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::SliderFloat("LightX", &lights[0].position.x, -20.0f, 20.0f);
	ImGui::SliderFloat("LightY", &lights[0].position.y, -20.0f, 20.0f);
	ImGui::SliderFloat("LightZ", &lights[0].position.z, -20.0f, 20.0f);
	ImGui::Separator();
	ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
	ImGui::ColorEdit3("lightColor", glm::value_ptr(lights[0].color));
	ImGui::SliderInt("shininess", &shininess, 32, 256);
	ImGui::SliderFloat("SpecularStrength", &SpecularStrength, 0.0f, 1.0f);
	ImGui::Separator();
	ImGui::Checkbox("Show normals", &drawNormals);
	if (ImGui::Button("Recalc map"))
	{
		map->Recalc();
	}
	ImGui::End();


}
