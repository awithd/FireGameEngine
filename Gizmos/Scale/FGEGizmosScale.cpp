#include "FGEGizmosScale.h"
#include "Tools/FGEConsole.h"

FGEGizmosScale::FGEGizmosScale(OpenGLFunctions *f, FGESUBSelectedTransformationMode *mode)
{
    transformation_type = 0;
    translation_item = new FGEGizmosScaleItem(f);
    shader = new FGEGLSL();


    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_selection = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/ScaleShader/GizmosScaleSelection.vert", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/ScaleShader/GizmosScaleSelection.frag");

    shader->clearAttribLocation();
    shader->appendAttribLocation(0, "vertex");
    translation_item->shaderProgram_grid = shader->initShader(f, "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/ScaleShader/Scale_grid.vert", "/home/corolo/Qt/FireGameEngine/Shader/Gizmos/ScaleShader/Scale_grid.frag");


    linepoint_1 = glm::vec3(0.0, 0.0, 0.0);
    linepoint_2 = glm::vec3(0.0, 0.0, 0.0);

    //point_1 = glm::vec3(0.0, 0.0, 0.0);
    //point_2 = glm::vec3(0.0, 0.0, 0.0);
    //point_3 = glm::vec3(0.0, 0.0, 0.0);


    current_transformation_mode = 0;

}


void FGEGizmosScale::clearDrag()
{
    x_move_selected = false;
    y_move_selected = false;
    z_move_selected = false;
    xy_move_selected = false;
    yz_move_selected = false;
    zx_move_selected = false;
    drag_selected = false;
}


glm::mat4 FGEGizmosScale::getRotationMatrix2V(glm::vec3 pos, glm::vec3 eye, glm::vec3 eyeu){
    glm::vec3 v_e = glm::normalize(eye-pos);
    /*if(v_e[0]<0) v_e[0]=-v_e[0];
    if(v_e[1]<0) v_e[1]=-v_e[1];
    if(v_e[2]<0) v_e[2]=-v_e[2];*/
    glm::vec3 v_y = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));

    float cos2a = glm::dot(v_e, v_y);
    qDebug() << "****** glm::dot: "<<cos2a;
    cos2a = glm::acos(cos2a);
    glm::vec3 f = glm::cross(v_e, v_y);
    //glm::vec3 u_axe = glm::cross(v_e, v_y);
    //glm::vec3 r_axe = glm::cross(v_e, v_y);

    cos2a = (cos2a*180.0)/3.14159265358979323846;
    qDebug() << "---------------------: "<<cos2a;
    float rx = 90-cos2a;
    qDebug() << "---------90-------: "<<rx;
    qDebug() << "ffffffffff : ("<<f[0]<<" , "<<f[1]<<" , "<<f[2]<<")";

    glm::mat4 f_m = glm::toMat4(glm::angleAxis( glm::radians(rx), glm::normalize(f)));


    /*glm::vec4 t =f_m*glm::vec4(v_y[0], v_y[1], v_y[2], 1.0);
    if(t[1]<0.0){
        float l = 180+90-cos2a;
        qDebug() << "---------l-------: "<<l;
        f_m = glm::toMat4(glm::angleAxis( glm::radians(l), glm::normalize(f)));
    }*/

    /*qDebug() << "F cos2a ggf: "<<cos2a;
    if(r_axe[2]<0) {
        cos2a = 180+(180-cos2a);
        r_axe[0] = -r_axe[0];
        r_axe[1] = -r_axe[1];
        r_axe[2] = -r_axe[2];
    }
    if(r_axe[0]<0 && r_axe[2]>=0) {
        cos2a = 90+cos2a;
        r_axe[0] = -r_axe[0];
        r_axe[1] = -r_axe[1];
        r_axe[2] = -r_axe[2];
    }*/
    //qDebug() << "////// cos2a: "<<cos2a;

    //qDebug() << "f : ("<<f[0]<<" , "<<f[1]<<" , "<<f[2]<<")";
    //qDebug() << "--------cos2a----------: "<<cos2a;

    //
    //qDebug() << "-----------------------: "<<rx;


    //qDebug() << "F r_axe : ("<<r_axe[0]<<" , "<<r_axe[1]<<" , "<<r_axe[2]<<")";

    //glm::mat4 f_m = glm::toMat4(glm::angleAxis( glm::radians(rx), glm::normalize(f)));

    ////////////////////////////
