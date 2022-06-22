/******************************************************************************
 *
 * $Id$
 *
 * Project:  WindNinja
 * Purpose:  Abstract base class for diffusion equation operations 
 * Author:   Natalie Wagenbrenner <nwagenbrenner@gmail.com>
 *
 ******************************************************************************
 *
 * THIS SOFTWARE WAS DEVELOPED AT THE ROCKY MOUNTAIN RESEARCH STATION (RMRS)
 * MISSOULA FIRE SCIENCES LABORATORY BY EMPLOYEES OF THE FEDERAL GOVERNMENT 
 * IN THE COURSE OF THEIR OFFICIAL DUTIES. PURSUANT TO TITLE 17 SECTION 105 
 * OF THE UNITED STATES CODE, THIS SOFTWARE IS NOT SUBJECT TO COPYRIGHT 
 * PROTECTION AND IS IN THE PUBLIC DOMAIN. RMRS MISSOULA FIRE SCIENCES 
 * LABORATORY ASSUMES NO RESPONSIBILITY WHATSOEVER FOR ITS USE BY OTHER 
 * PARTIES,  AND MAKES NO GUARANTEES, EXPRESSED OR IMPLIED, ABOUT ITS QUALITY, 
 * RELIABILITY, OR ANY OTHER CHARACTERISTIC.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

#ifndef DIFFUSION_EQUATION_H
#define DIFFUSION_EQUATION_H

#include "initialize.h"
#include "finiteElementMethod.h"
#include "linearAlgebra.h"
#include "poissonEquation.h"

class DiffusionEquation
{
    public:
        DiffusionEquation();
        ~DiffusionEquation();

        DiffusionEquation(DiffusionEquation const& A);
        DiffusionEquation& operator=(DiffusionEquation const& A);

        virtual void Initialize(const Mesh *mesh, WindNinjaInputs *input)=0;
        virtual void Discretize()=0;
        virtual void Solve(wn_3dVectorField &U1, wn_3dVectorField &U, boost::posix_time::time_duration dt)=0;
        virtual std::string identify()=0;
        virtual void Deallocate()=0;
        bool writePHIandRHS;
        std::string phiOutFilename;
        std::string rhsOutFilename;

    protected:
        Mesh const *mesh_; //reference to the mesh
        WindNinjaInputs *input_; //NOTE: don't use for Com since input.Com is set to NULL in equals operator
        boost::posix_time::time_duration currentDt;//current time step size in seconds (can change during simulation)
        double *PHI;
        double *xRHS, *yRHS, *zRHS;
        wn_3dScalarField heightAboveGround;
        wn_3dScalarField windSpeed;
        wn_3dVectorField windSpeedGradient;
        wn_3dVectorField U0_; //incoming wind field to diffuse

        FiniteElementMethod fem;

    private:

};

#endif	//DIFFUSION_EQUATION_H