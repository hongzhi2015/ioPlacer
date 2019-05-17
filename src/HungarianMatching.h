////////////////////////////////////////////////////////////////////////////////
// Authors: Vitor Bandeira, Mateus Fogaça, Eder Matheus Monteiro e Isadora
// Oliveira
//          (Advisor: Ricardo Reis)
//
// BSD 3-Clause License
//
// Copyright (c) 2019, Federal University of Rio Grande do Sul (UFRGS)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
////////////////////////////////////////////////////////////////////////////////

#ifndef __HUNGARIANMATCHING_H_
#define __HUNGARIANMATCHING_H_

#include "Coordinate.h"
#include "Core.h"
#include "Netlist.h"
#include "IOPlacementKernel.h"
#include "Slots.h"
#include "munkres/munkres.h"

#include <iostream>
#include <math.h>

class HungarianMatching {
       private:
        Core* _core;
        Matrix<DBU> _hungarianMatrix;
        Munkres<DBU> _hungarianSolver;
        Netlist* _netlist;
        slotVector_t* _slots;
        unsigned _numSlots;
        unsigned _numIOPins;

        void setNumSlots();

        void createMatrix();
        bool updateNeighborhood(bool);
        inline void markRemove(std::vector<unsigned>);
        inline void markExplore(std::vector<unsigned>);
        inline bool addSlot(Slot_t&);

       public:
        HungarianMatching(Netlist&, Core&, slotVector_t&);
        HungarianMatching(Section_t&, Core&);
        virtual ~HungarianMatching() = default;
        void run();
        void getFinalAssignment(std::vector<IOPin>&, slotVector_t&);
        void assignZeroSinkIOs(std::vector<IOPin>&, const slotVector_t&,
                               std::vector<IOPin>&);
};

#endif /* __HUNGARIANMATCHING_H_ */