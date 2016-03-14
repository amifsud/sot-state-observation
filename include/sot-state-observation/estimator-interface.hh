//
// Copyright (c) 2015,
// Alexis Mifsud
//
// CNRS
//
// This file is part of sot-dynamic.
// sot-dynamic is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
// sot-dynamic is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.  You should
// have received a copy of the GNU Lesser General Public License along
// with sot-dynamic.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef ESTIMATORINTERFACE_HH
#define ESTIMATORINTERFACE_HH

#include <dynamic-graph/entity.h>
#include <dynamic-graph/signal-ptr.h>
#include <dynamic-graph/signal-time-dependent.h>
#include <dynamic-graph/linear-algebra.h>

//#include <sot/core/matrix-rotation.hh>
#include <sot/core/matrix-homogeneous.hh>
//#include <sot/core/multi-bound.hh>
#include <sot/core/vector-utheta.hh>
#include <sot/core/vector-roll-pitch-yaw.hh>

#include <sot/core/matrix-homogeneous.hh>
#include <state-observation/tools/miscellaneous-algorithms.hpp>
#include <sot-state-observation/tools/definitions.hh>

#include <Eigen/StdVector>
#include <algorithm>

namespace sotStateObservation
{
    using dynamicgraph::Signal;
    using dynamicgraph::SignalPtr;
    using dynamicgraph::SignalTimeDependent;
    using dynamicgraph::Vector;
    using dynamicgraph::Matrix;
    using dynamicgraph::Entity;
    using dynamicgraph::sot::MatrixHomogeneous;
    using dynamicgraph::sot::MatrixRotation;
    using dynamicgraph::sot::VectorUTheta;
    using dynamicgraph::sot::VectorRollPitchYaw;

    using namespace sotStateObservation;
    using namespace stateObservation;

    struct contact
    {
      static const unsigned nbMax=4;
      // index for the contacts
      static const unsigned lf = 0;
      static const unsigned rf = 1;
      static const unsigned lh = 2;
      static const unsigned rh = 3;
    };

        /**
           \brief
        */
        class EstimatorInterface :
            public dynamicgraph::Entity,
            private boost::noncopyable //
        {
        public:
            /**
            \brief Constructor by name
            */
            EstimatorInterface(const std::string& inName);

            ~EstimatorInterface();

            /// Each entity should provide the name of the class it belongs to
            virtual const std::string& getClassName (void) const
            {
                return CLASS_NAME;
            }

            /// Header documentation of the python class
            virtual std::string getDocString () const
            {
                return
                    "Entity that compute the input and measurment vectors for the estimator plus the number of contacts";
            }

            Vector& getInput(Vector& input, const int& time);
            Vector& getMeasurement(Vector& measurement, const int& time);
            unsigned& getContactsNbr(unsigned& contactsNbr, const int& time);

            /**
            \name Parameters
            @{
            */
        protected:
            /*
            \brief Class name
            */
            static const std::string CLASS_NAME;

        private:

            /// Signals
            // Input signals
            dynamicgraph::SignalPtr <MatrixHomogeneous, int> positionLeftFootSIN_;
            dynamicgraph::SignalPtr <Vector, int> forceLeftFootSIN_;

            dynamicgraph::SignalPtr <MatrixHomogeneous, int> positionRightFootSIN_;
            dynamicgraph::SignalPtr <Vector, int> forceRightFootSIN_;

            dynamicgraph::SignalPtr <MatrixHomogeneous, int> positionLeftHandSIN_;
            dynamicgraph::SignalPtr <Vector, int> forceLeftHandSIN_;

            dynamicgraph::SignalPtr <MatrixHomogeneous, int> positionRightHandSIN_;
            dynamicgraph::SignalPtr <Vector, int> forceRightHandSIN_;

            // Output signals
            dynamicgraph::SignalPtr <Vector, int> inputSOUT_;
            dynamicgraph::SignalPtr <Vector, int> measurementSOUT_;
            dynamicgraph::SignalPtr <unsigned, int> contactsNbrSOUT_;

            /// Methods
            void computeStackOfContacts(const int& time);

            /// Parameters
            double time_;

            stateObservation::Vector forceThresholds_;

            std::list<int> stackOfContacts_;

            std::vector<stateObservation::Matrix4,Eigen::aligned_allocator_indirection<stateObservation::Matrix4> > inputHomoPosition_;
            std::vector<stateObservation::Vector6,Eigen::aligned_allocator_indirection<stateObservation::Vector6> > inputPosition_;
            std::vector<stateObservation::Vector6,Eigen::aligned_allocator_indirection<stateObservation::Vector6> > inputForces_;


        public:
          EIGEN_MAKE_ALIGNED_OPERATOR_NEW

      };

} // namespace sotStateObservation

#endif // ESTIMATORINTERFACE_HH