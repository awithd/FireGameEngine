#include "FGEGLSL.h"

FGEGLSL::FGEGLSL()
{
    this->path_models = "/home/corolo/Qt/FireGameEngine/Shader/Model/";
}

QString FGEGLSL::readFile(QString filename){
    QFile file(filename);
    if(!file.exists()){
        //qDebug() << "NO existe el archivo "<<filename;
    }else{
        //qDebug() << filename<<" encontrado...";
    }
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line += stream.readLine();
            line +="\n";
        }
    }
    line += "\0";
    file.close();
    return line;
}

unsigned int FGEGLSL::initShaderString(OpenGLFunctions *f, std::string &vertexCode, std::string &fragmentCode)
{
    //qDebug()<<"initShader 0";
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    int success;
    char infoLog[512];

    unsigned int vs_s = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vs_s, 1, &vShaderCode, NULL);
    f->glCompileShader(vs_s);

    //qDebug()<<"initShader 1";
        f->glGetShaderiv(vs_s, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            f->glGetShaderInfoLog(vs_s, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
        }
        //qDebug()<<"initShader 2";

    unsigned int fs_s = f->glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    f->glShaderSource(fs_s, 1, &fShaderCode, NULL);
    f->glCompileShader(fs_s);

        f->glGetShaderiv(fs_s, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            f->glGetShaderInfoLog(fs_s, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }
        //qDebug()<<"initShader 3";

    unsigned int shader_program = f->glCreateProgram();
    f->glAttachShader(shader_program, vs_s);
    f->glAttachShader(shader_program, fs_s);
    qDebug()<<"initShader 4";

    for(int i=0; i<attriblocation.length(); i++){
        QByteArray ba = attriblocation.at(i).name.toLatin1();
        const char *c_str2 = ba.data();
        qDebug()<<c_str2;
        f->glBindAttribLocation (shader_program, attriblocation.at(i).id, c_str2);
    }

    f->glLinkProgram(shader_program);

        f->glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            f->glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }
        //qDebug()<<"initShader 5";

    f->glDeleteShader(vs_s);
    f->glDeleteShader(fs_s);
//qDebug()<<"initShader 6";
    return shader_program;
}

