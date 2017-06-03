#include "VitaGUI.hpp"



VitaGUI::VitaGUI(){
	vita2d_init();
	vita2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	pgf = vita2d_load_default_pgf();
	std::string bgPath = "app0:assets/images/Vitacord-Background-8BIT.png";
	backgroundImage = vita2d_load_PNG_file(bgPath.c_str());
	loginFormImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-LoginForm-8BIT.png");
	loadingImage = vita2d_load_PNG_file("app0:assets/images/Vitacord-Loading-8BIT.png");
	
	inputbox emailI;
	emailI.x = 420;
	emailI.y = 105;
	emailI.w = 400;
	emailI.h = 55;
	loginInputs.push_back(emailI);
	
	inputbox passwordI;
	passwordI.x = 420;
	passwordI.y = 205;
	passwordI.w = 400;
	passwordI.h = 55;
	loginInputs.push_back(passwordI);
	
	inputbox loginI;
	loginI.x = 420;
	loginI.y = 370;
	loginI.w = 400;
	loginI.h = 70;
	loginInputs.push_back(loginI);
	
	loginTexts.push_back(" ");
	loginTexts.push_back(" ");
	
}
VitaGUI::~VitaGUI(){
	vita2d_fini();
	vita2d_free_texture(backgroundImage);
	vita2d_free_texture(loginFormImage);
	vita2d_free_texture(loadingImage);
	vita2d_free_pgf(pgf);
}
void VitaGUI::Draw(){
	vita2d_start_drawing();
	vita2d_clear_screen();

	
	if(state == 0){
		vita2d_draw_texture( backgroundImage , 0 , 0);
		vita2d_draw_texture( loginFormImage , 0 , 0 );
		vita2d_pgf_draw_text(pgf, 420, 154, RGBA8(255,255,255,255), 2.0f, loginTexts[0].c_str());
		vita2d_pgf_draw_text(pgf, 420, 250, RGBA8(255,255,255,255), 2.0f, loginTexts[1].c_str());
		
	}else if(state == 1){
		vita2d_draw_texture( backgroundImage , 0 , 0);
		vita2d_draw_texture_rotate(loadingImage, 0 , 0, loadingImageAngle);
		vita2d_pgf_draw_text(pgf, 300, 277, RGBA8(255,255,255,255), 2.0f, loadingString.c_str());
		loadingImageAngle ++;
	}else if(state == 2){
		
	}else if(state == 9){
		int i = 0;
		for( i = 0; i < rectangles.size() ; i++){
			vita2d_draw_rectangle(rectangles[i].x, rectangles[i].y, rectangles[i].w, rectangles[i].h, rectangles[i].color);
		}
	}

	
	vita2d_end_drawing();
	vita2d_swap_buffers();
}

int VitaGUI::click(int x , int y){
	if(state == 0){
		for(int i = 0 ; i < loginInputs.size() ; i++){
			if( x > loginInputs[i].x && x < loginInputs[i].x + loginInputs[i].w){
				if( y > loginInputs[i].y && y < loginInputs[i].y + loginInputs[i].h){
					return i;
				}
			}
		}
	}
	return -1;
}

void VitaGUI::AddRectangle(float nx , float ny , float nw , float nh , unsigned int ncolor){
	rectangle r;
	r.x = nx;
	r.y = ny;
	r.w = nw;
	r.h = nh;
	r.color = ncolor;
	rectangles.push_back(r);
}
void VitaGUI::RemoveRectangle(int index){
	
	if(index < rectangles.size()){
		rectangles.erase(rectangles.begin()+index);
	}
	
}

int VitaGUI::GetState(){
	return state;
}
void VitaGUI::SetState(int s){
	state = s;
}