/*
 *    Copyright (C) 2022 by YOUR NAME HERE
 *
 *    This file is part of RoboComp
 *
 *    RoboComp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    RoboComp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with RoboComp.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "specificworker.h"

/**
* \brief Default constructor
*/


SpecificWorker::SpecificWorker(TuplePrx tprx, bool startup_check) : GenericWorker(tprx)
{
	this->startup_check_flag = startup_check;
	// Uncomment if there's too many debug messages
	// but it removes the possibility to see the messages
	// shown in the console with qDebug()
//	QLoggingCategory::setFilterRules("*.debug=false\n");


}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker()
{
	std::cout << "Destroying SpecificWorker" << std::endl;
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params)
{
//	THE FOLLOWING IS JUST AN EXAMPLE
//	To use innerModelPath parameter you should uncomment specificmonitor.cpp readConfig method content
//	try
//	{
//		RoboCompCommonBehavior::Parameter par = params.at("InnerModelPath");
//		std::string innermodel_path = par.value;
//		innerModel = std::make_shared(innermodel_path);
//	}
//	catch(const std::exception &e) { qFatal("Error reading config params"); }






	return true;
}

void SpecificWorker::initialize(int period)
{
	std::cout << "Initialize worker" << std::endl;
	this->Period = period;
	if(this->startup_check_flag)
	{
		this->startup_check();
	}
	else
	{
		timer.start(Period);
	}

}

void SpecificWorker::compute()
{
    try{

        const auto ldata = laser_proxy->getLaserData();
        const int part = 3;
        RoboCompLaser::TLaserData copy;
        copy.assign(ldata.begin()+ldata.size()/part, ldata.end()-ldata.size()/part);
        std::ranges::sort(copy, {}, &RoboCompLaser::TData::dist);
        qInfo() << copy.front().dist; //Distancia del laser al muro
        if(copy.front().dist<1000)
        {
            try{
                float adv = 0; //Velocidad de avance
                float rot; //velocidad de giro

                std::cout << "----------------------------------------------------------------- " << copy.front().angle << endl;
                if(copy.front().angle < 0){
                    rot = 1;
                }else if(copy.front().angle >= 0){
                    rot = -1;
                }
                differentialrobot_proxy->setSpeedBase(adv, rot);
            }catch (const Ice::Exception &e){
                std::cout << e.what() << std::endl;
            }
        }
        else
        {
            try{
                float adv = 1000; //Velocidad de avance
                float rot = 0; //velocidad de giro
                differentialrobot_proxy->setSpeedBase(adv, rot);

            }catch (const Ice::Exception &e){
                std::cout << e.what() << std::endl;
            }
        }


        /*auto ldata = laser_proxy->getLaserData();
          for(const auto &l : ldata){
            qInfo() << l.angle << l.dist;
            qInfo() << "---------------";
        }*/
    }catch (const Ice::Exception &e){
        std::cout << e.what() << std::endl;
    }

    //el robot piensa



    //el robot hace
    /*try{
        float adv = 300;
        float rot = 0.5;
        differentialrobot_proxy->setSpeedBase(adv, rot);
    }catch (const Ice::Exception &e){
        std::cout << e.what() << std::endl;
    }*/

	//computeCODE
	//QMutexLocker locker(mutex);
	//try
	//{
	//  camera_proxy->getYImage(0,img, cState, bState);
	//  memcpy(image_gray.data, &img[0], m_width*m_height*sizeof(uchar));
	//  searchTags(image_gray);
	//}
	//catch(const Ice::Exception &e)
	//{
	//  std::cout << "Error reading from Camera" << e << std::endl;
	//}
	
	qInfo() << "hola";
}

int SpecificWorker::startup_check()
{
	std::cout << "Startup check" << std::endl;
	QTimer::singleShot(200, qApp, SLOT(quit()));
	return 0;
}




/**************************************/
// From the RoboCompDifferentialRobot you can call this methods:
// this->differentialrobot_proxy->correctOdometer(...)
// this->differentialrobot_proxy->getBasePose(...)
// this->differentialrobot_proxy->getBaseState(...)
// this->differentialrobot_proxy->resetOdometer(...)
// this->differentialrobot_proxy->setOdometer(...)
// this->differentialrobot_proxy->setOdometerPose(...)
// this->differentialrobot_proxy->setSpeedBase(...)
// this->differentialrobot_proxy->stopBase(...)

/**************************************/
// From the RoboCompDifferentialRobot you can use this types:
// RoboCompDifferentialRobot::TMechParams

/**************************************/
// From the RoboCompLaser you can call this methods:
// this->laser_proxy->getLaserAndBStateData(...)
// this->laser_proxy->getLaserConfData(...)
// this->laser_proxy->getLaserData(...)

/**************************************/
// From the RoboCompLaser you can use this types:
// RoboCompLaser::LaserConfData
// RoboCompLaser::TData

