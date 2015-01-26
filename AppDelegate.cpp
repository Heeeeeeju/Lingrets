#include "AppDelegate.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "MainScene.h"
#include "LoadingScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
	CCLog("GameStart");
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		//실행 시 나오는 창 크기 설정
		glview = GLView::createWithRect("Lingrets", Rect(0, 0, 1280 , 720 ));
		director->setOpenGLView(glview);
	}

	//개발용 디바이스 사이즈 설정, 해상도 변경정책 설정
	glview->setDesignResolutionSize(1280, 800, ResolutionPolicy::FIXED_HEIGHT);

	// turn on display FPS
	director->setDisplayStats(false);


    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	Scene *scene;
	CCLog("SceneCreate");

	if (false)//CCUserDefault::getInstance()->getBoolForKey("PlayFirstTime", true))
	{

		scene = GameScene ::createScene();

		CCLog("CreateFinish");
		CCUserDefault::getInstance()->setIntegerForKey("stage", 0);
		CCUserDefault::getInstance()->setIntegerForKey("clearedStage", 0);
		CCUserDefault::getInstance()->setBoolForKey("PlayFirstTime", true); 
		CCUserDefault::sharedUserDefault()->setStringForKey("EquipedBadgesData","");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("EquipedBadgesSize",0);
		CCUserDefault::sharedUserDefault()->setStringForKey("BadgeData","");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("BadgesSize", 0);
		CCUserDefault::getInstance()->setIntegerForKey("AdditionalTime", 0);
		CCUserDefault::getInstance()->setFloatForKey("RetryRate", 0);
		CCLog("SettingFinish");
	}
	else
	{

		// create a scene. it's an autorelease object
		//scene = LoadingScene::createScene();
		//scene = MainScene::createScene();
		//scene = LearningGame::createScene();
		scene = MainScene::createScene();
		//scene = ResultScene::createScene();
		CCLog("CreateFinish");
	
	}


    // run
    director->runWithScene(scene);
	CCLog("run");
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
