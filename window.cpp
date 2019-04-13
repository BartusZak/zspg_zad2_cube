#include "window.h"

#include <QCoreApplication>



static const char* kVertexShaderFile = "SimpleShader.vertex.glsl";
static const char* kFragmentShaderFile = "SimpleShader.fragment.glsl";

Window::Window( QWindow* parent)
    : QWindow( parent )
{
   setSurfaceType( OpenGLSurface );

   QSurfaceFormat format;
   format.setDepthBufferSize( 24 );
   format.setMajorVersion( 4);
   format.setMinorVersion( 3 );
   format.setSamples(4);
   format.setProfile( QSurfaceFormat::CoreProfile );
   setFormat(format);

    view_matrix_.SetUnitMatrix();
    projection_matrix_.SetUnitMatrix();
    perpendicular_view_matrix_.SetUnitMatrix();

    device_=nullptr;

    last_time_ = 0;

    context_ = new QOpenGLContext;
    context_->setFormat( requestedFormat() );
    context_->create();
    context_->makeCurrent( this );


}

Window::~Window(){
    delete context_;
    delete logger_;
    delete device_;
}

void Window::InitPrograms(){
    program_.Initialize(kVertexShaderFile, kFragmentShaderFile);
    glUseProgram(0);
}


void Window::SetViewMatrix(){
    glUseProgram(program_);
    program_.SetViewMatrix(view_matrix_);
    glUseProgram(0);
}

void Window::SetProjectionMatrix() {
    glUseProgram(program_);
    program_.SetProjectionMatrix(projection_matrix_);
    glUseProgram(0);
}


void Window::InitModels(){
    cube_.Initialize();
}

void Window::onMessageLogged( QOpenGLDebugMessage message ){
    qDebug() << message;
}


void Window::Initialize(){
    context_->makeCurrent( this );
    device_ = new QOpenGLPaintDevice;
    initializeOpenGLFunctions();

    logger_ = new QOpenGLDebugLogger(this);
    logger_->initialize();
    connect(logger_,  SIGNAL( messageLogged( QOpenGLDebugMessage ) ),
            this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ),
            Qt::DirectConnection );
    logger_->startLogging();

    InitPrograms();
    InitModels();
    perpendicular_view_matrix_ = Mat4::CreatePerpendicularViewMatrix(-5,5,-5,5,-100,100);
    projection_matrix_ = Mat4::CreateProjectionMatrix(60,
                                                      static_cast<float>(width())/static_cast<float>(height()),
                                                      1.0f,
                                                      100.0f);
    SetProjectionMatrix();

    view_matrix_.Translate( 0, 0, -2);
    SetViewMatrix();

    glViewport(0, 0, width(), height());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

}



void Window::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event)
    if(!device_)  Initialize();
    context_->makeCurrent( this );
    glViewport(0, 0, width(), height());
    projection_matrix_ = Mat4::CreateProjectionMatrix(60,
                                                      static_cast<float>(width())/static_cast<float>(height()),
                                                      1.0f,
                                                      100.0f);
    SetProjectionMatrix();

    if (isExposed()) render();
}

void Window::exposeEvent(QExposeEvent *event){
    Q_UNUSED(event);
    if(!device_)  Initialize();
    context_->makeCurrent( this );

    if (isExposed())
        render();
}


void Window::render(){
   if (!isExposed()) return;

   if(!device_)  Initialize();
   context_->makeCurrent( this );


   clock_t now = clock();

   if (last_time_ == 0) last_time_ = now;

//   float delta_t = static_cast<float>( now - last_time_ ) / CLOCKS_PER_SEC;

   last_time_ = now;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   cube_.Draw(program_);

   QPainter painter(device_);
   render(&painter);
   context_->swapBuffers(this);

    QCoreApplication::postEvent(this, new QEvent(QEvent::Expose));
}

void Window::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void Window::ZoomIn(){
    view_matrix_.Translate(0,0,1.0f);
     SetViewMatrix();
}

void Window::ZoomOut(){
    view_matrix_.Translate(0,0,-1.0f);
    SetViewMatrix();
}

void Window::SetPerspectiveView(){
    SetProjectionMatrix();
}

void Window::SetPerpendicularView(){
    glUseProgram(program_);
    program_.SetProjectionMatrix(perpendicular_view_matrix_);
    glUseProgram(0);
}

void Window::keyPressEvent(QKeyEvent *event){
    if(Qt::Key_Escape == event->key() ) QCoreApplication::exit();
    else if(Qt::Key_Right == event->key() ) {
        cube_.MoveRight();
    }
    else if(Qt::Key_Left == event->key() ) {
        cube_.MoveLeft();
    }
    else if(Qt::Key_Up == event->key() ) {
        cube_.MoveUp();
    }
    else if(Qt::Key_Down == event->key() ) {
        cube_.MoveDown();
    }
    else if(Qt::Key_PageUp == event->key() ) {
        ZoomIn();
    }
    else if(Qt::Key_PageDown == event->key() ) {
        ZoomOut();
    }
    else if(Qt::Key_Home == event->key() ) {
        SetPerspectiveView();
    }
    else if(Qt::Key_End == event->key() ) {
        SetPerpendicularView();
    }
}

