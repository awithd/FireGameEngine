#include "FGECamera.h"



/*FGECamera::FGECamera(){
    current_position = glm::vec3(0.0f, 0.0f,  0.0f);
    current_eye = glm::vec3(0.0f, 0.0f,  5.0f);
    current_target = glm::vec3(0.0f, 0.0f,  0.0f);
    current_up = glm::vec3(0.0f, 1.0f,  0.0f);
    alpha = 0.0;
    bita = 0.0;
    quat_arcball.angle = 0.0;//sqrt((1.0 + cos2a)*0.5);

    count = 0;

    last_pos_x=0;
    last_pos_y=0;
}
void FGECamera::init(FGEDataCameraView *view, FGEDataCameraProjection *projection){
    this->view = view;
    this->projection = projection;
}
double FGECamera::degrees_to_radians(double radius) {
    return (radius * PI)/180;
}
void FGECamera::update(){


}


void FGECamera::initRotationCameraAroundTarjet(int sx, int sy){
    qDebug() << "sphereCoords[0] " << sx;
    qDebug() << "sphereCoords[1] " << sy;
    quat_arcball.o_p = glm::vec3(0.0,0.0,80.0);
}

glm::vec3 FGECamera::sphereCoords(int sx, int sy)
{
    float r = 600.0, z;
    if((sx*sx+sy*sy) <= r*r){
        z = -sqrt(r*r-sx*sx-sy*sy);
    }else{
        z = 0;
    }
    quat_arcball.r = r*r;
    //qDebug() << "r " << quat_arcball.r;

    //qDebug() << "sphereCoords[0] " << sx;
    //qDebug() << "sphereCoords[1] " << sy;
    //qDebug() << "sphereCoords[2] " << z;

    return glm::vec3((float)sx, (float)sy, z);
}

glm::mat4 FGECamera::rotateCameraAroundTarjet(int sx, int sy, glm::vec4 view, glm::mat4 model, glm::mat4 projection){
    int xx =  last_pos_x-sx;
    int yy =  last_pos_y-sy;
    if(yy*yy >= xx*xx) {
        xx =0;

        glm::vec3 n_p = sphereCoords(0, yy);
        float cos2a = glm::dot(glm::normalize(glm::vec3(0.0,0.0,-300.0)), glm::normalize(n_p));
        cos2a = glm::acos(cos2a);
        quat_arcball.angle = ((cos2a*180.0)/3.14159265358979323846)*2;

        glm::vec3 f = glm::cross(glm::vec3(0.0,0.0, -300.0), n_p);


        glm::vec3 o = glm::unProject(glm::vec3(last_pos_x, last_pos_y, 0.0), model, projection, view);
        glm::vec3 d = glm::unProject(glm::vec3(last_pos_x+f[0], last_pos_y+f[1], f[2]), model, projection, view);

        quat_arcball.axis = d-o;
        if(quat_arcball.axis[0]==0 && quat_arcball.axis[1]==0 && quat_arcball.axis[2]==0) return glm::mat4(1.0);
        //qDebug() << "quat_arcball.axis[0] " << quat_arcball.axis[0];
        //qDebug() << "quat_arcball.axis[1] " << quat_arcball.axis[1];
        //qDebug() << "quat_arcball.axis[2] " << quat_arcball.axis[2];

        last_pos_x = sx;
        last_pos_y = sy;

        return glm::toMat4(glm::angleAxis( glm::radians(quat_arcball.angle), glm::normalize(glm::vec3(quat_arcball.axis[0], quat_arcball.axis[1], quat_arcball.axis[2]))));

    }else{
        yy =0;

        glm::vec3 n_p = sphereCoords(xx, 0);
        float cos2a = glm::dot(glm::normalize(glm::vec3(0.0,0.0,-300.0)), glm::normalize(n_p));
        cos2a = glm::acos(cos2a);
        quat_arcball.angle = ((cos2a*180.0)/3.14159265358979323846)*2;


        glm::vec3 f = glm::cross(glm::vec3(0.0,0.0, -300.0), n_p);

        glm::vec3 o = glm::unProject(glm::vec3(last_pos_x, last_pos_y, 0.0), model, projection, view);
        glm::vec3 d = glm::unProject(glm::vec3(last_pos_x+f[0], last_pos_y+f[1], f[2]), model, projection, view);

        quat_arcball.axis = d-o;
        quat_arcball.axis[0] = 0;
        quat_arcball.axis[2] = 0;
        if(quat_arcball.axis[1]>=0) quat_arcball.axis[1] = 1.0;
        else quat_arcball.axis[1] = -1.0;

        if(quat_arcball.axis[0]==0 && quat_arcball.axis[1]==0 && quat_arcball.axis[2]==0) return glm::mat4(1.0);
        //qDebug() << "quat_arcball.axis[0] " << quat_arcball.axis[0];
        //qDebug() << "quat_arcball.axis[1] " << quat_arcball.axis[1];
        //qDebug() << "quat_arcball.axis[2] " << quat_arcball.axis[2];

        last_pos_x = sx;
        last_pos_y = sy;

        return glm::toMat4(glm::angleAxis( glm::radians(quat_arcball.angle), glm::normalize(quat_arcball.axis)));
    }
}

void FGECamera::zoom(QWheelEvent *event){
    float s =event->angleDelta().y();
    //float _x = distance[0] - current_target[0];
    float _y = current_eye[1] - current_target[1];
    current_eye[1] += (s/12)*(_y/100);
    float _x = current_eye[0] - current_target[0];
    current_eye[0] += (s/12)*(_x/100);
    float _z = current_eye[2] - current_target[2];
    current_eye[2] += (s/12)*(_z/100);
    this->view->matrix = glm::lookAt(current_position+current_eye, current_position+current_target, current_up);

    //if(!struct_project->scene_current->projection->is_perspective){
        //qDebug() << "!!!!!!!!!!!is_perspective";
        this->projection->scaleFactor = SUPER_VAL_ZOOM/glm::length(current_eye);
    //}
}

void FGECamera::dragMouseMove(QMouseEvent *event, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection){
    if(key_shift){
        glm::vec3 worldCoordinates = glm::unProject(glm::vec3(event->position().x(), (HEIGHT-event->position().y()), 0.9), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));

        glm::vec3 w;
        w[0] = (worldCoordinates[0] - drag[0])*30;
        w[1] = (worldCoordinates[1] - drag[1])*30;
        w[2] = (worldCoordinates[2] - drag[2])*30;

        //current_eye -= w;
        //current_target -= w;
        current_position -= w;

        drag = worldCoordinates -w;

        //update();

        this->projection->scaleFactor = SUPER_VAL_ZOOM/glm::length(current_eye);
        this->view->matrix = glm::lookAt(current_position+current_eye, current_position+current_target, current_up);

    }else{
            count = 0;




            glm::mat4 _t = rotateCameraAroundTarjet( event->position().x(), HEIGHT-event->position().y(),  glm::vec4(0.0, 0.0,  WIDTH, HEIGHT), view, projection);
            glm::mat4 m_ = glm::translate(glm::mat4(1.0f), current_position)*_t;
            glm::vec4 t1 = glm::vec4(current_eye, 1.0)*m_;
            current_eye[0] = t1[0];
            current_eye[1] = t1[1];
            current_eye[2] = t1[2];
            glm::vec4 t2 = glm::vec4(current_up, 1.0)*m_;
            current_up[0] = t2[0];
            current_up[1] = t2[1];
            current_up[2] = t2[2];
            glm::vec4 t3 = glm::vec4(current_target, 1.0)*m_;
            current_target[0] = t3[0];
            current_target[1] = t3[1];
            current_target[2] = t3[2];

            this->projection->scaleFactor = SUPER_VAL_ZOOM/glm::length(current_eye);
            this->view->matrix = glm::lookAt(current_position+current_eye, current_position+current_target, current_up);

            //struct_project->scene_current->view->matrix = rotateCameraAroundTarjet( event->x(), HEIGHT-event->y(),  glm::vec4(0.0, 0.0,  WIDTH, HEIGHT), glm::mat4(1.0f), struct_project->scene_current->projection->matrix)*struct_project->scene_current->view->matrix;

            ////qDebug() << "camera length : " << glm::length(current_eye-current_target);
        //}

    }

}

void FGECamera::drag2DMousePress(QMouseEvent *event, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, float scaleFactor){
    glm::mat4 scale_view = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor))*view;
    glm::vec3 p0 = glm::unProject(glm::vec3(event->position().x(), HEIGHT-event->position().y(), 0.0), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 p1 = glm::unProject(glm::vec3(event->position().x(), HEIGHT-event->position().y(), 0.2), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 dir = p1-p0;
    glm::vec3 intersection;
    float dist;
    if(glm::intersectRayPlane(p0, dir, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), dist)){
        intersection = p0 + dist*dir;
    }
    drag = intersection;
    old_current_position = current_position;
}

void FGECamera::drag2DMouseMove(QMouseEvent *event, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection, float scaleFactor){
    glm::mat4 scale_view = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor))*view;
    glm::vec3 p0 = glm::unProject(glm::vec3(event->position().x(), HEIGHT-event->position().y(), 0.0), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 p1 = glm::unProject(glm::vec3(event->position().x(), HEIGHT-event->position().y(), 0.2), scale_view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
    glm::vec3 dir = p1-p0;
    glm::vec3 worldCoordinates;
    float dist;
    if(glm::intersectRayPlane(p0, dir, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), dist)){
        worldCoordinates = p0 + dist*dir;
    }

    glm::vec3 w;
    w[0] = (worldCoordinates[0] - drag[0]);
    w[1] = (worldCoordinates[1] - drag[1]);
    w[2] = (worldCoordinates[2] - drag[2]);

    w = -w;
    //drag = worldCoordinates;

    //current_position = old_current_position-w;
    current_eye[0] = w[0]+current_eye[0];
    current_eye[1] = w[1]+current_eye[1];
    current_target[0] = w[0]+current_target[0];
    current_target[1] = w[1]+current_target[1];

    //drag = worldCoordinates -w;

    //this->projection->scaleFactor = SUPER_VAL_ZOOM/glm::length(current_eye);
    this->view->matrix = glm::lookAt(current_eye, current_target, current_up);


}


void FGECamera::dragMousePress(QMouseEvent *event, int WIDTH, int HEIGHT, glm::mat4 &view, glm::mat4 &projection){
    if(key_shift){
        //float _y = current_eye[1] - current_target[1];

        glm::vec3 worldCoordinates = glm::unProject(glm::vec3(event->position().x(), HEIGHT-event->position().y(), 0.9), view, projection, glm::vec4(0.0, 0.0,  WIDTH, HEIGHT));
//float _y = distance[1] - current_target[1];

        drag = worldCoordinates;

        //qDebug() << "worldCoordinates[0] " << worldCoordinates[0];
        //qDebug() << "worldCoordinates[1] " << worldCoordinates[1];
        //qDebug() << "worldCoordinates[2] " << worldCoordinates[2];

    }else{
        last_pos_x = event->position().x();
        last_pos_y = HEIGHT-event->position().y();

    }
}

void FGECamera::setKeyShift(bool st){
    key_shift = st;
}
*/
