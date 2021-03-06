//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADGravity.h"

registerMooseObject("TensorMechanicsApp", ADGravity);

/**
 * This kernel defines the residual contribution from a gravitational body force
 */
InputParameters
ADGravity::validParams()
{
  InputParameters params = ADKernelValue::validParams();
  params.addClassDescription("Apply gravity. Value is in units of acceleration.");
  params.addParam<bool>("use_displaced_mesh", true, "Displaced mesh defaults to true");
  params.addRequiredParam<Real>(
      "value", "Value multiplied against the residual, e.g. gravitational acceleration");
  params.addParam<Real>("alpha", 0.0, "alpha parameter required for HHT time integration scheme");
  return params;
}

ADGravity::ADGravity(const InputParameters & parameters)
  : ADKernelValue(parameters),
    _density(getADMaterialProperty<Real>("density")),
    _value(getParam<Real>("value")),
    _alpha(getParam<Real>("alpha"))
{
}

ADReal
ADGravity::precomputeQpResidual()
{
  return -_density[_qp] * _value;
}
