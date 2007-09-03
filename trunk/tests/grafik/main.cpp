
#include <irrlicht.h>
#include <iostream>

using namespace irr;


int main()
{

	// create device

	IrrlichtDevice *device =
		createDevice(video::EDT_BURNINGSVIDEO, core::dimension2d<s32>(640, 480), 16, false);

	if (device == 0)
		return 1; // could not create selected driver.

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("landschaft.x");
	scene::ISceneNode* q3node = 0;

	if (q3levelmesh)
		q3node = smgr->addOctTreeSceneNode(q3levelmesh->getMesh(0));


	scene::ITriangleSelector* selector = 0;

	if (q3node)
	{
		q3node->setPosition(core::vector3df(0,0,0));

		selector = smgr->createOctTreeTriangleSelector(q3levelmesh->getMesh(0), q3node);
		q3node->setTriangleSelector(selector);
		selector->drop();
	}

	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0, 100.0f, 300.0f, -1, 0, 0, true);
	camera->setPosition(core::vector3df(0,200,0));

	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		selector, camera, core::vector3df(30,50,30),
		core::vector3df(0,-3,0),
		core::vector3df(0,50,0));
	camera->addAnimator(anim);
	anim->drop();

	//device->getCursorControl()->setVisible(false);

	smgr->addLightSceneNode(0, core::vector3df(0,4000,0),
		video::SColorf(1.0f,1.0f,1.0f,1.0f),
		1000.0f);

	int lastFPS = -1;

	while(device->run())
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, 0);

		smgr->drawAll();

		core::line3d<f32> line;
		line.start = camera->getPosition();
		line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;

		core::vector3df intersection;
		core::triangle3df tri;

		if (smgr->getSceneCollisionManager()->getCollisionPoint(
			line, selector, intersection, tri))
		{

			driver->setTransform(video::ETS_WORLD, core::matrix4());
			driver->draw3DTriangle(tri, video::SColor(0,255,0,0));
		}

		driver->endScene();

		int fps = driver->getFPS();

		if (lastFPS != fps)
		{
		  core::stringw str = L"Grafik Test - By Feuer [";
		  str += driver->getName();
		  str += "] FPS:";
		  str += fps;

		  device->setWindowCaption(str.c_str());
		  lastFPS = fps;
		}
	}

	device->drop();

	return 0;
}

