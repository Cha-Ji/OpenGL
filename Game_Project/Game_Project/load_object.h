#ifndef load_object_h
#define load_object_h

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
            int len = line.length();
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
                int nVertexes = s.size();
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
CModel floor2, floor1, hand, hand_light, key;

//한 함수에 정의하면 실행속도가 느려진다.
void displayKey(){
    GLfloat x, y, z, nx, ny, nz;
    int v_id, vt_id, vn_id, o, k, i;
    unsigned long nFaces, nPoints;

    //여러 오브젝트를 나타내 보자
    for(o = 0; o< key.objs.size(); o++){
        nFaces = key.objs[o].f.size();

        //obj가 하나일 때 가정
        for(k = 0; k < nFaces; k++){
            nPoints = key.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for(i = 0; i< nPoints; i++){
                v_id = key.objs[o].f[k].v_pairs[i].d[0];
                vt_id = key.objs[o].f[k].v_pairs[i].d[1];
                vn_id = key.objs[o].f[k].v_pairs[i].d[2];
                
                x = key.objs[o].v[v_id - 1].d[0];
                y = key.objs[o].v[v_id - 1].d[1];
                z = key.objs[o].v[v_id - 1].d[2];

                //법선 벡터
                nx = key.objs[o].vn[vn_id - 1].d[0];
                ny = key.objs[o].vn[vn_id - 1].d[1];
                nz = key.objs[o].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x,y,z);
            }
            glEnd();
        }
    }
}
void displayHand(){
    GLfloat x, y, z, nx, ny, nz;
    int v_id, vt_id, vn_id, o, k, i;
    unsigned long nFaces, nPoints;
    
    //여러 오브젝트를 나타내 보자
    for(o = 0; o< hand.objs.size(); o++){
        nFaces = hand.objs[o].f.size();

        //obj가 하나일 때 가정
        for(k = 0; k < nFaces; k++){
            nPoints = hand.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for(i = 0; i< nPoints; i++){
                v_id = hand.objs[o].f[k].v_pairs[i].d[0];
                vt_id = hand.objs[o].f[k].v_pairs[i].d[1];
                vn_id = hand.objs[o].f[k].v_pairs[i].d[2];
                x = hand.objs[o].v[v_id - 1].d[0];
                y = hand.objs[o].v[v_id - 1].d[1];
                z = hand.objs[o].v[v_id - 1].d[2];

                //법선 벡터
                nx = hand.objs[o].vn[vn_id - 1].d[0];
                ny = hand.objs[o].vn[vn_id - 1].d[1];
                nz = hand.objs[o].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x,y,z);
            }
            glEnd();
        }
    }
}
void displayHandLight(){
    GLfloat x, y, z, nx, ny, nz;
    int v_id, vt_id, vn_id, o, k, i;
    unsigned long nFaces, nPoints;
    
    //여러 오브젝트를 나타내 보자
    for(o = 0; o< hand_light.objs.size(); o++){
        nFaces = hand_light.objs[o].f.size();

        //obj가 하나일 때 가정
        for(k = 0; k < nFaces; k++){
            nPoints = hand_light.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for(i = 0; i< nPoints; i++){
                v_id = hand_light.objs[o].f[k].v_pairs[i].d[0];
                vt_id = hand_light.objs[o].f[k].v_pairs[i].d[1];
                vn_id = hand_light.objs[o].f[k].v_pairs[i].d[2];
                x = hand_light.objs[o].v[v_id - 1].d[0];
                y = hand_light.objs[o].v[v_id - 1].d[1];
                z = hand_light.objs[o].v[v_id - 1].d[2];

                //법선 벡터
                nx = hand_light.objs[o].vn[vn_id - 1].d[0];
                ny = hand_light.objs[o].vn[vn_id - 1].d[1];
                nz = hand_light.objs[o].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x,y,z);
            }
            glEnd();
        }
    }
}
void display2Floor(){
    GLfloat x, y, z, nx, ny, nz;
    int v_id, vt_id, vn_id, o, k, i;
    unsigned long nFaces, nPoints;
    //여러 오브젝트를 나타내 보자
    for(o = 0; o< floor2.objs.size(); o++){
        nFaces = floor2.objs[o].f.size();

        //obj가 하나일 때 가정
        for(k = 0; k < nFaces; k++){
            nPoints = floor2.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for(i = 0; i< nPoints; i++){
                v_id = floor2.objs[o].f[k].v_pairs[i].d[0];
                vt_id = floor2.objs[o].f[k].v_pairs[i].d[1];
                vn_id = floor2.objs[o].f[k].v_pairs[i].d[2];
                
                x = floor2.objs[o].v[v_id - 1].d[0];
                y = floor2.objs[o].v[v_id - 1].d[1];
                z = floor2.objs[o].v[v_id - 1].d[2];

                //법선 벡터
                nx = floor2.objs[o].vn[vn_id - 1].d[0];
                ny = floor2.objs[o].vn[vn_id - 1].d[1];
                nz = floor2.objs[o].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x,y,z);
            }
            glEnd();
        }
    }
}
void display1Floor(){
    GLfloat x, y, z, nx, ny, nz;
    int v_id, vt_id, vn_id, o, k, i;
    unsigned long nFaces, nPoints;
    
    //여러 오브젝트를 나타내 보자
    for(o = 0; o< floor1.objs.size(); o++){
        nFaces = floor1.objs[o].f.size();

        //obj가 하나일 때 가정
        for(k = 0; k < nFaces; k++){
            nPoints = floor1.objs[o].f[k].v_pairs.size();
            glBegin(GL_POLYGON);
            for(i = 0; i< nPoints; i++){
                v_id = floor1.objs[o].f[k].v_pairs[i].d[0];
                vt_id = floor1.objs[o].f[k].v_pairs[i].d[1];
                vn_id = floor1.objs[o].f[k].v_pairs[i].d[2];
                x = floor1.objs[o].v[v_id - 1].d[0];
                y = floor1.objs[o].v[v_id - 1].d[1];
                z = floor1.objs[o].v[v_id - 1].d[2];

                //법선 벡터
                nx = floor1.objs[o].vn[vn_id - 1].d[0];
                ny = floor1.objs[o].vn[vn_id - 1].d[1];
                nz = floor1.objs[o].vn[vn_id - 1].d[2];
                glNormal3f(nx, ny, nz);
                glVertex3f(x,y,z);
            }
            glEnd();
        }
    }
}


#endif /* load_object_h */
