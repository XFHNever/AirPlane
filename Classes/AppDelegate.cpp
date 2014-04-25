#include "AppDelegate.h"
#include "GameScene.h"
#include "WelcomeScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    CCSize s = pDirector->getWinSize();
    pEGLView->setDesignResolutionSize(360, 640, kResolutionNoBorder);

    CCSize visibleSize = pDirector->getVisibleSize();


    CCPoint orgin = pDirector->getVisibleOrigin();

    // turn on display FPS
//    pDirector->setDisplayStats(true);
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
  //  glClearColor(1.0, 1.0, 1.0, 1.0);

    // create a scene. it's an autorelease object
  //  GameScene *pScene = GameScene::create();
    WelcomeScene *pScene = WelcomeScene::create();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
