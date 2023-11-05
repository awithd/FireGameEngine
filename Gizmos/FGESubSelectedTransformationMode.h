#ifndef FGESUBSELECTEDTRANSFORMATIONMODE_H
#define FGESUBSELECTEDTRANSFORMATIONMODE_H


class FGESUBSelectedTransformationMode{
public:
    FGESUBSelectedTransformationMode();
    int getMode();
    void setMode(int mode);
    bool isGlobal();
    bool isLocal();
    bool isScreen();

private:
    int mode;
};

#endif // FGESUBSELECTEDTRANSFORMATIONMODE_H