unsigned int FGEGLSL::initShader(OpenGLFunctions *f, const char* vertexPath, const char* fragmentPath, const char* tessControlPath, const char* tessEvalPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string tessControlCode;
    std::string tessEvalCode;

    // قم بإنشاء دالة تقوم بتحميل محتوى الملف إلى سلسلة نصية
    auto loadShaderFromFile = [](const char* filePath) -> std::string {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(filePath);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            return stream.str();
        } catch (std::ifstream::failure& e) {
            qDebug() << "ShaderPath : " << filePath;
            qDebug() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
            return "";
        }
    };

    vertexCode = loadShaderFromFile(vertexPath);
    fragmentCode = loadShaderFromFile(fragmentPath);

    if(tessControlPath != nullptr && tessEvalPath != nullptr){
        tessControlCode = loadShaderFromFile(tessControlPath);
        tessEvalCode = loadShaderFromFile(tessEvalPath);
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* tcShaderCode = tessControlCode.c_str();
    const char* teShaderCode = tessEvalCode.c_str();

    int success;
    char infoLog[512];

    unsigned int vs_s = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vs_s, 1, &vShaderCode, NULL);
    f->glCompileShader(vs_s);

    f->glGetShaderiv(vs_s, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(vs_s, 512, NULL, infoLog);
        qDebug() << "vertexPath : " << vertexPath;
        qDebug() << "t ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }

    unsigned int fs_s = f->glCreateShader(GL_FRAGMENT_SHADER);
    f->glShaderSource(fs_s, 1, &fShaderCode, NULL);
    f->glCompileShader(fs_s);

    f->glGetShaderiv(fs_s, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(fs_s, 512, NULL, infoLog);
        qDebug() << "fragmentPath : " << fragmentPath;
        qDebug() << "t ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }

    unsigned int tc_s, te_s;
    if(tessControlPath != nullptr && tessEvalPath != nullptr){
        tc_s = f->glCreateShader(GL_TESS_CONTROL_SHADER);
        f->glShaderSource(tc_s, 1, &tcShaderCode, NULL);
        f->glCompileShader(tc_s);

        f->glGetShaderiv(tc_s, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            f->glGetShaderInfoLog(tc_s, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

        te_s = f->glCreateShader(GL_TESS_EVALUATION_SHADER);
        f->glShaderSource(te_s, 1, &teShaderCode, NULL);
        f->glCompileShader(te_s);

        f->glGetShaderiv(te_s, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            f->glGetShaderInfoLog(te_s, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }
    }

    unsigned int shader_program = f->glCreateProgram();
    f->glAttachShader(shader_program, vs_s);
    f->glAttachShader(shader_program, fs_s);

    if(tessControlPath != nullptr && tessEvalPath != nullptr){
        f->glAttachShader(shader_program, tc_s);
        f->glAttachShader(shader_program, te_s);
    }

    // ... الأكواد الأخرى لربط البرنامج والخصائص ...

    f->glLinkProgram(shader_program);

    f->glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        f->glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        qDebug() << "t ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
    }

    f->glDeleteShader(vs_s);
    f->glDeleteShader(fs_s);

    if(tessControlPath != nullptr && tessEvalPath != nullptr){
        f->glDeleteShader(tc_s);
        f->glDeleteShader(te_s);
    }

    return shader_program;
    // 1. retrieve the vertex/fragment source code from filePath
    /*qDebug()<<"y vertexPath : " <<vertexPath;
qDebug()<<"y fragmentPath : " <<fragmentPath;
    std::string vertexCode;
    std::string fragmentCode;
    std::string tessControlCode; // تحتاج لإضافة هذا المتغير
    std::string tessEvalCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream tcShaderFile;
    std::ifstream teShaderFile;


    qDebug() << "GL_SHADING_LANGUAGE_VERSION :" << f->glGetString(GL_SHADING_LANGUAGE_VERSION);

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    if(tessControlPath!=NULL){
        tcShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        teShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    }

    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        if(tessControlPath!=NULL){
            tcShaderFile.open(tessControlPath);
            teShaderFile.open(tessEvalPath);
        }

        std::stringstream vShaderStream, fShaderStream, tcShaderStream, teShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        if(tessControlPath!=NULL){
            tcShaderStream << tcShaderFile.rdbuf();
            teShaderStream << teShaderFile.rdbuf();
        }

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        if(tessControlPath!=NULL){
            tcShaderFile.close();
            teShaderFile.close();
        }

        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        if(tessControlPath!=NULL){
            tessControlCode = tcShaderStream.str();
            tessEvalCode = teShaderStream.str();
        }
    }
    catch (std::ifstream::failure& e)
    {

        qDebug() << "vertexPath : " << vertexPath;
        qDebug() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
    }
    //qDebug()<<"initShader 0";
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    int success;
    char infoLog[512];

    unsigned int vs_s = f->glCreateShader(GL_VERTEX_SHADER);
    f->glShaderSource(vs_s, 1, &vShaderCode, NULL);
    f->glCompileShader(vs_s);

    //qDebug()<<"initShader 1";
    f->glGetShaderiv(vs_s, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(vs_s, 512, NULL, infoLog);

        qDebug() << "vertexPath : " << vertexPath;
        qDebug() << "t ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
    }
        //qDebug()<<"initShader 2";

    unsigned int fs_s = f->glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    f->glShaderSource(fs_s, 1, &fShaderCode, NULL);
    f->glCompileShader(fs_s);

    f->glGetShaderiv(fs_s, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        f->glGetShaderInfoLog(fs_s, 512, NULL, infoLog);
        qDebug() << "fragmentPath : " << fragmentPath;

        qDebug() << "t ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
    }

    unsigned int tc_s, te_s;
    if(tessControlPath!=NULL){
        const char * tcShaderCode = tessControlCode.c_str();
        const char * teShaderCode = tessEvalCode.c_str();

        tc_s = f->glCreateShader(GL_TESS_CONTROL_SHADER); // the first fragment shader that outputs the color orange
        f->glShaderSource(tc_s, 1, &tcShaderCode, NULL);
        f->glCompileShader(tc_s);

        f->glGetShaderiv(tc_s, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            f->glGetShaderInfoLog(tc_s, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

        te_s = f->glCreateShader(GL_TESS_EVALUATION_SHADER); // the first fragment shader that outputs the color orange
        f->glShaderSource(te_s, 1, &teShaderCode, NULL);
        f->glCompileShader(te_s);

        f->glGetShaderiv(te_s, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            f->glGetShaderInfoLog(te_s, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
        }

    }


    unsigned int shader_program = f->glCreateProgram();
    f->glAttachShader(shader_program, vs_s);
    f->glAttachShader(shader_program, fs_s);
    if(tessControlPath!=NULL){
        f->glAttachShader(shader_program, tc_s);
        f->glAttachShader(shader_program, te_s);
    }
    //qDebug()<<"initShader 4";

    for(int i=0; i<attriblocation.length(); i++){
        QByteArray ba = attriblocation.at(i).name.toLatin1();
        const char *c_str2 = ba.data();
        f->glBindAttribLocation (shader_program, attriblocation.at(i).id, c_str2);
    }

    f->glLinkProgram(shader_program);

        f->glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            f->glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
            qDebug() << "t ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog;
        }
        //qDebug()<<"initShader 5";

    f->glDeleteShader(vs_s);
    f->glDeleteShader(fs_s);
    if(tessControlPath!=NULL){
        f->glDeleteShader(tc_s);
        f->glDeleteShader(te_s);
    }
//qDebug()<<"initShader 6";
    return shader_program;*/
}

void FGEGLSL::setVec4(OpenGLFunctions *f, unsigned int sh, const std::string &name, const glm::vec4 &value) const
{
    f->glUniform4fv(f->glGetUniformLocation(sh, name.c_str()), 1, &value[0]);
}
void FGEGLSL::setVec3f(OpenGLFunctions *f, unsigned int sh, const std::string &name, float x, float y, float z) const
{
    f->glUniform3f(f->glGetUniformLocation(sh, name.c_str()), x, y, z);
}
void FGEGLSL::setVec3(OpenGLFunctions *f, unsigned int sh, const std::string &name, int x, int y, int z) const
{
    f->glUniform3i(f->glGetUniformLocation(sh, name.c_str()), x, y, z);
}
void FGEGLSL::setVec2(OpenGLFunctions *f, unsigned int sh, const std::string &name, const glm::vec2 &value) const
{
    f->glUniform2fv(f->glGetUniformLocation(sh, name.c_str()), 1, &value[0]);
}
void FGEGLSL::setMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, const glm::mat4& mat) const
{
    f->glUniformMatrix4fv(f->glGetUniformLocation(sh, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void FGEGLSL::setFloat(OpenGLFunctions *f, unsigned int sh, const std::string &name, float value) const
{
    f->glUniform1f(f->glGetUniformLocation(sh, name.c_str()), value);
}

void FGEGLSL::setInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, int value) const
{
    f->glUniform1i(f->glGetUniformLocation(sh, name.c_str()), value);
}

void FGEGLSL::setUInt(OpenGLFunctions *f, unsigned int sh, const std::string &name, uint value) const
{
    f->glUniform1ui(f->glGetUniformLocation(sh, name.c_str()), value);
}


void FGEGLSL::setListMat4(OpenGLFunctions *f, unsigned int sh, const std::string& name, std::vector<glm::mat4> &mat, unsigned int size) const
{
    f->glUniformMatrix4fv(f->glGetUniformLocation(sh, name.c_str()), size, GL_FALSE, glm::value_ptr(mat[0]));
}