/*
    glm::vec4 k = f_m*glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    //glm::vec4 k = f_m*glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f));

    cos2a = glm::dot(v_e, glm::vec3(k[0], k[1], k[2]));
    qDebug() << "cos2a : "<<cos2a;
    cos2a = glm::acos(cos2a);
    f = glm::cross(v_e, glm::vec3(k[0], k[1], k[2]));
    cos2a = (cos2a*180.0)/3.14159265358979323846;
    qDebug() << "jjjjj cos2a : "<<cos2a;
    //if(cos2a<0) cos2a += (-cos2a);
    if(u_axe[2]<0) cos2a = 360-cos2a;
qDebug() << "F r_axe : ("<<u_axe[0]<<" , "<<u_axe[1]<<" , "<<u_axe[2]<<")";

    //r_axe = glm::cross(v_e, v_z);

    qDebug() << "F cos2a : "<<cos2a;
    glm::vec4 d = f_m*glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

    //qDebug() << "F r_axe : ("<<r_axe[0]<<" , "<<r_axe[1]<<" , "<<r_axe[2]<<")";
*/
    return /*glm::toMat4(glm::angleAxis( glm::radians(cos2a), glm::vec3(d[0], d[1], d[2])))*/f_m;

}




void FGEGizmosScale::draw2DGrid(OpenGLFunctions *f, glm::mat4 &model, glm::mat4 &projection){
    f->glLineWidth(1.0);
    f->glUseProgram(translation_item->shaderProgram_grid);
        //shader->setMat4(translation_item->shaderProgram_grid, "view", m_scale*view);
        shader->setMat4(f, translation_item->shaderProgram_grid, "projection", projection);
        shader->setMat4(f, translation_item->shaderProgram_grid, "model", model);
        shader->setVec3f(f, translation_item->shaderProgram_grid, "color", 0.6, 0.6, 0.6);

        f->glBindVertexArray(translation_item->vao_plane10);
        f->glDrawArrays(GL_LINES, 0, translation_item->mpcv10);
        f->glBindVertexArray(0);
    f->glUseProgram(0);
    f->glLineWidth(1.0);
}
/*
bool FGEGizmosTranslation::drawAxesOn2DGrid(glm::vec3 ){
    if(xy_move_selected){
        t_p1 = glm::vec4(0.0, 0.0, 10.5, 1.0);
        t_p2 = glm::vec4(0.0, 0.0, -10.5, 1.0);

        translation_item->xyz_axes[0] = __t[0];
        translation_item->xyz_axes[1] = __t[1];
        translation_item->xyz_axes[2] = 1000.0;
        translation_item->xyz_axes[3] = __t[0];
        translation_item->xyz_axes[4] = __t[1];
        translation_item->xyz_axes[5] = -1000.0;
        color = glm::vec3(0.0, 0.0, 1.0);

        if(sel_transf_mode->isLocal()){
            t_p1 = (model)*t_p1;
            t_p2 = (model)*t_p2;
            current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
            current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
            current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        }else if(sel_transf_mode->isGlobal()){
            t_p1 = (model/rotation_to_parent)*t_p1;
            t_p2 = (model/rotation_to_parent)*t_p2;
            current_eq_2d_line.world_point_a = glm::vec3(t_p1[0], t_p1[1], t_p1[2]);
            current_eq_2d_line.world_point_b = glm::vec3(t_p2[0], t_p2[1], t_p2[2]);
            current_eq_2d_line.screen_point_a = glm::project(glm::vec3(t_p1[0], t_p1[1], t_p1[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            current_eq_2d_line.screen_point_b = glm::project(glm::vec3(t_p2[0], t_p2[1], t_p2[2]), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        }

        glm::mat4 _model = model/rotation_to_parent;
        if(sel_transf_mode->isLocal()){
            _model = model ;
        }

        glBindVertexArray(translation_item->vao_xyza);
        glBindBuffer(GL_ARRAY_BUFFER, translation_item->vbo_xyza);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*6, &translation_item->xyz_axes[0]);

        glUseProgram(translation_item->shaderProgram_line);
        glLineWidth(3.0);
            shader->setMat4(translation_item->shaderProgram_line, "view", m_scale*view);
            shader->setMat4(translation_item->shaderProgram_line, "projection", projection);
            shader->setMat4(translation_item->shaderProgram_line, "model", _model);
            shader->setVec3f(translation_item->shaderProgram_line, "color", color[0], color[1], color[2]);

            glDrawArrays(GL_LINES, 0, 6);
            glBindVertexArray(0);
        glLineWidth(1.0);

    }
}
*/

