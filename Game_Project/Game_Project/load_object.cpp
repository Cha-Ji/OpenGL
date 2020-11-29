#include "Header.h"
void display_objs(){
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
}

