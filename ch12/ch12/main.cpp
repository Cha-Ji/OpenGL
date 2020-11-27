#define GL_SILENCE_DEPRECATION
#include <GLUT/GLUT.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

GLfloat camx = -12, camy = 2, camz = -7;
GLfloat cam2x = 5, cam2y = 0, cam2z = 0;
GLfloat cam_upx = 0, cam_upy = 1, cam_upz = 0;

//두개의 점을 가지는 클래스
class CPoint2f{ public: vector<float> d{0, 0};};
class CPoint3f{public: vector<float> d{0, 0, 0};};
class CPoint3i{public: vector<int> d{0, 0, 0};};
//face 좌표? 면을 이루는 쌍
class CFace{public:vector<CPoint3i> v_pairs;};
class CObj{
public:
    string name;
    vector<CPoint3f> v;
    vector<CPoint2f> vt;
    vector<CPoint3f> vn;
    vector<CFace> f;
};
class CModel{
public:
    vector<CObj>objs;
    
    vector<float> my_strtok_f(char* str, char* delimeter){
        vector<float> v;
        
        char* tok = strtok(str, delimeter); //MAC 에서는 함수가 다르다.
        
        while(tok != NULL){
            v.push_back(atof(tok));  //문자열을 실수형 숫자로 바꿔주는 함수
            tok = strtok(NULL, delimeter);
        }
        
        return v;
    }
    
    vector<string> my_strtok_s(char* str, char* delimeter){
        vector<string> v;
        
        char* tok = strtok(str, delimeter); //MAC 에서는 함수가 다르다.
        
        while(tok != NULL){
            v.push_back(tok);  //문자열을 실수형 숫자로 바꿔주는 함수
            tok = strtok(NULL, delimeter);
        }
        
        return v;
    }
    
    vector<int> my_strtok_i(char* str, char* delimeter){
        vector<int> v;
        
        char* tok = strtok(str, delimeter); //MAC 에서는 함수가 다르다.
        
        while(tok != NULL){
            v.push_back(atoi(tok));  //문자열을 실수형 숫자로 바꿔주는 함수
            tok = strtok(NULL, delimeter);
        }
        
        return v;
    }
    
    void loadObj(ifstream& fin){
        string line;
        CObj obj_tmp;
        int cnt = 0;       //obj count
        
        //이전 obj까지의 누적 벡터 수
        int cnt_prev_vertex = 0;
        int cnt_prev_texture = 0;
        int cnt_prev_normal = 0;
        
        while(getline(fin, line)){
            unsigned long len = line.length();
            vector<float> vf;
            vector<string> s;
            vector<int> vi;
            CPoint3f p3;
            CPoint2f p2;
            CPoint3i p3i;
            
            if(line[0] == 'o' && line[1] == ' '){
                obj_tmp.name = line.substr(2, len - 2);
                objs.push_back(obj_tmp);
                if(cnt > 0){
                    cnt_prev_vertex += objs[cnt - 1].v.size();
                    cnt_prev_texture += objs[cnt - 1].vt.size();
                    cnt_prev_normal += objs[cnt - 1].vn.size();
                }
                cnt += 1;
            }
            
            if(line[0] == 'v' && line[1] == ' '){
                vf = my_strtok_f((char*)line.substr(2, len - 2).c_str(), (char*)" ");
                p3.d = { vf[0], vf[1], vf[2]};
                objs[cnt-1].v.push_back(p3);
            }
            
            else if(line[0] == 'v' && line[1] == 't'){
                vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
                p3.d = { vf[0], vf[1]};
                objs[cnt-1].vt.push_back(p2);
            }
            
            else if(line[0] == 'v' && line[1] == 'n'){
                vf = my_strtok_f((char*)line.substr(3, len - 3).c_str(), (char*)" ");
                p3.d = { vf[0], vf[1], vf[2]};
                objs[cnt-1].vn.push_back(p3);
            }
            
            else if(line[0] == 'f' && line[1] == ' '){
                s = my_strtok_s((char*)line.substr(2, len - 2).c_str(), (char*)" ");
                unsigned long nVertexes = s.size();
                CFace face_tmp;
                for( int i = 0; i< nVertexes; i++){
                    vi = my_strtok_i((char*)s[i].c_str(), (char*)"/");
                    p3i.d = {
                        vi[0] - cnt_prev_vertex,
                        vi[1] - cnt_prev_texture,
                        vi[2] - cnt_prev_normal
                    };
                    face_tmp.v_pairs.push_back(p3i);
                }
                objs[cnt-1].f.push_back(face_tmp);
            }
        }
        
        
    }
};
CModel m;

//=================기본 함수========================
void mydisplay();
void reshape(int width, int height);
void init_light();
//===============================================
int main(int argc, char** argv){
    string filePath = "/Users/cha-ji/Downloads/blender/hallway.obj";
    ifstream fin(filePath);
    
    m.loadObj(fin);
    
    fin.close();
    
    //gl 관련
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(300, 200);
    
    glutCreateWindow("obj load");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);   //R, G, B, A(투명도)
    
    glutDisplayFunc(mydisplay);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    return 0;
}


void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camx, camy, camz,
              cam2x, cam2y, cam2z,
              cam_upx, cam_upy, cam_upz);
    
    GLfloat x, y, z, nx, ny, nz;
    int v_id, vt_id, vn_id;
    
    //여러 오브젝트를 나타내 보자
    for(int o = 0; o< m.objs.size(); o++){
        unsigned long nFaces = m.objs[o].f.size();
        
        //obj가 하나일 때 가정
        for(int k = 0; k < nFaces; k++){
            unsigned long nPoints = m.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for(int i = 0; i< nPoints; i++){
                v_id = m.objs[o].f[k].v_pairs[i].d[0];
                vt_id = m.objs[o].f[k].v_pairs[i].d[1];
                vn_id = m.objs[o].f[k].v_pairs[i].d[2];
                x = m.objs[o].v[v_id - 1].d[0];
                y = m.objs[o].v[v_id - 1].d[1];
                z = m.objs[o].v[v_id - 1].d[2];
                
                //법선 벡터
                nx = m.objs[o].vn[vn_id - 1].d[0];
                ny = m.objs[o].vn[vn_id - 1].d[1];
                nz = m.objs[o].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x,y,z);
            }
            glEnd();
        }
        
        
    }
    glFlush();
}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    GLfloat ratio = (float)width/height;
    gluPerspective(40, ratio, 0.1, 1000);
    
}

void init_light(){
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

