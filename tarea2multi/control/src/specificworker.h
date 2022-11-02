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

/**
	\brief
	@author authorname
*/



#ifndef SPECIFICWORKER_H
#define SPECIFICWORKER_H

#include <genericworker.h>
#include <innermodel/innermodel.h>
#include <ctime>

class SpecificWorker : public GenericWorker {
Q_OBJECT
public:
    SpecificWorker(TuplePrx tprx, bool startup_check);
    ~SpecificWorker();

    enum class EstadoRobot{
        Avanzar,
        Rotar,
        Pared,
        Espiral,
    };

    //Iniciamos el robot en modo espiral
    EstadoRobot estado = EstadoRobot::Espiral;

    //Tupla que guarda los valores de velocidad que se asignan al robot
    std::tuple<float, float> velocidades;

    EstadoRobot getEstado();

    bool setParams(RoboCompCommonBehavior::ParameterList params);
    //void avanzar();

    /*
     * Para calcular la media y saber la distancia */
    float Media(RoboCompLaserMulti::TLaserData &copy);

    void setEstado(EstadoRobot estado);

    std::tuple<float, float> avanzar(RoboCompLaserMulti::TLaserData &ldata);
    std::tuple<float, float> seguirMuro(RoboCompLaserMulti::TLaserData &ldata);
    std::tuple<float, float> espiral(RoboCompLaserMulti::TLaserData &ldata);
public slots:

    void compute();

    int startup_check();

    void initialize(int period);

private:
    std::shared_ptr<InnerModel> innerModel;
    bool startup_check_flag;
    float rot;
    float adv = 1300;
    unsigned t0;
    int contador=0;

    //Constantes
    struct Constantes
    {
        const float MAX_VEL = 1700;
        const float ROT_TURN=0.55;
        const float MAX_ROT_SPPED = 1.2;
        const float REFERENCE_DISTANCE = 1200;
        const float DELTA = 50;
        const int part = 3;
    }; Constantes fijas;


    //sangría automática ctrl+alt+l
};

#endif
