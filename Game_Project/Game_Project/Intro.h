
#ifndef Intro_h
#define Intro_h

using namespace cv;
void drawIntro();
//==========================function list===========
void concatImg(Mat& src);   //imshow menu + src
void createMenu(Mat& menu,Rect rMenu,string title);
Mat readImage();
void onMouse(int event, int mx, int my, int flag, void* param); //menu click event
bool bInsideRect(int x, int y, Rect rect);
//==================================================
string imgTitle = "GAME INTRO";
string imgPath = "/Users/cha-ji/Downloads/blender/init.png";
Mat I,menu,result;

//===========menu button========
Rect gameTitle(20, 160, 300, 100);
Rect gameStart(20, 370, 300, 200);

Rect descriptW(20, 700, 300, 100);
Rect descriptA(20, 800, 300, 100);
Rect descriptD(20, 900, 300, 100);
Rect descriptK(20, 1000, 300, 100);
void onMouse(int event, int mx, int my, int flag, void* param) {
    switch (event) {
        case EVENT_LBUTTONDOWN:
            //게임 시작
            if (bInsideRect(mx, my, gameStart)){
                destroyWindow(imgTitle);
                initGame();
            }
            break;
    }
}

Mat readImage() {
    I = imread(imgPath);
    if (I.empty()) {
        cout << "Error opening image" << endl;
        exit(EXIT_FAILURE);
    }
    resize(I, I, Size(1500,1500));
    return I;
}

//create Menu button
void createMenu(Mat& menu,Rect rMenu,string title){
    rectangle(menu, rMenu, Scalar(255), 1);
    putText(menu, title,Point(rMenu.x+15, rMenu.y+50),FONT_HERSHEY_SIMPLEX, 1.2, Scalar(255), 2);
}

void drawIntro(){
    I = readImage();
    
    //menu image
    menu = Mat::zeros(I.rows, 400,CV_8UC3); //CV_8UC3 for concat
    
    //crate menu button
    createMenu(menu, gameTitle, "Escape Here!");
    createMenu(menu, gameStart, "Game Start!");
    
    createMenu(menu, descriptW, "w : walk");
    createMenu(menu, descriptA, "a : turn L");
    createMenu(menu, descriptD, "d : turn R");
    createMenu(menu, descriptK, "k : get key");

    
    //create menu & set mouseEvent
    namedWindow(imgTitle);
    setMouseCallback(imgTitle, onMouse, &menu);
    
    //show image
    
    concatImg(I);
    waitKey();
}
//concat Img + menu
void concatImg(Mat& src){
    hconcat(menu, src, result);
    
    namedWindow(imgTitle,WINDOW_AUTOSIZE);
    imshow(imgTitle,result);
}
bool bInsideRect(int x, int y, Rect rect) {
    return (x >= rect.x && x < rect.x+ rect.width &&
            y >= rect.y && y < rect.y + rect.height);
}
#endif /* Intro_h */
