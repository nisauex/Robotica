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


SpecificWorker::SpecificWorker(TuplePrx tprx, bool startup_check) : GenericWorker(tprx) {
    this->startup_check_flag = startup_check;
    // Uncomment if there's too many debug messages
    // but it removes the possibility to see the messages
    // shown in the console with qDebug()
//	QLoggingCategory::setFilterRules("*.debug=false\n");


}

/**
* \brief Default destructor
*/
SpecificWorker::~SpecificWorker() {
    std::cout << "Destroying SpecificWorker" << std::endl;
}

bool SpecificWorker::setParams(RoboCompCommonBehavior::ParameterList params) {
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

void SpecificWorker::initialize(int period) {
    std::cout << "Initialize worker" << std::endl;
    this->Period = period;
    if (this->startup_check_flag) {
        this->startup_check();
    } else {
        timer.start(Period);
    }
    //std::cout << "Aquí llega" << std::endl;
}

void SpecificWorker::setEstado(EstadoRobot estado) {
    this->estado = estado;
}

SpecificWorker::EstadoRobot SpecificWorker::getEstado() {
    return estado;
}

void SpecificWorker::compute() {


    RoboCompLaserMulti::TLaserData ldata;
    try { ldata = lasermulti_proxy->getLaserData(3); }
    catch (const Ice::Exception &e) {
        std::cout << e.what() << std::endl;
        return;
    }

    switch (estado) {
        case EstadoRobot::Avanzar:
            velocidades = avanzar(ldata);
            break;
        case EstadoRobot::Pared:
            velocidades = seguirMuro(ldata);
            break;
        case EstadoRobot::Espiral:
            velocidades = espiral(ldata);
            break;
        case EstadoRobot::Rotar:
            break;
    }
    try {
        differentialrobotmulti_proxy->setSpeedBase(3, get<0>(velocidades), get<1>(velocidades));
    } catch (const Ice::Exception &e) { std::cout << e.what() << std::endl; };

}

std::tuple<float, float> SpecificWorker::espiral(RoboCompLaserMulti::TLaserData &ldata) {
    std::cout << "Espiral" << std::endl;

    //Control con reloj para que si llega al maximo de la espiral no repita el circulo todo el rato
    static std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();
    RoboCompLaserMulti::TLaserData copy(ldata.size());
    copy.assign(ldata.begin() + ldata.size() / fijas.part, ldata.end() - ldata.size() / fijas.part);
    std::ranges::sort(copy, {}, &RoboCompLaserMulti::TData::dist);

    RoboCompLaserMulti::TLaserData izquierda(ldata.begin(), ldata.begin() + ldata.size() / fijas.part);
    std::ranges::sort(izquierda, {}, &RoboCompLaserMulti::TData::dist);

    RoboCompLaserMulti::TLaserData derecha(ldata.begin() + 2 * (ldata.size() / fijas.part), ldata.end());
    std::ranges::sort(derecha, {}, &RoboCompLaserMulti::TData::dist);
    {
        if (copy.front().dist >= 400) //Controlamos que haya distancia
        {
            rot = 1.25;
            if (adv < 800)
            {
                adv += 5;
            }
            else
                estado = EstadoRobot::Avanzar;
        }
        else
        {
            estado = EstadoRobot::Avanzar;
        }
    }

    return make_tuple(adv, rot);
}

std::tuple<float, float> SpecificWorker::seguirMuro(RoboCompLaserMulti::TLaserData &ldata) {
    std::cout << "seguirMuro" << adv << std::endl;

    RoboCompLaserMulti::TLaserData centro(ldata.size());
    centro.assign(ldata.begin() + ldata.size() / fijas.part, ldata.end() - ldata.size() / fijas.part);
    std::ranges::sort(centro, {}, &RoboCompLaserMulti::TData::dist);
    std::cout << "Distancia al muro por la centro " << centro.front().dist << std::endl;

    RoboCompLaserMulti::TLaserData derecha(ldata.begin(), ldata.begin() + ldata.size() / fijas.part);
    std::ranges::sort(derecha, {}, &RoboCompLaserMulti::TData::dist);
    std::cout << "Distancia al muro por la derecha " << derecha.front().dist << std::endl;

    RoboCompLaserMulti::TLaserData izquierda(ldata.begin() + 2 * (ldata.size() / fijas.part), ldata.end());
    std::ranges::sort(izquierda, {}, &RoboCompLaserMulti::TData::dist);
    std::cout << "Distancia al muro por la izquierda " << izquierda.front().dist << std::endl;

    float mediaIzq = Media(izquierda);
    float mediaDer = Media(derecha);

    if (!(centro.front().dist < 1000)) {

        if (mediaIzq > fijas.REFERENCE_DISTANCE + fijas.DELTA) {
            adv = fijas.MAX_VEL;
            rot = 0.25;
        } else {
            if (mediaIzq < fijas.REFERENCE_DISTANCE - fijas.DELTA) {
                adv = fijas.MAX_VEL;
                rot = 0.25;
            } else {
                adv = fijas.MAX_VEL;
                rot = 0;
            }
        }
    }
    else
        estado = EstadoRobot::Avanzar;
    //if there is an imminent collision select TURN state,  adv=0, turn=+-0.5 and return tuple
    //si la distancia entre el muro y la que queremos mantener es mayor que 100
    // ret = 1.0 * (distancia al muro - distancia a seguir) / 1000
    // else ret es 0

    return make_tuple(adv, rot);

    //else do nothing  // it is parallel to the wall
    //return tuple


}

std::tuple<float, float> SpecificWorker::avanzar(RoboCompLaserMulti::TLaserData &ldata) {

    std::cout << "Avanzar " << std::endl;
    const int part = 3;
    RoboCompLaserMulti::TLaserData centro(ldata.size());
    centro.assign(ldata.begin() + ldata.size() / part, ldata.end() - ldata.size() / part);
    std::ranges::sort(centro, {}, &RoboCompLaserMulti::TData::dist);

    RoboCompLaserMulti::TLaserData derecha(ldata.begin(), ldata.begin() + ldata.size() / part);
    std::ranges::sort(derecha, {}, &RoboCompLaserMulti::TData::dist);
    std::cout << "Distancia al muro por la derecha " << derecha.front().dist <<std::endl;

    RoboCompLaserMulti::TLaserData izquierda(ldata.begin() + 2 * (ldata.size() / part), ldata.end());
    std::ranges::sort(izquierda, {}, &RoboCompLaserMulti::TData::dist);
    std::cout << "Distancia al muro por la izquierda " << izquierda.front().dist <<std::endl;

    //Calculamos la media para saber a que lado girar
    float mediaIzquierda = Media(izquierda);
    float mediaDerecha = Media(derecha);

    std::cout << "Avanzar " << adv << rot <<std::endl;
        if (centro.front().dist <= 1500) {
            if (contador < 100) //Contador para controlar si se queda atascado
            {
                contador++;
                if (mediaDerecha <= mediaIzquierda)
                    rot = -0.5;
                else
                    rot = 0.5;
            }
            else
            { //Si se atasca, hacemos una rotación mayor para que se gire totalmente
                if (mediaDerecha <= mediaIzquierda)
                    rot = -3.25;
                else
                    rot = 3.25;
                contador=0;
                sleep(5);
            }
            adv = 0;
        }
        else
        {
            if (adv < fijas.MAX_VEL)
            {
                adv += 40; //Aumentamos la velocidad hasta su máximo poco a poco
                rot = 0; //velocidad de giro
            }
    }

    std::cout << "Velocidad: " << adv << " Rotacion " << rot << std::endl;
    return make_tuple(adv, rot);
}



int SpecificWorker::startup_check() {
    std::cout << "Startup check" << std::endl;
    QTimer::singleShot(200, qApp, SLOT(quit()));
    return 0;
}

//Calculamos la media para saber que lado está mas cerca de un obstáculo
float SpecificWorker::Media(RoboCompLaserMulti::TLaserData &copy)
{
    float suma=0, media;
    for (long unsigned int i=0; i < copy.size(); i++)
    {
        suma+=copy.at(i).dist;
    }

    media=suma/copy.size();

    return media;
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

