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
CModel hallway, door;

void loadObject(string obj_name, CModel m){
    string filePath = "/Users/cha-ji/Downloads/blender/"+obj_name + ".obj";
    ifstream fin(filePath);
    hallway.loadObj(fin);
    fin.close();
}
#endif /* load_object_h */