bool FGEGizmosScale::isDragScale(){
    if(x_move_selected || y_move_selected || z_move_selected || xy_move_selected || yz_move_selected || zx_move_selected) return true;
    else return false;
}
//void FGEGizmosTranslation::updateAxesTranslation(FGETransform *transform, glm::vec4 &translate, float scaleFactor, bool is_perspective, glm::mat4 &view, glm::mat4 &projection, glm::mat4 &model, int WIDTH, int HEIGHT, int pos_x, int pos_y){
void FGEGizmosScale::updateAxesScale(FGETransformation *transform, glm::mat4 &view, glm::mat4 &projection, float scaleFactor, bool is_perspective, glm::vec2 &cursor, int WIDTH, int HEIGHT)
{

    glm::vec4 p = transform->getGlobalTransformation()*glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 _p = glm::vec3(p);
    glm::mat4 m_scale;

    if(!is_perspective){
        m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
    }else{
        m_scale= glm::mat4(1.0f);


    }
    glm::mat4 scale_view = m_scale*view;


    if(drag_selected || x_move_selected || y_move_selected || z_move_selected){

        glm::vec2 b, o, a, s;
        glm::vec3 pp = glm::project(_p, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        o[0] = pp[0]+(cursor[0] - w_drag_cursor[0]);
        o[1] = pp[1]+(cursor[1] - w_drag_cursor[1]);

        if(sel_transf_mode->isLocal() || sel_transf_mode->isGlobal()){

            a = glm::vec2(current_eq_2d_line.screen_point_a[0], current_eq_2d_line.screen_point_a[1]);
            b = glm::vec2(current_eq_2d_line.screen_point_b[0], current_eq_2d_line.screen_point_b[1]);

            //float _s = (b[1]-a[1])/(b[0]-a[0]);
            //float _b = a[1] - a[0]*_s;

            glm::vec4 hr = intersection2DRayRect(a, b, WIDTH, HEIGHT);

            if(hr!=glm::vec4(0.0,0.0,0.0,0.0)){
                s = glm::closestPointOnLine(o, glm::vec2(hr[0], hr[1]), glm::vec2(hr[2], hr[3]));
            }else{
                s = glm::closestPointOnLine(o, glm::vec2(hr[0], hr[1]), glm::vec2(hr[2], hr[3]));
            }

            glm::vec3 t_a, t_b, t_c, ws, r;

            t_a = getVertical2DLine(glm::vec3(s[0], s[1], 0.0), glm::vec3(current_eq_2d_line.screen_point_b[0], current_eq_2d_line.screen_point_b[1], 0.0));
            t_a = glm::unProject(t_a, scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
            ws = glm::unProject(glm::vec3(s[0], s[1], 0.0), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            r = t_a-ws;
            r = glm::vec3(r[0]*100, r[1]*100, r[2]*100);

            t_a = glm::vec3(ws[0]+r[0], ws[1]+r[1], ws[2]+r[2]);
            t_b = glm::vec3(ws[0]-r[0], ws[1]-r[1], ws[2]-r[2]);
            t_c = glm::unProject(glm::vec3(s[0], s[1], 1.0), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            glm::vec3 dir = current_eq_2d_line.world_point_b-current_eq_2d_line.world_point_a;
            float dist;
            glm::vec2 bary_pos;
            if(glm::intersectRayTriangle(current_eq_2d_line.world_point_a, dir, t_a,t_b,t_c, bary_pos, dist)){
                _p = current_eq_2d_line.world_point_a + dist*dir;
                 point_2 = _p;
                qDebug() << "****/////intersectRayTriangle////*******";

            }else{
                qDebug() << "****/////NO////*******";
            }
        }else if(sel_transf_mode->isScreen()){
            if(x_move_selected){
                _p = glm::unProject(glm::vec3(o[0], p[1], p[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            }else if(y_move_selected){
                _p = glm::unProject(glm::vec3(p[0], o[1], p[2]), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

            }

        }


    }/*else if(xy_move_selected /*|| yz_move_selected || zx_move_selected*//*){
     /*   glm::mat4 m_scale;
        if(!is_perspective){
            m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
        }else{
            m_scale= glm::mat4(1.0f);
        }

        glm::vec4 __p = model*glm::vec4(0.0, 0.0, 0.0, 1.0);
        _p = glm::vec3(__p[0], __p[1], __p[2]);

        glm::vec2 b, o, a, s;
        glm::vec3 p = glm::project(_p, m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        o[0] = p[0]+(cursor[0] - w_drag_cursor[0]);
        o[1] = p[1]+(cursor[1] - w_drag_cursor[1]);
        qDebug() << "--------------------s : ("<<o[0]<<", "<<o[1]<<")";


        glm::vec3 pos_s = glm::project(_p, m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 __pos_w = glm::unProject(glm::vec3(pos_s[0], pos_s[1], 0.5), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 __p1 = glm::unProject(glm::vec3(o[0], o[1], 0.0), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
        glm::vec3 __p2 = glm::unProject(glm::vec3(o[0], o[1], 0.2), m_scale*view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));


        glm::vec3 dir = glm::normalize(__p2-__p1);
        float dist;

        if(glm::intersectRayPlane(__p1, dir, _p, glm::normalize(glm::vec3(0.0, 0.0, 1.0)), dist)){
            glm::vec3 __yt = __p1 + dist*dir;
            _p = __yt;

        }

    }*/

    w_drag_cursor = glm::vec2(cursor[0], cursor[1]);

    p[0] = _p[0];
    p[1] = _p[1];
    p[2] = _p[2];
    p[3] = 1.0;
    qDebug() << "--------------------GGGG : ("<<_p[0]<<", "<<_p[1]<<", "<<_p[2]<<")";

    if(sel_transf_mode->isGlobal()){
        if(transform->getParent()!=NULL){
            p = transform->getParent()->getGlobalTransformation()/p;
            qDebug() << "--------------------translate : ("<<p[0]<<", "<<p[1]<<", "<<p[2]<<")";

/*
            glm::mat4 tr = glm::translate(glm::mat4(1.0f), glm::vec3(translate[0],translate[1],translate[2]));
            tr = tr/transform->getLocalMatrixRotation();
            translate = tr*glm::vec4(0.0,0.0,0.0,1.0);
*/

        }

    }else if(sel_transf_mode->isLocal()){
        if(transform->getParent()!=NULL){
            glm::vec4 tr = transform->getParent()->getGlobalTransformation()/p;
            p[0] = tr[0];
            p[1] = tr[1];
            p[2] = tr[2];
        }
    }else if(sel_transf_mode->isScreen()){
        if(transform->getParent()!=NULL){
            glm::vec4 tr = transform->getParent()->getGlobalTransformation()/p;
            p[0] = tr[0];
            p[1] = tr[1];
            p[2] = tr[2];
        }
    }

    glm::vec3 l = transform->getLocalVectorScale();

    glm::vec3 _c = glm::vec3(cursor[0], cursor[1], current_eq_2d_line.screen_c[2]);

    glm::vec3 __tw = glm::unProject(_c, view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

    //qDebug()<<"  length@@@@@ : "<<length;
    //qDebug()<<"  current_eq_2d_line.flot@@@@@ : "<<current_eq_2d_line.flot;


    if(x_move_selected){
        if(current_eq_2d_line.flot==0) {
            current_eq_2d_line.flot=l[0];
            current_eq_2d_line.clot = glm::length(__tw-current_eq_2d_line.world_c);
            glm::vec4 xvec = transform->getGlobalMatrixRotation()/glm::vec4(l[0],0,0,1);

            transform->setLocalXVectorScale(xvec[0]);

        }else{
            float length = current_eq_2d_line.flot*glm::length(__tw-current_eq_2d_line.world_c)/current_eq_2d_line.clot;

            //glm::vec4 xvec = transform->getGlobalMatrixRotation()/glm::vec4(length,0,0,1);

            transform->setLocalXVectorScale(length);
        }
    }else if(y_move_selected){
        if(current_eq_2d_line.flot==0) {
            current_eq_2d_line.flot=l[1];
            current_eq_2d_line.clot = glm::length(__tw-current_eq_2d_line.world_c);
            glm::vec4 xvec = transform->getGlobalMatrixRotation()/glm::vec4(0,l[1],0,1);

            //transform->setLocalVectorScale(xvec[0], xvec[1], xvec[2]);
            transform->setLocalYVectorScale(xvec[1]);
            qDebug()<<" ###### 0";
        }else{
            float length = current_eq_2d_line.flot*glm::length(__tw-current_eq_2d_line.world_c)/current_eq_2d_line.clot;
            transform->setLocalYVectorScale(length);
            qDebug()<<" ###### 1";
        }
    }else if(z_move_selected){
        if(current_eq_2d_line.flot==0) {
            current_eq_2d_line.flot=l[2];
            current_eq_2d_line.clot = glm::length(__tw-current_eq_2d_line.world_c);
            glm::vec4 xvec = transform->getGlobalMatrixRotation()/glm::vec4(0,0,l[2],1);

            //transform->setLocalVectorScale(xvec[0], xvec[1], xvec[2]);
            transform->setLocalZVectorScale(xvec[2]);
        }else{
            float length = current_eq_2d_line.flot*glm::length(__tw-current_eq_2d_line.world_c)/current_eq_2d_line.clot;
            transform->setLocalZVectorScale(length);
            qDebug()<<"  length@@@@@ : "<<length;
        }
    }


}
glm::vec4 FGEGizmosScale::intersection2DLineRect(float s, float b, int width, int height){

    bool fr = false;
    glm::vec4 r;
    float y, x;

    {
        x = 0.0;
        y = s*x+b;
        if(y>=0.0 && y<=height){
            if(!fr) {
                r[0] = 0.0;
                r[1] = y;
                fr = true;
                //qDebug() << "1 ";
            }else {
                r[2] = 0.0;
                r[3] = y;//qDebug() << "01 ";
                return r;
            }
        }
    }
    {
        y = 0.0;
        x = (y-b)/s;
        if(x>=0.0 && x<=width){
            if(!fr) {
                r[0] = x;
                r[1] = 0.0;
                fr = true;//qDebug() << "2 ";
            }else {
                r[2] = x;
                r[3] = 0.0;//qDebug() << "02 ";
                return r;
            }
        }
    }
    {
        x = width;
        y = s*x+b;
        if(y>=0.0 && y<=height){
            if(!fr) {
                r[0] = width;
                r[1] = y;//qDebug() << "3 ";
                fr = true;
            }else {
                r[2] = width;
                r[3] = y;//qDebug() << "03 ";
                return r;
            }
        }
    }
    {
        y = height;
        x = (y-b)/s;
        if(x>=0.0 && x<=width){
            if(!fr) {
                r[0] = x;
                r[1] = height;
                fr = true;//qDebug() << "4 ";
            }else {
                r[2] = x;
                r[3] = height;//qDebug() << "04 ";
                return r;
            }
        }
    }
//qDebug() << "5 ";
    return glm::vec4(0.0,0.0,0.0,0.0);
}


glm::vec3 FGEGizmosScale::getVertical2DLine(glm::vec3 p1, glm::vec3 p2){
    glm::vec3 a(0.0,0.0,-1.0);
    glm::vec3 b = p2-p1;
    glm::vec3 c = glm::cross(a, b);
    return p1+c;
}


glm::vec4 FGEGizmosScale::intersection2DRayRect(glm::vec2 p1, glm::vec2 p2, int width, int height){
    double dis = 0;
    QVector<glm::vec2> pl;
    glm::vec2 point;


    qDebug() << "--------------------______p1: ("<<p1[0]<<", "<<p1[1]<<")";
    qDebug() << "--------------------______p2: ("<<p2[0]<<", "<<p2[1]<<")";
    qDebug() << "--------------------______wh: ("<<width<<", "<<height<<")";
    {
        if(GetRayToLineSegmentIntersection(p1, NormalizeVector(p2), glm::vec2(0, 0), glm::vec2(0, 1), point)){
            pl.push_back(point);
        }else{
            if(GetRayToLineSegmentIntersection(p2, NormalizeVector(p1), glm::vec2(0, 0), glm::vec2(0, 1), point)){
                pl.push_back(point);
            }
        }
    }
    {
        if(GetRayToLineSegmentIntersection(p1, NormalizeVector(p2), glm::vec2(0, height), glm::vec2(0, 1), point)){
            pl.push_back(point);
        }else{
            if(GetRayToLineSegmentIntersection(p2, NormalizeVector(p1), glm::vec2(0, height), glm::vec2(0, 1), point)){
                pl.push_back(point);
            }
        }
    }
    {
        if(GetRayToLineSegmentIntersection(p1, NormalizeVector(p2), glm::vec2(0, 0), glm::vec2(1, 0), point)){
            pl.push_back(point);
        }else{
            if(GetRayToLineSegmentIntersection(p2, NormalizeVector(p1), glm::vec2(0, 0), glm::vec2(1, 0), point)){
                pl.push_back(point);
            }
        }
    }
    {
        if(GetRayToLineSegmentIntersection(p1, NormalizeVector(p2), glm::vec2(width, 0), glm::vec2(1, 0), point)){
            pl.push_back(point);
        }else{
            if(GetRayToLineSegmentIntersection(p2, NormalizeVector(p1), glm::vec2(width, 0), glm::vec2(1, 0), point)){
                pl.push_back(point);
            }
        }
    }
    qDebug() << "pl.size() : ("<<pl.size()<<")";

    if(pl.size()==1) qDebug() << "pl.size() : ("<<pl[0][0]<<", "<<pl[0][1]<<")";

    if(pl.size()==2){
        return glm::vec4(pl[0][0],pl[0][1],pl[1][0],pl[1][1]);
    }else{
        return glm::vec4(0, 0, width, height);
    }

}
// return the distance of ray origin to intersection point
bool FGEGizmosScale::GetRayToLineSegmentIntersection(glm::vec2 rayOrigin, glm::vec2 rayDirection, glm::vec2 point1, glm::vec2 point2, glm::vec2 point)
{
    glm::vec3 rayOrigin3 = glm::vec3(rayOrigin[0], rayOrigin[1], 0);
    glm::vec3 rayDirection3 = glm::vec3(rayDirection[0], rayDirection[1], 0);
    glm::vec3 plane_origin = glm::vec3(point1[0], point1[1], 0);
    glm::vec3 plane_normal = glm::vec3(point2[0], point2[1], 0);

    float dist;
    if(glm::intersectRayPlane(rayOrigin3, rayDirection3, plane_origin, glm::normalize(plane_normal), dist)){
        glm::vec3 __yt = rayOrigin3 + dist*rayDirection3;
        point = glm::vec2(__yt[0], __yt[1]);
        return true;
    }else{
        return false;
    }

    /*

    glm::vec2 v1 = rayOrigin - point1;
    glm::vec2 v2 = point2 - point1;
    glm::vec2 v3 = glm::vec2(-rayDirection[1], rayDirection[0]);

    float dot = glm::dot(v2, v3);
    if (abs(dot) < 0.000001)
        return -1.0f;

    glm::vec3 av2 = glm::vec3(v2[0], v2[1], 0);
    glm::vec3 av1 = glm::vec3(v1[0], v1[1], 0);
    float t1 = glm::length(glm::cross(av2, av1)) / dot;
    float t2 = glm::dot(v1, v3) / dot;

    if (t1 >= 0.0 && (t2 >= 0.0 && t2 <= 1.0))
        return t1;

    return -1.0f;*/
}

// use this to normalize rayDirection
glm::vec2 FGEGizmosScale::NormalizeVector(glm::vec2 pt)
{
    float length = sqrt(pt[0]*pt[0] + pt[1]*pt[1]);
    pt = pt / length;
    return pt;
}

// gets the intersection point
glm::vec2 FGEGizmosScale::GetRayIntersectionPoint(glm::vec2 origin, glm::vec2 vector, double distance)
{
    glm::vec2 pt;

    pt[0] = origin[0] + vector[0] * distance;
    pt[1] = origin[1] + vector[1] * distance;

    return pt;
}
